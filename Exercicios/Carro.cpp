#include <iostream>
#include <string>
using namespace std;

struct Carro
{
    int pessoas;
    int litros;
    int km;

    Carro(int pessoas=0, int litros=0, int km=0) 
    : pessoas(pessoas), litros(litros), km(km){}

    string mostrar()
    {
        return "pass: "+to_string(pessoas)+", gas: "+to_string(litros)+", km: "+to_string(km);
    }

    void entrar()
    {
        pessoas+=1;
        if(pessoas>2)  
        {
            cout<<"fail: limite de pessoas atingido\n";
            pessoas=2;
        }
    }

    void sair()
    {
        if(pessoas==0) cout<<"fail: nao ha ninguem no carro\n";
        else pessoas -=1;
    }

    void abastecer(int x)
    {
        litros += x;
        if(litros>100)litros=100;
    }

    void dirigir(int x)
    {
        if(pessoas==0) cout<< "fail: nao ha ninguem no carro\n";
        else if(litros==0) cout<< "fail: tanque vazio\n";

        else if(x>litros)
        {
            cout<< "fail: tanque vazio apos andar "+to_string(litros)+" km\n";
            km+=litros;
            litros=0;
        }

        else 
        {
            km+=x;
            litros-=x;
            if(litros<0)litros=0;
        }
    }
};

struct Student
{
    Carro carro;

    Student(int pessoas=0,int litros=0,int km=0)
    {
        carro = Carro(pessoas, litros, km);
    }
    
    void show()
    {
        cout<<carro.mostrar()<<"\n";
    }

    void enter()
    {
        carro.entrar();
    }

    void leave()
    {
        carro.sair();
    }

    void fuel(int x)
    {
        carro.abastecer(x);
    }

    void drive(int x)
    {
        carro.dirigir(x);
    }

};