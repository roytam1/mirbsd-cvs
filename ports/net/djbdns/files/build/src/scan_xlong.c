#include "scan.h"
#include "fromhex.h"

unsigned int scan_xlong(const char *src,unsigned long *dest) {
  register const char *tmp=src;
  register int l=0;
  register unsigned char c;
  while ((c=fromhex(*tmp))<16) {
    l=(l<<4)+c;
    ++tmp;
  }
  *dest=l;
  return tmp-src;
}
