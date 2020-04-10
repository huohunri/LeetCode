#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_FIFO_NAME "/tmp/Linux/chaper12/server_fifo"
#define CLIENT_FIFO_NAME "/tmp/Linux/chaper12/client_%d_fifo"

#define BUFFER_SIZE PIPE_BUF
#define MESSAGE_SIZE 20
#define NAME_SIZE 256

typedef struct message
{
    pid_t client_pid;
    char data[MESSAGE_SIZE + 1];
}message;