#ifndef ICOLLECTION_HPP
#define ICOLLECTION_HPP

using namespace std;


template <typename T>
class ICollection {
public:
    virtual ~ICollection() = default;
    // Декомпозиция
    virtual T Get(size_t index) const = 0;
    virtual size_t GetCount() const = 0;
    // Копирующий конструктор
    virtual ICollection<T>* Copy() const = 0;
};

#endif // ICOLLECTION_HPP
