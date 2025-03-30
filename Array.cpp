#include <bits/stdc++.h>
using namespace std;

void printVector(const vector<int>& vec, const string& nome = "Array") {
    cout << nome << ": [ ";
    for (const auto &elem : vec) {
        cout << elem << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> vazio;
    printVector(vazio, "Array vazio");

    vector<int> preenchido = {10, 20, 30, 40, 50};
    printVector(preenchido, "Array preenchido");

    preenchido.push_back(60);
    printVector(preenchido);
    preenchido.pop_back();
    cout << "Após pop_back():" << endl;
    printVector(preenchido);



    int n = 10;
    vector<int> sequencia;
    for (int i = 0; i <= n; ++i) {
        sequencia.push_back(i);
    }
    printVector(sequencia, "Sequência de 0 a n");

   
    srand(static_cast<unsigned int>(time(0)));
    vector<int> aleatorios;
    for (int i = 0; i < 10; ++i) {
        aleatorios.push_back(rand() % 100);
    }
    printVector(aleatorios, "Valores aleatórios");

    

    cout << "\nPercorrendo 'sequencia' com for-range: ";
    for (auto elem : sequencia) {
        cout << elem << " ";
    }
    cout << endl;

    cout << "Percorrendo 'aleatorios' com for indexado: ";
    for (size_t i = 0; i < aleatorios.size(); ++i) {
        cout << aleatorios[i] << " ";
    }
    cout << endl;

    int X = 5;
    auto it = find(sequencia.begin(), sequencia.end(), X);
    if (it != sequencia.end()) {
        cout << "\nElemento " << X << " encontrado na posição " 
             << distance(sequencia.begin(), it) << endl;
    } else {
        cout << "\nElemento " << X << " não encontrado." << endl;
    }

    vector<int> pares;
    for (int elem : sequencia) {
        if (elem % 2 == 0)
            pares.push_back(elem);
    }
    printVector(pares, "Números pares da sequência");

    vector<int> quadrados;
    for (int elem : sequencia) {
        quadrados.push_back(elem * elem);
    }
    printVector(quadrados, "Quadrados da sequência");
}
