#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <functional>
#include "ICollection.hpp"
#include "Enumerator.hpp"


template <typename T>
class Sequence: public ICollection<T>, public IEnumerable<T> {
    public:
        virtual ~Sequence() = default;

        // ICollection
        T Get(size_t index) const override {return this->Get(static_cast<int>(index));}
        size_t GetCount() const override {return static_cast<size_t>(this->GetLength());}

        // IEnumerator + IEnumerable
        class Iterator: public IEnumerator<T> {
            private:
                const Sequence<T> *sequence;
                int index;
                bool mode;
            public:
                Iterator(const Sequence<T> *other) {
                    sequence = other;
                    index = 0;
                    mode = true;
                }
                T Current() override {
                    if (mode || index >= sequence->GetLength()) {
                        throw out_of_range("Неправильный индекс!");
                    }
                    return sequence->Get(index);
                }
                void Reset() override {
                    index = 0;
                    mode = true;
                }
                bool MoveNext() override {
                    if (mode) {
                        mode = false;
                        return sequence->GetLength() > 0;
                    }
                    index++;
                    return index < sequence->GetLength();
                }
        };
        IEnumerator<T>* GetEnumerator() override {
            return new Iterator(this);
        }

        // Декомпозиция
        virtual int GetLength() const = 0;
        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual T& operator[](int index) = 0;
        virtual const T& operator[](int index) const = 0;
        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

        // Операции
        virtual Sequence<T>* Append(T item) = 0;
        virtual Sequence<T>* Prepend(T item) = 0;
        virtual Sequence<T>* Remove(int index) = 0;
        virtual Sequence<T>* InsertAt(T item, int index) = 0;
        virtual Sequence<T>* PutAt(T item, int index) = 0;
        virtual Sequence<T>* Concat(Sequence<T> *other) = 0;
};

#endif // SEQUENCE_HPP
