void print_help();

void print_version();

int parse_capacity_cmd(std::string capacity_cmd);

int parse_capacity_file(std::string capacity_file);

std::vector<int> parse_weights_cmd(std::string weights_cmd);

std::vector<int> parse_weights_file(std::string weights_file);

std::vector<int> parse_profits_cmd(std::string profits_cmd);

std::vector<int> parse_profits_file(std::string profits_file);

int check_params(int *capacity, int *objects, std::vector<int> *weights, std::vector<int> *profits);

int parse_params(int argc, char *argv[], int *capacity, int *objects, \
	std::vector<int> *weights, std::vector<int> *profits);
