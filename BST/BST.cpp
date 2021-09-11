#include <iostream>
#include <stack>
#include <unordered_set>

using namespace std;

class BST;

class Node{
private:
    int val;
    int m_count;
    Node* left;
    Node* right;
public:
    Node(int v, Node* l = nullptr, Node* r = nullptr)
    : val{v}, m_count{1}, left{l}, right{r} { }

    friend class BST;
};

class BST{
private:
    Node* root;
private:
    Node* search_node(int value);
    Node* delete_min(Node* p);
    Node* delete_value(Node* p, int val);
    void delete_tree(Node* p);

    int get_height(Node* p);
    int get_rank(Node* p, int val);
    int get_node_count(Node* p);

    Node* get_floor(Node* p, int val);
    Node* get_ceiling(Node* p, int val);
    Node* get_min(Node* p);
    Node* get_max(Node* p);

    void print_inorder(Node* p);
    Node* constructTreeUtil(int pre[], int* index, int key,
                        int min, int max, int size);
public:
    BST() : root{nullptr} { }
    ~BST(){
        delete_tree();
    }

    void insertNode(int value);
    void delete_tree();
    void delete_value(int val);
    void delete_min();
    void print_inorder();

    int get_node_count();
    int get_height(int val);
    int get_min();
    int get_max();
    int get_floor(int val);
    int get_ceiling(int val);
    int get_rank(int val);

    bool is_in_tree(int value);
    void constructTree(int pre[], int size);
};

void BST::insertNode(int value){
    Node* p_newNode = new Node(value);
    if (root == nullptr){
        root = p_newNode;
        return;
    }

    Node* p = root;
    while (true){
        if (value > p->val){        // in right-subtree
            p->m_count++;
            if (p->right == nullptr){   // arrived -> insert node
                p->right = p_newNode;
                return;
            }
            else p = p->right;          // not arrived -> go to next node
        }
        else if (value < p->val){   // in left-subtree
            p->m_count++;
            if (p->left == nullptr){
                p->left = p_newNode;
                return;
            }
            else p = p->left;
        }
        else return;
    }
}

void BST::delete_tree(Node* p){
    if (p == nullptr) return;
    if (p->left) delete_tree(p->left);
    if (p->right) delete_tree(p->right);
    delete p;
    p = nullptr;
}

void BST::delete_tree(){
    delete_tree(root);
}

Node* BST::delete_value(Node* p, int val){
    if (p == nullptr) return nullptr;
    if (val < p->val) p->left = delete_value(p->left, val);         // search for value
    else if (val > p->val) p->right = delete_value(p->right, val);  //
    else{
        if (p->right == nullptr){           // no right child
            Node* p_replace = p->left;
            delete p;
            return p_replace;
        }
        if (p->left == nullptr){            // no left child
            Node* p_replace = p->right;
            delete p;
            return p_replace;
        }

        Node* p_deleted = p;
        p = get_min(p_deleted->right);                  // get successor of deleted node

        Node* p_replace = new Node(p->val);                 // create new successor
        p_replace->right = delete_min(p_deleted->right);    // delete old successor and insert new right-subtree of deleted node to new successor
        p_replace->left = p_deleted->left;                  // insert left-subtree of deleted node to new successor

        delete p_deleted;

        p = p_replace;      // replace deleted node
    }

    p->m_count = 1 + get_node_count(p->left) + get_node_count(p->right); // update subtree counts

    return p;   // return to parent node
}

void BST::delete_value(int val){
    root = delete_value(root, val);
}

Node* BST::delete_min(Node* p){
    if (p == nullptr) return nullptr;
    if (p->left == nullptr){
        Node* p_right = p->right;
        delete p;

        return p_right;     // return to parent node
    }

    p->left = delete_min(p->left);
    p->m_count = 1 + get_node_count(p->left) + get_node_count(p->right);

    return p;       // return to parent node
}

void BST::delete_min(){
   root = delete_min(root);
}

void BST::print_inorder(Node* p){
    if (p == nullptr) return;
    print_inorder(p->left);
    cout<<p->val<<' ';
    print_inorder(p->right);
}

void BST::print_inorder(){
    print_inorder(root);
}

int BST::get_node_count(Node* p){
    if (p == nullptr) return 0;
    return p->m_count;
}

int BST::get_node_count(){
    return get_node_count(root);
}

int BST::get_height(Node* p){
    if (p == nullptr) return -1;

    return 1 + max(get_height(p->left), get_height(p->right));
}

