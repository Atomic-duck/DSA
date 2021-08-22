#include <iostream>

using namespace std;

int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void heapify(int arr[], int n, int k){
    int largest = k;
    int lc = 2*k + 1;
    int rc = 2*k + 2;
    if (lc < n && arr[lc] > arr[largest]) largest = lc;
    if (rc < n && arr[rc] > arr[largest]) largest = rc;

    if (largest != k){
        swap(arr[k], arr[largest]);
        heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n){
    // Build head
    for (int i = (n-1)/2; i >= 0; i--){
        heapify(arr, n, i);
    }

    while(n > 1){
        swap(arr[0], arr[--n]);
        heapify(arr, n, 0);
    }
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        arr[i] = getRandomNumber(-200, 200);
    }

    HeapSort(arr, n);

    for (int i = 0; i < n; i++){
        cout<< arr[i]<<' ';
        if (i > 0 && arr[i-1] > arr[i]) return -1;
    }
    cout<<'\n';

    return 0;
}
