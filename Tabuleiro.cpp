#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Board{
    int nPlayers;
    int boardSize;
    vector<int> pos;
    vector<bool> stuck;
    vector<int> traps;
    int current;
    bool finished;
    int winner;

    bool isTrap(int i){
        for(int t : traps){
            if(t == i) return true;
        }

        return false;
    }

    public:
    Board(int n, int sz) : nPlayers(n), boardSize(sz) {
        pos.assign(nPlayers,0);
        stuck.assign(nPlayers, false);
        traps.clear();
        current = 0;
        finished = false;
        winner = -1;
    }

    void addTrap(int p){
        if(traps.size() <3)traps.push_back(p);

        else cout<<"fail: ja existem 3 armadilhas\n";
    }

    void roll(int n){
        pos[current] = n;
        cout << "player" << current+1 << " andou para " << pos[current] << "\n";

        if (n >= 0 && n < traps.size() && traps[n]) {
            stuck[current] = true;
            cout << "player" << current+1 << " caiu em uma armadilha\n";
        }
    
        current = (current + 1) % nPlayers;
    }

    void show(){
        int total = boardSize + 1;
        for (int i = 0; i < nPlayers; i++) {
            string line(total, '.');
            int p = pos[i];
            if (p >= 0 && p < total) {
                line[p] = char('0' + (i+1)); 
            }
            cout << "player" << i+1 << ": " << line << "\n";
        }
        string tline(total, '.');
        for (int i = 0; i < total; i++) {
            if (traps[i])
                tline[i] = 'x';
        }
        cout << "traps__: " << tline << "\n";
    }
};