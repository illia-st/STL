#pragma once


#include <cstddef>
#include <iterator>

template<class blDataType>
class VectorIterator{
private:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = blDataType;
	using difference_type = std::ptrdiff_t;
	using pointer = blDataType*;
	using reference = blDataType&;
public:
	explicit VectorIterator(blDataType* ptr = nullptr) : m_ptr(ptr) {}
	VectorIterator(const VectorIterator<blDataType>& iterator) = default;
	~VectorIterator() = default;

	VectorIterator<blDataType>& operator=(const VectorIterator<blDataType>& rawIterator) = default;
	VectorIterator<blDataType>& operator=(blDataType * ptr) { m_ptr = ptr; return (*this); }

	operator bool() const
	{
		if (m_ptr)
			return true;
		else
			return false;
	}
	bool operator==(const VectorIterator<blDataType>& rawIterator) const { 
		return (m_ptr == rawIterator.getConstPtr());
	}
	bool operator!=(const VectorIterator<blDataType>& rawIterator)const { 
		return (m_ptr != rawIterator.getConstPtr()); 
	}
	VectorIterator<blDataType>& operator+=(const ptrdiff_t& movement) { m_ptr += movement; return (*this); }
	VectorIterator<blDataType>& operator-=(const ptrdiff_t& movement) { m_ptr -= movement; return (*this); }
	VectorIterator<blDataType>& operator++() { ++m_ptr; return (*this); }
	VectorIterator<blDataType>& operator--() { --m_ptr; return (*this); }
	VectorIterator<blDataType> operator++(int) { auto temp(*this); ++m_ptr; return temp; }
	VectorIterator<blDataType> operator--(int) { auto temp(*this); --m_ptr; return temp; }
	VectorIterator<blDataType> operator+(const ptrdiff_t& movement) { auto oldPtr = m_ptr; m_ptr += movement; auto temp(*this); m_ptr = oldPtr; return temp; }
	VectorIterator<blDataType> operator-(const ptrdiff_t& movement) { auto oldPtr = m_ptr; m_ptr -= movement; auto temp(*this); m_ptr = oldPtr; return temp; }

	ptrdiff_t operator-(const VectorIterator<blDataType>& rawIterator) { return std::distance(rawIterator.getPtr(), this->getPtr()); }

	blDataType& operator*() { return *m_ptr; }
	const blDataType& operator*() const { return *m_ptr; }
	blDataType* operator->() { return m_ptr; }

	blDataType* getPtr() const { return m_ptr; }
	const blDataType* getConstPtr() const { return m_ptr; }


protected:
	blDataType* m_ptr;
};