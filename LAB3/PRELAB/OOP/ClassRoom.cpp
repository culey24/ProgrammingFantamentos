class Room {
    private:
        double length, breadth, height;
    public:
        Room(double length, double breadth, double height);
        double calculateArea();
        double calculateVolume();
};

Room::Room(double length, double breadth, double height) : length(length), breadth(breadth), height(height) {}
double Room::calculateArea() {return length * breadth;}
double Room::calculateVolume() {return length*breadth*height;}