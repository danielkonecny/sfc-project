void print_help();

void print_version();

int parse_capacity_cmd(std::string capacity_cmd);

int parse_capacity_file(std::string capacity_file);

std::vector<int> parse_weights_cmd(std::string weights_cmd);

std::vector<int> parse_weights_file(std::string weights_file);

std::vector<int> parse_prices_cmd(std::string prices_cmd);

std::vector<int> parse_prices_file(std::string prices_file);

int check_params(int *capacity, std::vector<int> *weights, std::vector<int> *prices);

int parse_params(int argc, char *argv[], int *capacity, \
	std::vector<int> *weights, std::vector<int> *prices);
