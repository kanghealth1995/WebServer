# WebServer
简易多并发HTTP服务器
本项目服务器框架由游双的《Linux高性能服务器编程》这本书而来，具体实现了通过HTTP服务，远程访问或者下载个人简历这一功能。

部署方式如下：
1.首先需要安装mysqlserver;
	安装命令：sudo apt-get install mysql-server
注:
	初次安装，无密码时进入mysql:
	sudo vim /etc/mysql/debain.cnf
	内存在一个默认的账号密码，可用于进入，然后修改密码。
	修改mysql密码命令
	update mysql.user set authentication_string = password('asdzxc123') where user = 'root' and host='localhost'; 
	update user set plugin="mysql_native_password";
	flush privileges;
	quit;

2.安装MySQL开发包;
	安装命令：sudo apt-get install libmysqld-dev
3.创建表项：
	mysql -uroot -p
		// 建立yourdb库
		create database yourdb;

		// 创建user表
		USE WebServer;
		CREATE TABLE user(
		    username char(50) NULL,
			    passwd char(50) NULL
		)ENGINE=InnoDB;
4.在main.cpp中修改mysql的登陆账号，密码和数据库名称。
5.make，生成可执行文件server。
6.执行如下命令，在后台运行server
	nohup ./server &
	

遇到的问题:
1、bind失败:
	首先使用命令netstat查看80端口是否被占用，若被占用，杀掉占用的程序;
	然后查看/proc/sys/net/ipv4/ip_local_port_range，查看应用可使用的端口范围，若80不在其中，可修改；
	也可使用sudo执行server。

