#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Fone {
    string id, number;
public:
    Fone(string id="",string number="") :id(id), number(number) {}

    string getId() const {return id; }
    string getNumber() const { return number; }

    string str() const {
        return id + ":"+ number;
    }
};

struct Contact {
    string name;
    vector<Fone> fones;
    bool favorite;

public:
    Contact() : name(""), favorite(false) {} 
    Contact(string name) :name(name), favorite(false) {}

    string getName() const { return name;}

    bool isFavorite() const { return favorite;}

    void addFone(string id, string number) {

        fones.push_back(Fone(id, number));
    }

    void removeFone(int index) {
        if ( index >= 0 && index <(int)fones.size()) {
            fones.erase(fones.begin() + index);
        } 
        
        else cout << "fail: index invalido"<<endl;
    }

    void setFavorite( bool fav ) {
        favorite = fav;
    }

    string str() const {
        stringstream ss;
        ss << (favorite ?"@ " : "- ") << name << " [";
        for (size_t i=0;  i< fones.size(); i++) {
            if (i>0) ss << ", ";
            ss << fones[i].str();
        }
        ss << "]";
        return ss.str();
    }
};

class Agenda {
private:
    map<string, Contact> contacts;
    vector<Contact*> favorites;

public:
    void addContact(string name, vector<Fone> fones) {
        if ( contacts.find(name) == contacts.end())
            contacts[name] = Contact(name);
        
        for (auto &fone : fones)
            contacts[name].addFone( fone.getId(), fone.getNumber() );
    }

    void removeContact( string name ) {
        if ( contacts.erase(name) == 0)
            cout << "fail: contato nao encontrado"<<endl;
    }

    void removeFone( string name, int index) {
        if (contacts.find(name) != contacts.end())
            contacts[name].removeFone(index);
        else cout << "fail: contato nao encontrado"<<endl;
    }

    void favoriteContact( string name ) {
        if (contacts.find(name) != contacts.end()) {
            contacts[name].setFavorite( true );
            favorites.push_back( &contacts[name] );
        } else cout << "fail: contato nao encontrado"<<endl;
    }

    void removeFavorite( string name) {
        if ( contacts.find(name) != contacts.end()) {
            contacts[name].setFavorite(false);
            favorites.erase( remove_if( favorites.begin(), favorites.end(), [&name](Contact* c) { return c->getName() == name; }), favorites.end() );
        } 
        
        else cout <<"fail: contato nao encontrado"<<endl;
    }

    void showContacts() const {
        for (const auto& pair : contacts) cout << pair.second.str()<<endl;
    }

    void showFavorites() const {
        for (const auto& contact : favorites) cout << contact->str()<<endl;
    }
};

int main() {
    Agenda agenda;
    string line;

    while (true) {
        getline(cin, line);
        cout << "$ "<< line << endl;

        stringstream ss( line );
        string cmd, name;
        ss >> cmd;

        if (cmd == "end") break;
        else if ( cmd == "add") {
            ss >> name;
            vector<Fone> fones;
            string fone;
            while ( ss >> fone ) {
                size_t pos = fone.find(":");
                if (pos != string::npos)
                    fones.emplace_back( fone.substr(0, pos), fone.substr(pos + 1) );
            }
            agenda.addContact(name, fones);
        }
        else if (cmd == "rm") {
            ss >> name;
            agenda.removeContact(name);
        }
        else if ( cmd == "rmFone") {
            int index;
            ss >> name >> index;
            agenda.removeFone( name, index );
        }
        else if (cmd =="fav") {
            ss>>name;
            agenda.favoriteContact( name );
        }
        else if (cmd == "unfav") {
            ss>>name;
            agenda.removeFavorite( name );
        }
        else if (cmd == "show") {
            agenda.showContacts();
        }
        else if (cmd == "showFav") {
            agenda.showFavorites();
        }
        
        else cout << "fail: comando invalido"<<endl;
    }

    return 0;
}

void showContacts() const {
    for (const auto& contact : favorites) {
        cout << contact->str() << endl;
    }
    
    for (const auto& pair : contacts) {
        if (!pair.second.isFavorite()) {
            cout << pair.second.str() << endl;
        }
    }
}

