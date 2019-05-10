#include "net/itcp.h"

#include <iostream>
#include <string.h>


/*编译指令*/
/* g++ tcp_cli.cpp net/itcp.c -o cli -I./net/ */

int main() 
{
    int tcp_fd = itcp_socket(AF_INET);
    if(tcp_fd < 0) {
        return -1;
    }

    struct sockaddr_in * addr  =  set_sockaddr_in(AF_INET,"127.0.0.1",9999);
    if(addr == NULL ){
        return -2;
    }
    
    int ret = itcp_connect(tcp_fd, (struct sockaddr*)addr ,sizeof(struct sockaddr_in));
    if( ret < 0) {
        return -3;
    }

    char buf[4096] = {0};

    ssize_t num = itcp_recv(tcp_fd,buf,4096,0);

    std::cout <<"recv num:" << num  << std::endl;
    std::cout <<"recv data:" << buf << std::endl;


    dis_sockaddr_in(addr);
    close(tcp_fd);

    return 0;
}