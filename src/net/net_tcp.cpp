 #include "net_tcp.h"
 
net::net_tcp::net_tcp()
{

}

net::net_tcp::net_tcp(int fd)
{
    this->m_sockfd = fd;
}

net::net_tcp:: ~net_tcp()
{
    if(this->m_sockfd > 0){
        close(this->m_sockfd);
    } 
    if(this->m_addr != nullptr) {
        free(this->m_addr);
    }
}


bool net::net_tcp::init(int domain)
{
    int fd = itcp_socket(domain);
    if(fd < 0) {
        return false;
    }

    int ret = itcp_set_nonblock(fd);
    if(ret < 0) {
        close(fd);
        return false;
    }

    this->m_sockfd = fd;
    return true;
}

bool net::net_tcp::set_noblock()
{
    int ret = itcp_set_nonblock(this->m_sockfd);
    if(ret < 0) {
        return false;
    }
    return true;
}

int net::net_tcp::getfd()
{
    return this->m_sockfd;
}

bool net::net_tcp::net_connect(std::string &ip, unsigned short port)
{
    if(this->m_domain == AF_INET) {
        struct sockaddr_in * addr =  set_sockaddr_in(this->m_domain,ip.c_str(),port);
        if(addr == NULL) {
            return false;
        }

        int ret = itcp_connect(this->m_sockfd,(struct sockaddr*)addr,sizeof(struct sockaddr_in));
        if(ret < 0 ) {
            free(addr);
            return false;
        }

        this->m_addr = (struct sockaddr*)addr;
        return true;
    } else if(this->m_domain == AF_INET6 ){
        struct sockaddr_in6 * addr =  set_sockaddr_in6(this->m_domain,ip.c_str(),port);
        if(addr == NULL) {
            return false;
        }

        int ret = itcp_connect(this->m_sockfd,(struct sockaddr*)addr,sizeof(struct sockaddr_in));
        if(ret < 0 ) {
            free(addr);
            return false;
        }

        this->m_addr = (struct sockaddr*)addr;
        return true;
    } else {
        return false;
    }
}

bool net::net_tcp::net_bind(std::string &ip,unsigned short port)
{
    if(this->m_domain == AF_INET) {
        struct sockaddr_in * addr =  set_sockaddr_in(this->m_domain,ip.c_str(),port);
        if(addr == NULL) {
            return false;
        }

        int ret = itcp_bind(this->m_sockfd,(struct sockaddr*)addr,sizeof(struct sockaddr_in));
        if(ret < 0 ) {
            free(addr);
            return false;
        }

        this->m_addr = (struct sockaddr*)addr;
        return true;
    } else if(this->m_domain == AF_INET6 ){
        struct sockaddr_in6 * addr =  set_sockaddr_in6(this->m_domain,ip.c_str(),port);
        if(addr == NULL) {
            return false;
        }

        int ret = itcp_bind(this->m_sockfd,(struct sockaddr*)addr,sizeof(struct sockaddr_in));
        if(ret < 0 ) {
            free(addr);
            return false;
        }

        this->m_addr = (struct sockaddr*)addr;
        return true;
    } else {
        return false;
    }
}


ssize_t net::net_tcp::net_send(void * buf,size_t len, int flags)
{
    return itcp_send(this->m_sockfd,buf,len,flags);

}

ssize_t net::net_tcp::net_recv(void * buf,size_t len, int flags)
{
    return itcp_recv(this->m_sockfd,buf,len,flags);

}