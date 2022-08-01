#pragma once
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include "Abstract_List.h"
#include "ListNode.h"

template <class T>
class List: public Abstract_List<T>{
private:
    ListNode<T>* head = nullptr;
    ListNode<T>* end = nullptr;
    ListNode<T>* after_the_end {new ListNode<T>};
    size_t size = 0;
protected:
    void refresh_after_the_end();
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
    // at the end of loop t = copy.end
    while(t != copy.end){
        this->Push_Back(t->val);
        t = t->next;
    }
    this->Push_Back(t->val);
    this->refresh_after_the_end();
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
    this->end = moved.end;
    this->size = moved.size;
    moved.head = nullptr;
    moved.end = nullptr;
    moved.size = 0;

    this->refresh_after_the_end();
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
        //when size = 1 head = end head->next == end->next = nullptr
        this->Push_Back(el);
    }

    this->refresh_after_the_end();
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
        end = head;
    }
    //if there is the only element in our list
    else if(head->next == nullptr){
        end = new ListNode<T>(head, head, element);
        head->next = end;
        head->prev = end;
    }
    //if our size is > 1
    else{
        end->next = new ListNode(head, end, element);
        end = end->next;
        head->prev = end;
    }

    this->refresh_after_the_end();
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
        end = head;
    }
    //size > 0
    else {
        end->next = new ListNode<T>(head, end, element);
        head->prev = end->next;
        head = end->next;
    }

    this->refresh_after_the_end();
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
        this->refresh_after_the_end();
        return;
    }
    if(size == 1){
        delete head;
        size = 0;
        head = end = nullptr;
        this->refresh_after_the_end();
        return;
    }
    ListNode<T> * t = end;
    end = end->prev;
    end->next = t->next;
    delete t;
    --size;
    if(size == 1){
        head->next = head->prev = nullptr;
        end = head;
    }

    this->refresh_after_the_end();
}

template<class T>
void List<T>::Pop_Front() {
    if(size == 0){

        this->refresh_after_the_end();
        return;
    }
    if(size == 1){
        delete head;
        head = end = nullptr;
        size = 0;

        this->refresh_after_the_end();
        return;
    }
    ListNode<T> * t = head;
    head = head->next;
    head->prev = t->prev;
    delete t;
    --size;
    if(size == 1){
        head->next = head->prev = nullptr;
        end = head;
    }

    this->refresh_after_the_end();
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

    this->refresh_after_the_end();
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
        t = end;
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

    this->refresh_after_the_end();
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
        size_t counter {};
        while(counter != index){
            t = t->next;
            ++counter;
        }
    }
    else{
        t = end;
        size_t counter {this->size - 1};
        while(counter != index){
            t = t->prev;
            --counter;
        }
    }

    this->refresh_after_the_end();
    return t->val;
}

template<class T>
T List<T>::operator[](size_t index) const {
    return const_cast<List<T>*>(this)->operator[](index);
}

template<class T>
void List<T>::refresh_after_the_end() {
    after_the_end->prev = end;
    after_the_end->next = head;
}


