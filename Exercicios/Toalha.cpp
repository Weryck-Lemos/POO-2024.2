#include <bits/stdc++.h>
using namespace std;

struct Toalha{
    private:
    string cor;
    string tamanho;
    int umidade;

    public:
    Toalha(string c="", string t=""):
    cor(c), tamanho(t), umidade(0){}

    void enxu(int x){
        int maximoUmidade = pegarMaximoUmidade();
        if(umidade== maximoUmidade)cout<<"msg: toalha encharcada\n";
        umidade +=x;
        
        umidade = min(maximoUmidade, umidade);
    }

    void torc(){
        umidade =0;
    }

    int pegarMaximoUmidade(){
        if(tamanho =="P") return 10;
        else if(tamanho =="M") return 20;
        else if(tamanho =="G") return 30;

        return 0;
    }

    void estaSeca(){
        if(umidade==0)cout<<"True\n";
        else cout<<"False\n";
    }

    void mostr(){
        cout<<cor<<" "<<tamanho<<" "<<umidade<<"\n";
    }
};

struct Adapter{

    Toalha toalha;


    void criar(string cor, string tamanho){
        toalha = Toalha(cor, tamanho);
    }

    void enxugar(int x){
        toalha.enxu(x);
    }

    void seca(){
        toalha.estaSeca();
    }

    void torcer(){
        toalha.torc();
    }

    void mostrar(){
        toalha.mostr();
    }


};