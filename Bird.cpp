#include<string>
#include<vector>
#include<random>

#include"Bird.h"

Bird::Bird(int capacity, int objects, std::vector<int> weights) {
	int load = 0;
	int index;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, objects-1);

	configuration.reserve(objects);

	for(int i = 0; i < objects; i++)
		configuration.push_back(0);

	index = random_index(rng);
	load += weights[index];
	do {
		configuration[index] = 1;
		do {
	    	index = random_index(rng);
		} while(configuration[index] != 0);
		load += weights[index];
	} while(load < capacity);
}

int Bird::get_profit(std::vector<int> profits) {
	int profit = 0;

	for(size_t i = 0; i < configuration.size(); i++)
		profit += configuration[i]*profits[i];

	return profit;
}

int Bird::get_load(std::vector<int> weights) {
	int weight = 0;

	for(size_t i = 0; i < configuration.size(); i++)
		weight += configuration[i]*weights[i];

	return weight;
}


std::string Bird::get_config() {
	std::string config_string = "";
	for(auto &item : configuration)
		config_string += std::to_string(item) + " ";

	return config_string;
}
