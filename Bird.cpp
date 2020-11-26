#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#include "Bird.h"

Bird::Bird(Knapsack knapsack) {
	this->knapsack = knapsack;
	this->configuration.reserve(knapsack.getItemCount());

	for(int i = 0; i < knapsack.getItemCount(); i++)
		this->configuration.push_back(0);
}

void Bird::initBird() {
	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->knapsack.getItemCount()-1);

	int index = random_index(rng);
	int load = this->knapsack.getWeight(index);

	do {
		this->configuration[index] = 1;
		do {
	    	index = random_index(rng);
		} while(this->configuration[index] != 0);
		load += this->knapsack.getWeight(index);
	} while(load < this->knapsack.getCapacity());
}

void Bird::findNeighbors(std::vector<Bird> *neighbors) {
	int add_index;
	int clear_index;
	std::vector<std::vector<int>> prev_configs;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->knapsack.getItemCount()-1);

    for(auto &neighbor : *neighbors) {	
    	int load = this->getLoad();							// Get current load.
	    (&neighbor)->configuration = this->configuration;	// Reset configuration.

	    // Add 1 item to knapsack
		do {
	    	add_index = random_index(rng);
		} while((&neighbor)->configuration[add_index] != 0);
		(&neighbor)->configuration[add_index] = 1;
		load += this->knapsack.getWeight(add_index);

		// Remove items if necessary to not exceed the capacity.
		while(load > this->knapsack.getCapacity()) {
			do {
		    	clear_index = random_index(rng);
			} while(((&neighbor)->configuration[clear_index] != 1) || (clear_index == add_index));
			(&neighbor)->configuration[clear_index] = 0;
			load -= this->knapsack.getWeight(clear_index);
		}
    	prev_configs.push_back(neighbor.configuration);
    }

    std::sort(neighbors->begin(), neighbors->end(), [](Bird & one, Bird & two) {
		return one.getProfit() > two.getProfit();
	});
}

void Bird::findNeighbors(std::vector<Bird> *neighbors, std::vector<Bird> *shared) {
	int add_index;
	int clear_index;
	std::vector<std::vector<int>> prev_configs;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->knapsack.getItemCount()-1);

	// Replace first 'x' neighbors with shared from predecessor.
	for(size_t i = 0; i < shared->size(); i++) {
		(*neighbors)[i] = (*shared)[i];
		prev_configs.push_back((*neighbors)[i].configuration);
	}

    for(size_t i = shared->size(); i < neighbors->size(); i++) {	
    	int load = this->getLoad();								// Get current load.
	    (*neighbors)[i].configuration = this->configuration;	// Reset configuration.

	    // Add 1 item to knapsack
		do {
	    	add_index = random_index(rng);
		} while((*neighbors)[i].configuration[add_index] != 0);
		(*neighbors)[i].configuration[add_index] = 1;
		load += this->knapsack.getWeight(add_index);

		// Remove items if necessary to not exceed the capacity.
		while(load > this->knapsack.getCapacity()) {
			do {
		    	clear_index = random_index(rng);
			} while(((*neighbors)[i].configuration[clear_index] != 1) || (clear_index == add_index));
			(*neighbors)[i].configuration[clear_index] = 0;
			load -= this->knapsack.getWeight(clear_index);
		}
    	prev_configs.push_back((*neighbors)[i].configuration);
    }

    std::sort(neighbors->begin(), neighbors->end(), [](Bird & one, Bird & two) {
		return one.getProfit() > two.getProfit();
	});
}

void Bird::improve(Bird best_neighbor) {
	if(best_neighbor.getProfit() > this->getProfit())
		this->configuration = best_neighbor.getConfiguration();
}

int Bird::getProfit() {
	int profit = 0;

	for(size_t i = 0; i < this->configuration.size(); i++)
		profit += this->configuration[i]*this->knapsack.getProfit(i);

	return profit;
}

int Bird::getLoad() {
	int weight = 0;

	for(size_t i = 0; i < this->configuration.size(); i++)
		weight += this->configuration[i]*this->knapsack.getWeight(i);

	return weight;
}

std::vector<int> Bird::getConfiguration() {
	return this->configuration;
}

void Bird::setConfiguration(std::vector<int> config) {
	this->configuration = config;
}

void Bird::print() {
	std::cout << "Configuration: ";
	for(auto &item : this->configuration)
		std::cout << std::to_string(item) << " ";
	std::cout << std::endl;

	std::cout << "Load: " << this->getLoad() << std::endl;
	std::cout << "Profit: " << this->getProfit() << std::endl << std::endl;
}
