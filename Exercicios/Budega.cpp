#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
using namespace std;

class Person{
    public:
    string name;
    Person(const string &n) : name(n) {}
};

class Market{
    public: 
    vector<Person*> counters;
    list<Person*> waiting;

    void clearAll(){
        for(auto &p : counters){
            if(p) delete p;
        }

        counters.clear();

        for(auto p : waiting)delete p;
        waiting.clear();
    }

    void init(int numCounters){
        for(auto &p : counters){
            if(p) delete p;
        }

        counters = vector<Person*>(numCounters, nullptr);
        for(auto p: waiting)delete p;

        waiting.clear();
    }

    void enter(const string &name){
        Person *p = new Person(name);
        waiting.push_back(p);
    }

    void call(int counterIndex) {
        if(counterIndex < 0 || counterIndex >= (int)counters.size()){
            cout << "Erro: Caixa " << counterIndex << " inválido." << endl;
            return;
        }
        if(counters[counterIndex] != nullptr){
            cout << "fail: caixa ocupado\n";
            return;
        }
        if(waiting.empty()){
            cout << "fail: sem clientes\n";
            return;
        }
        Person *p = waiting.front();
        waiting.pop_front();
        counters[counterIndex] = p;
    }

    void show() {
        cout << "Caixas: [";
        for (int i = 0; i < (int)counters.size(); i++){
            if(counters[i])
                cout << counters[i]->name;
            else
                cout << "-----";
            if(i != (int)counters.size()-1)
                cout << ", ";
        }
        cout << "]" << endl;
        
        cout << "Espera: [";
        if(!waiting.empty()){
            auto it = waiting.begin();
            while(it != waiting.end()){
                cout << (*it)->name;
                it++;
                if(it != waiting.end())
                    cout << ", ";
            }
        }
        cout << "]" << endl;
    } 


    void finish(int counterIndex) {
        if (counterIndex < 0 || counterIndex >= (int)counters.size()) {
            cout<<"fail: caixa inexistente\n";
            return;
        }
        if (counters[counterIndex] == nullptr) {
            cout<<"fail: caixa vazio\n";
            return;
        }
        delete counters[counterIndex];
        counters[counterIndex] = nullptr;
    }
};
