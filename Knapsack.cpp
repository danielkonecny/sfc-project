#include <iostream>
#include <string>
#include <vector>

#include "Knapsack.h"

Knapsack::Knapsack() {
	this->test_count = 1;
}

void Knapsack::initKnapsack(int capacity, int item_count,
	std::vector<int> weights, std::vector<int> profits, std::vector<int> solutions) {
	this->capacity = capacity;
	this->item_count = item_count;
	this->weights = weights;
	this->profits = profits;
	this->solutions = solutions;
}

int Knapsack::getCapacity() {
	return this->capacity;
}

int Knapsack::getItemCount() {
	return this->item_count;
}

std::vector<int> Knapsack::getWeights() {
	return this->weights;
}

std::vector<int> Knapsack::getProfits() {
	return this->profits;
}

std::vector<int> Knapsack::getSolutions() {
	return this->solutions;
}

int Knapsack::getTestCount() {
	return this->test_count;
}

void Knapsack::setCapacity(int capacity) {
	this->capacity = capacity;
}

void Knapsack::setItemCount(int item_count) {
	this->item_count = item_count;
}

void Knapsack::setWeights(std::vector<int> weights) {
	this->weights = weights;
}

void Knapsack::setProfits(std::vector<int> profits) {
	this->profits = profits;
}

void Knapsack::setSolutions(std::vector<int> solutions) {
	this->solutions = solutions;
}

void Knapsack::setTestCount(int test_count) {
	this->test_count = test_count;
}

int Knapsack::getWeight(int index) {
	return this->weights[index];
}

int Knapsack::getProfit(int index) {
	return this->profits[index];
}

int Knapsack::countWeight(std::vector<int> configuration) {
	int weight = 0;

	for(size_t i = 0; i < (long unsigned)this->item_count; i++)
		weight += configuration[i]*this->getWeight(i);

	return weight;
}

int Knapsack::countProfit(std::vector<int> configuration) {
	int profit = 0;

	for(size_t i = 0; i < (long unsigned)this->item_count; i++)
		profit += configuration[i]*this->getProfit(i);

	return profit;
}

void Knapsack::print() {
	std::cout << "KNAPSACK PARAMETERS" << std::endl;
	std::cout << "Capacity: " << this->capacity << std::endl;
	std::cout << "Number of items: " << this->item_count << std::endl;
	std::cout << "Weights - Profits:" << std::endl;
	for(size_t i = 0; i < this->weights.size(); i++) {
		std::cout << i+1 << ": " << this->getWeight(i) << " - ";
		std::cout << this->getProfit(i) << std::endl;
	}
	std::cout << std::endl;
}
