class ClockType
{
   public:
      void setTime(int, int, int);
      void printTime() const;
      void incrementHours() {
          hr++;
          if (hr == 24) hr = 0;
      }
      void incrementMinutes() {
          min++;
          if (min == 60) {
            min = 0;
            incrementHours();
          }
      }
      void incrementSeconds() {
          sec++;
          if (sec == 60) {
            sec = 0;
            incrementMinutes();
          }
      }
      ClockType(int, int, int);
      ClockType();

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

