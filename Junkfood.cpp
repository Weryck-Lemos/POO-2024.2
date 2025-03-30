#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

template <typename CONTAINER, typename FUNC>
string map_join(const CONTAINER &cont, FUNC func, string delim)
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}

struct Espiral
{
    string nome;
    int quantidade;
    double preco;

public:
    Espiral(string n = "", int qtd = 0, double p = 0) : nome(n), quantidade(qtd), preco(p) {}

    // getter
    string getnome()
    {
        return nome;
    }

    int getqtd()
    {
        return quantidade;
    }

    double getpreco()
    {
        return preco;
    }

    // setter
    void setnome(string nome)
    {
        this->nome = nome;
    }

    void setqtd(int quantidade)
    {
        this->quantidade = quantidade;
    }

    void setpreco(double preco)
    {
        this->preco = preco;
    }

    string str()
    {
        ostringstream oss;

        oss << "[" << setw(8) << nome << " : " << quantidade << " U : " << fixed << setprecision(2)
            << preco << " RS]";

        return oss.str();
    }
};

struct Maquina
{
    vector<Espiral> espiral;
    double saldo;
    double lucro;

public:
    Maquina(int n)
    {
        espiral = vector<Espiral>(n, Espiral("empty", 0, 0));
        saldo = 0;
        lucro = 0;
    }

    Espiral getSlot(int i)
    {
        if (i < 0 || i >= int(espiral.size()))
        {
            cout << "fail: indice nao existe\n";
        }

        else
            return espiral[i];
    }

    void setSlot(int i, string n, int q, double p)
    {
        if (i < 0 || i >= int(espiral.size()))
        {
            cout << "fail: indice nao existe\n";
        }

        else
            espiral[i] = Espiral(n, q, p);
    }

    void limpar(int i)
    {
        if (i < 0 || i >= int(espiral.size()))
        {
            cout << "fail: indice nao existe\n";
        }

        else
            espiral[i] = Espiral("empty", 0, 0);
    }

    void inserirDinheiro(double value)
    {
        saldo += value;
    }

    string pedirTroco()
    {
        double troco = saldo;
        saldo = 0;

        ostringstream oss;
        oss<<fixed<<setprecision(2)<< "voce recebeu "<<troco<<" RS\n";
        return oss.str();
    }

    void comprar(int i)
    {
        if (i < 0 || i > int(espiral.size()))
        {
            cout << "fail: indice nao existe\n";
        }

        else if (espiral[i].getqtd() <= 0)
        {
            cout << "fail: espiral sem produtos\n";
        }

        else if (espiral[i].getpreco() > saldo)
        {
            cout << "fail: saldo insuficiente\n";
        }

        else
        {
            Espiral &e = espiral[i];
            saldo -= e.getpreco();
            lucro += e.getpreco();
            e.setqtd(e.getqtd() - 1);

            cout<<"voce comprou um "<<espiral[i].getnome()<<"\n";
        }
    }

    double getSaldo()
    {
        return saldo;
    }

    string toString()
    {
        ostringstream oss;

        oss << "saldo: "<<fixed<<setprecision(2) << saldo << "\n";

        for (int i = 0; i < int(espiral.size()); i++)
        {
            oss << i << " " << espiral[i].str() << "\n";
        }

        return oss.str();
    }
};

int main()
{
    Maquina maquina(0);
    while (true)
    {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try
        {
            if (cmd == "show")
            {
                cout << maquina.toString();
            }
            else if (cmd == "init")
            {
                int n_espirais{};
                ss >> n_espirais;
                maquina = Maquina(n_espirais);
            }
            else if (cmd == "limpar")
            {
                int indice{};
                ss >> indice;
                maquina.limpar(indice);
            }
            else if (cmd == "dinheiro")
            {
                int value{};
                ss >> value;
                maquina.inserirDinheiro(value);
            }
            else if (cmd == "comprar")
            {
                int index{};
                ss >> index;
                maquina.comprar(index);
            }
            else if (cmd == "set")
            {
                int index{};
                string name;
                int qtd{};
                double price{};
                ss >> index >> name >> qtd >> price;
                maquina.setSlot(index, name, qtd, price);
            }
            else if (cmd == "troco")
            {
                cout << maquina.pedirTroco();
            }
            else if (cmd == "end")
            {
                break;
            }
            else
            {
                cout << "comando invalido" << endl;
            }
        }
        catch (const char *e)
        {
            cout << e << endl;
        }
    }
}
