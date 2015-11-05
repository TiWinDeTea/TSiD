#include "s_formatedTime.hpp"

std::string formatedTime() {
  
  time_t now;
  time(&now);
  struct tm * timeinfo;
  timeinfo = localtime (&now);
  char buffer[100];
  strftime (buffer,100,"%a %m/%d/%y %H:%M:%S",timeinfo);
  return std::string(buffer);
}