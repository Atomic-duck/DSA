#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

vector<int> findMaxAcrossSubarr(int *arr, int low, int high, int mid){
    int lsum = INT_MIN;
    int l;
    int sum = 0;
    for (int i = mid; i >= low; i--){
        sum = sum + arr[i];
        if (sum > lsum){
            lsum = sum;
            l = i;
        }
    }

    int rsum = INT_MIN;
    int h;
    sum = 0;
    for (int i = mid + 1; i <= high; i++){
        sum = sum + arr[i];
        if (sum > rsum){
            rsum = sum;
            h = i;
        }
    }

    return vector<int> {l, h, lsum+rsum};
}

vector<int> findMaxSubarr(int *arr, int low, int high){
    if (low == high) return vector<int> {low, high, arr[low]};

    int mid = low + (high-low)/2;
    vector<int> larr = findMaxSubarr(arr, low, mid);
    vector<int> rarr = findMaxSubarr(arr, mid+1, high);
    vector<int> across = findMaxAcrossSubarr(arr, low, high, mid);

    if (larr.back() > rarr.back() && larr.back() > across.back()) return larr;
    else if (rarr.back() > larr.back() && rarr.back() > across.back()) return rarr;
    else return across;
}

vector<int> findMaxSubarr_bf(int *arr, int n){
    vector<int> res (3, INT_MIN);
    for (int i = 1; i <= n; i++){
        int sum = 0;
        for (int j = 0; j < i; j++){
            sum += arr[j];
        }
        if (sum > res[2]){
            res[0] = 0;
            res[1] = i-1;
            res[2] = sum;
        }

        for (int j = i; j < n; j++){
            sum = sum - arr[j-i] + arr[j];
            if (sum > res[2]){
                res[0] = j-i+1;
                res[1] = j;
                res[2] = sum;
            }
        }
    }

    return res;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        arr[i] = getRandomNumber(-200, 200);
    }

    // Divide and Conquer method
    auto t1 = high_resolution_clock::now();

    vector<int> maxSubarr = findMaxSubarr(arr, 0, n-1);

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<microseconds>(t2-t1);

    cout<< maxSubarr[2]<<" : "<<ms_int.count()<<" microseconds"<<'\n';

    // Brute Force method

/*    vector<int> maxSubarr_bf = findMaxSubarr_bf(arr, n);

    auto t3 = high_resolution_clock::now();
    auto ms_int2 = duration_cast<microseconds>(t3-t2);

    cout<< maxSubarr_bf[2]<<" : "<<ms_int2.count()<<" microseconds"<<'\n';
*/
    return 0;
}
