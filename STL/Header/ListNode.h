#pragma once
template<typename T>
struct ListNode{
    //I have to make the listnode to know about those the last last element
private:
    ListNode* next;
    ListNode* prev;
    T val;
    template<typename J>
    friend void MoveNext(ListNode<J>*& ptr);
    template<typename J>
    friend void MovePrev(ListNode<J>*& ptr);
    template<typename J>
    friend J GetValue(const ListNode<J>* ptr);
    template<typename J>
    friend J& GetValue(ListNode<J>* ptr);
    template<typename J>
    friend J* GetNext(ListNode<J>* ptr);
    template<typename J>
    friend J* GetPrev(ListNode<J>* ptr);
public:
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
namespace {
    template<typename J>
    void MoveNext(ListNode<J>*& ptr) {ptr = ptr->next;}

    template<typename J>
    void MovePrev(ListNode<J>*& ptr) {ptr = ptr->prev;}

    template<typename J>
    J GetValue(const ListNode<J>* ptr)  {return ptr->val; }

    template<typename J>
    J& GetValue(ListNode<J>* ptr) {return ptr->val;}

    template<typename J>
    J* GetNext(ListNode<J>* ptr) {return ptr->next;}

    template<typename J>
    J* GetPrev(ListNode<J>* ptr) {return ptr->prev;}
}