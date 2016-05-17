#include <string>
#include <boost/program_options.hpp>
#include "worker.h"
#include "config.h"

using namespace std;
using namespace boost::program_options;

int main(int argc, char **argv) {

	string config;
	options_description desc("Options");
	desc.add_options()("help", "Options related to the program.")("config,c",
			value<string>(&config)->default_value("config/sample.cfg"), "Configuration File");

	variables_map vm;
	try {
		store(parse_command_line(argc, argv, desc), vm);
		notify(vm);
	} catch (exception &e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	//print help
	if (vm.count("help")) {
		cout << desc << endl;
		return EXIT_SUCCESS;
	}

	//init config
	initZookeeperConfig();

	//parse config
	parseWorkerConfig(config.c_str());

	//data dictionary config
	alenka::data_dict_redis_simple_host = _dd.redis_simple_host;
	alenka::data_dict_redis_simple_port = _dd.redis_simple_port;
	alenka::data_dict_redis_simple_pool = _dd.redis_simple_pool;

	//hdfs config
	alenka::file_system_hdfs_host = _fs.hdfs_host.c_str();
	alenka::file_system_hdfs_port = _fs.hdfs_port;
	alenka::file_system_hdfs_base_path = _fs.hdfs_base_path.c_str();

	log_init((CLogLevel)log_level, (log_path + string("worker.log")).c_str());

    ZooKeeper zk(_zk.hosts, _zk.timeout);

    Worker w(&zk);
    w.startWatchThread();

    while(!w.isConnected()) {
        sleep(1);
    }

    w.createWorkspace();
    w.createWorker();
    w.getTasks();

    while(!w.isExpired()) {
        sleep(1);
    }

    return 0;
}
