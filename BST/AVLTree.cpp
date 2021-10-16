#include <iostream>

using namespace std;

enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

class Node
{
public:
	int data;
	Node *left;
	Node *right;
	BalanceValue balance;
	Node(const int &val)
	{
		data = val;
		left = right = NULL;
		balance = EH;
	}
};

class AVL
{
private:
	Node *root;
protected:
	Node *rotateRight(Node *&node);
	Node *rotateLeft(Node *&node);
	Node *leftBalance(Node *&node, bool &taller);
	Node *rightBalance(Node *&node, bool &taller);
	Node *removeLeftBalance(Node *&node, bool &shorter);
	Node *removeRightBalance(Node *&node, bool &shorter);
	//TODO Methods
	Node *insertRec(Node *&node, const int &value, bool &taller);
	Node *removeRec(Node *&node, const int &value, bool &shorter, bool &success);

	void printHelper(Node* node, string indent, bool last);
    void inorderRec(Node* node);
public:
	AVL()
	{
		this->root = NULL;
	}

	// TODO Methods
	void insert(const int &value);
	void remove(const int &value);

	void printTree();
    void printInorder();
};

Node *AVL::rotateRight(Node *&node)
{
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    return temp;
}


Node *AVL::rotateLeft(Node *&node)
{
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    return temp;
}

Node *AVL::rightBalance(Node *&node, bool &taller)
{
    if (node->right->balance == RH){
        node->right->balance = EH;
        node->balance = EH;
        node = rotateLeft(node);
    }
    else if (node->right->balance == LH){
        Node* leftChild = node->right->left;
        if (leftChild->balance == EH){
            node->right->balance = EH;
            node->balance = EH;
        }
        else if (leftChild->balance == RH){
            node->right->balance = EH;
            node->balance = LH;
        }
        else{
            node->right->balance = RH;
            node->balance = EH;
        }

        leftChild->balance = EH;
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
    }

    taller = false;
    return node;
}


Node *AVL::leftBalance(Node *&node, bool &taller)
{
	if (node->left->balance == LH){
        node->left->balance = EH;
        node->balance = EH;
        node = rotateRight(node);
    }
    else if (node->left->balance == RH){
        Node* rightChild = node->left->right;
        if (rightChild->balance == EH){
            node->left->balance = EH;
            node->balance = EH;
        }
        else if (rightChild->balance == RH){
            node->left->balance = LH;
            node->balance = EH;
        }
        else{
            node->left->balance = EH;
            node->balance = RH;
        }

        rightChild->balance = EH;
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
    }

    taller = false;

    return node;
}

Node *AVL::insertRec(Node *&node, const int &value, bool &taller)
{
	if (node == NULL){
        node = new Node(value);
        taller = true;
        return node;
    }

    if (value < node->data){
        node->left = insertRec(node->left, value, taller);

        if (taller){
            if (node->balance == EH) node->balance = LH;
            else if (node->balance == RH){
                node->balance = EH;
                taller = false;
            }
            else {
                node = leftBalance(node, taller);
            }
        }
    }
    else if (value > node->data){
        node->right = insertRec(node->right, value, taller);

        if (taller){
            if (node->balance == EH) node->balance = RH;
            else if (node->balance == LH){
                node->balance = EH;
                taller = false;
            }
            else
            {
                node = rightBalance(node, taller);
            }
        }
    }

    return node;
}


void AVL::insert(const int &value)
{
    bool taller = false;
    root = insertRec(root, value, taller);
}

Node *AVL::removeRec(Node *&node, const int &value, bool &shorter, bool &success)
{
	if (!node){
        shorter = false;
        success = false;
        return node;
	}

	if (value < node->data){
        node->left = removeRec(node->left, value, shorter, success);
        if (shorter){
            node = removeRightBalance(node, shorter);
        }
	}
	else if (value > node->data){
        node->right = removeRec(node->right, value, shorter, success);
        if (shorter){
            node = removeLeftBalance(node, shorter);
        }
	}
	else{
        Node* deleteNode = node;
        if (node->right == NULL){
            node = node->left;
            success = true;
            shorter = true;
            delete deleteNode;
        }
        else if (node->left == NULL){
            node = node->right;
            success = true;
            shorter = true;
            delete deleteNode;
        }
        else{
            Node* p = node->left;
            while(p->right){
                p = p->right;
            }

            node->data = p->data;
            node->left = removeRec(node->left, p->data, shorter, success);

            if (shorter){
                node = removeRightBalance(node, shorter);
            }
        }
	}

	return node;
}


void AVL::remove(const int &value)
{
    bool shorter = false;
    bool success = false;
	root = removeRec(root, value, shorter, success);
}


Node *AVL::removeRightBalance(Node *&node, bool &shorter)
{
	if (node->balance == LH){
        node->balance = EH;
	}
	else if (node->balance == EH){
        node->balance = RH;
        shorter = false;
	}
	else{
        if (node->right->balance == LH){
            Node* lc = node->right->left;
            if (lc->balance == LH){
                node->right->balance = RH;
                node->balance = EH;
            }
            else if (lc->balance == EH){
                node->right->balance = EH;
                node->balance = LH;
            }
            else{
                node->right->balance = EH;
                node->balance = LH;
            }

            lc->balance = EH;
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        else{
            if (node->right->balance == RH){
                node->right->balance = EH;
                node->balance = EH;
            }
            else{
                node->right->balance = LH;
                node->balance = RH;
                shorter = false;
            }
            node = rotateLeft(node);
        }
	}

	return node;
}


Node *AVL::removeLeftBalance(Node *&node, bool &shorter)
{
	if (node->balance == RH){
        node->balance = EH;
	}
	else if (node->balance == EH){
        node->balance = LH;
        shorter = false;
	}
	else{
        if (node->left->balance == RH){
            Node* rc = node->left->right;
            if (rc->balance == RH){
                node->left->balance = LH;
                node->balance = EH;
            }
            else if (rc->balance == EH){
                node->left->balance = EH;
                node->balance = RH;
            }
            else{
                node->left->balance = EH;
                node->balance = RH;
            }

            rc->balance = EH;
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        else{
            if (node->left->balance == LH){
                node->left->balance = EH;
                node->balance = EH;
            }
            else{
                node->left->balance = RH;
                node->balance = LH;
                shorter = false;
            }
            node = rotateRight(node);
        }
	}

	return node;
}

void AVL::printHelper(Node* node, string indent, bool last) {
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

void AVL::printTree(){
    printHelper(root, "", true);
    cout<<'\n';
}

void AVL::inorderRec(Node* node){
    if (!node) return;
    inorderRec(node->left);
    cout<<node->data<<' ';
    inorderRec(node->right);
}

void AVL::printInorder(){
    inorderRec(root);
    cout<<'\n';
}

int main()
{

    AVL a;
    int n;
    cin >> n;
    while (n > 0){
        int x;
        cin>>x;
        a.insert(x);
        a.printTree();
        n--;
    }

    cin >> n;
    while (n > 0){
        int x;
        cin>>x;
        a.remove(x);
        a.printTree();
        n--;
    }

    return 0;
}
