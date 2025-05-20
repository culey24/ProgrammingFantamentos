template <typename T>
class Array {
public:
    Array(int size, T initValue);
    ~Array();

    void setAt(int idx, const T & value) {
        if (idx >= size || idx < 0) throw -1;
        p[idx] = value;
    }
    T getAt(int idx) {
        if (idx >= size|| idx < 0) throw -1;
        return p[idx];
    }
    
    void print();

private:
    int size;
    T * p;
};

template<typename T>
void Array<T>::print() {
    for (int i = 0; i < this->size; ++i) {
        cout << (i > 0 ? " " : "")
            << this->p[i];
    }
    cout << endl;
}

// TODO

