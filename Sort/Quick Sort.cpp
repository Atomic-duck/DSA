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

int medianOf3(int arr[], int l, int h){
    int m = l + (h-l)/2;
    int mx1, mx2, mx3;
    mx1 = max(max(arr[l], arr[h]), arr[m]);
    mx3 = min(min(arr[l], arr[h]), arr[m]);
    mx2 = arr[l] + arr[h] + arr[m] - mx1 - mx3;
// sort 3 median
    arr[l] = mx3;
    arr[m] = mx2;
    arr[h] = mx1;
// swap to set pivot is next of first element - arr[l] always < arr[l+1]-pivot
    swap(arr[l+1], arr[m]);
    return l+1;
}

int Partition(int arr[], int l, int h){
    int p = medianOf3(arr, l, h); // guaranteed worse case is n*log(n)
    int i = l + 1;
    int j = h;
    while (i <= j){
        while (arr[i] <= arr[p]) i++;
        while (arr[j] > arr[p]) j--;

        if (i < j){
            swap(arr[i++], arr[j--]);
        }
    }

    swap(arr[p], arr[j]);

    return j;
}

void QuickSort(int arr[], int l, int h){
    if (l + CUTOFF - 1 >= h){
        InsertionSort(arr, l, h);
        return;
    }

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
            swap(arr[i], arr[gt--]);
        }
        else if (arr[i] < v){
            swap(arr[i++], arr[lt++]);
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
        if (i > 0 && arr[i-1] > arr[i]) return -10;
    }
    cout<<'\n';

    return 0;
}
