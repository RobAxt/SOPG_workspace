#include "handleServerUtil.h"

typedef int (*action_t)(char* key, char* value, char* response);

static int readFile(char* key, char* value, char* response);
static int writeFile(char* key, char* value, char* response);
static int deleteFile(char* key, char* value, char* response);

typedef struct
{
  char* command;
  action_t action;
} command_t;

static command_t commands[] = {
    {"SET", writeFile},
    {"GET", readFile},
    {"DEL", deleteFile},
};

static const int MAX_CMND = sizeof(commands) / sizeof(command_t);

int handleCommand(char* cmnd, char* resp)
{
  printf("[INFO] Message Received: %s", cmnd);

  char* token = strtok(cmnd, DELIMS);
  char* key = strtok(NULL, DELIMS);
  char* value = strtok(NULL, DELIMS);
  int cmndIdx = 0;
  int status = ERROR;

  if(token != NULL)
  {
    printf("[INFO] Command received: %s\n", token);

    while(cmndIdx < MAX_CMND)
    {
      if(strcmp(token, commands[cmndIdx].command) == 0)
      {
        status = commands[cmndIdx].action(key, value, resp);
        break;
      }
      cmndIdx++;
    }

    if(cmndIdx == MAX_CMND)
    {
      fprintf(stderr, "[ERROR] Command Not Found\n");
      status = ERROR;
    }
  }
  else
  {
    fprintf(stderr, "[ERROR] Emtpy Command\n");
    status = ERROR;
  }
  return status;
}

static int readFile(char* key, char* value, char* response)
{
  if(key == NULL || response == NULL)
  {
    fprintf(stderr, "[ERROR] Bad Command Arguments\n");
    return ERROR;
  }

  printf("[INFO] Key received: %s\n", key);

  int fd = open(key, O_RDONLY);
  if(fd <= 0)
  {
    perror("[ERROR] Error opening file for reading");
    return NOT_FOUND;
  }

  ssize_t bytesRead = read(fd, response, BUFSIZE - 2);

  if(bytesRead < 0)
  {
    perror("[ERROR] Error reading file");
    close(fd);
    return OK;
  }

  if(bytesRead < BUFSIZE)
  {
    response[bytesRead] = '\n';
    response[bytesRead + 1] = '\0';
  }

  close(fd);
  return OK_RESPONSE;
}

static int writeFile(char* key, char* value, char* response)
{
  if(key == NULL || value == NULL)
  {
    fprintf(stderr, "[ERROR] Bad Command Arguments\n");
    return ERROR;
  }

  printf("[INFO] Key-Value received: %s - %s\n", key, value);

  int fd = open(key, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if(fd <= 0)
  {
    perror("[ERROR] Error opening file for writing");
    return NOT_FOUND;
  }

  ssize_t bytesWrite = write(fd, value, strlen(value));
  if(bytesWrite < 0)
  {
    perror("[ERROR] Error writing file");
    close(fd);
    return OK;
  }

  close(fd);
  return OK;
}

static int deleteFile(char* key, char* value, char* response)
{
  if(key != NULL)
  {
    printf("[INFO] Key received: %s\n", key);

    if(remove(key) == 0)
    {
      printf("[INFO] Deleted successfully\n");
      return OK;
    }
    else
    {
      perror("[ERROR] Unable to delete the file");
      return OK;
    }
  }
  fprintf(stderr, "[ERROR] Bad Command Arguments\n");
  return ERROR;
}
