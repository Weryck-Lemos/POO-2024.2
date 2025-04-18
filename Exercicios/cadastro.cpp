#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iomanip>
using namespace std;

class Account {
protected:
    int id;
    string clientName;
    double balance;
public:
    Account(int id, string clientName, double initial) : id(id), clientName(clientName), balance(initial) {}
    virtual void deposit(double v) { balance += v; }
    virtual bool withdraw(double v) = 0;
    virtual void update() = 0;
    int getId() const { return id; }
    string getClientName() const { return clientName; }
    double getBalance() const { return balance; }
    virtual string type() const = 0;
    virtual string toString() const {
        stringstream ss;
        ss << id << ":" << clientName << ":" << fixed << setprecision(2) << balance << ":" << type();
        return ss.str();
    }
    virtual ~Account() {}
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int id, string clientName, double initial) : Account(id, clientName, initial) {}
    bool withdraw(double v) override { balance -= v; return true; }
    void update() override { balance -= 20.0; }
    string type() const override { return "CC"; }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int id, string clientName, double initial) : Account(id, clientName, initial) {}
    bool withdraw(double v) override {
        if(v > balance) return false;
        balance -= v;
        return true;
    }
    void update() override { balance *= 1.01; }
    string type() const override { return "CP"; }
};

class Client {
    string name;
    vector<int> accountIds;
public:
    Client(string name): name(name) {}
    string getName() const { return name; }
    void addAccount(int accId) { accountIds.push_back(accId); }
    string toString() const {
        stringstream ss;
        ss << name << " [";
        for(size_t i = 0; i < accountIds.size(); i++){
            ss << accountIds[i];
            if(i != accountIds.size()-1)
                ss << ", ";
        }
        ss << "]";
        return ss.str();
    }
};

class Agency {
    map<string, shared_ptr<Client>> clients;
    map<int, shared_ptr<Account>> accounts;
    int nextAccountId = 0;
public:
    bool addClient(const string &name) {
        if(clients.count(name)) return false;
        auto cli = make_shared<Client>(name);
        clients[name] = cli;
        auto ca = make_shared<CheckingAccount>(nextAccountId, name, 0.0);
        nextAccountId++;
        auto sa = make_shared<SavingsAccount>(nextAccountId, name, 0.0);
        nextAccountId++;
        accounts[ca->getId()] = ca;
        accounts[sa->getId()] = sa;
        cli->addAccount(ca->getId());
        cli->addAccount(sa->getId());
        return true;
    }
    bool deposit(int accountId, double v) {
        if(accounts.count(accountId) == 0) return false;
        accounts[accountId]->deposit(v);
        return true;
    }
    bool withdraw(int accountId, double v) {
        if(accounts.count(accountId) == 0) return false;
        return accounts[accountId]->withdraw(v);
    }
    bool transf(int fromId, int toId, double v) {
        if(accounts.count(fromId) == 0 || accounts.count(toId) == 0) return false;
        if(!accounts[fromId]->withdraw(v)) return false;
        accounts[toId]->deposit(v);
        return true;
    }
    void update() {
        for(auto &p : accounts)
            p.second->update();
    }
    string show() const {
        stringstream ss;
        ss << "- Clients" << "\n";
        for(auto &p : clients)
            ss << p.second->toString() << "\n";
        ss << "- Accounts" << "\n";
        for(auto &a : accounts)
            ss << a.second->toString() << "\n";
        return ss.str();
    }
};

int main(){
    Agency agency;
    string line, cmd;
    while(getline(cin, line)){
        cout << "$" << line << "\n";
        istringstream iss(line);
        iss >> cmd;
        if(cmd == "end") break;
        else if(cmd == "show")
            cout << agency.show();
        else if(cmd == "addCli") {
            string clientId;
            iss >> clientId;
            if(!agency.addClient(clientId))
                cout << "fail: client already exists" << "\n";
        }
        else if(cmd == "saque") {
            int accountId; double value;
            iss >> accountId >> value;
            if(!agency.withdraw(accountId, value))
                cout << "fail: saldo insuficiente" << "\n";
        }
        else if(cmd == "deposito") {
            int accountId; double value;
            iss >> accountId >> value;
            if(!agency.deposit(accountId, value))
                cout << "fail: conta nao encontrada" << "\n";
        }
        else if(cmd == "transf") {
            int fromId, toId; double value;
            iss >> fromId >> toId >> value;
            if(!agency.transf(fromId, toId, value))
                cout << "fail: conta nao encontrada" << "\n";
        }
        else if(cmd == "update")
            agency.update();
        else
            cout << "fail: comando invalido" << "\n";
    }
    return 0;
}
