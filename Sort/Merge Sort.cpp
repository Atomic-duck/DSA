#include <iostream>

using namespace std;

int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

const int CUTOFF = 7;

void InsertionSort(int arr[], int l, int h){
    for (int i = l+1; i <= h; i++){
        int j = i;
        while(j >= l+1 && arr[j] < arr[j-1]){
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
}

void Merge(int arr[], int l, int h, int m){
    int i = l;
    int j = m + 1;
    int sarr[(size_t)(h - l) + 1];
    int idx = 0;
    while(idx < h - l + 1){
        if (i <= m && j <= h){
            if (arr[i] < arr[j]){
                sarr[idx] = arr[i];
                i++;
            }
            else{
                sarr[idx] = arr[j];
                j++;
            }
        }
        else if (i <= m){
            sarr[idx] = arr[i];
            i++;
        }
        else if (j <= h){
            sarr[idx] = arr[j];
            j++;
        }
        idx++;
    }

    idx = 0;
    for (int ii = l; ii <= h; ii++, idx++){
        arr[ii] = sarr[idx];
    }
}

void MergeSort(int arr[], int l, int h){
    if (l + CUTOFF - 1 >= h){           // Mergesort has too much overhead for tiny subarrays.
        InsertionSort(arr, l, h);      // Cutoff to insertion sort for = 7 items.
        return;
    }

    int m = l + (h-l)/2;
    MergeSort(arr, l, m);
    MergeSort(arr, m+1, h);
    if (arr[m] <= arr[m+1]) return; // Stop if already sorted
    Merge(arr, l, h, m);
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        arr[i] = getRandomNumber(-20, 20);
    }

    MergeSort(arr, 0, n-1);

    cout<<"Sorted: ";
    for (int i = 0; i < n; i++){
        cout<< arr[i]<<' ';
        if (i > 0 && arr[i-1] > arr[i]) return -1;
    }
    cout<<'\n';

    return 0;
}
