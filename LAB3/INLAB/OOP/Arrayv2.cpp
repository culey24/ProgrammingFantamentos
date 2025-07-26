template <typename T>
class Array {
public:
    Array(int size, T initValue);
    ~Array();
    void print();
    
    Array(const Array<T> & other); // Copy Constructor
    
private:
    int size;
    T * p;
};

template<typename T>
void Array<T>::print() {
    for (int i = 0; i < this->size; ++i) {
        cout << (i > 0 ? " " : "") << this->p[i];
    }
    cout << endl;
}

// TODO
template<typename T>
Array<T>::Array(const Array<T> & other) {
    size = other.size;
    p = new T[size];
    for (int i = 0; i < size; i++) {
        p[i] = other.p[i];
    }
}
