#include "tcpServerUtil.h"

int setupTCPServerSocket(const int service)
{
  struct sockaddr_in serverAddr = {0};

  int passiveSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(passiveSocket < 0)
  {
    perror("listener: bind");
    return SOCKET_ERROR;
  }
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(service);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(passiveSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    close(passiveSocket);
    perror("[ERROR] Bind");
    return BIND_ERROR;
  }
  
  if (listen(passiveSocket, MAX_PENDING) < 0) 
  { 
    close(passiveSocket);
    perror("[ERROR] Listen");
    return LISTEN_ERROR;
  }
  
  return passiveSocket;
}

int acceptTCPConnection(int servSock)
{
  socklen_t addrLen = sizeof(struct sockaddr_in);
  struct sockaddr_in clientAddr;
  int activeSocket;
  
  printf("[INFO] Server: esperando una conexion...\n");
  if((activeSocket = accept(servSock, (struct sockaddr *)&clientAddr, &addrLen)) < 0)
  {
   perror("[WARN] accept");
   return ACCEPT_ERROR;
  }

  char ipClient[32];
  inet_ntop(AF_INET, &(clientAddr.sin_addr), ipClient, sizeof(ipClient));
  printf("[INFO] Server: conexion desde:  %s\n", ipClient);
  
  return activeSocket;
}

void handleTCPClient(int clntSocket)
{
  char buffer[BUFSIZE];
  char responseBuffer[BUFSIZE]; 
  int result;
  ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
  if (numBytesRcvd < 0)
  {
    perror("[ERROR] Recv() failed");
    close(clntSocket);
    return; //RECV_ERROR
  }

  buffer[numBytesRcvd] = '\0';   
  result = handleCommand(buffer, responseBuffer);
  
  switch(result)
  {
    case OK:
    case OK_RESPONSE:
      break;
    case NOT_FOUND:
      break;
    default:
  } 
  
  close(clntSocket);
  
}
