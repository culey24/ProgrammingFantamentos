#include <iostream>

using namespace std;

//TODO
class Coordinate{
    private:
        float x, y;
    public:
        Coordinate(float xval, float yval) : x(xval), y(yval) {}
        float getX() {return x;}
        float getY() {return y;}
        void setX(float val) {x = val;}
        void setY(float val) {y = val;}
        float distanceTo(const Coordinate& other) {
            return (float)(abs(x - other.x) + abs(y - other.y));
        }
};


int main () {
    float Xa, Xb, Ya, Yb;
    cin >> Xa >> Xb >> Ya >> Yb;
    Coordinate a(1,2);
    Coordinate b(0,1);
    cout << a.distanceTo(b) << endl;
    a.setX(Xa); a.setY(Ya);
    b.setX(Xb); b.setY(Yb);
    cout << abs(a.getX() - b.getX()) + abs(a.getY() - b.getY()) << endl;
    cout << a.distanceTo(b) << endl;
    cout << abs(Xa - Xb) + abs(Ya - Yb);
    return 0;
}