#pragma once
#include <iterator>
#include <string>
#include "ListNode.h"

template<typename BlDataType>
class ListIterator{
private:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = BlDataType;
    using const_value_type = const BlDataType;
    using difference_type = std::ptrdiff_t;
    using pointer = ListNode<BlDataType>*;
    using const_pointer = const ListNode<BlDataType>*;
    using reference = ListNode<BlDataType>&;
    using full_iterator_type = ListIterator<BlDataType>;
    using const_full_iterator_type = const ListIterator<BlDataType>;
public:
    explicit ListIterator(pointer ptr = nullptr): m_ptr{ptr}{}
    ListIterator(const full_iterator_type & iterator){
        *this = iterator;
    }
    ListIterator(full_iterator_type&& iterator) noexcept {
        *this = iterator;
    }
    ~ListIterator() = default;
    full_iterator_type& operator = (const full_iterator_type& iterator){
        m_ptr = iterator.m_ptr;
        return *this;
    }
    full_iterator_type& operator = (full_iterator_type&& iterator) noexcept{
        m_ptr = iterator.m_ptr;
        iterator.m_ptr = nullptr;
        return *this;
    }
    full_iterator_type& operator = (pointer ptr) noexcept{
        m_ptr = ptr;
        return *this;
    }
    bool operator == (const_full_iterator_type& rhs) const {return this->m_ptr == rhs.m_ptr;}
    bool operator != (const_full_iterator_type& rhs) const {return this->m_ptr != rhs.m_ptr;}
    bool operator < (const_full_iterator_type& rhs) const {return this->m_ptr->val < rhs.m_ptr->val;}
    full_iterator_type& operator++ (){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        m_ptr = m_ptr->next;
        return (*this);
    }
    full_iterator_type operator ++(int) {
        if(m_ptr == nullptr) {
            std::string error{"Your iterator is out of range, please check your code at line " +
                                                  std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        auto temp(*this);
        m_ptr = m_ptr->next;
        return temp;
    }
    full_iterator_type& operator --(){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        };
        m_ptr = m_ptr->prev;
        return *this;
    }
    full_iterator_type operator --(int){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        auto temp(*this);
        m_ptr = m_ptr->prev;
        return temp;
    }
    value_type& operator *(){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        return m_ptr->val;
    }
    const_value_type& operator *() const{
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        return m_ptr->val;
    }
    const SharedListNode<BlDataType>* operator -> () const{
        return new SharedListNode<BlDataType>*(m_ptr);
    }
    SharedListNode<BlDataType>* getPtr() const { return new SharedListNode<BlDataType>*(m_ptr);}
    const SharedListNode<BlDataType>* getConstPtr() const { return new SharedListNode<BlDataType>*(m_ptr); }



protected:
    pointer m_ptr;
};