#include "main.h"

int main()
{
  printf("[INFO] Hello World!\n");

  int servSock = setupTCPServerSocket(TCP_PORT);
  if(servSock < 0)
    return EXIT_FAILURE;

  while(true)
  {
    int clntSock = acceptTCPConnection(servSock);
    if(clntSock < 0)
    {
      perror("[WARN] Accept() failed");
    }
    else
    {
      handleTCPClient(clntSock);
    }
  }
  return EXIT_SUCCESS;
}
