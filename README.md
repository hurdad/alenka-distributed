UNDER HEAVY DEVELOPMENT [Does not work yet]

# alenka-distributed
distributed implementation of alenka gpu database engine

Framework for running concurrent alenka queries, distributed across servers.

### Architecture
* Zookeeper - distributed, fault tolerant, process coordination [master/worker framework]
* HDFS + short ciruit reads
* Redis - metadata [data dictionary]
* Python shell [bin/alenka-shell.py]

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
software installation:
```
sudo su root
yum install epel-release wget nano 
wget http://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-repo-rhel7-7.5-18.x86_64.rpm
yum install cuda-repo-rhel7-7.5-18.x86_64.rpm
cd /etc/yum.repos.d/
wget https://archive.cloudera.com/cdh5/redhat/7/x86_64/cdh/cloudera-cdh5.repo
yum update
yum install hadoop-libhdfs-devel boost-devel libconfig-devel hiredis-devel zookeeper-native java-1.8.0-openjdk-devel gcc-c++ automake cmake git bison flex cuda
yum install redis hadoop-hdfs-namenode hadoop-hdfs-datanode
echo 'export PATH=/usr/local/cuda-7.5/bin:${PATH}' > /etc/profile.d/cuda.sh
echo '/usr/lib/jvm/java/jre/lib/amd64/server/' > /etc/ld.so.conf.d/java.conf 
echo '/usr/lib/hadoop/lib/native/' > /etc/ld.so.conf.d/hadoop.conf 
ldconfig
exit
```
clone and build:
```
cd ~
git clone --recursive https://github.com/hurdad/alenka-distributed.git
cd alenka-distributed
cd deps/Alenka/deps/ && make
cd deps/ && make
sh autogen.sh
./configure
make
```
configure hdfs:
```
sudo nano /etc/hadoop/conf/core-site.xml
```
core-site.xml
```
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
<property>
 <name>fs.defaultFS</name>
 <value>hdfs://localhost:8020</value>
</property>
</configuration>
```
format hdfs:
```
sudo -u hdfs hdfs namenode -format
```
start hdfs namenode & datanode:
```
sudo /etc/init.d/hadoop-hdfs-namenode start
sudo /etc/init.d/hadoop-hdfs-datanode start
```
start redis:
```
sudo systemctl start redis
```
set enviroment variables:
```
export CLASSPATH=$(hadoop classpath --glob)
export LD_LIBRARY_PATH=/usr/lib/hadoop/lib/native/:$LD_LIBRARY_PATH
```
start master
```
src/master -c config/sample.cfg
```
start worker
```
src/worker -c config/sample.cfg
```
submit query
```
bin/alenka-shell.py -q query.sql
```
