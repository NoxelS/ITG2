#include <iostream>
#include <type_traits>
template <class T>
class Vektor {
   private:
    T* begin_ptr;
    T* end_ptr;
    size_t size_v = 0;
    size_t capacity_v;

   public:
    T* data;

    Vektor(size_t n = 0) : capacity_v(n) {
        data = (T*)malloc(n * sizeof(T));
        begin_ptr = data;
        end_ptr = data;  // Because it is empty
    }

    ~Vektor() {
        /*
         * If we call the destructor on the elements we may encounter the problem that T is also a Vektor<T>.
         * In this case we need to call the destructor on the elements of the Vektor<T> elements.
         */
        if constexpr (std::is_same<T, Vektor<T>>::value) {
            for (size_t i = 0; i < size_v; i++) data[i].~Vektor<T>();
        } else {
            for (size_t i = 0; i < size_v; i++) data[i].~T();
        }
    }

    size_t size() const { return size_v; }
    size_t capacity() const { return capacity_v; }

    void reserve(size_t n) {
        /* Reserve memory and copy over elements */
        T* newData = (T*)malloc((size_v + n) * sizeof(T));
        for (size_t i = 0; i < size_v; i++) {
            newData[i] = data[i];
        };

        // Delete old data
        for (size_t i = 0; i < size_v; i++) data[i].~T();
        free(data);

        data = newData;

        // Set new pointers
        begin_ptr = data;
        end_ptr = data + size_v + n;

        // Set new capacity
        capacity_v = size_v + n;
    }

    void push_back(const T& element) {
        // Reserve space if needed
        if (size_v >= capacity_v) reserve(1);

        data[size_v] = element;
        ++size_v;
        end_ptr = data + size_v;
    }

    class iterator {
       private:
        T* actual;

       public:
        iterator(T* element = NULL) : actual(element){};

        iterator(const Vektor<T>& container) : actual(container.data) {}

        iterator& operator++() {
            if (actual) actual = actual + 1;
            return *this;
        };

        iterator operator++(int) {
            iterator temp = *this;
            ++*this;
            return temp;
        };

        bool operator==(const iterator& i) { return *actual == *i.actual; };
        bool operator!=(const iterator& i) { return *actual != *i.actual; };
        T& operator*() { return *actual; };
        T* operator->() { return actual; };
    };

    bool operator==(const Vektor<T>& v) {
        if (size_v != v.size_v) return false;
        for (size_t i = 0; i < size_v; i++) {
            if (data[i] != v.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vektor<T>& v) { return !(*this == v); }

    /**
     * Question: Why do we need to keep the begin_ptr and end_ptr? 
     *           We could just use data and data+size_v here right?
    */
    iterator begin() const { return iterator(begin_ptr); };
    iterator end() const { return iterator(end_ptr); };
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vektor<T>& v) {
    // You can use g++filt to get the real type names here
    std::cout << "v<" << typeid(T).name() << ", ";
    std::cout << v.size() << ">(";
    for (auto it = v.begin(); it != v.end(); it++) std::cout << *it << ", ";
    std::cout << ")";
    return os;
}