bin_PROGRAMS=master worker 
master_SOURCES=master-cpp/master-main.cpp master-cpp/master.cpp clog.cpp zookeeper.cpp
worker_SOURCES=worker-cpp/worker-main.cpp worker-cpp/worker.cpp clog.cpp zookeeper.cpp

master_LDFLAGS=-DTHREADED
worker_LDFLAGS=-DTHREADED ../deps/Alenka/src/libalenka.a

worker_CPPFLAGS=-I../deps/Alenka/include