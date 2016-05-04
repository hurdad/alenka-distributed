bin_PROGRAMS=master worker 
master_SOURCES=master-cpp/master_main.cpp master-cpp/master.cpp clog.cpp zookeeper.cpp
worker_SOURCES=worker-cpp/worker_main.cpp worker-cpp/worker.cpp clog.cpp zookeeper.cpp

master_LDFLAGS=-DTHREADED
worker_LDFLAGS=-DTHREADED