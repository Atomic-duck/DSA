#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* parent;
    Node* left;
    Node* right;
    bool color; // true = red, black = false

    Node(int x, Node* p = nullptr){
        data = x;
        parent = p;
        left = nullptr;
        right = nullptr;
        color = 1;
    }

    ~Node(){
        if (left && !left->parent) delete left;
        if (right && !right->parent) delete right;
    }
};

class RBTree{
private:
    Node* root;
private:
    Node* initNULLLeave();

    Node* insertRec(Node* node, int key);
    void removeRec(Node* node, int key);

    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsert(Node* node);
    void fixRemove(Node* node);

    void printHelper(Node* node, string indent, bool last);
    void inorderRec(Node* node);
    void clearRec(Node* node);
public:
    RBTree(){
        root = nullptr;
    }

    ~RBTree(){
        clear();
    }

    void insert(int key);
    void remove(int key);
    Node* search(int key);
    void clear();

    void printTree();
    void printInorder();
};

Node* RBTree::initNULLLeave(){
    Node* p = new Node(0);
    p->color = 0;

    return p;
}

void RBTree::clearRec(Node* node){
    if (node == nullptr) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void RBTree::clear(){
    clearRec(root);
    root = nullptr;
}

void RBTree::printHelper(Node* node, string indent, bool last) {
    // print the tree structure on the screen
    if (node != nullptr) {
        cout<<indent;
        if (last) {
            if (node != root){
                cout<<"R====";
            }
            else cout<<"Root ";
            indent += "     ";
        } else {
            cout<<"L====";
            indent += "|    ";
        }

        cout<<node->data<<" : ";
        if (node != root && !node->parent) cout<<"N\n";
        else if (node->color) cout<<"R\n";
        else cout<<"B\n";

        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}

void RBTree::printTree(){
    printHelper(root, "", true);
}

void RBTree::inorderRec(Node* node){
    if (!node) return;
    inorderRec(node->left);
    cout<<node->data<<' ';
    inorderRec(node->right);
}

void RBTree::printInorder(){
    inorderRec(root);
    cout<<'\n';
}

void RBTree::rotateLeft(Node* node){
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
    if (node->right->parent) node->right->parent = node;
}

void RBTree::rotateRight(Node* node){
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
    if (node->left->parent) node->left->parent = node;
}

void RBTree::fixInsert(Node* node){
    if (!node) return;
    while(node->parent && node->parent->color){
        if (node->parent == node->parent->parent->right){
            Node* u = node->parent->parent->left;    // uncle
            if (u && u->color){
                u->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            }
            else{
                if (node == node->parent->left){
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotateLeft(node->parent->parent);
            }
        }
        else{
            Node* u = node->parent->parent->right;    // uncle
            if (u && u->color){
                u->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;

                node = node->parent->parent;
            }
            else{
                if (node == node->parent->right){
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotateRight(node->parent->parent);
            }
        }
    }

    root->color = 0;
}

Node* RBTree::insertRec(Node* node, int key){
    if (key < node->data){
        if (node->left->parent) return insertRec(node->left, key);
        node->left->color = 1;
        node->left->data = key;
        node->left->parent = node;
        node->left->left = initNULLLeave();
        node->left->right = initNULLLeave();
        return node->left;
    }
    else if (key > node->data){
        if (node->right->parent) return insertRec(node->right, key);
        node->right->color = 1;
        node->right->data = key;
        node->right->parent = node;
        node->right->left = initNULLLeave();
        node->right->right = initNULLLeave();
        return node->right;
    }

    return nullptr;
}

void RBTree::insert(int key){
    if (!root){
        root = new Node(key);
        root->color = false;
        root->left = initNULLLeave();
        root->right = initNULLLeave();
        return;
    }

    Node* p = insertRec(root, key);
    if(p) fixInsert(p);
}

void RBTree::fixRemove(Node* node){
    Node* s;
    while(node != root && node->color == 0){
        if (node == node->parent->left){
            s = node->parent->right;
            if (s->color == 1){
                node->parent->color = 1;
                s->color = 0;
                rotateLeft(node->parent);
                s = node->parent->right;
            }

            if (s->right->color == 0 && s->left->color == 0){
                s->color = 1;
                if (node->parent->color == 1){
                    node->parent->color = 0;
                    return;
                }
                node = node->parent;
            }
            else{
                if (s->left && s->left->color == 1){
                    s->left->color = 0;
                    s->color = 1;
                    rotateRight(s);
                    s = node->parent->right;
                }

                s->color = node->parent->color;
                s->right->color = 0;
                node->parent->color = 0;
                rotateLeft(node->parent);

                node = root;
            }
        }
        else{
            s = node->parent->left;
            if (s->color == 1){
                node->parent->color = 1;
                s->color = 0;
                rotateRight(node->parent);
                s = node->parent->left;
            }

            if (s->left->color == 0 && s->right->color == 0){
                s->color = 1;
                if (node->parent->color == 1){
                    node->parent->color = 0;
                    return;
                }
                node = node->parent;
            }
            else{
                if (s->left->color == 0){
                    s->right->color = 0;
                    s->color = 1;
                    rotateLeft(s);
                    s = node->parent->left;
                }

                s->color = node->parent->color;
                s->left->color = 0;
                node->parent->color = 0;
                rotateRight(node->parent);

                node = root;
            }
        }
    }

    node->color = 0;
}

void RBTree::removeRec(Node* node, int key){
    if (!node) return;

    if (key < node->data && node->left->parent) removeRec(node->left, key);
    else if (key > node->data && node->right->parent) removeRec(node->right, key);
    else{
        if (node->left->parent && node->right->parent){
            Node* temp = node->left;
            while(temp->right->parent) temp = temp->right;
            swap(node->data, temp->data);
            node = temp;
        }

        if (node->right->parent){
            if (node->color == 0) node->right->color = 0;

            if (node != root){
                if (node == node->parent->right) node->parent->right = node->right;
                else node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else{
                root = node->right;
                node->right->parent = nullptr;
                node->right = nullptr;
            }

        }
        else if (node->left->parent){
            if (node->color == 0) node->left->color = 0;

            if (node != root){
                if (node == node->parent->right) node->parent->right = node->left;
                else node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else{
                root = node->left;
                node->left->parent = nullptr;
                node->left = nullptr;
            }
        }
        else{
            if (node == root) root = nullptr;
            else{
                if (node->color == 0) fixRemove(node);
                if (node == node->parent->left) node->parent->left = initNULLLeave();
                else node->parent->right = initNULLLeave();
            }
        }

        delete node;
    }
}

void RBTree::remove(int key){
    removeRec(root, key);
}

int main()
{
    RBTree rb;
    char c;
    int x;

    rb.printTree();

    do{
        cin>>c;
        cin>>x;
        if (c == 'a') rb.insert(x);
        else if (c == 'd') rb.remove(x);
        rb.printTree();
    } while(c != 'e');

    return 0;
}
