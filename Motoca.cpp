#include <bits/stdc++.h>
using namespace std;

struct Pessoa{
    private:
    int age=0;
    string name="";


    public:
    //construtor
    Pessoa(int age=0, string name=""):age(age), name(name){}

    //getter
    int getAge(){return age;}
    string getName(){return name;}


    //set
    void setAge(int a) {age=a;}
    void setName(string n) {name=n;}

    string toString(){
        ostringstream oss;

        oss<<name<<':'<<age;
        return oss.str();
    }
};

struct Motoca{
    private:
    Pessoa pessoa;
    int potencia=1;
    int time=0;

    //construtor
    public:
    Motoca(int potencia=1, int time=0): potencia(potencia), time(time){}

    
    bool inserir(Pessoa p){
        if(pessoa.getName().empty()){
            pessoa = p;
            return true;
        }
        else{
            cout<<"fail: busy motorcycle\n";
            return false;
        }
    }

    Pessoa remover(){
        if(pessoa.getName()==""){
            cout<<"fail: empty motorcycle\n---\n";
            return Pessoa();
        }

        else{
            cout<<pessoa.toString()<<"\n";
            pessoa = Pessoa();
            return pessoa;
        }
    }

    void comprar(int n){
        time +=n;
    }


    void dirigir(int x){
        if(time==0){
            cout<<"fail: buy time first\n";
        }

        else if(pessoa.getName()==""){
            cout << "fail: empty motorcycle\n";
        }

        else if(pessoa.getAge()>10){
            cout << "fail: too old to drive\n";
        }

        else if(time < x){
            cout << "fail: time finished after "<< x -time  << " minutes\n";
            time =0;
        }

        else{
            time -= x;
        }
    }

    void buzinar(){
        cout<<'P';
        for(int i=0; i<potencia; i++){
            cout<<'e';
        }
        cout<<"m\n";
    }

    Pessoa getPerson(){
        return pessoa;
    }

    int getPower(){
        return potencia;
    }

    int getTime(){
        return time;
    }

    string str(){
        ostringstream oss;

        if(pessoa.getName()==""){
            oss<<"power:"<<potencia<<", time:"<<time<<", person:(empty)\n";
        }

        else{
            oss<<"power:"<<potencia<<", time:"<<time<<", person:("<<pessoa.toString()<<")\n";
        }
        return oss.str();
    }
};

class Student{
    Motoca motoca;

    public:

    Student() : motoca(){};


    void init(int potencia=1){
        motoca = Motoca(potencia);
    }

    void enter(string name, int age){
        Pessoa pessoa(age,name);
        motoca.inserir(pessoa);
    }

    void leave(){
        motoca.remover();
    }

    void honk(){
        motoca.buzinar();
    }

    void buy(int t){
        motoca.comprar(t);
    }

    void drive(int t){
        motoca.dirigir(t);
    }

    void show(){
        cout<<motoca.str();
    }

};