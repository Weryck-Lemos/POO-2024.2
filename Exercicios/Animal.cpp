#include <iostream>
#include <string>

struct Animal {
    std::string especie;
    std::string barulho;
    int estagio;

    Animal(std::string especie = "", std::string barulho = "") :
        especie(especie), estagio(0), barulho(barulho) {}

    std::string str() {
        return especie + ":" + std::to_string(estagio) + ":" + barulho;
    }

    void envelhecer(int x) {
        estagio += x;
        if (estagio >= 4) {
            std::cout << "warning: " << especie << " morreu\n";
            estagio = 4;
        }
    }

    std::string emitir_som() {
        if (estagio == 0) return "---";
        if (estagio == 4) return "RIP";
        return barulho;
    }
};

struct Student {
    Animal animal;

    Student(std::string especie = "", std::string barulho = "") {
        animal = Animal(especie, barulho);
    }

    void grow(int nivel) {
        animal.envelhecer(nivel);
    }

    void noise() {
        std::cout << animal.emitir_som() << "\n";
    }

    void show() {
        std::cout << animal.str() << "\n";
    }
};
