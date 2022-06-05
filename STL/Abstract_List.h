#pragma once
template <class T>
class Abstract_List{
public:
    virtual void Push_Back(const T& element) = 0;
    virtual void Push_Back(T&& element) = 0;
    virtual void Push_Front(const T& element) = 0;
    virtual void Push_Front(T&& element) = 0;
    virtual void Pop_Back() = 0;
    virtual void Pop_Front() = 0;
    virtual void Insert(size_t index, const T& value) = 0;
    [[nodiscard]] virtual  size_t Size() const = 0;
    [[nodiscard]] virtual bool Empty() const = 0;
    [[nodiscard]] virtual void clear() = 0;
    virtual T& operator [](size_t index) = 0;
    virtual T operator [](size_t index) const = 0;
};
