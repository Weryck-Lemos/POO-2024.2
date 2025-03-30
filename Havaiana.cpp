#include <bits/stdc++.h>
using namespace std;

class Havaiana {
    int tamanho;

public:
    void setTamanho(int value) {
        if (value % 2 == 0 && value >= 20 && value <= 50) {
            this->tamanho = value;
        } 
    }

    int getTamanho() {
        return tamanho;
    }
};

int main() {
    Havaiana chinelo;
    int tamanho;

    cin>>tamanho;
    while (tamanho %2!= 0 ||tamanho < 20 || tamanho>50) {
        cout<<"Tamanho invalido. Tente entre 20 e 50\n ";
        cin>>tamanho;
    }


    chinelo.setTamanho(tamanho);
    if (chinelo.getTamanho()!= 0) {
        cout << "configurado: "<<chinelo.getTamanho()<<"\n";
    }
}
