#ifndef LISTSEQUENCE_HPP
#define LISTSEQUENCE_HPP

#include <iostream>
#include "Sequence.hpp"
#include "LinkedList.hpp"
using namespace std;


template <typename T>
class ListSequence: public Sequence<T> {
    private:
        LinkedList<T> *list;
    public:
        // Создание объекта
        ListSequence();
        ~ListSequence() override;
        ListSequence(T* items, int count);
        ListSequence(const LinkedList<T> &other);

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
ListSequence<T>::ListSequence() {
    this->list = new LinkedList<T>();
}

template <typename T>
ListSequence<T>::~ListSequence() {
    delete this->list;
}

template <typename T>
ListSequence<T>::ListSequence(T* items, int count) {
    this->list = new LinkedList<T>(items, count);
}

template <typename T>
ListSequence<T>::ListSequence(const LinkedList<T> &other) {
    this->list = new LinkedList<T>(other);
}

// Декомпозиция
template <typename T>
int ListSequence<T>::GetLength() const {
    return this->list->GetLength();
}

template <typename T>
T ListSequence<T>::GetFirst() const {
    return this->list->GetFirst();
}

template <typename T>
T ListSequence<T>::GetLast() const {
    return this->list->GetLast();
}

template <typename T>
T ListSequence<T>::Get(int index) const {
    return this->list->Get(index);
}

template <typename T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    ListSequence<T> *newList = new ListSequence<T>(*this->list->GetSubList(startIndex, endIndex));
    return newList;
}

// Операции
template <typename T>
Sequence<T>* ListSequence<T>::Append(T item) {
    this->list->Append(item);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::Prepend(T item) {
    this->list->Prepend(item);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::InsertAt(T item, int index) {
    this->list->InsertAt(item, index);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T> *other) {
    for (int i = 0; i < other->GetLength(); i++) {
        this->Append(other->Get(i));
    }
    return this;
}

#endif // LISTSEQUENCE_HPP
