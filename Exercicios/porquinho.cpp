#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <iomanip>
#include <string>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& c, FN f, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it)
        ss << (it == c.begin() ? "" : sep) << f(*it);
    return prefix + ss.str() + suffix;
}

class Valuable {
public:
    virtual double getValue() const = 0;
    virtual int getVolume() const = 0;
    virtual string toString() const = 0;
    virtual ~Valuable(){}
};

enum class CoinType { M10, M25, M50 };

class Coin : public Valuable {
    CoinType type;
public:
    Coin(CoinType t): type(t) {}
    double getValue() const override {
        if(type == CoinType::M10) return 0.10;
        else if(type == CoinType::M25) return 0.25;
        else return 0.50;
    }
    int getVolume() const override {
        if(type == CoinType::M10) return 1;
        else if(type == CoinType::M25) return 2;
        else return 3;
    }
    string toString() const override {
        stringstream ss;
        ss << fixed << setprecision(2) << getValue() << ":" << getVolume();
        return ss.str();
    }
};

class Item : public Valuable {
    string label;
    double value;
    int volume;
public:
    Item(string l, int vol): label(l), value(0.0), volume(vol) {}
    double getValue() const override { return value; }
    int getVolume() const override { return volume; }
    string toString() const override {
        stringstream ss;
        ss << label << ":" << fixed << setprecision(2) << value << ":" << volume;
        return ss.str();
    }
    string toStringIntact() const {
        return label + ":" + to_string(volume);
    }
};

class PiggyBank {
    int maxVolume;
    int currentVolume;
    bool broken;
    vector<shared_ptr<Valuable>> valuables;
public:
    PiggyBank(int vol): maxVolume(vol), currentVolume(0), broken(false) {}
    bool insert(shared_ptr<Valuable> v) {
        if(broken) { cout << "fail: the pig is broken" << "\n"; return false; }
        if(currentVolume + v->getVolume() > maxVolume) { cout << "fail: the pig is full" << "\n"; return false; }
        valuables.push_back(v);
        currentVolume += v->getVolume();
        return true;
    }
    vector<shared_ptr<Valuable>> extractCoins() {
        vector<shared_ptr<Valuable>> coins;
        if(!broken) { cout << "fail: you must break the pig first" << "\n"; return coins; }
        vector<shared_ptr<Valuable>> remaining;
        for(auto v : valuables) {
            if(dynamic_pointer_cast<Coin>(v))
                coins.push_back(v);
            else
                remaining.push_back(v);
        }
        valuables = remaining;
        return coins;
    }
    vector<shared_ptr<Valuable>> extractItems() {
        vector<shared_ptr<Valuable>> items;
        if(!broken) { cout << "fail: you must break the pig first" << "\n"; return items; }
        vector<shared_ptr<Valuable>> remaining;
        for(auto v : valuables) {
            if(dynamic_pointer_cast<Item>(v))
                items.push_back(v);
            else
                remaining.push_back(v);
        }
        valuables = remaining;
        return items;
    }
    double getValue() const {
        double sum = 0;
        if(broken) {
            for(auto v : valuables)
                sum += v->getValue();
        } else {
            for(auto v : valuables)
                if(dynamic_pointer_cast<Coin>(v))
                    sum += v->getValue();
        }
        return sum;
    }
    int getVolume() const { return (broken ? 0 : currentVolume); }
    string show() const {
        stringstream ss;
        if(!broken) {
            vector<string> coinList;
            vector<string> itemList;
            for(auto v : valuables) {
                if(auto coinPtr = dynamic_pointer_cast<Coin>(v))
                    coinList.push_back(coinPtr->toString());
                else if(auto itemPtr = dynamic_pointer_cast<Item>(v))
                    itemList.push_back(itemPtr->toStringIntact());
            }
            ss << "state=intact : coins=" << map_join(coinList, [](const string &s){ return s; }, ", ", "[", "]")
               << " : items=" << map_join(itemList, [](const string &s){ return s; }, ", ", "[", "]")
               << " : value=" << fixed << setprecision(2) << getValue()
               << " : volume=" << getVolume() << "/" << maxVolume;
        } else {
            vector<string> coinList;
            vector<string> itemList;
            for(auto v : valuables) {
                if(auto coinPtr = dynamic_pointer_cast<Coin>(v))
                    coinList.push_back(coinPtr->toString());
                else if(auto itemPtr = dynamic_pointer_cast<Item>(v))
                    itemList.push_back(itemPtr->toStringIntact());
            }
            ss << "state=broken : coins=" << map_join(coinList, [](const string &s){ return s; }, ", ", "[", "]")
               << " : items=" << map_join(itemList, [](const string &s){ return s; }, ", ", "[", "]")
               << " : value=" << fixed << setprecision(2) << getValue()
               << " : volume=" << getVolume() << "/" << maxVolume;
        }
        return ss.str();
    }
    void breakPig() { if(broken) return; broken = true; currentVolume = 0; }
};

int main(){
    shared_ptr<PiggyBank> pig = nullptr;
    string line, cmd;
    while(getline(cin, line)){
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end") break;
        else if(cmd == "init"){
            int volumeMax; ss >> volumeMax;
            pig = make_shared<PiggyBank>(volumeMax);
        }
        else if(cmd == "show"){
            if(pig) cout << pig->show() << endl;
        }
        else if(cmd == "addCoin"){
            int coinVal; ss >> coinVal;
            if(!pig) continue;
            if(coinVal != 10 && coinVal != 25 && coinVal != 50) { cout << "fail: invalid coin" << endl; continue; }
            CoinType type;
            if(coinVal == 10) type = CoinType::M10;
            else if(coinVal == 25) type = CoinType::M25;
            else type = CoinType::M50;
            pig->insert(make_shared<Coin>(type));
        }
        else if(cmd == "addItem"){
            string label; int vol; ss >> label >> vol;
            if(pig) pig->insert(make_shared<Item>(label, vol));
        }
        else if(cmd == "break"){
            if(pig) pig->breakPig();
        }
        else if(cmd == "extractItems"){
            if(pig){
                vector<shared_ptr<Valuable>> items = pig->extractItems();
                if(items.empty()) cout << "[]" << endl;
                else cout << map_join(items, [](shared_ptr<Valuable> v) {
                    auto itemPtr = dynamic_pointer_cast<Item>(v);
                    return itemPtr ? itemPtr->toStringIntact() : v->toString();
                }, ", ", "[", "]") << endl;
            }
        }
        else if(cmd == "extractCoins"){
            if(pig){
                vector<shared_ptr<Valuable>> coins = pig->extractCoins();
                if(coins.empty()) cout << "[]" << endl;
                else cout << map_join(coins, [](shared_ptr<Valuable> v) { return v->toString(); }, ", ", "[", "]") << endl;
            }
        }
        else cout << "fail: invalid command" << endl;
    }
    return 0;
}
