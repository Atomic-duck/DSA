#include <iostream>

using namespace std;

template <class T> class ListNode;
template <class T> class List_iterator;

template <class T>
class List{
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int m_size;
public:
    typedef List_iterator<T> iterator;

    List();
    List(const List<T>& l);
    ~List();

    int size() const {return m_size;}
    bool empty() const {return m_size == 0;}

    T& value_at(int index);
    T& value_n_from_end(int n);
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T& front();
    T& back();

    void insertAt(int index, const T& value);
    void eraseAt(int index);
    void insertAt(iterator pos, const T& value);
    void eraseAt(iterator pos);
    void reverseList();
    void remove_value(const T& value);

    iterator begin() const;
    iterator end() const;

    List<T> operator=(const List<T>& l);
};

template <class T>
List<T>::List(){
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

template <class T>
List<T>::List(const List<T>& l){
    head = nullptr;
    tail = nullptr;
    m_size = 0;

    for (ListNode<T>* p = l.head; p != nullptr; p = p->next){
        push_back(p->m_value);
    }
}

template <class T>
List<T>::~List(){
    ListNode<T>* cur = head;
    while(cur){
        ListNode<T>* p_deleted = cur;
        cur = cur->next;
        delete p_deleted;
    }
}

template <class T>
T& List<T>::value_at(int index){
    if (index < 0 || index >= m_size) throw out_of_range("invalid index");

    ListNode<T>* cur = head;
    for (int i = 0; i < index; i++){
        cur = cur->next;
    }

    return cur->m_value;
}

template <class T>
T& List<T>::value_n_from_end(int n){
    if (n < 1 || n > m_size) throw out_of_range("invalid index");

    ListNode<T>* res = head;
    ListNode<T>* cur = head;

    for (int i = 1; i < n; i++){
        cur = cur->next;
    }

    while(cur->next != nullptr){
        cur = cur->next;
        res = res->next;
    }

    return res->m_value;
}

template <class T>
void List<T>::push_front(const T& value){
    ListNode<T>* p_newNode = new ListNode<T>(value, head);
    head = p_newNode;
    if (m_size == 0) tail = p_newNode;
    m_size++;
}

template <class T>
void List<T>::push_back(const T& value){
    if (empty()) push_front(value);
    else{
        ListNode<T>* p_newNode = new ListNode<T>(value);

        tail->next = p_newNode;
        tail = p_newNode;
        m_size++;
    }
}

template <class T>
void List<T>::pop_front(){
    if (!empty()){
        ListNode<T>* p_deleted = head;
        head = head->next;
        if (head == nullptr) tail = head;

        delete p_deleted;
        m_size--;
    }

}

template <class T>
void List<T>::pop_back(){
    if (m_size == 1){
        return pop_front();
    }
    else if(m_size > 1) {
        ListNode<T>* p_preDeleted;

        while(p_preDeleted->next->next != nullptr){
            p_preDeleted = p_preDeleted->next;
        }

        p_preDeleted->next = nullptr;
        delete tail;
        tail = p_preDeleted;
        m_size--;
    }
}

template <class T>
T& List<T>::front(){
    if (head == nullptr) throw out_of_range("no element");
    return head->m_value;
}

template <class T>
T& List<T>::back(){
    if (tail == nullptr) throw out_of_range("no element");
    return tail->m_value;
}

template <class T>
void List<T>::insertAt(int index, const T& value){
    if (index == 0) push_front(value);
    else if (index > 0 && index < m_size){
        ListNode<T>* p_pre = head;
        for (int i = 1; i < index; i++){
            p_pre = p_pre->next;
        }

        ListNode<T>* p_newNode = new ListNode<T>(value, p_pre->next);
        p_pre->next = p_newNode;
        m_size++;
    }
}

template <class T>
void List<T>::eraseAt(int index){
    if (index == 0) pop_front();
    else if (index == m_size - 1) pop_back();
    else if (index > 0 && index < m_size - 1){
        ListNode<T>* p_preDeleted;
        ListNode<T>* p_deleted = head;
        for (int i = 0; i < index; i++){
            p_preDeleted = p_deleted;
            p_deleted = p_deleted->next;
        }

        p_preDeleted->next = p_deleted->next;
        delete p_deleted;
        m_size--;
    }
}

template <class T>
void List<T>::insertAt(iterator pos, const T& value){
    if (pos.current_node == head) push_front(value);
    else if (pos.current_node != nullptr){
        ListNode<T>* p_newNode = new ListNode<T> (value, pos.current_node);
        ListNode<T>* cur = head;
        while(cur->next != pos.current_node){
            cur = cur->next;
        }
        cur->next = p_newNode;
        m_size++;
    }
}

template <class T>
void List<T>::eraseAt(iterator pos){
    if (pos.current_node == head) pop_front();
    else if (pos.current_node == tail) pop_back();
    else if (pos.current_node != nullptr){
        ListNode<T>* cur = head;
        while(cur->next != pos.current_node){
            cur = cur->next;
        }

        cur->next = pos.current_node->next;
        delete pos.current_node;
        m_size--;
    }
}

template <class T>
void List<T>::reverseList(){
    if (m_size <= 1) return;

    ListNode<T>* p_aux = head->next->next;
    ListNode<T>* p_from = head->next;
    ListNode<T>* p_to = head;

    tail = head;
    while(p_from != nullptr){
        if (p_to == head) p_to->next = nullptr;

        p_from->next = p_to;
        p_to = p_from;
        p_from = p_aux;
        if (p_aux != nullptr) p_aux = p_aux->next;
    }

    head = p_to;
}

template <class T>
void List<T>::remove_value(const T& value){
    int i = 0;
    ListNode<T>* cur = head;
    while(cur && cur->m_value != value){
        cur = cur->next;
        i++;
    }

    eraseAt(i);
}

template <class T>
typename List<T>::iterator List<T>::begin() const{
    return iterator(head);
}

template <class T>
typename List<T>::iterator List<T>::end() const{
    return iterator(tail->next);
}

template <class T>
class ListNode{
private:
    T m_value;
    ListNode<T>* next;

    ListNode(const T& value, ListNode<T>* p = nullptr) : m_value{value}, next{p} {}

    friend class List<T>;
    friend class List_iterator<T>;
};

template <class T>
class List_iterator{
private:
    ListNode<T>* current_node;
public:
    typedef List_iterator<T> iterator;

    List_iterator() : current_node{nullptr}{ }
    List_iterator(ListNode<T>* source_node) : current_node{source_node}{ }
    List_iterator(List_iterator<T>* source_iterator) : current_node{source_iterator->current_node} { }

    T& operator*(); // dereferencing operator
    iterator& operator= (const iterator& rhs);
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;

    iterator& operator++(int);

    friend class List<T>;
};

template <class T>
T& List_iterator<T>::operator*(){
    return current_node->m_value;
}

template <class T>
typename List_iterator<T>::iterator& List_iterator<T>::operator= (const iterator& rhs){
    current_node = rhs.current_node;

    return *this;
}

template<class T>
typename List_iterator<T>::iterator& List_iterator<T>::operator++(int){
    current_node = current_node->next;
    return *this;
}

template<class T>
bool List_iterator<T>::operator==(const iterator & rhs) const
{
    return ( this->current_node == rhs.current_node );
}

template <class T>
bool List_iterator<T>::operator!=(const iterator & rhs) const
{
    return !( *this == rhs );
}

int main()
{
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.eraseAt(10);
    l.eraseAt(1);
    l.insertAt(0, 10);
    l.insertAt(1, 20);
    l.pop_back();
    l.pop_front();

    l.reverseList();
    l.remove_value(90);

    List<int>::iterator i;

    for (i = l.begin(); i != l.end(); i++){
        cout<<*i<<' ';
    }
    cout<<'\n';

//    cout<<l.front()<<' '<<l.back()<<' '<<l.value_at(3)<<' '<<l.value_n_from_end(3)<<'\n';

    return 0;
}
