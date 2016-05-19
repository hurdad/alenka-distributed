# alenka-distributed
distributed implementation of alenka gpu database engine

Framework for running concurrent alenka queries, distributed across servers.

### Architecture
* Zookeeper - distributed, fault tolerant, process coordination [master/worker framework]
* HDFS + short ciruit reads
* Redis - metadata [data dictionary]
* Python shell [bin/alenka-shell.py]

Gettting Started
========
### Requirements:
* Zookeeper Cluster
* Hadoop HDFS Cluster
* Redis Server or Cluster
* CUDA enabled GPU

### Shared Library Requirements:
* libalenka (https://github.com/antonmks/Alenka)
* libhiredis
* libredis3m (libalenka submodule)
* libzookeeper_mt
* libboost_system
* libboost_thread
* libhdfs + libjvm
* libboost_program_options
* libconfig++

Quick Start with Cloudera CDH 5x + CentOS 7
========
```
sudo su root
wget http://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-repo-rhel7-7.5-18.x86_64.rpm
yum install cuda-repo-rhel7-7.5-18.x86_64.rpm
cd /etc/yum.repos.d/
wget https://archive.cloudera.com/cdh5/redhat/7/x86_64/cdh/cloudera-cdh5.repo
yum update
yum install hadoop-libhdfs hadoop-libhdfs-devel boost-devel libconfig-devel hiredis-devel zookeeper-native java-1.8.0-openjdk-devel gcc-c++ automake cmake git bison flex cuda
echo '/usr/lib/jvm/java/jre/lib/amd64/server/' > /etc/ld.so.conf.d/java.conf 
echo '/usr/lib/hadoop/lib/native/' > /etc/ld.so.conf.d/hadoop.conf 
ldconfig
exit

cd ~
git clone --recursive https://github.com/hurdad/alenka-distributed.git
cd alenka-distributed
cd deps/Alenka/deps/ && make
cd deps/ && make
sh autogen.sh
./configure
make
export CLASSPATH=$(hadoop classpath --glob)
export LD_LIBRARY_PATH=/usr/lib/hadoop/lib/native/:$LD_LIBRARY_PATH

src/master -c config/sample.cfg
src/worker -c config/sample.cfg
bin/alenka-shell.py -q query.sql

```
