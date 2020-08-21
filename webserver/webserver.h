#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include<cstring>
#include <sys/epoll.h>

#include "../log/log.h"
#include "../mysql/sql_connect.h"
#include "../threadpool/threadpool.h"
#include "../http/http_conn.h"
#include "../utils/utils.h"

using namespace std;
const int MAX_FD = 65536;           //最大文件描述符
const int MAX_EVENT_NUMBER = 10000; //最大事件数
const int TIMESLOT = 5;             //最小超时单位

class WebServer
{
public:
    WebServer();
    ~WebServer();

    void init(int port , string user, string passWord, string databaseName,
              int log_write , int opt_linger, int sql_num,
              int thread_num, int close_log);

    void thread_pool();
    void sql_pool();
    void log_write();
    //void trig_mode();
    void eventListen();
    void eventLoop();

    void timer(int connfd, struct sockaddr_in client_address);
    void adjust_timer(util_timer *timer);
    void deal_timer(util_timer *timer, int sockfd);

    void dealclientdata();

    bool dealwithsignal(bool& timeout, bool& stop_server);
    void dealwithread(int sockfd);
    void dealwithwrite(int sockfd);

public:
    //基础
    int m_port;//服务器端口号
    char *m_root;//服务器根目录
    int m_log_write;//日志同步或异步
    int m_close_log;//是否启用日志
    //int m_actormodel;//两种模式切换

    int m_pipefd[2];
    int m_epollfd;
    http_conn *users;//服务器httpl_conn对象

    //数据库相关
    connection_pool *m_connPool;
    string m_user;         //登陆数据库用户名
    string m_passWord;     //登陆数据库密码
    string m_databaseName; //使用数据库名
    int m_sql_num;

    //线程池相关
    threadpool<http_conn> *m_pool;
    int m_thread_num;

    //epoll_event相关
    epoll_event events[MAX_EVENT_NUMBER];

    int m_listenfd;
    int m_OPT_LINGER;   //是否启用优雅断开连接
    //int m_TRIGMode;
    //int m_LISTENTrigmode=1;//边缘触发模式   1
    //int m_CONNTrigmode=1;//边缘触发模式     1

    //定时器相关
    client_data *users_timer;
    Utils utils;
};
#endif
