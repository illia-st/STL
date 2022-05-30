#pragma once
#include <memory>
#include <vector>
#include <initializer_list>


//дописати клас ітератор і можна тестувати
template<class T>
class Vector {
private:
	size_t capacity = 0;
	size_t size = 0;
	std::unique_ptr<T> arr;
public:
	Vector();
	Vector(size_t size_);
	Vector(const Vector<T>& copy);
	Vector(Vector<T>&& moved);
	Vector(const std::initializer_list<T>& items);
	T& operator[](size_t index);
	T operator[](size_t index) const;
	Vector<T>& operator = (const Vector<T>& copy);
	Vector<T>& operator = (Vector<T>&& moved);
	void Push_Back(const T& element);
	void Push_Back(T&& element);
	void Pop_Back();
	size_t Size() const;
	bool Empty() const;
};

template<class T>
Vector::Vector() {};
template<class T>
Vector::Vector(size_t size_) : capacity(size_), size(size_) {
	arr = std::make_unique<T[]>(capacity);
}
template<class T>
Vector::Vector(const Vector<T>& copy) : capacity(copy.capacity), size(copy.size) {
	*this = copy;
}
template<class T>
Vector::Vector(Vector<T>&& moved) : capacity(moved.capacity), size(moved.size) {
	*this = std::move(moved);
}
template<class T>
Vector::Vector(const std::initializer_list<T> items) : capacity(items.size()), size(items.size()) {
	arr = std::make_unique<T[]>(capacity);
	size_t i = 0;
	for (const auto& item : items) {
		arr.get()[i++] = item;
	}
}

template<class T>
T& Vector::operator[](size_t index) {
	if (index >= size) {
		throw std::out_of_range("The index is bigger than vector's size.");
	}
	return arr.get()[index];
}
template<class T>
T Vector::operator[] (size_t index) const {
	if (index >= size) {
		throw std::out_of_range("The index is bigger than vector's size.");
	}
	return arr.get()[index];
}

template<class T>
Vector<T>& operator = (const Vector& copy) {
	this->arr = std::make_unique<T[]>(this->capacity);
	for (size_t i = 0; i < this->size; ++i) {
		this->arr.get()[i] = copy.arr.get()[i];
	}
}
template<class T>
Vector<T>& operator = (Vector&& moved) {
	arr = std::unique_ptr<T>(moved.arr);
	moved.size = 0;
	moved.capacity = 0;
}

template<class T>
void Vector::Push_Back(const T& element) {
	if (size == capacity) {
		auto temp = std::make_unique<T[]>(this->capacity * 2);
		for (size_t i = 0; i < this->size; ++i) {
			temp.get()[i] = this->arr.get()[i];
		}
		this->arr = temp;
		this->capacity *= 2;
	}
	arr.get()[size++] = element;
}
template<class T>
void Vector::Push_Back(T&& element) {
	if (size == capacity) {
		auto temp = std::make_unique<T[]>(this->capacity * 2);
		for (size_t i = 0; i < this->size; ++i) {
			temp.get()[i] = this->arr.get()[i];
		}
		this->arr = temp;
		this->capacity *= 2;
	}
	arr.get()[size++] = element;
}
template<class T>
void Vector::Pop_Back() {
	--size;
}

template<class T>
size_t Vector::Size() const {
	return this->size;
}
template<class T>
size_t Vector::Empty() const {
	return this->size == 0;
}