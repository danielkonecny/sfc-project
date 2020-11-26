#include <iostream>
#include <vector>

#include "Mbo.h"

Mbo::Mbo() {}

void Mbo::initMbo(int bird_count, int neighbor_count, int shared_count,
	int tour_count, Knapsack knapsack) {

	this->bird_count = bird_count;
	this->neighbor_count = neighbor_count;
	this->shared_count = shared_count;
	this->tour_count = tour_count;
	this->stop_criteria = \
		knapsack.getItemCount() * knapsack.getItemCount() * knapsack.getItemCount();

	Bird auxiliary_bird(knapsack);
	std::vector<Bird> birds(this->bird_count, auxiliary_bird);
	for(auto &bird : birds)
		bird.initBird();
	this->birds = birds;

	std::vector<Bird> neighbors_leader(this->neighbor_count, auxiliary_bird);
	std::vector<Bird> neighbors_successor;
	this->neighbors_leader = neighbors_leader;
	this->neighbors_successor = neighbors_successor;

	this->knapsack = knapsack;
}

int Mbo::getBirdCount() {
	return this->bird_count;
}

int Mbo::getNeighborCount() {
	return this->neighbor_count;
}

int Mbo::getSharedCount() {
	return this->shared_count;
}

int Mbo::getTourCount() {
	return this->tour_count;
}

int Mbo::getStopCriteria() {
	return this->stop_criteria;
}

std::vector<Bird> Mbo::getBirds() {
	return this->birds;
}

Bird Mbo::getBird(int index) {
	return this->birds[index];
}

Knapsack Mbo::getKnapsack() {
	return this->knapsack;
}

void Mbo::setBirdCount(int bird_count) {
	this->bird_count = bird_count;
}

void Mbo::setNeighborCount(int neighbor_count) {
	this->neighbor_count = neighbor_count;
}

void Mbo::setSharedCount(int shared_count) {
	this->shared_count = shared_count;
}

void Mbo::setTourCount(int tour_count) {
	this->tour_count = tour_count;
}

void Mbo::setStopCriteria(int stop_criteria) {
	this->stop_criteria = stop_criteria;
}

void Mbo::setBirds(std::vector<Bird> birds) {
	this->birds = birds;
}

void Mbo::setBird(Bird bird, int index) {
	this->birds[index] = bird;
}

void Mbo::setKnapsack(Knapsack knapsack) {
	this->knapsack = knapsack;
}

void Mbo::optimize() {
	for(int step = 0; this->testStopCriteria(); step++) {
		for(int tour = 0; tour < this->getTourCount(); tour++) {
			this->trainTour();
			this->decreaseStopCriteriaWithTour();
		}
		this->rotateBirds(step);
	}
}

bool Mbo::testStopCriteria() {
	return this->stop_criteria > 0;
}

void Mbo::decreaseStopCriteriaWithTour() {
	this->stop_criteria -= this->getBirdCount();
}

void Mbo::trainTour() {
	Bird empty_bird(this->getKnapsack());

	// UPDATE LEADER
	this->birds[0].findNeighbors(&this->neighbors_leader);
	this->birds[0].improve(this->neighbors_leader[0]);

	// UPDATE LEFT BRANCH OF V
	this->neighbors_successor = this->neighbors_leader;
	for(int left = 1; left < this->getBirdCount(); left += 2) {
		std::vector<Bird> shared;
		for(int i = 1; i < this->getSharedCount()+1; i++)
			shared.push_back(this->neighbors_successor[i]);
		this->birds[left].findNeighbors(&this->neighbors_successor, &shared);
		this->birds[left].improve(this->neighbors_successor[0]);
	}

	// UPDATE RIGHT BRANCH OF V
	this->neighbors_successor = this->neighbors_leader;

	// Erase neighbors sent to the left...
	this->neighbors_successor.erase(this->neighbors_successor.begin()+1,
		this->neighbors_successor.begin()+this->shared_count+1); 

	// ...and append new zero-initialized birds ínstead of the erased ones.
	std::vector<Bird> erased_neighbors(this->shared_count, empty_bird);
	this->neighbors_successor.insert(this->neighbors_successor.end(),
		std::begin(erased_neighbors), std::end(erased_neighbors));

	for(int right = 2; right < this->getBirdCount(); right += 2) {
		std::vector<Bird> shared;
		for(int i = 1; i < this->getSharedCount()+1; i++)
			shared.push_back(this->neighbors_successor[i]);
		this->birds[right].findNeighbors(&this->neighbors_successor, &shared);
		this->birds[right].improve(this->neighbors_successor[0]);
	}
}

void Mbo::rotateBirds(int step) {
	Bird tmp = this->getBird(0);
	// Left branch rotation.
	if(step % 2 == 0) {
		this->setBird(this->getBird(1), 0);
		for(int i = 3; i < this->getBirdCount(); i += 2)
			this->setBird(this->getBird(i), i - 2);
		this->setBird(tmp, this->getBirdCount() - 2);
	}
	// Right branch rotation.
	else {
		for(int i = 2; i < this->getBirdCount(); i += 2)
			this->setBird(this->getBird(i), i - 2);
		this->setBird(tmp, this->getBirdCount() - 1);
	}
}

