#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* parent;
    Node* left;
    Node* right;

    Node(int x){
        data = x;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

class SplayTree{
private:
    Node* root;
private:
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void splay(Node* node);
    Node* join(Node* lt, Node* rt);
    void split(Node* node, Node* &lt, Node* &rt);

    Node* insertRec(Node* node, int key);
    Node* searchRec(Node* node, int key);

    void printHelper(Node* node, string indent, bool last);
    void inorderRec(Node* node);
public:
    SplayTree(){
        root = nullptr;
    }

    void insert(int key);
    void remove(int key);
    Node* search(int key);

    void printTree();
    void printInorder();
};

void SplayTree::rotateLeft(Node* node){
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    if (node->parent == nullptr)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;

    temp->parent = node->parent;
    node->parent = temp;
    if (node->right) node->right->parent = node;
}

void SplayTree::rotateRight(Node* node){
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    if (node->parent == nullptr)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;

    temp->parent = node->parent;
    node->parent = temp;
    if (node->left) node->left->parent = node;
}

void SplayTree::splay(Node* node){

    while(node->parent){
        Node* pa = node->parent;
        Node* g_pa = node->parent->parent;

        if (g_pa == nullptr){
            if (node == pa->left){ // zig
                rotateRight(pa);
            }
            else{                           // zag
                rotateLeft(pa);
            }
        }
        else{
            if (node == pa->left && pa == g_pa->left){  // zig-zig
                rotateRight(g_pa);
                rotateRight(pa);
            }
            else if (node == pa->right && pa == g_pa->right){   // zag-zag
                rotateLeft(g_pa);
                rotateLeft(pa);
            }
            else if (node == pa->left && pa == g_pa->right){    // zag-zig
                rotateRight(pa);
                rotateLeft(g_pa);
            }
            else{    // zig-zag
                rotateLeft(pa);
                rotateRight(g_pa);
            }
        }
    }
}

Node* SplayTree::join(Node* lt, Node* rt){
    if (lt == nullptr) return rt;
    if (rt == nullptr) return lt;

    // find largest node
    Node* p_max = lt;
    while(p_max->right) p_max = p_max->right;

    // moves the largest node to the root node
    splay(p_max);
    p_max->right = rt;
    rt->parent = p_max;

    return p_max;
}

void SplayTree::split(Node* node, Node* &lt, Node* &rt){
    splay(node);
    lt = node;
    rt = node->right;

    node->right = nullptr;
    if (rt) rt->parent = nullptr;
}

Node* SplayTree::searchRec(Node* node, int key){
    if (key < node->data && node->left){
        return searchRec(node->left, key);
    }
    else if (key > node->data && node->right){
        return searchRec(node->right, key);
    }

    return node;
}

Node* SplayTree::search(int key){
    if (!root) return nullptr;
    Node* p = searchRec(root, key);
    splay(p);

    return p;
}

Node* SplayTree::insertRec(Node* node, int key){
    if (key < node->data){
        if (node->left) return insertRec(node->left, key);

        node->left = new Node(key);
        node->left->parent = node;

        return node->left;
    }
    else if (key > node->data){
        if (node->right) return insertRec(node->right, key);

        node->right = new Node(key);
        node->right->parent = node;

        return node->right;
    }

    return node;
}

void SplayTree::insert(int key){
    if (!root) root = new Node(key);
    else{
        Node* p = insertRec(root, key);
        splay(p);
    }
}

void SplayTree::remove(int key){
    if (!root) return;

    Node* p = search(key);

    if (p->data == key){
        Node* lt;
        Node* rt;
        split(p, lt, rt);

        if (lt->left) lt->left->parent = nullptr;
        root = join(lt->left, rt);
        delete p;
    }
    else splay(p);
}

void SplayTree::printHelper(Node* node, string indent, bool last) {
    // print the tree structure on the screen
    if (node != nullptr) {
        cout<<indent;
        if (last) {
            if (node != root){
                cout<<"R----";
            }
            else cout<<"Root ";
            indent += "     ";
        } else {
            cout<<"L----";
            indent += "|    ";
        }

        cout<<node->data<<endl;

        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}

void SplayTree::printTree(){
    printHelper(root, "", true);
}

void SplayTree::inorderRec(Node* node){
    if (!node) return;
    inorderRec(node->left);
    cout<<node->data<<' ';
    inorderRec(node->right);
}

void SplayTree::printInorder(){
    inorderRec(root);
    cout<<'\n';
}

int main()
{
    SplayTree t;
    int n;
    cin >> n;
    while(n > 0){
        int x;
        cin>> x;
        t.insert(x);
        t.printTree();
        n--;
    }

    cin >> n;
    while(n > 0){
        int x;
        cin>> x;
        t.remove(x);
        t.printTree();
        n--;
    }

    return 0;
}
