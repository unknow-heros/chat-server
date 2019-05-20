#include "net_tcp.h"


namespace net {

class net_epoll {
public:
    net_epoll();
    net_epoll(int sockfd);
    net_epoll(const net_tcp * ntcp);
    net_epoll(const net_epoll &) = delete;
    ~net_epoll();

public:
    bool net_add;
    bool net_del;
    int net_wait();





};

} //namespace net