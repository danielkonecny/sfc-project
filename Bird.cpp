#include<iostream>
#include<string>
#include<vector>
#include<random>

#include"Bird.h"

Bird::Bird(Mbo mbo) {
	this->mbo = mbo;
	this->configuration.reserve(mbo.getItemCount());

	for(int i = 0; i < mbo.getItemCount(); i++)
		this->configuration.push_back(0);
}

void Bird::initBird() {
	int load = 0;
	int index;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

	index = random_index(rng);
	load += this->mbo.getWeight(index);
	do {
		this->configuration[index] = 1;
		do {
	    	index = random_index(rng);
		} while(this->configuration[index] != 0);
		load += this->mbo.getWeight(index);
	} while(load < this->mbo.getCapacity());
}

void Bird::findNeighbors(std::vector<Bird> *neighbors) {
	int add_index;
	int clear_index;
	std::vector<std::vector<int>> prev_configs;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

	bool duplicate_flag = false;

    for(auto &neighbor : *neighbors) {	
    	do {
    		duplicate_flag = false;
	    	int load = this->getLoad();
		    (&neighbor)->configuration = this->configuration;

			do {
		    	add_index = random_index(rng);
			} while((&neighbor)->configuration[add_index] != 0);
			(&neighbor)->configuration[add_index] = 1;
			load += this->mbo.getWeight(add_index);

			while(load > this->mbo.getCapacity()) {
				do {
			    	clear_index = random_index(rng);
				} while(((&neighbor)->configuration[clear_index] != 1) || (clear_index == add_index));
				(&neighbor)->configuration[clear_index] = 0;
				load -= this->mbo.getWeight(clear_index);
			}

			for(const auto &config : prev_configs) {
				if(config == neighbor.configuration)
					duplicate_flag = true;
			}
    	} while(duplicate_flag);

    	prev_configs.push_back(neighbor.configuration);
    }
}

/*
void Bird::findNeighbors(Bird *neighbor) {
	int load = this->getLoad();
	int add_index;
	int clear_index;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

    neighbor->configuration = this->configuration;

	do {
    	add_index = random_index(rng);
	} while(neighbor->configuration[add_index] != 0);
	neighbor->configuration[add_index] = 1;
	load += this->mbo.getWeight(add_index);

	while(load > this->mbo.getCapacity()) {
		do {
	    	clear_index = random_index(rng);
		} while((neighbor->configuration[clear_index] != 1) || (clear_index == add_index));
		neighbor->configuration[clear_index] = 0;
		load -= this->mbo.getWeight(clear_index);
	}
}
*/

/*
void Bird::findNeighbors(int capacity, int objects, std::vector<int> weights, std::vector<int> configuration) {
	int load = 0;
	int add_index;
	int clear_index;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, objects-1);

    this->configuration = configuration;

	for(size_t i = 0; i < this->configuration.size(); i++)
		load += this->configuration[i]*weights[i];

	do {
    	add_index = random_index(rng);
	} while(this->configuration[add_index] != 0);
	this->configuration[add_index] = 1;
	load += weights[add_index];

	while(load > capacity) {
		do {
	    	clear_index = random_index(rng);
		} while((this->configuration[clear_index] != 1) || (clear_index == add_index));
		this->configuration[clear_index] = 0;
		load -= weights[clear_index];
	}
}
*/

int Bird::getProfit() {
	int profit = 0;

	for(size_t i = 0; i < this->configuration.size(); i++)
		profit += this->configuration[i]*this->mbo.getProfit(i);

	return profit;
}

int Bird::getLoad() {
	int weight = 0;

	for(size_t i = 0; i < this->configuration.size(); i++)
		weight += this->configuration[i]*this->mbo.getWeight(i);

	return weight;
}


std::vector<int> Bird::getConfiguration() {
	return this->configuration;
}

void Bird::printMe() {
	std::cout << "Configuration: ";
	for(auto &item : this->configuration)
		std::cout << std::to_string(item) << " ";
	std::cout << std::endl;

	std::cout << "Load: " << this->getLoad() << std::endl;
	std::cout << "Profit: " << this->getProfit() << std::endl;
}
