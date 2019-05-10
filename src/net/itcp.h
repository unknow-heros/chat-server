#ifndef __NET_ITCP_H__
#define __NET_ITCP_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

/*创建一个TCP socket*/
int itcp_socket(int domain);

/*设置udp套接字为非阻塞*/
int itcp_set_nonblock(int udp_fd);

/*设置udp套接字为阻塞*/
int itcp_set_block(int udp_fd);

/*绑定IP地址和端口*/
int itcp_bind(int tcp_fd,struct sockaddr* addr,socklen_t addrlen);

/*连接UDP服务器*/
int itcp_connect(int tcp_fd, const struct sockaddr *addr,socklen_t addrlen);

/*开始监听tcp_fd 套接字*/
int itcp_listen(int tcp_fd);

/*创建sockaddr_in 结构体,用于绑定,连接或者发送数据*/
struct sockaddr_in * set_sockaddr_in(int domain,const char * ip, unsigned short port);

/*释放sockaddr_in结构体*/
void dis_sockaddr_in(struct sockaddr_in * addr);

/*创建sockaddr_in6 结构体,用于绑定,连接或者发送数据 用于IPV6*/
struct sockaddr_in6 * set_sockaddr_in6(int domain,const char * ip, unsigned short port);

/*创建sockaddr_in6结构体*/
void dis_sockaddr_in6(struct sockaddr_in6 * addr6);

/*开始监听tcp_fd 套接字*/
int itcp_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/*send data*/
ssize_t itcp_send(int sockfd, const void *buf, size_t len, int flags);

/*recv data*/
ssize_t itcp_recv(int sockfd, void *buf, size_t len, int flags);



#ifdef __cplusplus
}
#endif

#endif