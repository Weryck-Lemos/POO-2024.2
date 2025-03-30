#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

struct Carregador
{
private:
    int potencia;

public:
    Carregador(int p = 0) : potencia(p) {}

    int getPotencia() const
    {
        return potencia;
    }
};

struct Bateria
{
private:
    int carga;
    int capacidade;

public:
    Bateria(int c = 0, int cap = 0) : carga(c), capacidade(cap) {}

    int getCarga() const
    {
        return carga;
    }

    int getCapacidade() const
    {
        return capacidade;
    }

    void consumir(int tempo)
    {
        carga = max(0, carga - tempo);
    }

    void carregar(int potencia, int tempo)
    {
        carga = min(capacidade, carga + potencia * tempo);
    }

    void mostrar() const
    {
        cout << carga << "/" << capacidade;
    }
};

struct Notebook
{
private:
    bool ligado;
    Bateria bateria;
    Carregador carregador;
    int tempo;

public:
    Notebook() : ligado(false), bateria(0, 0), carregador(0), tempo(0) {}

    void ligar()
    {
        if (bateria.getCarga() > 0 || carregador.getPotencia() > 0)
        {
            if (!ligado)
            {
                ligado = true;
            }
            else
            {
                cout << "Notebook ja esta ligado\n";
            }
            return;
        }

        cout << "fail: não foi possível ligar\n";
    }

    void desligar()
    {
        if (ligado)
        {
            ligado = false;
        }
        else
        {
            cout << "Notebook ja esta desligado\n";
        }
    }

    void mostrar()
    {

        if (!ligado)
        {
            cout << "Notebook: desligado";
        }

        else
        {
            cout << "Notebook: ligado por " << tempo << " min";
        }
        if (carregador.getPotencia() != 0)
            cout << ", Carregador " << carregador.getPotencia() << "W";

        if (bateria.getCapacidade() != 0)
        {
            cout << ", Bateria ";
            bateria.mostrar();
        }

        cout << "\n";
    }

    void usar(int t)
    {
        if (!ligado)
        {
            cout << "fail: desligado\n";
            return;
        }

        if (bateria.getCarga() == 0 && carregador.getPotencia() == 0)
        {
            cout << "Sem carga na bateria ou carregador\n";
            desligar();
            return;
        }

        if (carregador.getPotencia() > 0)
        {
            bateria.carregar(carregador.getPotencia(), t);
            tempo +=t;
        }

        else if (bateria.getCarga() > 0 || carregador.getPotencia() ==0)
        {
            int tempoUsado = min(t, bateria.getCarga());
            bateria.consumir(tempoUsado);
            tempo += t;

            if (bateria.getCarga() == 0 && carregador.getPotencia() == 0)
            {
                cout << "fail: descarregou\n";
                desligar();
            }
        }
    }

    void setBateria(int capacidade)
    {
        if (bateria.getCapacidade() == 0)
        {
            bateria = Bateria(capacidade, capacidade);
        }

        else
        {
            cout << "fail: bateria já conectado\n";
        }
    }

    void rmBateria()
    {
        if (bateria.getCapacidade() == 0)
        {
            cout << "fail: Sem bateria\n";
        }
        else
        {
            cout << "Removido ";
            bateria.mostrar();
            cout << "\n";
            bateria = Bateria(0, 0);
            if(carregador.getPotencia()==0)desligar();
        }
    }

    void setCarregador(int potencia)
    {
        if (carregador.getPotencia() == 0)
        {
            carregador = Carregador(potencia);
        }
        else
        {
            cout << "fail: carregador já conectado\n";
        }
    }

    void rmCarregador()
    {
        if (carregador.getPotencia() == 0)
        {
            cout << "fail: Sem carregador\n";
        }
        else
        {
            cout << "Removido " << carregador.getPotencia() << "W\n";
            carregador = Carregador(0);

            if (bateria.getCarga() == 0) desligar();
        }
    }
};

int main()
{
    Notebook notebook;
    while (true)
    {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }
        else if (cmd == "show")
        {
            notebook.mostrar();
        }
        else if (cmd == "turn_on")
        {
            notebook.ligar();
        }
        else if (cmd == "turn_off")
        {
            notebook.desligar();
        }
        else if (cmd == "use")
        {
            int minutes;
            ss >> minutes;
            notebook.usar(minutes);
        }
        else if (cmd == "set_charger")
        {
            int power;
            ss >> power;
            notebook.setCarregador(power);
        }
        else if (cmd == "rm_charger")
        {
            notebook.rmCarregador();
        }
        else if (cmd == "set_battery")
        {
            int capacity;
            ss >> capacity;
            notebook.setBateria(capacity);
        }
        else if (cmd == "rm_battery")
        {
            notebook.rmBateria();
        }
        else
        {
            cout << "fail: comando invalido\n";
        }
    }
}
