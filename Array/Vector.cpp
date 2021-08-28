#include <iostream>

using namespace std;

template <class T>
class Vector{
private:
    T *arr;
    int capacity;
    int current;

    void resize(int size);
public:
    typedef T* iterator;

    Vector();
    Vector(int cap);
    Vector(int cap,const T& initial);
    Vector(Vector<T>& v);
    ~Vector();

    int getCapacity() const {return capacity;}
    int size() const {return current;}
    bool empty() const {return current == 0;}
    T& front() {return arr[0];}
    T& back() {return arr[current-1];}

    iterator begin();
    iterator end();
    void push_back(const T& value);
    void pop_back();
    T& at(int index);

    void insert(int index,const T& value);
    void prepend(const T& value);
    void deleteIndex(int index);
    void removeValue(const T& value);
    int findValue(const T& value);

    T& operator[](int index);
    Vector<T> operator=(const Vector<T>& v);
    void clear();
};

template <class T>
Vector<T>::Vector(){
    capacity = 16;
    current = 0;
    arr = new T[capacity];
}

template <class T>
Vector<T>::Vector(int cap,const T& initial){
    capacity = 2*cap;
    current = cap;
    arr = new T[capacity];
    for (int i = 0; i < current; i++){
        arr[i] = initial;
    }
}

template <class T>
Vector<T>::Vector(int cap){
    capacity = cap;
    current = 0;
    arr = new T[cap];
}

template <class T>
Vector<T>::Vector(Vector<T>& v){
    capacity = v.getCapacity();
    current = v.size();
    arr = new T[capacity];
    for (int i = 0; i < current; i++){
        arr[i] = v[i];
    }
}

template <class T>
Vector<T>::~Vector(){
    delete[] arr;
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin(){
    return arr;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end(){
    return arr + current;
}

template <class T>
void Vector<T>::push_back(const T& value){
    if (current == capacity) resize(2*capacity);
    arr[current++] = value;
}

template <class T>
void Vector<T>::pop_back(){
    if (current == 0) return;
    if (current > 4 && current == capacity/4) resize(capacity/2);
    current--;
}

template <class T>
void Vector<T>::resize(int cap){
    int *newArr = new T[cap];
    capacity = cap;

    for (int i = 0; i < current; i++){
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
}

template <class T>
T& Vector<T>::operator[](int index){
    return arr[index];
}

template <class T>
Vector<T> Vector<T>::operator=(const Vector<T>& v){
    delete[] arr;

    capacity = v.getCapacity();
    current = v.size();
    arr = new T[capacity];
    for (int i = 0; i < current ; i++){
        arr[i] = v[i];
    }

    return *this;
}

template <class T>
void Vector<T>::clear(){
    capacity = 16;
    current = 0;
    delete[] arr;
    arr = new T[capacity];
}

template <class T>
void Vector<T>::insert(int index,const T& value){
    if (index < 0 || index >= current) return;
    if (current == capacity) resize(2*capacity);

    for(int i = ++current; i > index; i--){
        arr[i] = arr[i-1];
    }
    arr[index] = value;
}

template <class T>
void Vector<T>::prepend(const T& value){
    insert(0, value);
}

template <class T>
void Vector<T>::deleteIndex(int index){
    if (index < 0 || index >= current) return;
    if (current > 4 && current == capacity/4) resize(capacity/2);
    for (int i = index; i < current - 1; i++){
        arr[i] = arr[i+1];
    }
    current--;
}

template <class T>
void Vector<T>::removeValue(const T& value){
    for (int i = 0; i < current; i++){
        if (arr[i] == value){
            deleteIndex(i);
        }
    }
}

template <class T>
int Vector<T>::findValue(const T& value){
    for (int i = 0; i < current; i++){
        if (arr[i] == value) return i;
    }

    return -1;
}

template <class T>
T& Vector<T>::at(int index){
    if (index < 0 || index >= current)
        throw std::out_of_range("invalid index");

    return arr[index];
}

int main()
{
    Vector<int> arr;

    for (int i = 0; i < 10; i++){
        arr.push_back(i);
    }

    arr.pop_back();
    arr.insert(4, 20);
    arr.prepend(-1);
    arr.deleteIndex(4);
    arr.deleteIndex(20);
    arr.removeValue(2);
    arr.removeValue(20);
    cout<<arr.findValue(7)<<'\n';
    cout<<arr.front()<<'\n';
    cout<<arr.back()<<'\n';
    cout<<arr.getCapacity()<<'\n';
    cout<<arr.size()<<'\n';

    for (Vector<int>::iterator p = arr.begin(); p != arr.end(); p++){
        cout<<*p<<' ';
    }
    cout<<'\n';

    return 0;
}
