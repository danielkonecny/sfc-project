#ifndef MBO_H
#define MBO_H

#include "Knapsack.h"
#include "Bird.h"

class Mbo {
private:
	int bird_count;
	int neighbor_count;
	int shared_count;
	int tour_count;
	int stop_criteria;
	std::vector<Bird> birds;
	std::vector<Bird> neighbors_leader;
	std::vector<Bird> neighbors_successor;
	Knapsack knapsack;

public:
	Mbo(void);
	
	void initMbo(int, int, int, int, Knapsack);

	int getBirdCount();
	int getNeighborCount();
	int getSharedCount();
	int getTourCount();
	int getStopCriteria();
	std::vector<Bird> getBirds();
	Bird getBird(int);
	Knapsack getKnapsack();

	void setBirdCount(int);
	void setNeighborCount(int);
	void setSharedCount(int);
	void setTourCount(int);
	void setStopCriteria(int);
	void setBirds(std::vector<Bird>);
	void setBird(Bird, int);
	void setKnapsack(Knapsack);

	void optimize();
	bool testStopCriteria();
	void decreaseStopCriteriaWithTour();
	void trainTour();
	void rotateBirds(int);
	int getBestProfit();
	std::vector<int> getBestConfiguration();
	int evaluate();
	void updateStats(int*, int*, int*);

	void print();
	void printResults();
	void printConfiguration();
};

#endif
