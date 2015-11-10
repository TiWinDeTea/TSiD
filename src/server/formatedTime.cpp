#include "s_formatedTime.hpp"

std::string formatedTime() {
  
  time_t now;
  time(&now);
  struct tm * timeinfo;
  timeinfo = localtime (&now);
  char buffer[100];
  strftime (buffer,100,"%a %d/%m/%y %H:%M",timeinfo);
  return std::string(buffer);
}