#include "../../include/server0/tcout.hpp"

std::ostream& tcout() {
  
  time_t now;
  time(&now);
  struct tm * timeinfo;
  timeinfo = localtime (&now);
  char buffer[10];
  strftime (buffer,10,"[%H:%M] ",timeinfo);
  setColors("light cyan");
  std::cout << buffer;
  setColors("reset");
  return std::cout;
}