int BST::get_height(int val){
    Node* p = search_node(val);
    if (p == nullptr) return 0;

    return get_height(p);
}

Node* BST::get_min(Node* p){
    if (p == nullptr) return nullptr;
    if (p->left != nullptr) return get_min(p->left);
    else return p;
}

int BST::get_min(){
    Node* p = get_min(root);
    if (p != nullptr) return p->val;
    else return INT_MIN;
}

Node* BST::get_max(Node* p){
    if (p == nullptr) return nullptr;
    if (p->right != nullptr) return get_max(p->right);
    else return p;
}

int BST::get_max(){
    Node* p = get_max(root);
    if (p != nullptr) return p->val;
    else return INT_MAX;
}

Node* BST::get_floor(Node* p, int val){
    if (p == nullptr) return nullptr;

    if (val == p->val) return p;

    if (val < p->val) return get_floor(p->left, val);   // desired node is in left-subtree

    // desired node is p or in right-subtree of p
    Node* p_floor = get_floor(p->right, val);   // check if there is a better node in right-subtree
    if (p_floor != nullptr) return p_floor;
    else return p;
}

int BST::get_floor(int val){
    Node* p = get_floor(root, val);
    if (p == nullptr) return INT_MIN;

    return p->val;
}

Node* BST::get_ceiling(Node* p, int val){
    if (p == nullptr) return nullptr;

    if (val == p->val) return p;

    if (val > p->val) return get_ceiling(p->right, val);

    Node* p_ceil = get_ceiling(p->left, val);
    if (p_ceil != nullptr) return p_ceil;
    else return p;
}

int BST::get_ceiling(int val){
    Node* p = get_ceiling(root, val);
    if (p == nullptr) return INT_MAX;

    return p->val;

}

int BST::get_rank(Node* p, int val){
    if (p == nullptr) return 0;
    if (val < p->val) return get_rank(p->left, val);
    if (val > p->val) return 1 + get_node_count(p->left) + get_rank(p->right, val);

    return get_node_count(p->left);
}

int BST::get_rank(int val){
    return get_rank(root, val);
}

Node* BST::search_node(int value){
    Node* p = root;

    while(p){
        if (value > p->val) p = p->right;
        else if (value < p->val) p = p->left;
        else return p;
    }

    return p;
}

bool BST::is_in_tree(int value){
    Node* p = search_node(value);
    return p != nullptr;
}

//
Node* BST::constructTreeUtil(int pre[], int* index, int key,
                        int min, int max, int size)
{
    if (*index == size - 1){
        (*index)++;
        return new Node(key);
    }

    Node* p = new Node(key);
    ++(*index);

    if (pre[*index] > min && pre[*index] < key){
        p->left = constructTreeUtil(pre, index, pre[*index], min, key, size);
    }

    if (*index < size && pre[*index] < max){
        p->right = constructTreeUtil(pre, index, pre[*index], key, max, size);
    }

    return p;

}

void BST::constructTree(int pre[], int size)
{
    delete_tree();

    int index = 0;
    root = constructTreeUtil(pre, &index, pre[0],
                             INT_MIN, INT_MAX, size);
}

int main()
{
    BST b;

    b.insertNode(0);
    b.insertNode(1);
    b.insertNode(-2);
    b.insertNode(3);
    b.insertNode(-4);
    b.insertNode(5);
    b.insertNode(2);
    b.insertNode(-10);
    b.insertNode(-5);
    b.insertNode(-1);

    b.delete_min();
    b.delete_value(1);
    cout<<b.get_ceiling(2)<<'\n';
    cout<<b.get_floor(-1)<<'\n';
    cout<<b.get_height(0)<<'\n';
    cout<<b.get_max()<<'\n';
    cout<<b.get_min()<<'\n';
    cout<<b.get_node_count()<<'\n';
    cout<<b.get_rank(3)<<'\n';
    cout<<b.is_in_tree(1)<<'\n';

    b.print_inorder();
    cout<<'\n';

    int pre[] = {100, 10, 3, 1, 8, 7, 22, 20, 12, 18, 13, 14, 16, 21, 36, 30, 27, 26 ,34, 64, 51, 48, 42, 41, 46, 44, 49, 58, 92, 67, 65, 71, 70, 83, 74, 72, 80, 77, 79, 90, 87, 93, 99, 98, 96, 1079, 695, 884, 823, 995};
    int size = sizeof(pre) / sizeof(pre[0]);

    b.constructTree(pre, size);

    b.print_inorder();
    cout<<'\n';

    return 0;
}
