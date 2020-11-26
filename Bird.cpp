#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<algorithm>

#include"Bird.h"

Bird::Bird(Mbo mbo) {
	this->mbo = mbo;
	this->configuration.reserve(mbo.getItemCount());

	for(int i = 0; i < mbo.getItemCount(); i++)
		this->configuration.push_back(0);
}

void Bird::initBird() {
	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

	int index = random_index(rng);
	int load = this->mbo.getWeight(index);

	do {
		this->configuration[index] = 1;
		do {
	    	index = random_index(rng);
		} while(this->configuration[index] != 0);
		load += this->mbo.getWeight(index);
	} while(load < this->mbo.getCapacity());
}

void Bird::initBird(std::vector<std::vector<int>> duplicates) {
	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

    bool duplicate_flag = false;
    std::vector<int> original_configuration = this->configuration;

    do {
    	duplicate_flag = false;							// Reset duplicate flag.
		int index = random_index(rng);
		int load = this->mbo.getWeight(index);			// Choose first random thing to add to knapsack.
		this->configuration = original_configuration;	// Reset configuration (necessary if run multiple times).

		// Add things to knapsack until capacity is exceeded.
		do {
			this->configuration[index] = 1;
			do {
		    	index = random_index(rng);
			} while(this->configuration[index] != 0);
			load += this->mbo.getWeight(index);
		} while(load < this->mbo.getCapacity());
		/*
		// Check if not duplicate.
		for(const auto &duplicate : duplicates) {
			if(duplicate == this->configuration)
				duplicate_flag = true;
		}
		*/
	} while(duplicate_flag);
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
    		duplicate_flag = false;								// Reset duplicate flag.
	    	int load = this->getLoad();							// Get current load.
		    (&neighbor)->configuration = this->configuration;	// Reset configuration.

		    // Add 1 item to knapsack
			do {
		    	add_index = random_index(rng);
			} while((&neighbor)->configuration[add_index] != 0);
			(&neighbor)->configuration[add_index] = 1;
			load += this->mbo.getWeight(add_index);

			// Remove items if necessary to not exceed the capacity.
			while(load > this->mbo.getCapacity()) {
				do {
			    	clear_index = random_index(rng);
				} while(((&neighbor)->configuration[clear_index] != 1) || (clear_index == add_index));
				(&neighbor)->configuration[clear_index] = 0;
				load -= this->mbo.getWeight(clear_index);
			}
			/*
			// Check if not duplicate.
			for(const auto &config : prev_configs) {
				if(config == neighbor.configuration)
					duplicate_flag = true;
			}
			*/
    	} while(duplicate_flag);

    	prev_configs.push_back(neighbor.configuration);
    }
}

void Bird::findNeighbors(std::vector<Bird> *neighbors, std::vector<Bird> *shared) {
	int add_index;
	int clear_index;
	std::vector<std::vector<int>> prev_configs;

	std::random_device dev;
	std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, this->mbo.getItemCount()-1);

	bool duplicate_flag = false;

	// Replace first 'x' neighbors with shared from predecessor.
	for(size_t i = 0; i < shared->size(); i++) {
		(*neighbors)[i] = (*shared)[i];
		prev_configs.push_back((*neighbors)[i].configuration);
	}

    for(size_t i = shared->size(); i < neighbors->size(); i++) {	
    	do {
    		duplicate_flag = false;									// Reset duplicate flag.
	    	int load = this->getLoad();								// Get current load.
		    (*neighbors)[i].configuration = this->configuration;	// Reset configuration.

		    // Add 1 item to knapsack
			do {
		    	add_index = random_index(rng);
			} while((*neighbors)[i].configuration[add_index] != 0);
			(*neighbors)[i].configuration[add_index] = 1;
			load += this->mbo.getWeight(add_index);

			// Remove items if necessary to not exceed the capacity.
			while(load > this->mbo.getCapacity()) {
				do {
			    	clear_index = random_index(rng);
				} while(((*neighbors)[i].configuration[clear_index] != 1) || (clear_index == add_index));
				(*neighbors)[i].configuration[clear_index] = 0;
				load -= this->mbo.getWeight(clear_index);
			}
			/*
			// Check if not duplicate.
			for(const auto &config : prev_configs) {
				if(config == (*neighbors)[i].configuration)
					duplicate_flag = true;
			}
			*/
    	} while(duplicate_flag);

    	prev_configs.push_back((*neighbors)[i].configuration);
    }
}

void Bird::improve(Bird best_neighbor) {
	if(best_neighbor.getProfit() > this->getProfit())
		this->configuration = best_neighbor.getConfiguration();
}

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

void Bird::setConfiguration(std::vector<int> config) {
	this->configuration = config;
}

void Bird::printMe() {
	std::cout << "Configuration: ";
	for(auto &item : this->configuration)
		std::cout << std::to_string(item) << " ";
	std::cout << std::endl;

	std::cout << "Load: " << this->getLoad() << std::endl;
	std::cout << "Profit: " << this->getProfit() << std::endl;
}

void sortByProfit(std::vector<Bird> *birds) {
	std::sort(birds->begin(), birds->end(), [](Bird & one, Bird & two) {
		return one.getProfit() > two.getProfit();
	});
}
