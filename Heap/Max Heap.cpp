#include <iostream>

using namespace std;

class MaxHeap{
private:
    int* arr;
    int cap;
    int m_size;
private:
    void sift_up(int k);
    void sift_down (int k);
public:
    MaxHeap(int capacity = 20){
        cap = capacity;
        arr = new int[cap];
        m_size = 0;
    }
    ~MaxHeap(){
        delete[] arr;
    }

    void insertItem(int val);
    void remove_index(int idx);
    void heapify();
    int extract_max();

    int get_max() const;
    int get_size() const;
    bool isEmpty() const;

    void printHeap();
};

void MaxHeap::insertItem(int val){
    if (m_size < cap) arr[m_size++] = val;
    sift_up(m_size-1);
}

void MaxHeap::sift_up(int k){
    if (k == 0) return;

    int p = (k-1)/2;
    if (arr[p] < arr[k]){
        swap(arr[p], arr[k]);
        sift_up(p);
    }
}

void MaxHeap::sift_down (int k){
    int lc = 2*k + 1;
    int rc = 2*k + 2;
    int largest = k;
    if (lc < m_size && arr[lc] > arr[largest]) largest = lc;
    if (rc < m_size && arr[rc] > arr[largest]) largest = rc;

    if (largest != k){
        swap(arr[k], arr[largest]);
        sift_down(largest);
    }
}

void MaxHeap::heapify(){
    for (int i = (m_size-1)/2; i >= 0; i--){
        sift_down(i);
    }
}

void MaxHeap::remove_index(int idx){
    if (idx < 0 || idx >= m_size) return;

    for (int i = idx; i < m_size-1; i++){
        arr[i] = arr[i+1];
    }
    m_size--;
    heapify();
}

int MaxHeap::extract_max(){
    int m = arr[0];

    swap(arr[0], arr[--m_size]);
    sift_down(0);

    return m;
}

int MaxHeap::get_max() const{
    return arr[0];
}

int MaxHeap::get_size() const{
    return m_size;
}

bool MaxHeap::isEmpty() const{
    return m_size == 0;
}

void MaxHeap::printHeap(){
    for (int i = 0; i < m_size; i++){
        cout<<arr[i]<<' ';
    }
    cout<<'\n';
}

int main()
{
    int arr[] = {-1,0,1,2,5,10,6,3,-6,-1,-4};
    MaxHeap m;

    for (int i = 0; i < 11; i++){
        m.insertItem(arr[i]);
    }

    m.remove_index(6);

    cout<<m.extract_max()<<'\n';
    cout<<m.get_max()<<'\n';
    cout<<m.get_size()<<'\n';

    m.printHeap();

    return 0;
}
