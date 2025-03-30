#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Calculadora{
    int bateria;
    int maxBateria;
    float display;

    Calculadora(int b = 0, int m = 0, int d = 0):
    bateria(b), maxBateria(m), display(d){}

    string toString(){
        ostringstream oss;
        oss<<fixed<<setprecision(2);
        oss<<"display = "<<display<<", battery = "<<bateria;
        return oss.str();
    }
    
    void iniciar(int x){
        maxBateria = x;
        bateria = 0;
    }

    void charge(int x){
        bateria += x;

        bateria = min(bateria, maxBateria);
    }

    void soma(int x, int y){

        if(bateria == 0){
            cout<<"fail: bateria insuficiente\n";
            return;
        }
        display = x+y;
        bateria --;
    }

    void divid(float x, float y){
        if(y==0){
            cout<<"fail: divisao por zero\n";
            bateria--;
            return;
        }

        if(bateria == 0){
            cout<<"fail: bateria insuficiente\n";
            return;
        }

        display = x/y;
        bateria--;
    }
};

struct Student{
    Calculadora calculadora;

    Student(int bateria=0, int display=0, int maxBateria=0)
    {
        calculadora = Calculadora(bateria, maxBateria, display);
    }

    void init(int x){
        calculadora.iniciar(x);
    }

    void show(){
        cout<<calculadora.toString()<<"\n";
    }

    void charge(int x){
        calculadora.charge(x);
    }

    void sum(int x, int y){
        calculadora.soma(x,y);
    }

    void div(float x, float y){
        calculadora.divid(x,y);
    }

};