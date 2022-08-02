#pragma once
template<typename T>
struct ListNode{
    //I have to make the listnode to know about those the last last element
    ListNode* next;
    ListNode* prev;
    T val;
    ListNode(): next(nullptr), prev(nullptr), val(){}
    explicit ListNode(T val_): next(nullptr), prev(nullptr), val(val_){}
    ListNode(ListNode* next, ListNode* prev, T val_): next(next), prev(prev), val(val_) {}
    T& operator ++(){prev = prev->next; next = next->next; val = prev->next->val; return val;}
    T& operator --(){prev = prev->prev; next = next->prev; val = prev->next->val; return val;}
    T operator ++(int){const T t = next->prev->val; prev = prev->next; next = next->next; val = prev->next->val; return t;}
    T operator --(int){const T t = next->prev->val; prev = prev->prev; next = next->prev; val = prev->next->val; return t;}
    T& operator *(){return static_cast<T&&>(val);}
    const T& operator *() const {return val;}
};