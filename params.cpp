#include<iostream>
#include<cstring>
#include<vector>
#include<unistd.h>
#include<stdlib.h>
#include<fstream>

#include"params.h"

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

std::vector<int> parse_profits_cmd(std::string profits_cmd) {
	std::vector<int> profits;
	std::vector<std::string> profits_string;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = profits_cmd.find(delimiter)) != std::string::npos) {
		profits_string.push_back(profits_cmd.substr(0, string_index));
		profits_cmd.erase(0, string_index + delimiter.length());
	}
	profits_string.push_back(profits_cmd.substr(0, string_index));

	for(auto profit_string = profits_string.begin(); profit_string != profits_string.end(); profit_string++) {
		char *pEnd;
		int profit;

		profit = (int)strtol((*profit_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given profit is not an integer: " << *profit_string << std::endl;
			profit = -1;
		}
		
		profits.push_back(profit);
	}

	return profits;
	
}

std::vector<int> parse_profits_file(std::string profits_file) {
	std::vector<int> profits;
	std::vector<std::string> profits_string;
	std::string profit_line;
	std::ifstream infile(profits_file);

	while(std::getline(infile, profit_line)) {
		profits_string.push_back(profit_line);
	}

	for(auto profit_string = profits_string.begin(); profit_string != profits_string.end(); profit_string++) {
		char *pEnd;
		int profit;

		profit = (int)strtol((*profit_string).c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given profit is not an integer: " << *profit_string << std::endl;
			profit = -1;
		}
		
		profits.push_back(profit);
	}

	return profits;
}

int check_params(int *capacity, int *objects, std::vector<int> *weights, std::vector<int> *profits) {
	if(*capacity <= 0)
		return -1;

	for(auto weight = weights->begin(); weight != weights->end(); weight++)
		if(*weight <= 0)
			return -2;

	for(auto profit = profits->begin(); profit != profits->end(); profit++)
		if(*profit <= 0)
			return -3;

	if(weights->size() <= 0)
		return -2;

	if(profits->size() <= 0)
		return -3;

	if(weights->size() != profits->size())
		return -4;

	*objects = weights->size();

	return 0;
}

int parse_params(int argc, char *argv[], int *capacity, int *objects, \
	std::vector<int> *weights, std::vector<int> *profits) {

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
				*profits = parse_profits_cmd(optarg);
				break;
			case 'P':
				*profits = parse_profits_file(optarg);
				break;
			case '?':
				std::cerr << "Unknown parameter: " << char(optopt) << std::endl;
				break;
		}
	}

	return check_params(capacity, objects, weights, profits);
}
