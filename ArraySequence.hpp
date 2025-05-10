#ifndef ARRAYSEQUENCE_HPP
#define ARRAYSEQUENCE_HPP

#include <iostream>
#include "Sequence.hpp"
#include "DynamicArray.hpp"
using namespace std;


template <typename T>
class ArraySequence: public Sequence<T> {
    private:
        DynamicArray<T> *array;
    public:
        // Создание объекта
        ArraySequence();
        ~ArraySequence() override;
        ArraySequence(int size);
        ArraySequence(T* items, int count);
        ArraySequence(const DynamicArray<T> &other);
        
        // Декомпозиция
        int GetLength() const override;
        T GetFirst() const override;
        T GetLast() const override;
        T Get(int index) const override;
        Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;

        // Операции
        Sequence<T>* Append(T item) override;
        Sequence<T>* Prepend(T item) override;
        Sequence<T>* InsertAt(T item, int index) override;
        Sequence<T>* Concat(Sequence<T> *other) override;
};

// Создание объекта
template <typename T>
ArraySequence<T>::ArraySequence(): ArraySequence<T>::ArraySequence(0) {}

template <typename T>
ArraySequence<T>::~ArraySequence() {
    delete this->array;
}

template <typename T>
ArraySequence<T>::ArraySequence(int size) {
    this->array = new DynamicArray<T>(size);
}

template <typename T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    this->array = new DynamicArray<T>(items, count);
}

template <typename T>
ArraySequence<T>::ArraySequence(const DynamicArray<T> &other) {
    this->array = new DynamicArray<T>(other);
}

// Декомпозиция
template <typename T>
int ArraySequence<T>::GetLength() const {
    return this->array->GetSize();
}

template <typename T>
T ArraySequence<T>::GetFirst() const {
    return this->array->Get(0);
}

template <typename T>
T ArraySequence<T>::GetLast() const {
    return this->array->Get(this->array->GetSize()-1);
}

template <typename T>
T ArraySequence<T>::Get(int index) const {
    return this->array->Get(index);
}

template <typename T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (endIndex >= this->array->GetSize() || startIndex < 0 || endIndex <= startIndex) {
        throw out_of_range("The index is out of range!");
    }
    DynamicArray<T> *newArray = new DynamicArray<T>(endIndex-startIndex+1);
    for (int i = 0; i < endIndex-startIndex+1; i++) {
        newArray->Set(i, this->array->Get(i+startIndex));
    }
    return new ArraySequence<T>(*newArray);
}

// Операции
template <typename T>
Sequence<T>* ArraySequence<T>::Append(T item) {
    this->array->Resize(this->array->GetSize()+1);
    this->array->Set(this->array->GetSize()-1, item);
    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::Prepend(T item) {
    DynamicArray<T> *newArray = new DynamicArray<T>(this->array->GetSize()+1);
    newArray->Set(0, item);
    for (int i = 0; i < this->array->GetSize(); i++) {
        newArray->Set(i+1, this->array->Get(i));
    }
    this->array = newArray;
    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::InsertAt(T item, int index) {
    this->array->Set(index, item);
    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T> *other) {
    for (int i = 0; i < other->GetLength(); i++) {
        this->Append(other->Get(i));
    }
    return this;
}

#endif // ARRAYSEQUENCE_HPP
