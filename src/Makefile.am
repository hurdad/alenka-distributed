bin_PROGRAMS=master worker 
master_SOURCES=master-cpp/master-main.cpp master-cpp/master.cpp config.cpp clog.cpp zookeeper.cpp
worker_SOURCES=worker-cpp/worker-main.cpp worker-cpp/worker.cpp config.cpp clog.cpp zookeeper.cpp

master_LDFLAGS=-DTHREADED
worker_LDFLAGS=-DTHREADED -L=../deps/Alenka/src/ -lalenka

worker_CPPFLAGS=-I../deps/Alenka/include