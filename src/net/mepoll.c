#include "mepoll.h"
#include <stdlib.h>



int m_epoll_create()
{
    return epoll_create1(0);
}


struct epoll_event * m_epoll_event_create( uint32_t events, epoll_data_t data)
{
    struct epoll_event * ev = (struct epoll_event *)calloc(sizeof(struct epoll_event),1);
    if( ev == NULL) {
        return NULL;
    }

    ev->data = data;
    ev->events = events;
    
    return ev;
}

void m_epoll_event_del(struct epoll_event * event)
{
    if(event != NULL ){
        free(event);
    }
}


int m_epoll_ctl_add(int epfd,int listenfd, struct epoll_event *event)
{
    return epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,event);
}


int m_epoll_ctl_mod(int epfd,int listenfd, struct epoll_event *event)
{
    return epoll_ctl(epfd,EPOLL_CTL_MOD,listenfd,event);
}


int m_epoll_ctl_del(int epfd,int listenfd, struct epoll_event *event)
{
    return epoll_ctl(epfd,EPOLL_CTL_DEL,listenfd,event);
}


int m_epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout)
{
    return epoll_wait(epfd,events,maxevents,timeout);
}