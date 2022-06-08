#pragma once
#include <memory>
#include <vector>
#include <initializer_list>
#include "VectorIterator.h"


template<class T>
class Vector {
private:
	size_t capacity = 0;
	size_t size = 0;
	std::unique_ptr<T> arr;
	using iterator = VectorIterator<T>;
	using const_iterator = VectorIterator<const T>;
public:
	Vector();
	explicit Vector(size_t size_);
	Vector(const Vector<T>& copy);
	Vector(Vector<T>&& moved) noexcept;
	Vector(const std::initializer_list<T>& items);
	T& operator[](size_t index);
	T operator[](size_t index) const;
	Vector<T>& operator = (const Vector<T>& copy);
	Vector<T>& operator = (Vector<T>&& moved) noexcept;
	Vector<T>& operator = (std::initializer_list<T> copy);
	void Push_Back(const T& element);
	void Push_Back(T&& element);
	void Pop_Back();
	[[nodiscard]] size_t Size() const;
	[[nodiscard]] size_t Capacity() const;
	[[nodiscard]] bool Empty() const;

	iterator begin() { return iterator(&this->operator[](0)); }
	iterator end() { return iterator(&this->operator[](size)); }

	const_iterator cbegin() { return const_iterator(&this->operator[](0)); }
	const_iterator cend() { return const_iterator(&this->operator[](size)); }

};

template<class T>
Vector<T>::Vector() = default;
template<class T>
Vector<T>::Vector(size_t size_) : capacity(size_), size(size_) {
	arr.reset(new T[capacity]{});
}
template<class T>
Vector<T>::Vector(const Vector<T>& copy) : capacity(copy.capacity), size(copy.size) {
	*this = copy;
}
template<class T>
Vector<T>::Vector(Vector<T>&& moved) noexcept: capacity(moved.capacity), size(moved.size) {
	*this = std::move(moved);
}
template<class T>
Vector<T>::Vector(const std::initializer_list<T>& items) : capacity(items.size()), size(items.size()) {
	*this = items;
}

template<class T>
T& Vector<T>::operator[](size_t index){
	return arr.get()[index];
}
template<class T>
T Vector<T>::operator[] (size_t index) const {
	return arr.get()[index];
}

template<class T>
Vector<T>& Vector<T>::operator = (std::initializer_list<T> copy) {
	this->arr.release();
	arr.reset(new T[copy.size()]{});
	this->capacity = copy.size();
	this->size = copy.size();
	size_t i = 0;
	for (const auto& item : copy) {
		arr.get()[i++] = item;
	}

	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& copy) {
	this->arr.reset(new T[copy.capacity]{});
	this->capacity = copy.capacity;
	this->size = copy.size;
	for (size_t i = 0; i < this->size; ++i) {
		this->arr.get()[i] = copy.arr.get()[i];
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator = (Vector<T>&& moved) noexcept {
	this->arr.reset(moved.arr.release());
	this->capacity = moved.capacity;
	this->size = moved.size;
	moved.size = 0;
	moved.capacity = 0;

	return *this;
}

template<class T>
void Vector<T>::Push_Back(const T& element) {
	if (size == capacity) {
		std::unique_ptr<T> temp(new T[this->capacity * 2]{});
		for (size_t i = 0; i < this->size; ++i) {
			temp.get()[i] = this->arr.get()[i];
		}
		this->arr.reset(temp.release());
		this->capacity *= 2;
	}
	arr.get()[size++] = element;
}
template<class T>
void Vector<T>::Push_Back(T&& element) {
	if (size == capacity) {
		std::unique_ptr<T> temp(new T[this->capacity * 2]{});
		for (size_t i = 0; i < this->size; ++i) {
			temp.get()[i] = this->arr.get()[i];
		}
		this->arr.reset(temp.release());
		this->capacity *= 2;
	}
	arr.get()[size++] = element;
}
template<class T>
void Vector<T>::Pop_Back() {
	--size;
}

template<class T>
[[nodiscard]] size_t Vector<T>::Size() const {
	return this->size;
}

template<class T>
[[nodiscard]] size_t Vector<T>::Capacity() const {
	return this->capacity;
}
template<class T>
[[nodiscard]] bool Vector<T>::Empty() const {
	return this->size == 0;
}

