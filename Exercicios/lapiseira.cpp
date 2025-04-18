#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <memory>
#include <iomanip>
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
            return 0;
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
            Grafite* bico = nullptr;
            vector<Grafite*> tambor;
    
            //construtor
            Lapiseira(float thickness = 0) : thickness(thickness){}

            void init(float cal){
                if(bico){
                    delete bico;
                    bico = nullptr;
                }

                for(auto g : tambor) delete g;

                tambor.clear();
                thickness = cal;
            }

            void pull() {
                if(bico != nullptr) {
                    cout << "fail: ja existe grafite no bico\n";
                    return;
                }
                if(tambor.empty()){
                    cout << "fail: tambor vazio\n";
                    return;
                }
                bico = tambor.back();
                tambor.pop_back();
            }
    
            bool hasGrafite(){
                return bico != nullptr;
            }
    
            void remove(){
                if(!hasGrafite()){
                    cout<<"fail: nao existe grafite\n";
                }
    
                else{
                    delete bico;
                    bico = nullptr;
                }
            }
    
            void write(){
                if(!hasGrafite()) cout<<"fail: nao existe grafite\n";
    
                else if(bico->getSize() <=10) {
                    cout<<"fail: tamanho insuficiente\n";
                    remove();
                }
    
                else{
                    int usage = bico->usagePerSheet();
                    if(bico->getSize()- usage >=10){
                        bico->setSize(bico->getSize() - usage);
                    }
                    else{
                        bico->setSize(10);
                        cout<<"fail: folha incompleta\n";
                        remove();
                    }
                }
            }
    
            void insert(float c, string d, int t){
                if(thickness != t){
                    cout<<"fail: calibre incompativel\n";
                }
    
                else if(bico != nullptr){
                    cout<<"fail: ja existe grafite\n";
                }
    
                else bico = new Grafite(c, d, t);
            }
    
            void show(){
                cout << fixed << setprecision(1) << "calibre: " << thickness << ", ";
                cout << "bico: ";
                if(bico == nullptr)
                    cout << "[]";
                else
                cout << "[" << bico->getThickness() << ":" << bico->getHardness() << ":" << bico->getSize() << "]";
                cout << ", tambor: ";
                if(tambor.empty()) cout<<"<>";

                else{
                    cout<<"<";
                    for (size_t i = 0; i < tambor.size(); i++){
                        cout << "[" << tambor[i]->getThickness() << ":" << tambor[i]->getHardness() << ":" << tambor[i]->getSize() << "]";
                        if(i != tambor.size()-1)
                            cout << ", ";
                    }
                    cout << ">";
                }
            cout<<"\n";
        }
    };
    

