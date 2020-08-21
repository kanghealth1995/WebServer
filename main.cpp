#include <string>
#include "./config/config.h"
#include "./webserver/webserver.h"
#include "./log/log.h"
#include "./mysql/sql_connect.h"
#include "./threadpool/threadpool.h"

using namespace std;

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "123456";
    string databasename = "WebServer";

    //命令行解析
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    //初始化
    server.init(config.Port, user, passwd, databasename, config.LogWrite, 
                config.OPT_LINGER,   config.sql_num,  config.thread_num, 
                config.close_log);
    //日志初始化
    server.log_write();
    // int m_close_log=server.m_close_log;
    // LOG_DEBUG("%s %s %s",user,passwd,databasename);
    // LOG_ERROR("%s", "dealclientdata failure");
    
    //sql连接池初始化
    server.sql_pool();

    //线程池
    server.thread_pool();
    
    //监听
    server.eventListen();

    //运行
    server.eventLoop();

    return 0;
}