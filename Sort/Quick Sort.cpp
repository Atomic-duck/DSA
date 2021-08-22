#include <iostream>

using namespace std;

int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

const int CUTOFF = 10;

void InsertionSort(int arr[], int l, int h){
    for (int i = l+1; i <= h; i++){
        int j = i;
        while(j >= l+1 && arr[j] < arr[j-1]){
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
}

int Partition(int arr[], int l, int h){
    int i = l;
    int j = h - 1;

    while(i < j){
        if (arr[i] > arr[h]){
            swap(arr[i], arr[j]);
            --j;
        }
        else ++i;
    }

    if (arr[i] > arr[h]){
        swap(arr[i], arr[h]);
        return i;
    }
    else{
        swap(arr[i+1], arr[h]);
        return i+1;
    }
}

void QuickSort(int arr[], int l, int h){
    if (l >= h) return;

    int p = Partition(arr, l, h);

    QuickSort(arr, l, p - 1);
    QuickSort(arr, p + 1, h);
}

void QuickSort_dbkey(int arr[], int l, int h){ // handle double keys efficently
    if (l + CUTOFF - 1 >= h){           // Quicksort has too much overhead for tiny subarrays.
        InsertionSort(arr, l, h);      // Cutoff to insertion sort for = 10 items.
        return;
    }

    int i = l;
    int lt = l, gt = h; // (lt <= idx <= gt) -> all arr[idx] are equal
    int v = arr[l]; // idx < lt -> arr[idx] < v && idx > gt -> arr[idx] > v

    while(i <= gt){
        if (arr[i] > v){
            swap(arr[i], arr[gt]);
            gt--;
        }
        else if (arr[i] < v){
            swap(arr[i], arr[lt]);
            lt++;
            i++;
        }
        else i++;
    }

    QuickSort_dbkey(arr, l, lt-1);
    QuickSort_dbkey(arr, gt + 1, h);
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        arr[i] = getRandomNumber(-200, 200);
    }

    QuickSort_dbkey(arr, 0, n-1);

    for (int i = 0; i < n; i++){
        cout<< arr[i]<<' ';
        if (i > 0 && arr[i-1] > arr[i]) return -1;
    }
    cout<<'\n';

    return 0;
}
