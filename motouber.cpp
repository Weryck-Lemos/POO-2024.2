#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

struct Pessoa{
    private:
    string nome;
    int dinheiro;

    public:
    Pessoa(string str= "None", int i=0): nome(str), dinheiro(i){}

    string getNome(){
        return nome;
    } 

    int getDinheiro(){
        return dinheiro;
    }
    void pagar(int x){
        if(dinheiro >= x)dinheiro -=x;
        else dinheiro =0;
    }

    void setNome(string n){
        nome = n;
    }

    void setDinheiro(int x){ 
        dinheiro +=x;
    }

    string dados(){
        if(nome != "None"){
            ostringstream oss;

            oss<<nome<<":"<<dinheiro;
            return oss.str();
        }
        return "None";
    }
};

struct Moto{
    private:
    int custo;
    Pessoa motorista;
    Pessoa passageiro;

    public:
    Moto() : custo(0), motorista("None"), passageiro("None") {}

    void setMotorista(string n, int d){
        motorista.setNome(n);
        motorista.setDinheiro(d);
    }

    void setPassageiro(string n, int d){
        if(motorista.getNome()!="None"){
            passageiro.setNome(n);
            passageiro.setDinheiro(d);
        }
        else{
            cout<<"Nao ha motorista\n";
        }
    }

    void Dirigir(int km){
        if(passageiro.getNome()!="None"){
            custo += km;
        }

        else{
            cout<<"Nao ha passageiro\n";
        }
    }

    void Sair(){
        if(passageiro.getNome() != "None"){
            int valorPago = min(custo, passageiro.getDinheiro());

            motorista.setDinheiro(valorPago);
            passageiro.pagar(valorPago);
        
            if (passageiro.getDinheiro() < custo) {
                int restante = custo - valorPago;
                motorista.setDinheiro(restante);
                cout << "fail: Passenger does not have enough money\n";
            }

            cout << passageiro.getNome() << ":" << passageiro.getDinheiro() << " leave\n";

            

            passageiro = Pessoa();
            custo = 0;
        }
    }

    string Mostrar(){
        ostringstream oss;
        oss<<"Cost: "<<custo<<", Driver: "<<motorista.dados()<<", Passenger: "<<passageiro.dados()<<"\n";
        return oss.str();
    }
};

struct Adapter{
    Moto moto;
    void setDriver(string nome, int dinheiro){
        moto.setMotorista(nome, dinheiro);
    }

    void setPass(string nome, int dinheiro){
        moto.setPassageiro(nome, dinheiro);
    }

    void drive(int distancia){
        moto.Dirigir(distancia);
    }

    void leavePass(){
        moto.Sair();
    }

    void show(){
        cout<<moto.Mostrar();
    }
};