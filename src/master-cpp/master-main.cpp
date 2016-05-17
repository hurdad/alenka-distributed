#include <string>
#include <boost/program_options.hpp>
#include "master.h"
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
	initDataDictConfig();
	initFileSystemConfig();

	//parse config
	parseMasterConfig(config.c_str());

    log_init((CLogLevel)log_level, (log_path + string("master.log")).c_str());

    ZooKeeper zk(_zk.hosts, _zk.timeout);

    Master m(&zk);
    m.startWatchThread();

    while(!m.isConnected()) {
        sleep(1);
    }

    m.createMaster();
    m.checkMaster();

    while(!m.isExpired()) {
        sleep(1);
    }

    return 0;
}
