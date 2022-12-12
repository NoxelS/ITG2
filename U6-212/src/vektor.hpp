
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
        end_ptr = data + n;
    }

    ~Vektor() {
        for (size_t i = 0; i < size_v; i++) data[i].~T();
        free(data);
    }

    size_t size() { return size_v; }
    size_t capacity() { return capacity_v; }

    void reserve(size_t n) {
        T* newData = (T*)malloc((size_v + n) * sizeof(T));
        for (size_t i = 0; i < size_v; i++) {
            newData[i] = data[i];
        };
        delete[] data;

        data = newData;
        begin_ptr = newData;
        end_ptr = newData + size_v + n;
        capacity_v = size_v + n;
    }

    void push_back(T element) {
        if (size_v >= capacity_v) {
            reserve(1);
        }
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

        bool operator==(const iterator& i) { return *actual == *i.acutal; };
        bool operator!=(const iterator& i) { return !(this == i); };
        T& operator*() { return *actual; };
        T* operator->() { return actual; };
    };

    iterator begin() { return iterator(begin_ptr); };
    iterator end() { return iterator(end_ptr); };
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vektor<T>& v) {
    for (auto a : v) {
        std::cout << a;
    }
    return os;
}