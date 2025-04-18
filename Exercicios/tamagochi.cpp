#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Tamagochi {
private:
    int energia, saciedade, limpeza;
    int maxEnergia, maxSaciedade, maxLimpeza;
    int idade, diamantes;
    bool vivo;

    void verificarMorte() {
        if (energia <= 0) {
            cout << "fail: pet morreu de fraqueza\n";
            vivo = false;
        } else if (saciedade <= 0) {
            cout << "fail: pet morreu de fome\n";
            vivo = false;
        } else if (limpeza <= 0) {
            cout << "fail: pet morreu de sujeira\n";
            vivo = false;
        }
    }

public:
    Tamagochi(int maxEnergia, int maxSaciedade, int maxLimpeza) 
        : energia(maxEnergia), saciedade(maxSaciedade), limpeza(maxLimpeza),
          maxEnergia(maxEnergia), maxSaciedade(maxSaciedade), maxLimpeza(maxLimpeza),
          idade(0), diamantes(0), vivo(true) {}

    void comer() {
        if (!vivo) {
            cout<<"fail: pet esta morto\n";
            return;
        }
        saciedade = min(saciedade + 4, maxSaciedade);
        energia = max(energia - 1, 0);
        limpeza = max(limpeza - 2, 0);
        idade++;
        verificarMorte();
    }

    void brincar() {
        if (!vivo) {
            cout<<"fail: pet esta morto\n";
            return;
        }
        energia = max(energia - 2, 0);
        saciedade = max(saciedade - 1, 0);
        limpeza = max(limpeza - 3, 0);
        diamantes++;
        idade++;
        verificarMorte();
    }

    void dormir() {
        if (!vivo) {
            cout << "fail: pet esta morto\n";
            return;
        }
        if (energia < maxEnergia - 4) {
            idade += (maxEnergia - energia);
            energia = maxEnergia;
            saciedade = max(saciedade - 1, 0);
            verificarMorte();
        } else {
            cout << "fail: nao esta com sono\n";
        }
    }

    void tomarBanho() {
        if (!vivo) {
            cout << "fail: pet esta morto\n";
            return;
        }
        limpeza = maxLimpeza;
        energia = max(energia - 3, 0);
        saciedade = max(saciedade - 1, 0);
        idade+=2;
        verificarMorte();
    }

    void mostrarStatus() const {
        cout << "E:" << energia << "/" << maxEnergia << ", "
             << "S:" << saciedade << "/" << maxSaciedade << ", "
             << "L:" << limpeza << "/" << maxLimpeza << ", "
             << "D:" << diamantes << ", "
             << "I:" << idade << "\n";
    }
};

class Student {
private:
    Tamagochi pet;
public:
    Student(int energy, int hungry, int clean) : pet(energy, hungry, clean) {}

    void show() {
        pet.mostrarStatus();
    }

    void play() {
        pet.brincar();
    }

    void shower() {
        pet.tomarBanho();
    }

    void eat() {
        pet.comer();
    }

    void sleep() {
        pet.dormir();
    }
};
