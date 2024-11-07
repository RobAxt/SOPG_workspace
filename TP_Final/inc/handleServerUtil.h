#ifndef HANDLE_SERVER_UTIL_H
#define HANDLE_SERVER_UTIL_H

#include <stdio.h>

#define OK_RESPONSE 2
#define OK          1
#define NOT_FOUND   -1
#define ERROR       -2

int handleCommand(const char * cmnd, char* resp);

#endif // HANDLE_SERVER_UTIL_H
