class ClockType
{
public:
    ClockType();
      
    void setTime(int, int, int);
    void printTime() const;

private:
    int hr;
    int min;
    int sec;
};

void ClockType::printTime() const
{
   if (hr < 10)
      cout << "0";
   cout << hr << ":";
   if (min < 10)
      cout << "0";
   cout << min << ":";
   if (sec < 10)
      cout << "0";
   cout << sec;
}

// TODO
void ClockType::setTime(int hour, int minute, int second) {
    hr = (hour >= 0 && hour < 24) ? hour : 0;
    min = (minute >= 0 && minute < 60) ? minute : 0;
    sec = (second >= 0 && second < 60) ? second : 0;
}