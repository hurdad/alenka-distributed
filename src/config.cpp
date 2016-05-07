#include "config.h"

//config structs
zookeeper_config _zk;
data_dictionary _dd;
file_system _fs;
int log_level = 4;

const string getMasterPath(){
	return _zk.base_path + MASTERPATH;
}

const string getWorkerPath(){
	return _zk.base_path + WORKERPATH;
}

const string getAssignPath(){
	return _zk.base_path + ASSIGNPATH;
}

const string getTaskPath(){
	return _zk.base_path + TASKPATH;
}

void initZookeeperConfig(){
	_zk.hosts = "localhost:2181";
	//_zk.timeout = 10000;
	_zk.base_path = "/alenka";
}

void initDataDictConfig(){
	_dd.redis_simple_host = "localhost";
	_dd.redis_simple_port = 6379;
	_dd.redis_simple_pool = true;
}

void initFileSystemConfig(){
	_fs.hdfs_host = "default";
	_fs.hdfs_port = 0;
	_fs.hdfs_base_path = "/alenka/";
}

void parseMasterConfig(const char * configFile) {
	Config cfg;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(configFile);
	} catch (const FileIOException &fioex) {
		std::cerr << "Error while reading config file: " << configFile << std::endl;
		exit (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Configuration parse error at " << pex.getFile() << ":" << pex.getLine()
				<< " - " << pex.getError() << std::endl;
		exit (EXIT_FAILURE);
	}

	//
	// Parse Config
	//
	cfg.lookupValue("zookeeper.host", _zk.hosts);
	int zk_timeout = _zk.timeout;
	cfg.lookupValue("zookeeper.timeout", zk_timeout);
	_zk.timeout = zk_timeout;
	cfg.lookupValue("zookeeper.base_path", _zk.base_path);

	cfg.lookupValue("log_level", log_level);

}

void parseWorkerConfig(const char * configFile) {
	Config cfg;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(configFile);
	} catch (const FileIOException &fioex) {
		std::cerr << "Error while reading config file: " << configFile << std::endl;
		exit (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Configuration parse error at " << pex.getFile() << ":" << pex.getLine()
				<< " - " << pex.getError() << std::endl;
		exit (EXIT_FAILURE);
	}

	//
	// Parse Config
	//
	cfg.lookupValue("zookeeper.host", _zk.hosts);
	int zk_timeout = _zk.timeout;
	cfg.lookupValue("zookeeper.timeout", zk_timeout);
	_zk.timeout = zk_timeout;
	cfg.lookupValue("zookeeper.base_path", _zk.base_path);

	cfg.lookupValue("data_dictionary.redis_simple_host", _dd.redis_simple_host);
	int redis_simple_port = _dd.redis_simple_port;
	cfg.lookupValue("data_dictionary.redis_simple_port", redis_simple_port);
	_dd.redis_simple_port = redis_simple_port;
	cfg.lookupValue("data_dictionary.redis_simple_pool", _dd.redis_simple_pool);

	cfg.lookupValue("file_system.hdfs_host", _fs.hdfs_host);
	int hdfs_port = _fs.hdfs_port;
	cfg.lookupValue("file_system.hdfs_port", hdfs_port);
	_fs.hdfs_port = hdfs_port;
	cfg.lookupValue("file_system.hdfs_base_path", _fs.hdfs_base_path);

	cfg.lookupValue("log_level", log_level);
}
