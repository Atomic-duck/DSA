#include <iostream>
#include <list>
#include <cstring>

using namespace std;

// hash table implement phone number - name
class HashTable{
private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups];
private:
    int hasFunction(int key);
public:
    HashTable(){}
    bool isEmpty() const;
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const{
    for (int i = 0; i < hashGroups; i++){
        if (!table[i].empty()) return false;
    }

    return true;
}

int HashTable::hasFunction(int key){
    return key%hashGroups;
}

void HashTable::insertItem(int key, string value){
    int idx = hasFunction(key);
    for (auto p = table[idx].begin(); p != table[idx].end(); p++){
        if (p->first == key) {
            p->second = value;
            return;
        }
    }

    table[idx].emplace_back(key, value);
}

void HashTable::removeItem(int key){
    int idx = hasFunction(key);
    for (auto p = table[idx].begin(); p != table[idx].end(); p++){
        if (p->first == key) {
            table[idx].erase(p);
            return;
        }
    }
}

string HashTable::searchTable(int key){
    int idx = hasFunction(key);
    for (auto p = table[idx].begin(); p != table[idx].end(); p++){
        if (p->first == key) {
            return p->second;
        }
    }

    return "not found";
}

void HashTable::printTable(){
    for (int i = 0; i < hashGroups; i++){
        for (auto p = table[i].begin(); p != table[i].end(); p++){
            cout <<(*p).first<<' '<<(*p).second<<'\n';
        }
    }
}

int main()
{
    HashTable t1;
    t1.insertItem(1234, "A");
    t1.insertItem(1314, "B");
    t1.insertItem(1344, "C");
    t1.removeItem(1234);


    t1.printTable();

    if(!t1.isEmpty()) cout<<t1.searchTable(1234);

    return 0;
}
