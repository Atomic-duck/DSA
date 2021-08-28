#include <iostream>

using namespace std;

#define NONE -1
#define DElETED 0

class HashTable{
private:
    int m_size;
    static const int M = 10;
    int keys[M];
    string vals[M];
private:
    int hasFunction(int key);
public:
    HashTable();
    bool isEmpty() const;
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

HashTable::HashTable(){
    m_size = 0;
    for (int i = 0; i < M; i++){
        keys[i] = NONE;
    }
}

bool HashTable::isEmpty() const{
    return m_size == 0;
}

int HashTable::hasFunction(int key){
    return key%M;
}

void HashTable::insertItem(int key, string value){
    int d = 0;
    int i;
    for (i = hasFunction(key); keys[i] != DElETED && keys[i] != NONE; i = (i+1)%M){
        if (keys[i] == key) break;
        if (++d == M) return; // overflow
    }

    keys[i] = key;
    vals[i] = value;
    m_size++;
}

void HashTable::removeItem(int key){
    int d = 0;
    int i;
    for (i = hasFunction(key); keys[i] != NONE; i = (i+1)%M){
        if (keys[i] == key) break;
        if (++d == M) return; // overflow
    }

    keys[i] = DElETED;
    m_size--;
}

string HashTable::searchTable(int key){
    int d = 0;
    int i;
    for (i = hasFunction(key); keys[i] != NONE; i = (i+1)%M){
        if (keys[i] == key) return vals[i];
        if (++d == M) break; // overflow
    }

    return "not found";
}

void HashTable::printTable(){
    for (int i = 0; i < M; i++){
        if (keys[i] != NONE && keys[i] != DElETED)
            cout<< keys[i]<< ' '<<vals[i]<<'\n';
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
