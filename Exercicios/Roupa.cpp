#include <bits/stdc++.h>
using namespace std;

struct Roupa{
    private:
    string size;

    public:
    Roupa(string sz =""): size(sz){}

    vector<string> possible = {"PP", "P", "M", "G", "GG", "XG"};
    void setSize(string sz){
        for(size_t i=0; i<possible.size(); i++){
            if(sz == possible[i]){
                size = sz;
                return;
            }
        }

        cout<<"fail: Valor inválido, tente PP, P, M, G, GG ou XG\n";
    }

    string getSize(){
        ostringstream oss;

        oss<<"size: ("<<size<<")\n";
        return oss.str();
    }
};

class Adapter {
public:
Roupa roupa;

    Adapter() {
    }
    void size(string& size) {
        roupa.setSize(size);
    }
    void show() {
        cout<<roupa.getSize();
    }
};