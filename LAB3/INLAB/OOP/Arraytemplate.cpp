#include <iostream>
using namespace std;

template <typename T>
class Array {
public:
    Array(int size, T initValue);
    ~Array();

    Array(const Array<T> & other) {
        size = other.size;
        delete[] p;
        p = new T[size];
        for (int i = 0; i < size; i++) {
            p[i] = other.p[i];
        }
        cout<<"Call copy constructor"<<endl;
    } // Copy constructor
    Array<T> & operator=(const Array<T> & other) {
        if (this == &other) return *this;
        delete[] p;
        size = other.size;
        p = new T[size];
        for (int i = 0; i < size; i++) {
            p[i] = other.p[i];
        }
        cout<<"Call assignment operator"<<endl;
        return *this;
    } // Copy assignment operator
    
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

