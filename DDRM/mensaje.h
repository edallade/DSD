

#define MAX_LEN_DATA 4000
struct mensaje
{
   int messageType;
   unsigned int requestId;
   int operationId;
   char arguments[MAX_LEN_DATA];
};
