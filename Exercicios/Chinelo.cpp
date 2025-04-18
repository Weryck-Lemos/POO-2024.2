#include <bits/stdc++.h>
using namespace std;

struct Chinela{
    private:
    int tamanho;

    public:
    
    Chinela() : tamanho(0){}

    bool valido(int t){
        return t>=20 && t<=50 && t%2==0;
    }

    void setTamanho(int t){
        if(valido(t))tamanho = t;
    }

    int getTamanho(){
        return tamanho;
    }

};

int main(){
    Chinela chinela;

    int t=0;

    while(!chinela.valido(t)){
        cin>>t;

        if(chinela.valido(t)){
            chinela.setTamanho(t);
            cout<<"Tamanho "<<chinela.getTamanho()<<" aceito!\n";
            break;
        }

        cout<<"tamanho invalido, digite um valor par entre 20 e 50\n";
    }
}