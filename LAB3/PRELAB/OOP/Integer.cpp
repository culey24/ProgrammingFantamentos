class Integer {
    private:
        int val;
    public:
        Integer(int value);
        void setValue(int value);
        int getValue() const;
};

Integer::Integer(int value) : val(value) {}

void Integer::setValue(int value) {val = value;}

int Integer::getValue() const {return val;} 