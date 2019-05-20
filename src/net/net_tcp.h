#include "itcp.h"

#include<string>


namespace net {


class net_tcp {
public:
    net_tcp();
    net_tcp(int fd);
    net_tcp(const net_tcp & ) = delete;
    ~net_tcp();

public:
    bool init(int domain);
    bool set_noblock();
    int  getfd();

    bool net_connect(std::string &ip, unsigned short port);
    bool net_bind(std::string &ip,unsigned short port);

    ssize_t net_send(void * buf,size_t len, int flags);
    ssize_t net_recv(void * buf,size_t len, int flags);

private:
    int m_sockfd = -1;
    int m_domain = -1;
    struct sockaddr* m_addr = nullptr;


};
} //namespace net