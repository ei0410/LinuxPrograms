#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    int sd;
    struct sockaddr_in addr;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port   = htons(22222);
    addr.sin_addr.s_addr = inet_addr("192.168.11.2");

    connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

    if (send(sd, "I am send process", 17, 0) < 0) {
        perror("send");
        return -1;
    }

    close(sd);
    return 0;
}
