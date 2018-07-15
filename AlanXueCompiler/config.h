#include <string>

using std::string;

class Config {
private:
	static int dict_start_index_;
public:
	static void init(string config_file_name = "config.txt");
	static int get_dict_start_index();
};