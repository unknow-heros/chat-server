#ifndef __M_EPOLL_H__
#define __M_EPOLL_H__

#include <sys/epoll.h>



#ifdef __cplusplus
extern "C" {
#endif

/*创建一个EPOLL FD*/
int m_epoll_create();

/*创建一个epoll_event*/
struct epoll_event * m_epoll_event_create( uint32_t events, epoll_data_t data);

/*释放一个epoll_event*/
void m_epoll_event_del(struct epoll_event * event);

/*添加一个fd,并监听设置的event*/
int m_epoll_ctl_add(int epfd,int listenfd, struct epoll_event *event);

/*修改一个fd 监听的事件*/
int m_epoll_ctl_mod(int epfd,int listenfd, struct epoll_event *event);

/*从epoll 上删除一个fd的监听*/
int m_epoll_ctl_del(int epfd,int listenfd, struct epoll_event *event);

/*事件循环*/
int m_epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);

#ifdef __cplusplus
}
#endif



#endif