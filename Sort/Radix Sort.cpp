#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void RadixSort(int arr[], int n){
    const int cs = 10;
    int *barr = new int[n];
    // Get max element
    int k = INT_MIN;
    for (int i = 0; i < n; i++){
        if (arr[i] > k) k = abs(arr[i]);
    }

    int d = log10(k) + 1; // d-digits k

    for (int i = 1; i <= d; i++){
        int carr[cs] = {0};
        // Counting number of each elements in arr
        for (int  j = 0; j < n; j++){
            int e = pow(10,i);
            int x = arr[j]%e / pow(10,i-1);
            carr[x] += 1;
        }
        // Counting number of elements are less than element arr[idx]
        for (int j = 1; j < cs; j++){
            carr[j] += carr[j-1];
        }
        // Sorting into B array
        for (int j = n-1; j >= 0; j--){ // Because carr[idx] (position in arr) decrease after each loop so that the value of element must decrease too => j = n-1 -> 0 to remain the stable of arr in previous loop
            int e = pow(10,i);
            int x = arr[j]%e / pow(10,i-1);
            barr[carr[x]-1] = arr[j];
            --carr[x];
        }

        for (int j = 0; j < n; j++){
            arr[j] = barr[j];
        }
    }

}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        arr[i] = getRandomNumber(0, 1000);
        cout<< arr[i]<<' ';
    }
    cout<<'\n';

    RadixSort(arr, n);

    cout<<"Sorted: ";
    for (int i = 0; i < n; i++){
        cout<< arr[i]<<' ';
    }

    return 0;
}
