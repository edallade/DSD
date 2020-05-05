
#include <sys/time.h>
struct mensaje
{
   unsigned int requestId;
   char arguments[36];
   struct timeval timestamp;
};
