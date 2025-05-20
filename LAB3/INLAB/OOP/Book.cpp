// string.h is included

class Book {
    char* name;
public:
    Book(const char*);
    ~Book();
    
    void display();
    char* getName();
};

void Book::display() {
    cout << "Book: " << this->name << endl;
}

char* Book::getName() {
    return this->name;
}

int getSize(const char* str) {
    if (!str) return 0;
    int count = 0;
    while (str[count] != '\0') count++;
    return count;
}

Book::Book(const char* str) {
    int size = getSize(str);
    name = new char[size + 1];
    for (int i = 0; i < size; i++) {
        name[i] = str[i];
    }
    name[size] = '\0';
}
Book::~Book() {
    delete[] name;
}
// TODO: Book and ~Book