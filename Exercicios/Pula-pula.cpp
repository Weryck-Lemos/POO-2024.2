#include <iostream>
#include <memory>
#include <sstream>
#include <list>
using namespace std;

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

class Kid{
    public:
    string name;
    int age;

    Kid(string n, int a) : name(n), age(a) {}

    string to_string() const{
        ostringstream oss;

        oss<<name<<":"<<age;
        return oss.str();
    }
};

class Trampoline{
    list<Kid> waiting;
    list<Kid> playing;

    public:

    void arrive(string name, int age){
        waiting.push_front(Kid(name, age));

    }

    void enter(){
        if(waiting.empty()){
            return;
        }

        playing.push_front(waiting.back());
        waiting.pop_back();
    }

    void leave() {
        if (playing.empty()) {
            return;
        }
        waiting.push_front(playing.back());
        playing.pop_back();
    }

    void remove(string name) {
        for (auto it = waiting.begin(); it != waiting.end(); it++) {
            if (it->name == name) {
                waiting.erase(it);
                return;
            }
        }

        for (auto it = playing.begin(); it != playing.end(); it++) {
            if (it->name == name) {
                playing.erase(it);
                return;
            }
        }

        cout << "fail: " << name << " nao esta no pula-pula" << endl;
    }

    string to_string() const {
        ostringstream ss;

        ss << "[";
        for (auto it = waiting.begin(); it != waiting.end(); it++) {
            if (it != waiting.begin()) ss << ", ";
            ss << it->to_string();
        }
        ss << "] => [";

        for (auto it = playing.begin(); it != playing.end(); it++) {
            if (it != playing.begin()) ss << ", ";
            ss << it->to_string();
        }
        ss << "]";

        return ss.str();
    }

};