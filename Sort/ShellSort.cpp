#include <iostream>

using namespace std;

class Complex{
public:
    friend bool operator== (const Complex& c1, const Complex& c2);
    friend bool operator!= (const Complex& c1, const Complex& c2);

    friend bool operator< (const Complex& c1, const Complex& c2);
    friend bool operator> (const Complex& c1, const Complex& c2);

    friend bool operator<= (const Complex& c1, const Complex& c2);
    friend bool operator>= (const Complex& c1, const Complex& c2);
};

class ShellSort   {
private:
    int* arr;
    int n;
public:
    ShellSort(int *increments, int lengthOfIncrements){
        arr = increments;
        n = lengthOfIncrements;
    }

    static void sortSegment(Complex *list, int length, int increment, int segment = 0){
        int k = increment;
        for (int i = segment + k; i < length; i += k){
            for (int j = i - k; j >= 0; j -= k){
                if (list[j] > list[j+k]) swap(list[j], list[j+k]);
                else break;
            }
        }

    }


    void sort(Complex *list, int length){
        for (int i = 0; i < n; i++){
            int k = arr[i];
            int segment = 0;
            while(segment < k){
                sortSegment(list, length, k, segment);
                segment = segment + 1;
            }
        }
    }
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
