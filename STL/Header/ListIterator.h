#pragma once
#include <iterator>

template<typename BlDataType>
class ListIterator{
private:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = BlDataType;
    using difference_type = std::ptrdiff_t;
    using pointer = BlDataType*;
    using reference = BlDataType&;
    using full_iterator_type = ListIterator<BlDataType>;
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
    
protected:
    pointer m_ptr;
};