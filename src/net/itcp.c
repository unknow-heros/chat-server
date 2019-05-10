#include "itcp.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int itcp_socket(int domain)
{
    int tcp_fd = socket(domain,  SOCK_STREAM | SOCK_CLOEXEC,0);
    if( tcp_fd < 0 ) {
        return -1;
    }

    int yes = 1;
    int ret = setsockopt(tcp_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if(ret < 0 ){
        close(tcp_fd);
        return -2;
    }

    return tcp_fd;
}

/*设置udp套接字为非阻塞*/
int itcp_set_nonblock(int tcp_fd)
{
    int flags = fcntl(tcp_fd,F_GETFL,0);
    if(flags < 0) {
        return flags;
    }

    return fcntl(tcp_fd,F_SETFL,flags | O_NONBLOCK);

}

/*设置udp套接字为阻塞*/
int itcp_set_block(int tcp_fd)
{
     int flags = fcntl(tcp_fd,F_GETFL,0);
    if(flags < 0) {
        return flags;
    }

    return fcntl(tcp_fd,F_SETFL,flags &~ O_NONBLOCK);
}



int itcp_bind(int tcp_fd,struct sockaddr* addr,socklen_t addrlen)
{
    int ret = bind(tcp_fd,addr,addrlen);
    if( ret < 0) {
        return -1;
    };
    return 0;
}

int itcp_connect(int tcp_fd, const struct sockaddr *addr,socklen_t addrlen)
{
     return connect(tcp_fd,addr,addrlen);
}

struct sockaddr_in * set_sockaddr_in(int domain,const char * ip, unsigned short port)
{
    unsigned char buf[sizeof(struct in_addr)] = {0};
    int ret = inet_pton(domain, ip,buf);
    if(ret < 0 ) {
        return NULL;
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    memset(addr,0,sizeof(struct sockaddr_in));
    addr->sin_family        = domain;
    addr->sin_addr.s_addr   = inet_addr(ip);
    addr->sin_port          = htons(port);

    return addr;
}

void dis_sockaddr_in(struct sockaddr_in * addr)
{
    if( addr != NULL) {
        free(addr);
    }
}

struct sockaddr_in6 * set_sockaddr_in6(int domain,const char * ip, unsigned short port)
{
    unsigned char buf[sizeof(struct in6_addr)] = {0};
    int ret = inet_pton(domain, ip,buf);
    if(ret < 0 ) {
        return NULL;
    }

    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)malloc(sizeof(struct sockaddr_in6));
    memset(&addr6, 0, sizeof(addr6));

    addr6->sin6_family  = domain;
    inet_pton(domain,ip, &addr6->sin6_addr);  
    //addr6->sin6_addr    = in6addr_any
    addr6->sin6_port    = htons(port);

    return addr6;
}

void dis_sockaddr_in6(struct sockaddr_in6 * addr6)
{
    if(addr6 != NULL) {
        free(addr6);
    }
}




int itcp_accept(int tcp_fd, struct sockaddr *addr, socklen_t *addrlen)
{
    return accept(tcp_fd,addr,addrlen);
}


/*send data*/
ssize_t itcp_send(int sockfd, const void *buf, size_t len, int flags)
{
    return send(sockfd,buf,len,flags);
}

/*recv data*/
ssize_t itcp_recv(int sockfd, void *buf, size_t len, int flags)
{
    return recv(sockfd,buf,len,flags);
}