#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

enum class CoinType { M10, M25, M50 };

class Valuable {
public:
    virtual double getValue() const = 0;
    virtual int getVolume() const = 0;
    virtual string toString() const = 0;
    virtual ~Valuable(){}
};

class Coin : public Valuable {
    CoinType type;
public:
    Coin(CoinType t): type(t) {}
    double getValue() const override {
        if(type == CoinType::M10) return 0.10;
        if(type == CoinType::M25) return 0.25;
        if(type == CoinType::M50) return 0.50;
        return 0;
    }
    int getVolume() const override {
        if(type == CoinType::M10) return 1;
        if(type == CoinType::M25) return 2;
        if(type == CoinType::M50) return 3;
        return 0;
    }
    string toString() const override {
        stringstream ss;
        if(type == CoinType::M10)
            ss << "M10";
        else if(type == CoinType::M25)
            ss << "M25";
        else if(type == CoinType::M50)
            ss << "M50";
        ss << ":" << fixed << setprecision(2) << getValue() << ":" << getVolume();
        return ss.str();
    }
};

class Item : public Valuable {
    string label;
    double value;
    int volume;
public:
    Item(string l, double v, int vol): label(l), value(v), volume(vol) {}
    double getValue() const override { return value; }
    int getVolume() const override { return volume; }
    string toString() const override {
        stringstream ss;
        ss << label << ":" << fixed << setprecision(2) << value << ":" << volume;
        return ss.str();
    }
};

class PiggyBank {
    int maxVolume;
    int currentVolume;
    bool broken;
    vector<Valuable*> valuables;
public:
    PiggyBank(int vol): maxVolume(vol), currentVolume(0), broken(false) {}
    ~PiggyBank() {
        for(auto v: valuables)
            delete v;
    }
    bool insert(Valuable* v) {
        if(broken) {
            cout << "fail: the pig is broken" << "\n";
            delete v;
            return false;
        }
        if(currentVolume + v->getVolume() > maxVolume) {
            cout << "fail: the pig is full" << "\n";
            delete v;
            return false;
        }
        valuables.push_back(v);
        currentVolume += v->getVolume();
        return true;
    }
    vector<Valuable*> extractCoins() {
        vector<Valuable*> coins;
        if(!broken) {
            cout << "fail: you must break the pig first" << "\n";
            return coins;
        }
        vector<Valuable*> remaining;
        for(auto v: valuables) {
            if(dynamic_cast<Coin*>(v))
                coins.push_back(v);
            else
                remaining.push_back(v);
        }
        valuables = remaining;
        return coins;
    }
    vector<Valuable*> extractItems() {
        vector<Valuable*> items;
        if(!broken) {
            cout << "fail: you must break the pig first" << "\n";
            return items;
        }
        vector<Valuable*> remaining;
        for(auto v: valuables) {
            if(dynamic_cast<Item*>(v))
                items.push_back(v);
            else
                remaining.push_back(v);
        }
        valuables = remaining;
        return items;
    }
    double getValue() const {
        double sum = 0;
        for(auto v: valuables)
            sum += v->getValue();
        return sum;
    }
    int getVolume() const {
        return broken ? 0 : currentVolume;
    }
    string show() const {
        stringstream ss;
        ss << "[";
        for (size_t i = 0; i < valuables.size(); i++) {
            ss << valuables[i]->toString();
            if(i != valuables.size()-1)
                ss << ", ";
        }
        ss << "] : ";
        ss << fixed << setprecision(2) << getValue() << "$ : ";
        ss << getVolume() << "/" << maxVolume << " : ";
        ss << (broken ? "broken" : "intact");
        return ss.str();
    }
    void breakPig() {
        if(broken) return;
        broken = true;
        currentVolume = 0;
    }
};

int main(){
    PiggyBank* pig = nullptr;
    string line, cmd;
    while(getline(cin, line)){
        cout << "$" << line << "\n";
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end") break;
        else if(cmd == "init"){
            int vol;
            ss >> vol;
            if(pig) { delete pig; pig = nullptr; }
            pig = new PiggyBank(vol);
        }
        else if(cmd == "addCoin"){
            int coinVal;
            ss >> coinVal;
            if(pig) {
                if(coinVal != 10 && coinVal != 25 && coinVal != 50) {
                    cout << "fail: invalid coin" << "\n";
                    continue;
                }
                CoinType type;
                if(coinVal == 10)
                    type = CoinType::M10;
                else if(coinVal == 25)
                    type = CoinType::M25;
                else
                    type = CoinType::M50;
                pig->insert(new Coin(type));
            }
        }
        else if(cmd == "addItem"){
            string label;
            double value;
            int vol;
            ss >> label >> value >> vol;
            if(pig) pig->insert(new Item(label, value, vol));
        }
        else if(cmd == "break"){
            if(pig) pig->breakPig();
        }
        else if(cmd == "extractCoins"){
            if(pig){
                vector<Valuable*> coins = pig->extractCoins();
                if(!coins.empty()){
                    cout << "[";
                    for(size_t i = 0; i < coins.size(); i++){
                        cout << coins[i]->toString();
                        if(i != coins.size()-1)
                            cout << ", ";
                    }
                    cout << "]\n";
                    for(auto c : coins)
                        delete c;
                }
            }
        }
        else if(cmd == "extractItems"){
            if(pig){
                vector<Valuable*> items = pig->extractItems();
                if(!items.empty()){
                    cout << "[";
                    for(size_t i = 0; i < items.size(); i++){
                        cout << items[i]->toString();
                        if(i != items.size()-1)
                            cout << ", ";
                    }
                    cout << "]\n";
                    for(auto i : items)
                        delete i;
                }
            }
        }
        else if(cmd == "show"){
            if(pig) cout << pig->show() << "\n";
        }
        else cout << "fail: invalid command" << "\n";
    }
    delete pig;
    return 0;
}
