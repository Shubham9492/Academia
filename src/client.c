#include "../headers/headers.h"
#include "../headers/read_line.h"

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Client:- <ip-address> <port-number>\n");
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port_number = atoi(argv[2]);
    struct sockaddr_in server_address;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Client socket creation successful\n");

    memset (&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(ip_address);
    if(connect(sd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("Client and server connection successfully established\n");

    char send_bf[50], recv_bf[1024];
    memset(recv_bf, 0, sizeof(recv_bf));
    while(read(sd, recv_bf, sizeof(recv_bf)) > 0) {    
        write(STDOUT_FILENO, recv_bf, strlen(recv_bf));
        memset(send_bf, 0, sizeof(send_bf));
        read_line(STDIN_FILENO, send_bf, sizeof(send_bf));
        write(sd, send_bf, strlen(send_bf));
        memset(recv_bf, 0, sizeof(recv_bf));
    }

    close(sd);
    return 0;
}