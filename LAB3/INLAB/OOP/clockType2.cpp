class ClockType
{
public:
    void setTime(int, int, int);
    bool equalTime(const ClockType&) const;
    ClockType(int, int, int);
    ClockType();

private:
    int hr;
    int min;
    int sec;
};

// TODO
bool ClockType::equalTime(const ClockType& other) const {
    return (hr == other.hr && min == other.min && sec == other.sec);
}