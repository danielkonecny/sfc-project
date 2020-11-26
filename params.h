#ifndef PARAMS_H
#define PARAMS_H

#include "Knapsack.h"

void print_help();

void print_version();

int parse_test(std::string test_cmd);

int parse_capacity_cmd(std::string capacity_cmd);

int parse_capacity_file(std::string capacity_file);

std::vector<int> parse_weights_cmd(std::string weights_cmd);

std::vector<int> parse_weights_file(std::string weights_file);

std::vector<int> parse_profits_cmd(std::string profits_cmd);

std::vector<int> parse_profits_file(std::string profits_file);

std::vector<int> parse_solutions_cmd(std::string solutions_cmd);

std::vector<int> parse_solutions_file(std::string solutions_file);

int check_params(Knapsack *knapsack);

int parse_params(int argc, char *argv[], Knapsack *knapsack);

#endif
