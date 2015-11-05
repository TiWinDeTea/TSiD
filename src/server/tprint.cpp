#include "s_tprint.hpp"

void tprint() {
  
  time_t now;
  time(&now);
  struct tm * timeinfo;
  timeinfo = localtime (&now);
  char buffer[10];
  strftime (buffer,10,"[%H:%M] ",timeinfo);
  setColors("light cyan");
  std::cout << buffer;
  setColors("reset");
}