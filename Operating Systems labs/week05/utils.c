#include "utils.h"

char flipChar(char c)
{
  if('a' <= c && c<= 'z')
    return 'z' - (c - 'a');
  else if('A' <= c && c<= 'Z')
    return 'Z' - (c - 'A');
  else if('0' <= c && c<= '9')
    return '9' - (c - '0');
}
