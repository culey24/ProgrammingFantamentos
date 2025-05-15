class ClockType
{
   public:
      ClockType(int, int, int); //constructor with parameters
      ClockType(); //default constructor
      
      void printTime() const;

   private:
      int hr;
      int min;
      int sec;
};

void ClockType::printTime() const { 
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

//TODO

ClockType::ClockType(int inhr, int inmin, int insec) {
    hr = (inhr >= 0 && inhr < 24) ? inhr : 0;
    min = (inmin >= 0 && inmin < 60) ? inmin : 0;
    sec = (insec >= 0 && insec < 60) ? insec : 0;
}
ClockType::ClockType() : hr(0), min(0), sec(0) {}