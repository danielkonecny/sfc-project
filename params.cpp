#include<iostream>
#include<cstring>
#include<vector>
#include<unistd.h>
#include<stdlib.h>
#include<fstream>

void print_help() {
	// TODO
	std::cout << "HELP!" << std::endl;
}

void print_version() {
	// TODO
	std::cout << "VERSION!" << std::endl;
}

int parse_capacity_cmd(std::string capacity_cmd) {
	int capacity;
	char *pEnd;

	capacity = (int)strtol(capacity_cmd.c_str(), &pEnd, 10);

	if(*pEnd != '\0') {
		std::cerr << "Given capacity is not an integer: " << capacity_cmd << std::endl;
		capacity = -1;
	}
	
	return capacity;
}

int parse_capacity_file(std::string capacity_file) {
	int capacity;
	std::ifstream infile(capacity_file);
	std::string capacity_string;
	char *pEnd;

	std::getline(infile, capacity_string);

	capacity = (int)strtol(capacity_string.c_str(), &pEnd, 10);

	if(*pEnd != '\0') {
		std::cerr << "Given capacity is not an integer: " << capacity_string << std::endl;
		capacity = -1;
	}
	
	return capacity;
}

std::vector<int> parse_weights_cmd(std::string weights_cmd) {
	std::vector<int> weights;
	std::vector<std::string> weights_string;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = weights_cmd.find(delimiter)) != std::string::npos) {
		weights_string.push_back(weights_cmd.substr(0, string_index));
		weights_cmd.erase(0, string_index + delimiter.length());
	}
	weights_string.push_back(weights_cmd.substr(0, string_index));

	for(auto weight_string = weights_string.begin(); weight_string != weights_string.end(); weight_string++) {
		char *pEnd;
		int weight;

		weight = (int)strtol((*weight_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given weight is not an integer: " << *weight_string << std::endl;
			weight = -1;
		}
		
		weights.push_back(weight);
	}

	return weights;
}

std::vector<int> parse_weights_file(std::string weights_file) {
	std::vector<int> weights;
	std::vector<std::string> weights_string;
	std::string weight_line;
	std::ifstream infile(weights_file);

	while(std::getline(infile, weight_line)) {
		weights_string.push_back(weight_line);
	}

	for(auto weight_string = weights_string.begin(); weight_string != weights_string.end(); weight_string++) {
		char *pEnd;
		int weight;

		weight = (int)strtol((*weight_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given weight is not an integer: " << *weight_string << std::endl;
			weight = -1;
		}
		
		weights.push_back(weight);
	}

	return weights;
}

std::vector<int> parse_prices_cmd(std::string prices_cmd) {
	std::vector<int> prices;
	std::vector<std::string> prices_string;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = prices_cmd.find(delimiter)) != std::string::npos) {
		prices_string.push_back(prices_cmd.substr(0, string_index));
		prices_cmd.erase(0, string_index + delimiter.length());
	}
	prices_string.push_back(prices_cmd.substr(0, string_index));

	for(auto price_string = prices_string.begin(); price_string != prices_string.end(); price_string++) {
		char *pEnd;
		int price;

		price = (int)strtol((*price_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given price is not an integer: " << *price_string << std::endl;
			price = -1;
		}
		
		prices.push_back(price);
	}

	return prices;
	
}

std::vector<int> parse_prices_file(std::string prices_file) {
	std::vector<int> prices;
	std::vector<std::string> prices_string;
	std::string price_line;
	std::ifstream infile(prices_file);

	while(std::getline(infile, price_line)) {
		prices_string.push_back(price_line);
	}

	for(auto price_string = prices_string.begin(); price_string != prices_string.end(); price_string++) {
		char *pEnd;
		int price;

		price = (int)strtol((*price_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given price is not an integer: " << *price_string << std::endl;
			price = -1;
		}
		
		prices.push_back(price);
	}

	return prices;
}

int check_params(int *capacity, std::vector<int> *weights, std::vector<int> *prices) {
	(void)capacity;
	(void)weights;
	(void)prices;
	// TODO - check if capacity, all weights and all prices are > 0 
	// TODO - check if weights vector is longer than 0
	// TODO - check if prices vector is longer than 0
	// TODO - check if weights and prices vector lengths match
	return 0;
}

int parse_params(int argc, char *argv[], int *capacity, \
	std::vector<int> *weights, std::vector<int> *prices) {

	// TODO - expand for long options
	int option;

	while((option = getopt(argc, argv, "hvc:C:w:W:p:P:")) != -1) {
		switch(option) {
			case 'h':
				print_help();
				return 1;
			case 'v':
				print_version();
				return 1;
			case 'c':
				*capacity = parse_capacity_cmd(optarg);
				break;
			case 'C':
				*capacity = parse_capacity_file(optarg);
				break;
			case 'w':
				*weights = parse_weights_cmd(optarg);
				break;
			case 'W':
				*weights = parse_weights_file(optarg);
				break;
			case 'p':
				*prices = parse_prices_cmd(optarg);
				break;
			case 'P':
				*prices = parse_prices_file(optarg);
				break;
			case '?':
				std::cerr << "Unknown parameter: " << char(optopt) << std::endl;
				break;
		}
	}

	return check_params(capacity, weights, prices);
}
