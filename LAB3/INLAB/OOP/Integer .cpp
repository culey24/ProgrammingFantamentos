#include<iostream>
using namespace std;

// TODO
class Integer {
    private:
        int val;
    public:
        Integer(int n) : val(n) {}
        Integer(Integer* integer) {
            val = integer->val;
        }
        Integer operator+(const Integer& other) {
            return Integer(val + other.val);
        }
        Integer operator+(int plus) {
            return Integer(val + plus);
        }
        void print();
};

void Integer::print() {
    cout << this->val << endl;
}

int main() {
    int x, y, z;
    cin >> x >> y >> z;
    Integer a(x);
    Integer b(y);
    Integer* t = new Integer(z);
    Integer c(t);
    
    a.print(); b.print();
    (a + b + c + 4).print();
    
    delete t;
    return 0;
}