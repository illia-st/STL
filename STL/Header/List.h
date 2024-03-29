#pragma once
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include "Abstract_List.h"
#include "ListNode.h"
#include "ListIterator.h"

template <class T>
class List: public Abstract_List<T>{
private:
    using iterator = ListIterator<T>;
    using const_iterator = const ListIterator<T>;

    ListNode<T>* head = nullptr;
    ListNode<T>* tail = nullptr;
    size_t size = 0;
public:
    List();
    virtual ~List();
    List(const List<T>& copy);
    List(List<T>&& moved) noexcept;
    List(std::initializer_list<T> elements);
    List<T>& operator = (const List<T>& copy);
    List<T>& operator = (List<T>&& moved) noexcept;
    List<T>& operator = (std::initializer_list<T> elements);
    T& operator [](size_t index) override;
    T operator [](size_t index) const override;
    void Push_Back(const T& element) override;
    void Push_Back(T&& element) override;
    void Push_Front(const T& element) override;
    void Push_Front(T&& element) override;
    void Pop_Back() override;
    void Pop_Front() override;
    void Insert(size_t index, const T& value) override;
    [[nodiscard]] size_t Size() const override;
    [[nodiscard]] bool Empty() const override;
    void clear() override;
    iterator begin(){
        return iterator(head);
    }
    const_iterator begin() const{
        return const_iterator(head);
    }
    iterator end(){
        return iterator(nullptr);
    }
    const_iterator end() const{
        return const_iterator(nullptr);
    }

};
// zero parameters constructor
template<class T>
List<T>::List() = default;

template<class T>
List<T>::~List() {
    this->clear();
}

template<class T>
List<T>& List<T>::operator = (const List<T> &copy) {
    if(size > 0){// it would be better to add method clear and use it here and in the destructor
        this->clear();
    }
    ListNode<T>* t = copy.head;
    // at the tail of loop t = copy.tail
    while(t != copy.tail){
        this->Push_Back(t->val);
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
    if(size > 0){
        this->clear();
    }
    this->head = moved.head;
    this->tail = moved.tail;
    this->size = moved.size;
    moved.head = nullptr;
    moved.tail = nullptr;
    moved.size = 0;

    return *this;
}

template<class T>
List<T>::List(List<T> &&moved) noexcept{
    *this = std::move(moved);
}

template<class T>
List<T>& List<T>::operator = (std::initializer_list<T> elements) {
    if(size > 0){
        this->clear();
    }
    //this->Push_Back(1);
    for(const auto& el: elements){
        //when size = 1 head = tail head->next == tail->next = nullptr
        this->Push_Back(el);
    }
    return *this;
}

template<class T>
List<T>::List(std::initializer_list<T> elements) {
    *this = elements;
}

template<class T>
size_t List<T>::Size() const {
    return this->size;
}

template<class T>
void List<T>::Push_Back(const T &element) {
    if(size == 0){
        head = new ListNode<T>(element);
        tail = head;
    }
    //if there is the only element in our list
    else if(head->next == nullptr){
        tail = new ListNode<T>(nullptr, head, element);
        head->next = tail;
    }
    //if our size is > 1
    else{
        tail->next = new ListNode<T>(nullptr, tail, element);
        tail = tail->next;
    }
    ++size;
}

template<class T>
void List<T>::Push_Back(T &&element) {
    this->Push_Back(element);
}

template<class T>
void List<T>::Push_Front(const T &element) {
    //if out list is empty
    if(head == nullptr){
        head = new ListNode<T>(element);
        tail = head;
    }
    //size > 0
    else {
        head->prev = new ListNode<T>(head, nullptr, element);
        head = head->prev;
    }
    ++size;
}

template<class T>
void List<T>::Push_Front(T &&element) {
    this->Push_Front(element);
}

template<class T>
void List<T>::Pop_Back() {
    //if it works correctly, replace it by macro DELETER
    if(size == 0){
        return;
    }
    if(size == 1){
        delete head;
        size = 0;
        head = tail = nullptr;
        return;
    }
    ListNode<T> * t = tail;
    tail = tail->prev;
    tail->next = nullptr;
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
        head = tail = nullptr;
        size = 0;
        return;
    }
    ListNode<T> * t = head;
    head = head->next;
    head->prev = nullptr;
    delete t;
    --size;
}

template<class T>
[[nodiscard]] bool List<T>::Empty() const {
    return size == 0;
}
template<class T>
void List<T>::clear(){
    while(this->size > 0){
        this->Pop_Back();
    }

}

template<class T>
void List<T>::Insert(size_t index, const T &value) {
    if(index > this->size){
        std::string error = "Your index is bigger that size. Line number " + std::to_string(__LINE__)
                + " file " + __FILE__;
        throw std::out_of_range(error);
    }
    if(index == 0) {this->Push_Front(value); return;}
    if(index == this->size) {this->Push_Back(value); return;}


    //if direction == true we begin moving from the head
    bool direction = (this->size/2 > index);
    ListNode<T>* t;
    if(direction){
        t = head;
        size_t counter = 0;
        while(counter != index){
            t = t->next;
            ++counter;
        }
    }
    else{
        t = tail;
        size_t counter = this->size - 1;
        while(counter != index){
            t = t->prev;
            --counter;
        }
    }
    //now t pointer is on the correct position
    ListNode<T>* p = t->prev;
    p->next = new ListNode<T>(t, p, value);
    t->prev = p->next;
    ++size;

}

template<class T>
T& List<T>::operator[](size_t index) {
    if(index >= this->size){
        std::string error = "Your index is bigger that size. Line number " + std::to_string(__LINE__)
                            + " file " + __FILE__;
        throw std::out_of_range(error);
    }

    //if direction == true we begin moving from the head
    bool direction {this->size / 2 > index};
    ListNode<T>* t;
    if(direction){
        t = head;
        size_t counter = 0;
        while(counter != index){
            t->next;
            ++counter;
        }
    }
    else{
        t = tail;
        size_t counter = this->size - 1;
        while(counter != index){
            t = t->prev;
            --counter;
        }
    }

    return t->val;
}

template<class T>
T List<T>::operator[](size_t index) const {
    return const_cast<List<T>*>(this)->operator[](index);
}


