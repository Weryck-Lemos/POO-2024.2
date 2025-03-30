#include <bits/stdc++.h>
using namespace std;

class Grafite{
private:
    float thickness=0;
    string hardness="";
    int size=0;

public:
    //construtor
    Grafite(float thickness=0, string hardness="", int size=0):
    thickness(thickness), hardness(hardness), size(size){}

    int usagePerSheet(){
        if (hardness == "HB") return 1;
        if (hardness == "2B") return 2;
        if (hardness == "4B") return 4;
        if (hardness == "6B") return 6;
    }

    //Get
    string getHardness() {return hardness;}
    int getSize() {return size;}
    float getThickness() {return thickness;}

    //Set
    void setSize(int newSize) {size = newSize;}
};

class Lapiseira{
    public:
        float thickness = 0;
        Grafite grafite;

        //construtor
        Lapiseira(float thickness = 0) : thickness(thickness){}

        bool hasGrafite(){
            return !grafite.getHardness().empty() && grafite.getSize()>0 && grafite.getThickness()>0;
        }

        void remove(){
            if(!hasGrafite()){
                cout<<"fail: nao existe grafite\n";
            }

            else{
                grafite = Grafite();
            }
        }

        void writePage(){
            if(!hasGrafite()) cout<<"fail: nao existe grafite\n";

            else if(grafite.getSize()<=10) cout<<"fail: tamanho insuficiente\n";

            else{
                int usage = grafite.usagePerSheet();
                if(grafite.getSize()- usage >=10){
                    grafite.setSize(grafite.getSize() - usage);
                }
                else{
                    grafite.setSize(10);
                    cout<<"fail: folha incompleta\n";
                }
            }
        }

        void insert(Grafite newGrafite){
            if(thickness != newGrafite.getThickness()){
                cout<<"fail: calibre incompativel\n";
            }

            else if(!grafite.getHardness().empty()){
                cout<<"fail: ja existe grafite\n";
            }

            else grafite= newGrafite;
        }

        void str(){
            if(grafite.getThickness()==0 && grafite.getHardness().empty() && grafite.getSize()==0){
                cout<<fixed<<setprecision(1)<<"calibe: "<< thickness<<", grafite: null\n";
            }

            else{
                cout<<fixed<<setprecision(1)<<"calibre: "<<thickness<<", grafite: ["<<grafite.getThickness()<<":"<<grafite.getHardness()<<":"<<grafite.getSize()<<"]\n";
            }
        }
};

class Student{
    private:
        Lapiseira pencil;

    public:
        Student(float thickness):pencil(thickness){}

        void insert(double thickness, string hardness, int lenght){
            pencil.insert(Grafite(thickness, hardness, lenght));
        }

        void remove(){
            pencil.remove();
        }

        void writePage(){
            pencil.writePage();
        }

        void show(){
            pencil.str();
        }


};