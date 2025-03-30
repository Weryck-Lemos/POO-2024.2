#include <bits/stdc++.h>
using namespace std;

struct Camisa{
    private:
    string tamanho;

    public:

    Camisa() :tamanho(""){}

    vector<string> TamanhosValidos= {"PP", "P", "M", "G", "GG", "XG"};

    bool valido(string t){
        for(size_t i=0; i<TamanhosValidos.size(); i++){
            if(t == TamanhosValidos[i]){
                return true;
            }
        }
        return false;
    }

    void setTamanho(string t){
        if(valido (t))tamanho =t;
    }

    string getTamanho(){
        return tamanho;
    }
};

int main(){
    Camisa camisa;

    string t="";
    while(!camisa.valido(t)){
        cout<<"Digite o tamanho da camisa: ";
        cin>>t;

        if(camisa.valido(t)){
            camisa.setTamanho(t);
            cout<<"Tamanho "<<camisa.getTamanho()<<" encontrado\n";
            break;
        }

        cout<<"Digite um tamanho de roupa valido\n";
    }
}