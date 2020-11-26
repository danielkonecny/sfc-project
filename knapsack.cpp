#include<iostream>
#include<string>
#include<vector>

#include"Bird.h"
#include"params.h"

void train_tour(const int z, const int x, Bird bird, std::vector<Bird> *birds,
	std::vector<Bird> *neighbors_leader, std::vector<Bird> *neighbors) {

	/*
	for(auto &single_bird : *birds)
		single_bird.printMe();
	std::cout << std::endl;
	*/

	// UPDATE LEADER
	(*birds)[0].findNeighbors(neighbors_leader);
	sortByProfit(neighbors_leader);
	/*
	std::cout << "0" << std::endl;
	for(auto &neighbor : neighbors_leader)
		neighbor.printMe();
	std::cout << std::endl;
	*/
	(*birds)[0].improve((*neighbors_leader)[0]);

	// UPDATE LEFT BRANCH OF V
	(*neighbors) = (*neighbors_leader);

	for(int left = 1; left < z; left += 2) {
		std::vector<Bird> shared;
		for(int i = 1; i < x+1; i++)
			shared.push_back((*neighbors)[i]);
		(*birds)[left].findNeighbors(neighbors, &shared);
		sortByProfit(neighbors);
		(*birds)[left].improve((*neighbors)[0]);
	}

	// UPDATE RIGHT BRANCH OF V
	// Erase neighbors send to the left and append new zero-initialized birds ínstead or the erased ones.
	(*neighbors) = (*neighbors_leader);
	neighbors->erase(neighbors->begin()+1, neighbors->begin()+x+1);
	std::vector<Bird> erased_neighbors(x, bird);
	neighbors->insert(neighbors->end(), std::begin(erased_neighbors), std::end(erased_neighbors));

	for(int right = 2; right < z; right += 2) {
		std::vector<Bird> shared;
		for(int i = 1; i < x+1; i++)
			shared.push_back((*neighbors)[i]);
		(*birds)[right].findNeighbors(neighbors, &shared);
		sortByProfit(neighbors);
		(*birds)[right].improve((*neighbors)[0]);
	}
}

int main(int argc, char *argv[])
{
	int params_state;

	int capacity;
	int item_count;
	std::vector<int> weights;
	std::vector<int> profits;
	std::vector<int> solutions;

	std::cout << std::endl << "MBO Knapsack Problem 01 Solver" << std::endl << std::endl;

	params_state = parse_params(argc, argv, &capacity, &item_count, &weights, &profits, &solutions);

	if(params_state < 0) {
		return params_state;
	}
	else if(params_state == 0) {
		const int z = 71;		// Number of birds.
		const int k = 5;		// Number of neighbors of leader bird.
		const int x = 1;		// Number of shared neighbors.
		const int m = 30;		// Number of tours.
		int K = item_count*item_count*item_count;

		Mbo mbo(capacity, item_count, weights, profits);

		mbo.printMe();
		std::cout << std::endl;

		// Generate initial population of birds.
		Bird bird(mbo);
		std::vector<Bird> birds(z, bird);
		std::vector<std::vector<int>> duplicates;

		for(auto &bird : birds) {
			bird.initBird(duplicates);
			duplicates.push_back(bird.getConfiguration());
		}

		std::vector<Bird> neighbors_leader(k, birds[0]);
		std::vector<Bird> neighbors;
		
		for(int step = 0; step < 2*z; step++) {
			for(int tour = 0; tour < m; tour++) {
				train_tour(z, x, bird, &birds, &neighbors_leader, &neighbors);
				K--;
				if(K < 0)
					break;
			}
			if(K < 0)
				break;

			// ROTATE BIRDS
			Bird tmp = birds[0];
			// LEFT BRANCH ROTATION
			if(step % 2 == 0) {
				birds[0] = birds[1];
				for(int i = 3; i < z; i += 2) {
					birds[i-2] = birds[i];
				}
				birds[z-2] = tmp;
			}
			// RIGHT BRANCH ROTATION
			else {
				for(int i = 2; i < z; i += 2) {
					birds[i-2] = birds[i];
				}
				birds[z-1] = tmp;
			}
		}

		int best_profit = 0;
		std::vector<int> best_config;
		for(auto &bird : birds) {
			int profit = bird.getProfit();
			if(profit > best_profit) {
				best_profit = profit;
				best_config = bird.getConfiguration();
			}
		}

		Bird solution(mbo);
		solution.initBird();
		solution.setConfiguration(solutions);

		if(best_config == solutions) {
			std::cout << "CORRECT!" << std::endl;
		}
		else {
			std::cout << "FALSE!" << std::endl;
			std::cout << "Best profit: " << best_profit << std::endl;
			std::cout << "Best config: ";
			for(auto &config : best_config)
				std::cout << config << " ";
			std::cout << std::endl;
		}
		std::cout << "Solution profit: " << solution.getProfit() << std::endl;
		std::cout << "Solution: ";
		for(auto &solution : solutions)
			std::cout << solution << " ";
		std::cout << std::endl;
	}
	return 0;
}