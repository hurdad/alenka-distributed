#ifndef CONFIG_H_
#define CONFIG_H_

#include "libconfig.h++"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace libconfig;

struct zookeeper_config {
	string hosts;
	int timeout;
	string base_path;
};
extern zookeeper_config _zk;

struct data_dictionary {
	string redis_simple_host;
	int	redis_simple_port;
	bool redis_simple_pool;
};
extern data_dictionary _dd;

struct file_system {
	string hdfs_host;
	int hdfs_port;
	string hdfs_base_path;
};
extern file_system _fs;

extern int log_level;

static const std::string MASTERPATH = "/masters";
static const std::string WORKERPATH = "/workers";
static const std::string ASSIGNPATH = "/assign";
static const std::string TASKPATH = "/tasks";

extern const string getMasterPath();

extern const string getWorkerPath();

const string getAssignPath();

const string getTaskPath();

void initZookeeperConfig();

void initDataDictConfig();

void initFileSystemConfig();

void parseMasterConfig(const char * configFile);

void parseWorkerConfig(const char * configFile);

#endif /* CONFIG_H_ */
