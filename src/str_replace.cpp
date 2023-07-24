#include <string>
#include <cstring>
int str_replace_internal(char * buffer, uint64_t buffer_len, std::string str, uint64_t pos, uint64_t len, uint64_t target)
{
  str.replace(pos, len, std::to_string(target));
  if(str.size() > buffer_len - 1)   // NULL ptr
  {
    return -1;
  }
  else
  {
    strcpy(buffer, str.c_str());
    return 0;
  }
}
extern "C" int str_replace(char * buffer, uint64_t buffer_len, char * str, uint64_t pos, uint64_t len, uint64_t target)
{
  return str_replace_internal(buffer, buffer_len, str, pos, len, target);
}
