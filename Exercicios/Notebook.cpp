#include <bits/stdc++.h>
using namespace std;

struct Carregador{
    private:
    int potencia;

    public:
    Carregador(int p =0) : potencia(p){}

    int getPotencia(){
        return potencia;
    }
};

struct Bateria{
    private:
    int carga;
    int capacidade;

    public:
    Bateria(int c = 0, int cap=0): capacidade(cap), carga(c) {}

    int getCarga(){
        return carga;
    }

    int getCapacidade(){
        return capacidade;
    }

    void consumir(int tempo){
        carga = max(0, carga-tempo);
    }

    void mostrar(){
        cout<<carga<<"/"<<capacidade<<"\n";
    }

    void carregar(int tempo){
        carga = min(capacidade, carga+capacidade);
    }
};

struct Notebook{
    private:
    bool ligado;
    Bateria bateria;
    Carregador carregador;

    public:
    Notebook() : ligado(false), bateria(0,50), carregador(0){}


    void ligar(){
        if(bateria.getCarga()>0 || carregador.getPotencia()>0){
            if(!ligado){
                ligado = true;
                cout<<"Notebook ligado\n";
            }
            else cout<<"Notebook ja esta ligado\n";
        }
        else cout<<"Nao e possivel ligar, esta sem carga\n";
    }

    void desligar(){
        if(ligado){
            ligado = false;
            cout<<"Notebook desligado\n";
        }
        else cout<<"Notebook ja esta desligado\n";
    }

    void mostrar(){
        if(bateria.getCapacidade()==0)cout<<"sem bateria\n";
        else bateria.mostrar();
        cout<<"Carregador: "<<carregador.getPotencia()<<" de potencia\n";
    }

    void usar(int tempo){
        if(!ligado){
            cout<<"O notebook nao pode ser usado, ligue-o\n";
            
        }

        else if(bateria.getCarga()==0 && carregador.getPotencia()==0){
            cout<<"bateria Sem carga";
            desligar();
        }

        if (carregador.getPotencia() > 0) {
                bateria.carregar(min(tempo, carregador.getPotencia())); // Carrega a bateria enquanto estiver usando
            }

            if (bateria.getCarga() > 0) {
                bateria.consumir(tempo);
                cout << "usando por " << tempo << " minuto(s)\n";
            } else {
                cout << "usando por " << bateria.getCarga() << " minuto(s), notebook descarregou\n";
                bateria.consumir(bateria.getCarga());
                desligar();
            }
    }

    void setBateria(int c){
        if(bateria.getCarga()==0){
            bateria = Bateria(c);
            cout<<"Bateria inserida\n";
        }
        else cout<<"Ja tem bateria\n";
    }

    void rmBateria(){
        if(bateria.getCarga()==0){
            cout<<"Nao tem bateria para remover\n";
            
        }
        else{ 
            bateria= Bateria(0);
            cout<<"Bateria removida\n";
        }
        
    }
};

int main() {
    Notebook notebook;

    notebook.mostrar();
    notebook.usar(10);
    notebook.ligar();
    notebook.mostrar();

    notebook.setBateria(50); // Define uma bateria com capacidade 50.
    notebook.mostrar();
    notebook.usar(10);
    notebook.ligar();
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    notebook.ligar();
    notebook.rmBateria();
    notebook.mostrar();

    return 0;
}
