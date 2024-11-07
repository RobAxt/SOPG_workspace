#include "handleServerUtil.h"

static int readFile(char* key, char* value);
static int writeFile(char* key, char* value);
static int deleteFile(char* key);

int handleCommand(char * cmnd, char* resp)
{
  printf("[INFO] Message Received: %s", cmnd);
  
  char *token = strtok(cmnd, DELIMS);
  int cmndAction = 0;
  int status = 0;  
  if(token != NULL)
  {
    printf("[INFO] Command received: %s\n", token);
    if( strcmp(token, GET_CMND) == 0)
      cmndAction = GET_CMND_IDX;
    if( strcmp(token, SET_CMND) == 0)
      cmndAction = SET_CMND_IDX;
    if( strcmp(token, DEL_CMND) == 0)
      cmndAction = DEL_CMND_IDX;
     
    switch(cmndAction)
    {
      case GET_CMND_IDX: 
      {
        char *key = strtok(NULL, DELIMS);
        printf("[INFO] Key received: %s\n", key);
        status = readFile(key, resp);
        break;
      }
      case SET_CMND_IDX:
      {
        char *key = strtok(NULL, DELIMS);
        char *value = strtok(NULL, DELIMS);
        printf("[INFO] Key-Value received: %s - %s\n", key, value);
        status = writeFile(key, value);
        break;
      }
      case DEL_CMND_IDX:
      {
        char *key = strtok(NULL, DELIMS);
        printf("[INFO] Key received: %s\n", key);
        status = deleteFile(key);
        break;
      }
      default:
        fprintf(stderr,"[ERROR] Bad Command\n");
        return ERROR;
    }
  }
  else
  {
    fprintf(stderr,"[ERROR] Bad Command\n");
    return ERROR;
  }
  return status;
}


static int readFile(char* key, char* value)
{
  if( key == NULL || value == NULL)
  {
    fprintf(stderr,"[ERROR] Bad Command\n");  
    return ERROR;
  }
  
  int fd = open(key, O_RDONLY);
  if (fd <= 0)
  {
   perror("[ERROR] Error opening file for reading");
   return NOT_FOUND;
  }

  ssize_t bytesRead = read(fd, value, BUFSIZE);
  
  if(bytesRead < 0)
  {
    perror("[ERROR] Error reading file");
    close(fd);
    return OK;
  }
  
  value[bytesRead] = '\n';
  value[bytesRead+1] = '\0';  
  
  close(fd);
  return OK_RESPONSE;  
}

static int writeFile(char* key, char* value)
{
  if( key == NULL || value == NULL)
  {
    fprintf(stderr,"[ERROR] Bad Command\n");  
    return ERROR;
  }
  
  int fd = open(key, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd <= 0)
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

static int deleteFile(char* key)
{
  if(key != NULL)
  {
    if(remove(key) == 0)
    {
      printf("[INFO] Deleted successfully\n");
      return OK;
    }
    else
    {
     fprintf(stderr,"[ERROR] Unable to delete the file\n");
     return OK;
    }
  }
  fprintf(stderr,"[ERROR] Bad Command\n");
  return ERROR;
}


