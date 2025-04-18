#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class Client {
    string id;
    int phone;
public:
    Client(string id, int phone): id(id), phone(phone) {}
    string getId() const { return id; }
    int getPhone() const { return phone; }
    string toString() const { return id + ":" + to_string(phone); }
};

class Theater {
    vector<Client*> seats;
    int search(const string &name) {
        for (int i = 0; i < seats.size(); i++) {
            if (seats[i] != nullptr && seats[i]->getId() == name)
                return i;
        }
        return -1;
    }
    bool verifyIndex(int index) {
        return index >= 0 && index < seats.size();
    }
public:
    Theater(int qtd) { seats.resize(qtd, nullptr); }
    ~Theater() {
        for (auto c : seats)
            delete c;
    }
    void reserve(string id, int phone, int index) {
        if (!verifyIndex(index)) {
            cout << "fail: cadeira nao existe" << endl;
            return;
        }
        if (seats[index] != nullptr) {
            cout << "fail: cadeira ja esta ocupada" << endl;
            return;
        }
        if (search(id) != -1) {
            cout << "fail: cliente ja esta no cinema" << endl;
            return;
        }
        seats[index] = new Client(id, phone);
    }
    void cancel(string id) {
        int pos = search(id);
        if (pos == -1) {
            cout << "fail: cliente nao esta no cinema" << endl;
            return;
        }
        delete seats[pos];
        seats[pos] = nullptr;
    }
    string toString() {
        stringstream ss;
        ss << "[";
        for (int i = 0; i < seats.size(); i++) {
            if (seats[i] == nullptr)
                ss << "-";
            else
                ss << seats[i]->toString();
            if (i < seats.size() - 1)
                ss << " ";
        }
        ss << "]";
        return ss.str();
    }
};

int main() {
    Theater* theater = nullptr;
    string line, cmd;
    while(getline(cin, line)) {
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "end")
            break;
        else if (cmd == "init") {
            int qtd;
            ss >> qtd;
            if(theater) { delete theater; theater = nullptr; }
            theater = new Theater(qtd);
        }
        else if (cmd == "reserve") {
            string id;
            int phone, index;
            ss >> id >> phone >> index;
            if(theater)
                theater->reserve(id, phone, index);
        }
        else if (cmd == "cancel") {
            string id;
            ss >> id;
            if(theater)
                theater->cancel(id);
        }
        else if (cmd == "show") {
            if(theater)
                cout << theater->toString() << endl;
        }
        else
            cout << "fail: comando invalido" << endl;
    }
    delete theater;
    return 0;
}
