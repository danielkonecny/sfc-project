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
	std::cout << "MBO Knapsack Problem 01 Solver - v1.0!" << std::endl;
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
	std::vector<std::string> weight_strings;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = weights_cmd.find(delimiter)) != std::string::npos) {
		weight_strings.push_back(weights_cmd.substr(0, string_index));
		weights_cmd.erase(0, string_index + delimiter.length());
	}
	weight_strings.push_back(weights_cmd.substr(0, string_index));

	for(auto &weight_string : weight_strings) {
		char *pEnd;
		int weight;

		weight = (int)strtol(weight_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given weight is not an integer: " << weight_string << std::endl;
			weight = -1;
		}
		
		weights.push_back(weight);
	}

	return weights;
}

std::vector<int> parse_weights_file(std::string weights_file) {
	std::vector<int> weights;
	std::vector<std::string> weight_strings;
	std::string weight_line;
	std::ifstream infile(weights_file);

	while(std::getline(infile, weight_line)) {
		weight_strings.push_back(weight_line);
	}

	for(auto &weight_string : weight_strings) {
		char *pEnd;
		int weight;

		weight = (int)strtol(weight_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given weight is not an integer: " << weight_string << std::endl;
			weight = -1;
		}
		
		weights.push_back(weight);
	}

	return weights;
}

std::vector<int> parse_profits_cmd(std::string profits_cmd) {
	std::vector<int> profits;
	std::vector<std::string> profit_strings;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = profits_cmd.find(delimiter)) != std::string::npos) {
		profit_strings.push_back(profits_cmd.substr(0, string_index));
		profits_cmd.erase(0, string_index + delimiter.length());
	}
	profit_strings.push_back(profits_cmd.substr(0, string_index));

	for(auto &profit_string : profit_strings) {
		char *pEnd;
		int profit;

		profit = (int)strtol(profit_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given profit is not an integer: " << profit_string << std::endl;
			profit = -1;
		}
		
		profits.push_back(profit);
	}

	return profits;
	
}

std::vector<int> parse_profits_file(std::string profits_file) {
	std::vector<int> profits;
	std::vector<std::string> profit_strings;
	std::string profit_line;
	std::ifstream infile(profits_file);

	while(std::getline(infile, profit_line)) {
		profit_strings.push_back(profit_line);
	}

	for(auto &profit_string : profit_strings) {
		char *pEnd;
		int profit;

		profit = (int)strtol(profit_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given profit is not an integer: " << profit_string << std::endl;
			profit = -1;
		}
		
		profits.push_back(profit);
	}

	return profits;
}

std::vector<int> parse_solutions_cmd(std::string solutions_cmd) {
	std::vector<int> solutions;
	std::vector<std::string> solution_strings;
	const std::string delimiter = ",";
	size_t string_index;

	while((string_index = solutions_cmd.find(delimiter)) != std::string::npos) {
		solution_strings.push_back(solutions_cmd.substr(0, string_index));
		solutions_cmd.erase(0, string_index + delimiter.length());
	}
	solution_strings.push_back(solutions_cmd.substr(0, string_index));

	for(auto &solution_string : solution_strings) {
		char *pEnd;
		int solution;

		solution = (int)strtol(solution_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given solution is not an integer: " << solution_string << std::endl;
			solution = -1;
		}
		
		solutions.push_back(solution);
	}

	return solutions;
	
}

std::vector<int> parse_solutions_file(std::string solutions_file) {
	std::vector<int> solutions;
	std::vector<std::string> solution_strings;
	std::string solution_line;
	std::ifstream infile(solutions_file);

	while(std::getline(infile, solution_line)) {
		solution_strings.push_back(solution_line);
	}

	for(auto &solution_string : solution_strings) {
		char *pEnd;
		int solution;

		solution = (int)strtol(solution_string.c_str(), &pEnd, 10);

		if(*pEnd != '\0') {
			std::cerr << "Given solution is not an integer: " << solution_string << std::endl;
			solution = -1;
		}
		
		solutions.push_back(solution);
	}

	return solutions;
}

int check_params(int *capacity, int *objects, std::vector<int> *weights,
	std::vector<int> *profits, std::vector<int> *solutions) {

	if(*capacity <= 0) {
		std::cerr << "Capacity too low: " << *capacity << std::endl;
		return -1;
	}

	for(auto &weight : *weights) {
		if(weight <= 0){
			std::cerr << "Weight too low: " << weight << std::endl;
			return -2;
		}
	}

	for(auto &profit : *profits){
		if(profit <= 0){
			std::cerr << "Profit too low: " << profit << std::endl;
			return -3;
		}
	}

	for(auto &solution : *solutions){
		if(solution != 0 && solution != 1){
			std::cerr << "Solution not binary: " << solution << std::endl;
			return -4;
		}
	}

	if(weights->size() <= 0){
		std::cerr << "Not enough weights: " << weights->size() << std::endl;
		return -2;
	}

	if(profits->size() <= 0){
		std::cerr << "Not enough profits: " << profits->size() << std::endl;
		return -3;
	}

	if(solutions->size() <= 0){
		std::cerr << "Not enough solutions: " << solutions->size() << std::endl;
		return -4;
	}

	if((weights->size() != profits->size()) || (weights->size() != solutions->size())){
		std::cerr << "Number of weights, profits and solutions does not match." << std::endl;
		return -5;
	}

	*objects = weights->size();

	return 0;
}

int parse_params(int argc, char *argv[], int *capacity, int *objects,
	std::vector<int> *weights, std::vector<int> *profits, std::vector<int> *solutions) {

	// TODO - expand for long options
	int option;

	while((option = getopt(argc, argv, "hvc:C:w:W:p:P:s:S:")) != -1) {
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
			case 's':
				*solutions = parse_solutions_cmd(optarg);
				break;
			case 'S':
				*solutions = parse_solutions_file(optarg);
				break;
			case '?':
				std::cerr << "Unknown parameter: " << char(optopt) << std::endl;
				break;
		}
	}

	return check_params(capacity, objects, weights, profits, solutions);
}
