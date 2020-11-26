#include<iostream>
#include<string>
#include<vector>

#include "mbo.h"

Mbo::Mbo() {}

Mbo::Mbo(int capacity, int item_count, std::vector<int> weights, std::vector<int> profits) {
	this->capacity = capacity;
	this->item_count = item_count;
	this->weights = weights;
	this->profits = profits;
}

int Mbo::getCapacity() {
	return this->capacity;
}

int Mbo::getItemCount() {
	return this->item_count;
}

std::vector<int> Mbo::getWeights() {
	return this->weights;
}

std::vector<int> Mbo::getProfits() {
	return this->profits;
}

int Mbo::getWeight(int index) {
	return this->weights[index];
}

int Mbo::getProfit(int index) {
	return this->profits[index];
}

void Mbo::printMe() {
	std::cout << "KNAPSACK PROBLEM 01" << std::endl;

	std::cout << "Capacity: " << this->capacity << std::endl;

	std::cout << "Number of items: " << this->item_count << std::endl; 
	
	std::cout << "Weights: ";
	for(auto weight = this->weights.begin(); weight != this->weights.end(); weight++) {
		std::cout << *weight << " ";
	}
	std::cout << std::endl;

	std::cout << "Profits: ";
	for(auto profit = this->profits.begin(); profit != this->profits.end(); profit++) {
		std::cout << *profit << " ";
	}
	std::cout << std::endl;
}
