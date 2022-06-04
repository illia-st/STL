#pragma once
#include <cstddef>
#include <initializer_list>
#include <algorithm>

template<class Type>
struct ListNode{
    Type* next;
    Type* prev;
    Type val;
    ListNode(): next(nullptr), prev(nullptr), val(){}
    explicit ListNode(Type val_): next(nullptr), prev(nullptr), val(val_){}
    ListNode(Type* next, Type* prev, Type val_): next(next), prev(prev), val(val_) {}
};

template <class T>
class List{
private:
    ListNode<T>* head = nullptr;
    ListNode<T>* end = nullptr;
    size_t size = 0;
public:
    List();
    virtual ~List();
    List(const List<T>& copy);
    List(List<T>&& moved) noexcept;
    List(const std::initializer_list<T> &elements);
    List<T>& operator = (const List<T>& copy);
    List<T>& operator = (List<T>&& moved) noexcept;
    List<T>& operator = (const std::initializer_list<T>& elements);
    void Push_Back(const T& element);
    void Push_Back(T&& element);
    void Push_Front(const T& element);
    void Push_Front(T&& element);
    void Pop_Back();
    void Pop_Front();
    [[nodiscard]] size_t Size() const;
    [[nodiscard]] bool Empty() const;
};
// zero parameters constructor
template<class T>
List<T>::List() = default;

template<class T>
List<T>::~List() {
    if(this->size > 1) {
        while (head->next != end) {
            ListNode<T> temp = head;
            head = head->next;
            delete temp;
        }
    }
    delete end;
    delete head;
    this->size = 0;
}

template<class T>
List<T>& List<T>::operator = (const List<T> &copy) {
    if(this != nullptr){
        this->~List();// actually I could make more complex implementation but I decided to make it easier
    }
    ListNode<T>* t = copy.head;
    // at the end of loop t = copy.end
    while(t != copy.end){
        T value = t->val;
        this->Push_Back(value);
        t = t->next;
    }
    this->Push_Back(t->val);
    return *this;
}

template<class T>
List<T>::List(const List<T> &copy) {
    *this = copy;
}

template<class T>
List<T>& List<T>::operator = (List<T> &&moved) noexcept {
    if(this != nullptr){
        this->~List();
    }
    this->head = moved.head;
    this->end = moved.end;
    this->size = moved.size;
    moved.head = nullptr;
    moved.end = nullptr;
    moved.size = 0;
    return *this;
}

template<class T>
List<T>::List(List<T> &&moved) noexcept{
    *this = std::move(moved);
}

template<class T>
List<T>& List<T>::operator = (const std::initializer_list<T>& elements) {
    if(this != nullptr){
        this->~List();
    }
    head = new ListNode<T>();
    end = new ListNode<T>();
    head->next = end;
    head->prev = end;
    end->next = head;
    end->prev = head;
    size = 0;
    for(const auto& el: elements){
        this->Push_Back(el);
    }
    //no need to initialize this->size because push_back increments it after each adding
    return *this;
}

template<class T>
List<T>::List(const std::initializer_list<T> &elements) {
    *this = elements;
}

template<class T>
size_t List<T>::Size() const {
    return this->size;
}

template<class T>
void List<T>::Push_Back(const T &element) {
    //if out list is empty
    if(head == nullptr){
        head = new ListNode(element);
        end = head;
    }
    //if there is the only element in our list
    else if(head->next == nullptr){
        end = new ListNode(head, head, element);
        head->next = end;
        head->prev = end;
    }
    //if our size is > 1
    else{
        end->next = new ListNode(head, end, element);
        end = end->next;
    }
    ++size;
}

template<class T>
void List<T>::Push_Back(T &&element) {
    this->Push_Back(std::move(element));
}

template<class T>
void List<T>::Push_Front(const T &element) {
    //if out list is empty
    if(head == nullptr){
        head = new ListNode(element);
        end = head;
    }
    //size > 0
    else {
        end->next = new ListNode(head, end, element);
        head = end->next;
    }
    ++size;
}

template<class T>
void List<T>::Push_Front(T &&element) {
    this->Push_Front(std::move(element));
}

template<class T>
void List<T>::Pop_Back() {
    //if it works correcntly, replace it by macro DELETER
    if(size == 0){
        return;
    }
    if(size == 1){
        delete head;
        delete end;
        size = 0;
        return;
    }
    ListNode<T> * t = end;
    end = end->prev;
    end->next = t->next;
    delete t;
    --size;
}

template<class T>
void List<T>::Pop_Front() {
    if(size == 0){
        return;
    }
    if(size == 1){
        delete head;
        delete end;
        size = 0;
        return;
    }
    ListNode<T> * t = head;
    head = head->next;
    head->prev = t->prev;
    delete t;
    --size;
}

template<class T>
[[nodiscard]] bool List<T>::Empty() const {
    return size == 0;
}