int Mbo::getBestProfit() {
	int best_profit = -1;
	for(auto &bird : this->getBirds()) {
		int profit = bird.getProfit();
		if(profit > best_profit) {
			best_profit = profit;
		}
	}
	return best_profit;
}

std::vector<int> Mbo::getBestConfiguration() {
	std::vector<int> best_configuration;
	int best_profit = -1;
	for(auto &bird : this->getBirds()) {
		int profit = bird.getProfit();
		if(profit > best_profit) {
			best_profit = profit;
			best_configuration = bird.getConfiguration();
		}
	}
	return best_configuration;
}

int Mbo::evaluate() {
	Bird solution_bird(this->getKnapsack());
	solution_bird.setConfiguration(knapsack.getSolutions());

	if(this->getBestProfit() == solution_bird.getProfit()) {
		if(this->getBestConfiguration() == solution_bird.getConfiguration())
			return 0;
		else
			return 1;
	}
	else {
		return -1;
	}
}

void Mbo::updateStats(int *test_best, int *test_worst, int *test_sum) {
	int profit = this->getBestProfit();
	if((*test_best) == 0 && (*test_worst) == 0 && (*test_sum) == 0) {
		(*test_best) = profit;
		(*test_worst) = profit;
		(*test_sum) = profit;
	}
	else if((*test_best) > 0 && (*test_worst) > 0 && (*test_sum) > 0) {
		if((*test_best) < profit)
			(*test_best) = profit;
		else if(*test_worst > profit)
			(*test_worst) = profit;
		(*test_sum) += profit;
	}
	else {
		std::cerr << "Unexpected test values!" << std::endl;
		exit(-1);
	}
}

void Mbo::print() {
	std::cout << "MIGRATING BIRDS OPTIMIZATION" << std::endl;
	std::cout << "Bird count (z): " << this->getBirdCount() << std::endl;
	std::cout << "Neighbor count (k): " << this->getNeighborCount() << std::endl;
	std::cout << "Shared count (x): " << this->getSharedCount() << std::endl;
	std::cout << "Tour count (m): " << this->getTourCount() << std::endl;
	std::cout << "Stop criteria (K): " << this->getStopCriteria() << std::endl << std::endl;
}

void Mbo::printResults() {
	int evaluation = this->evaluate();

	if(evaluation == 0) {
		std::cout << "CORRECT!" << std::endl;
		std::cout << "Profit: " << this->getBestProfit() << std::endl;
	}
	else if(evaluation > 0) {
		std::cout << "CORRECT - ALTERNATIVE SOLUTION!" << std::endl;
		std::cout << "Profit: " << this->getBestProfit() << std::endl;
		std::cout << "Differences: MBO (weight-profit) - Best (weight-profit)" << std::endl;
		for(size_t i = 0; i < (long unsigned)this->getKnapsack().getItemCount(); i++) {
			if(this->getBestConfiguration()[i] != knapsack.getSolutions()[i]) {
				std::cout << i+1 << ": " << "(" << this->getBestConfiguration()[i]*knapsack.getWeight(i);
				std::cout << "-" << this->getBestConfiguration()[i]*knapsack.getProfit(i) << ") - ";
				std::cout << "(" << knapsack.getSolutions()[i]*knapsack.getWeight(i) << "-";
				std::cout << knapsack.getSolutions()[i]*knapsack.getProfit(i) << ")" << std::endl;
			}
		}
	}
	else {
		std::cout << "FALSE! (Knapsack Capacity: " << knapsack.getCapacity() << ")" << std::endl;
		std::cout << "MBO:\n- Profit: " << this->getBestProfit();
		std::cout << "\n- Used Capacity: " << knapsack.countWeight(this->getBestConfiguration()) << std::endl;
		std::cout << "Best Solution:\n- Profit: " << knapsack.countProfit(knapsack.getSolutions());
		std::cout << "\n- Used Capacity: " << knapsack.countWeight(knapsack.getSolutions()) << std::endl;
		std::cout << "Differences: MBO (weight-profit) - Best (weight-profit)" << std::endl;
		for(size_t i = 0; i < (long unsigned)this->getKnapsack().getItemCount(); i++) {
			if(this->getBestConfiguration()[i] != knapsack.getSolutions()[i]) {
				std::cout << i+1 << ": " << "(" << this->getBestConfiguration()[i]*knapsack.getWeight(i);
				std::cout << "-" << this->getBestConfiguration()[i]*knapsack.getProfit(i) << ") - ";
				std::cout << "(" << knapsack.getSolutions()[i]*knapsack.getWeight(i) << "-";
				std::cout << knapsack.getSolutions()[i]*knapsack.getProfit(i) << ")" << std::endl;
			}
		}
	}
}

void Mbo::printConfiguration() {
	for(auto &config : this->getBestConfiguration()) {
		std::cout << config << std::endl;
	}
}
