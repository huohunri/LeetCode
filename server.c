#include "client.h"

int main()
{
    int server_fifo_fd;
    int client_fifo_fd;

    int res;

    char client_fifo_name[NAME_SIZE];

    message msg;

    msg.client_pid = getpid();
    sprintf(client_fifo_name, CLIENT_FIFO_NAME, msg.client_pid);

    if (mkfifo(client_fifo_name, 0777) == -1)
    {
        fprintf(stderr, "Sorry, create client fifo failure!/n");
        exit(EXIT_FAILURE);
    }

    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1)
    {
        fprintf(stderr, "Sorry, open server fifo failure!/n");
        exit(EXIT_FAILURE);
    }

    sprintf(msg.data, "Hello from %d", msg.client_pid);
    printf("%d sent %s ", msg.client_pid, msg.data);
    write(server_fifo_fd, &msg, sizeof(msg));

    client_fifo_fd = open(client_fifo_name, O_RDONLY);
    if (client_fifo_fd == -1)
    {
        fprintf(stderr, "Sorry, client fifo open failure!/n");
        exit(EXIT_FAILURE);
    }

    res = read(client_fifo_fd, &msg, sizeof(msg));
    if (res > 0)
    {
        printf("received:%s/n", msg.data);
    }

    close(client_fifo_fd);
    close(server_fifo_fd);
    unlink(client_fifo_name);

    exit(EXIT_SUCCESS);
}