#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"
#include "ip6.h"
#include "error.h"

int socket_send6(int s,const char *buf,unsigned int len,const char ip[16],uint16 port,uint32 scope_id)
{
  struct sockaddr_in6 sa;

  byte_zero(&sa,sizeof sa);
  sa.sin6_family = AF_INET6;
  uint16_pack_big((char *) &sa.sin6_port,port);
  byte_copy((char *) &sa.sin6_addr,16,ip);
  return sendto(s,buf,len,0,(struct sockaddr *) &sa,sizeof sa);
}
