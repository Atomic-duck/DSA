#include <iostream>
#include <queue>
using namespace std;

class nodeDetail {
public:
    int data;
    int min;
    int max;

    nodeDetail(int v, int m, int ma) : data{v}, min{m}, max{ma} { }
};

bool levelOrderIsOfBST(int arr[], int n){   //Check if the given array
    queue<nodeDetail*> q;                   // can represent Level Order Traversal of Binary Search Tree
    nodeDetail* p = new nodeDetail (arr[0], INT_MIN, INT_MAX);
    q.push(p);
    int i = 1;
    while(i < n && !q.empty()){
        p = q.front();
        q.pop();

        for (int j = 0; j < 2; j++){
            if (arr[i] > p->min && arr[i] < p->data){           // left child
                if (j == 1) break;          // two left child -> break
                nodeDetail* p_new = new nodeDetail (arr[i], p->min, p->data);
                q.push(p_new);
                i++;
            }
            else if (arr[i] < p->max && arr[i] > p->data){      // right child
                nodeDetail* p_new = new nodeDetail (arr[i], p->data, p->max);
                q.push(p_new);
                i++;
                break;
            }
        }
    }

    return i == n;
}

int main()
{
    int arr[] = {11, 8, 15, 5, 13, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (levelOrderIsOfBST(arr, n))
        cout << "Yes";
    else
        cout << "No";

    return 0;
}
