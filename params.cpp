#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>

#include "params.h"

void print_help() {
	std::cout << std::endl;
	std::cout << "Migrating Birds Optimization Knapsack Problem 01 Solver";
	std::cout << std::endl << "HELP" << std::endl;
	std::cout << "-h - optional - print help command" << std::endl;
	std::cout << "-v - optional - print application version" << std::endl;
	std::cout << "-i - optional - if used, information about optimization will be printed to stdout" << std::endl;
	std::cout << "-t - optional (argument) - print help command" << std::endl;
	std::cout << "-c - optional (argument) - capacity of the knapsack given by an integer" << std::endl;
	std::cout << "-C - optional (argument) - capacity of the knapsack given by an integer in a file" << std::endl;
	std::cout << "-w - optional (argument) - weight of each item separated by comma" << std::endl;
	std::cout << "-W - optional (argument) - weight of each item spearated by a new line in a file" << std::endl;
	std::cout << "-p - optional (argument) - price of each item separated by comma" << std::endl;
	std::cout << "-P - optional (argument) - price of each item separated by a new line in a file" << std::endl;
	std::cout << "-s - optional (argument) - solution of the problem, 0/1 values separated by comma" << std::endl;
	std::cout << "-S - optional (argument) - solution of the problem, 0/1 values separated by a new line in a file" << std::endl;
}

void print_version() {
	std::cout << std::endl;
	std::cout << "Migrating Birds Optimization Knapsack Problem 01 Solver";
	std::cout << std::endl << "VERSION 1.0" << std::endl << std::endl;
}

int parse_test(std::string test_cmd) {
	int test;
	char *pEnd;

	test = (int)strtol(test_cmd.c_str(), &pEnd, 10);

	if(*pEnd != '\0') {
		std::cerr << "Given test number is not an integer: " << test_cmd << std::endl;
		test = -1;
	}
	
	return test;
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

int check_params(Knapsack *knapsack) {
	if(knapsack->getCapacity() <= 0) {
		std::cerr << "Capacity too low: " << knapsack->getCapacity() << std::endl;
		return -1;
	}
	for(auto &weight : knapsack->getWeights()) {
		if(weight <= 0){
			std::cerr << "Weight too low: " << weight << std::endl;
			return -2;
		}
	}
	for(auto &profit : knapsack->getProfits()) {
		if(profit <= 0){
			std::cerr << "Profit too low: " << profit << std::endl;
			return -3;
		}
	}
	for(auto &solution : knapsack->getSolutions()) {
		if(solution != 0 && solution != 1){
			std::cerr << "Solution not binary: " << solution << std::endl;
			return -4;
		}
	}
	if(knapsack->getWeights().size() <= 0) {
		std::cerr << "Not enough weights: " << knapsack->getWeights().size() << std::endl;
		return -2;
	}
	if(knapsack->getWeights().size() <= 0) {
		std::cerr << "Not enough profits: " << knapsack->getWeights().size() << std::endl;
		return -3;
	}
	if(knapsack->getSolutions().size() <= 0) {
		std::cerr << "Not enough solutions: " << knapsack->getSolutions().size() << std::endl;
		return -4;
	}
	if((knapsack->getWeights().size() != knapsack->getProfits().size())
		|| (knapsack->getWeights().size() != knapsack->getSolutions().size())) {
		std::cerr << "Number of weights, profits and solutions does not match." << std::endl;
		return -5;
	}
	if(knapsack->getTestCount() <= 0) {
		std::cerr << "Test Count is too low: " << knapsack->getTestCount() << std::endl;
		return -6;
	}
	knapsack->setItemCount(knapsack->getWeights().size());
	return 0;
}

int parse_params(int argc, char *argv[], Knapsack *knapsack) {

	int option;
	int check = 0;
	int extension = 0;

	while((option = getopt(argc, argv, "hvit:c:C:w:W:p:P:s:S:")) != -1) {
		switch(option) {
			case 'h':
				print_help();
				return 1;
			case 'v':
				print_version();
				return 1;
			case 'i':
				extension = 2;
				std::cout << std::endl;
				std::cout << "Migrating Birds Optimization Knapsack Problem 01 Solver";
				std::cout << std::endl << "INFORMATION MODE" << std::endl << std::endl;
				break;
			case 't':
				extension = 3;
				std::cout << std::endl;
				std::cout << "Migrating Birds Optimization Knapsack Problem 01 Solver";
				std::cout << std::endl << "TEST MODE" << std::endl << std::endl;
				knapsack->setTestCount(parse_test(optarg));
				break;
			case 'c':
				knapsack->setCapacity(parse_capacity_cmd(optarg));
				break;
			case 'C':
				knapsack->setCapacity(parse_capacity_file(optarg));
				break;
			case 'w':
				knapsack->setWeights(parse_weights_cmd(optarg));
				break;
			case 'W':
				knapsack->setWeights(parse_weights_file(optarg));
				break;
			case 'p':
				knapsack->setProfits(parse_profits_cmd(optarg));
				break;
			case 'P':
				knapsack->setProfits(parse_profits_file(optarg));
				break;
			case 's':
				knapsack->setSolutions(parse_solutions_cmd(optarg));
				break;
			case 'S':
				knapsack->setSolutions(parse_solutions_file(optarg));
				break;
			case '?':
				std::cerr << "Unknown parameter: " << char(optopt) << std::endl;
				break;
		}
	}

	check = check_params(knapsack);

	if(check < 0)
		print_help();
	else if(check == 0)
		check = extension;

	return check;
}
