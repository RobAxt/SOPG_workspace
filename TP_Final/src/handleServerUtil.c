#include "handleServerUtil.h"

int handleCommand(const char * cmnd, char* resp)
{
  printf("[INFO] Message Received: %s", cmnd);
  return OK;
}
