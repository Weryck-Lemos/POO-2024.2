#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Relogio{
    int hora;
    int minuto;
    int segundo;

    public:

        Relogio() : hora(0), minuto(0), segundo(0){}


        // getter
        int getHora() {return hora;}
        int getMinuto() {return minuto;}
        int getSegundo() {return segundo;}


        //setter
        void setHora(int h){
            if(h>=0 && h<=23){
                hora = h;
                return;
            } 
            cout<<"fail: hora invalida\n";
        }

        void setMinuto(int m){
            if(m>=0 && m<=59){
                minuto = m;
                return;
            }
            cout<<"fail: minuto invalido\n";
        }

        void setSegundo(int s){
            if(s>=0 && s<=59){
                segundo = s;
                return;
            }
            cout<<"fail: segundo invalido\n"; 
        }


        //retornar tempo
        string toString(){
            ostringstream oss;

            oss << setw(2) << setfill('0') << hora << ':';
            oss << setw(2) << setfill('0') << minuto<< ':';
            oss << setw(2) << setfill('0')<< segundo;

            return oss.str();
        }


        //incrementa 1 segudno
        void next(){
            segundo ++;

            if(segundo> 59){
                segundo=0;
                minuto++;
            }

            if(minuto >59){
                minuto = 0;
                hora++;
            }

            if(hora>23){
                hora=0;
            }
        }
};

struct Student{

private:
    Relogio relogio;


public:
    void init(int h = 0,int m=0,int s=0){
        relogio.hora = 0;
        relogio.minuto = 0;
        relogio.segundo = 0;
        relogio.setHora(h);
        relogio.setMinuto(m);
        relogio.setSegundo(s);

    }

    void setHour(int h){
        relogio.setHora(h);
    }

    void setMinute(int m){
        relogio.setMinuto(m);
    }

    void setSecond(int s){
        relogio.setSegundo(s);
    }

    void show(){
        cout<<relogio.toString()<<"\n";
    }

    void nextSecond(){
        relogio.next();
    }
};