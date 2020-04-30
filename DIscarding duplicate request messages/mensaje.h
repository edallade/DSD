

#define MAX_LEN_DATA 4000
struct mensaje
{
   int messageType;
    int requestId;
   int operationId;
   char arguments[sizeof(int)];
};
