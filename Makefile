CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

server: main.cpp ./utils/utils.cpp ./http/http_conn.cpp ./log/log.cpp ./mysql/sql_connect.cpp ./webserver/webserver.cpp ./config/config.cpp
	$(CXX) -o server  $^ $(CXXFLAGS) -lpthread -lmysqlclient

clean:
	rm  -r server