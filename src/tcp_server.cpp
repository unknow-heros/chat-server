#include "net/itcp.h"

#include <iostream>
#include <string.h>

/*编译指令*/
/* g++ tcp_server.cpp net/itcp.c -o server -I./net/ */

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
    
    int ret = itcp_bind(tcp_fd, (struct sockaddr*)addr ,sizeof(struct sockaddr_in));
    if( ret < 0) {
        return -3;
    }

    ret = itcp_listen(tcp_fd);
    if( ret < 0) {
        return -4;
    }

    char hello[] = {"hello tcp"};
    char buf[4096] = {0};

    std::cout<< " tcp serer started " <<std::endl;
    while(1) 
    {      
        int cfd = itcp_accept(tcp_fd,NULL,NULL);
        if(cfd < 0) {
            continue;
        }

        std::cout << "来了一个TCP连接" << std::endl;
        ssize_t num =  itcp_send(cfd,hello,strlen(hello),0);
        
        std::cout << "给TCP 发送了:" << num <<std::endl;
        close(cfd);
    }

    dis_sockaddr_in(addr);
    close(tcp_fd);

    return 0;
}