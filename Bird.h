#ifndef BIRD_H
#define BIRD_H

#include "Knapsack.h"

class Bird {
private:
	Knapsack knapsack;
	std::vector<int> configuration;

public:
	Bird(Knapsack);

	void initBird();
	void findNeighbors(std::vector<Bird>*);
	void findNeighbors(std::vector<Bird>*, std::vector<Bird>*);
	void improve(Bird);
	int getProfit();
	int getLoad();
	std::vector<int> getConfiguration();
	void setConfiguration(std::vector<int>);
	void print();
};

#endif
