#include <iostream>

template<typename T>
class DoubleList
{
public:
    DoubleList();//
    ~DoubleList();//
    void push_back(T);//
    void push_first(T);//
    void pop_back();//
    void pop_first();//
    void insert(T, int);//
    void erase(int);//
    void erase(int, int);
    T front();//
    T back();//
    void clear();//
    void resize(int);//
    int size();//
    void remove(T);//?
    void print();//

private:
    struct Node
    {
        Node* prev;
        T useful_data;
        Node* next;
    }*head, *tail;
    int m_size;
};

int main() {
    DoubleList<int> list;
    list.push_back(15);
    list.push_back(32);
    list.push_back(96);
    list.push_back(17);
    list.push_first(100);
    list.erase(1,2);
    //list.clear();
    std::cout << list.size() << std::endl;
    list.print();
    return 0;
}

//constructor
template<typename T>
DoubleList<T>::DoubleList() {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

//destructor
template<typename T>
DoubleList<T>::~DoubleList() {
    if (head) {
        while (head) {
            head = head->next;
        }
        tail = nullptr;
    }
}

//push back
template<typename T>
void DoubleList<T>::push_back(T value) {
    Node* tmp = new Node();
    tmp->useful_data = value;
    tmp->next = nullptr;
    tmp->prev = tail;
    if (!tail) {
        head = tmp;
        tail = tmp;
        ++m_size;
        return;
    }
    tail->next = tmp;
    tail = tmp;  
    ++m_size;
}

//pop back
template<typename T>
void DoubleList<T>::pop_back() {
    if (!head) {
        std::cout << "is empty";
        return;
    }
    if (head == tail) {
        Node* tmp = head;
        head = nullptr;
        tail = nullptr;
        delete tmp;
        --m_size;
        return;
    }
    Node* tmp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete tmp;
    tmp = nullptr;
    --m_size;
}

//pop first
template<typename T>
void DoubleList<T>::pop_first() {
    if (!head) {
        std::cout << "is empty\n";
        return;
    }
    if (head == tail) {
        Node* tmp = head;
        head = nullptr;
        tail = nullptr;
        delete tmp;
        --m_size;
        return;
    }
    Node* tmp = head;
    head = head->next;
    head->prev = nullptr;
    delete tmp;
    --m_size;
}

//push front
template<typename T>
void DoubleList<T>::push_first(T value) {
    Node* tmp = new Node;
    tmp->useful_data = value;
    if (!head) {
        head = tmp;
        tail = tmp;
        head->next = nullptr;
        ++m_size;
        return;
    }
    
    tmp->next = head;
    tmp->prev = nullptr;
    head = tmp;
    ++m_size;
}

//front
template<typename T>
T DoubleList<T>::front() {
    if (!head) {
        return INT16_MIN;
    }
    return head->useful_data;
}

//back
template<typename T>
T DoubleList<T>::back() {
    if (!tail) {
        return INT16_MIN;
    }
    return tail->useful_data;
}

//remove
template<typename T>
void DoubleList<T>::remove(T value) {
    Node* tmp = head;
    while (tmp)
    {
        if (tmp->useful_data == value) {
            if (tmp == head) {
                pop_first();
                return;
            }
            if (tmp == tail) {
                pop_back();
                return;
            }
             tmp->prev->next = tmp->next;
             tmp-> next -> prev = tmp->prev;
             Node* tmp1 = tmp;
             tmp = tmp-> next;
             delete tmp1;
             --m_size;
             return;
        }
        tmp = tmp->next;
    }
    if (tmp->useful_data != value) {
        std::cout << "not found\n";
        return;
    }
    --m_size;
}

///size
template<typename T>
int DoubleList<T>::size() {
    return m_size;
}

//insert
template<typename T>
void DoubleList<T>::insert(T value, int pos) {
    Node* tmp = head;
    if (pos < m_size) {
    for (int i = 0; i < pos; ++i) {
        tmp = tmp->next;
    }
   // std::cout << tmp->useful_data << std::endl;
    Node* tmp2 = tmp->next;
    Node* node = new Node;
    node->useful_data = value;
    tmp->next = node;
    node->next = tmp2;
    ++m_size;
    }
    //++m_size;
}

//erase
template<typename T>
void DoubleList<T>::erase(int index) {
    Node* tmp = head;
    if (m_size > index) {
        for (int i = 0; i < index; ++i) {
            tmp = tmp->next;
        }
        Node* tmp2 = tmp->prev;
        Node* tmp3 = tmp->next;
        
        delete tmp;
        tmp2->next = tmp3;
        tmp = nullptr;
        --m_size;
    }
}

//resize
template<typename T>
void DoubleList<T>::resize(int new_size) {
    if (new_size < m_size) {
        for (int i = new_size; i <= m_size; ++i) {
            pop_back();
        }
        m_size = new_size;
        return;
    }
    if (new_size > m_size) {
        for (int i = m_size; i <= new_size; ++i) {
            push_back(0);
        }
        m_size = new_size;
        return;
    }
}

//clear
template<typename T>
void DoubleList<T>::clear() {
    while (tail) {
        delete tail;
        tail = tail->prev;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

//erase i1,i2
template<typename T>
void DoubleList<T>::erase(int index1, int index2) {
    if (index1 == 0) {
        for (int i = index1; i <= index2; ++i) {
            pop_first();
        }
        return;
    }
    Node* tmp1 = head;
    Node* tmp2 = head;

    for (int i = 0; i < index1; ++i) {
        tmp1 = tmp1->next;
    }
    for (int i = 0; i < index1 - 1; ++i) {
        tmp2 = tmp2->next;
    }

    if (index1 < index2) {
        for (int i = 0; i < (index2 - index1) + 1; ++i) {
            Node* tmp = tmp1->next;
            delete tmp1;
            tmp1 = tmp;
            --m_size;
        }
    }

    if (tmp1) {
        tmp1->prev = tmp2;
        tmp2->next = tmp1;
    }
}

//print
template<typename T>
void DoubleList<T>::print() {
    Node* tmp = head;
    while (tmp)
    {
        std::cout << tmp->useful_data << "  ";
        tmp = tmp->next;
    } 
}