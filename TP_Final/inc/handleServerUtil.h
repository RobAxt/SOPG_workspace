#ifndef HANDLE_SERVER_UTIL_H
#define HANDLE_SERVER_UTIL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "tcpServerUtil.h"

#define DELIMS       " \n\r"
#define MAX_TOKENS   3
#define GET_CMND     "GET"
#define GET_CMND_IDX 1
#define SET_CMND     "SET"
#define SET_CMND_IDX 2
#define DEL_CMND     "DEL"
#define DEL_CMND_IDX 3

#define OK_RESPONSE  2
#define OK           1
#define NOT_FOUND   -1
#define ERROR       -2

int handleCommand(char * cmnd, char* resp);

#endif // HANDLE_SERVER_UTIL_H
