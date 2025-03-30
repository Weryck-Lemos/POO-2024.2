#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

struct Operation{
    string desc;
    int op;
    int balance;

    Operation(string d, int o, int b): desc(d),op(o), balance(b){}
};

struct Account{
    int number;
    int balance;
    vector<Operation> ops;

    public:
    Account(int n) : number(n), balance(0){
        ops.push_back(Operation("opening", 0,0));
    }

    bool verif(int value){
        if(value<=0){
            cout<<"fail: invalid value\n";
            return true;
        }

        return false;
    }

    void init(int num){
        number = num;
        balance = 0;
        ops.clear();
        ops.push_back(Operation("opening", 0, 0));
        deposit(num);

    }

    bool deposit(int value){
        if(verif(value))return false;

        balance += value;
        ops.push_back(Operation("deposit", value, balance));
        return true;
    }

    bool withdraw(int value){
        if(verif(value))return false;

        if(value > balance){
            cout<<"fail: insufficient balance\n";
            return false;
        }

        balance -= value;
        ops.push_back(Operation("withdraw", -value, balance));
        return true;
    }

    bool fee(int value){
        if(verif(value))return false;

        balance -= value;
        ops.push_back(Operation("fee", -value, balance));
        return true;
    }

    string extract(int n=0){
        stringstream ss;
        int start =0;

        if(n >0 && n< int(ops.size())) start = int(ops.size()) - n;

        for(int i= start; i< int(ops.size()); i++){
            ss<<setw(2)<<i<<": " 
            <<setw(8)<<right<< ops[i].desc<<":"
            <<setw(5)<< ops[i].op<<":"
            <<setw(5)<< ops[i].balance<<"\n";
        }

        return ss.str();
    }

    string show() {
        stringstream ss;
        ss << "account:" << number << " balance:" << balance;
        return ss.str();
    }

    void reverse(const vector<int>& indices) {
        for (int idx : indices) {
            if(idx < 0 || idx >= (int)ops.size()) {
                cout << "fail: index " << idx << " invalid" << "\n";
                continue;
            }
            if(ops[idx].desc != "fee") {
                cout << "fail: index " << idx << " is not a fee" << "\n";
                continue;
            }
            int amt = -ops[idx].op;
            balance += amt;
            ops.push_back(Operation("reverse", amt, balance));
        }
    }
};

int main() {
    Account* account = nullptr;
    string line, cmd;
    while(getline(cin, line)) {
        cout << "$" << line << "\n";
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end") break;
        else if(cmd == "init") {
            int num;
            ss >> num;
            if(account) account->init(num);
            else account = new Account(num);
        }
        else if(cmd == "show") {
            if(account) cout << account->show() << "\n";
        }
        else if(cmd == "deposit") {
            int value;
            ss >> value;
            if(account) account->deposit(value);
        }
        else if(cmd == "withdraw") {
            int value;
            ss >> value;
            if(account) account->withdraw(value);
        }
        else if(cmd == "fee") {
            int value;
            ss >> value;
            if(account) account->fee(value);
        }
        else if(cmd == "extract"){
            int n;
            ss>>n;
            if(account) cout << account->extract(n);
        }
        else if(cmd == "reverse") {
            vector<int> indices;
            int idx;
            while(ss >> idx)
                indices.push_back(idx);
            if(account) account->reverse(indices);
        }
        else cout << "fail: invalid command" << "\n";
    }
    delete account;
    return 0;
}