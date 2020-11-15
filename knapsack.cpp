#include<iostream>
#include<string>
#include<vector>

#include"Bird.h"
#include"mbo.h"
#include"params.h"

int main(int argc, char *argv[])
{
	int params_state;

	int capacity;
	int objects;
	std::vector<int> weights;
	std::vector<int> profits;

	params_state = parse_params(argc, argv, &capacity, &objects, &weights, &profits);

	if(params_state < 0) {
		return params_state;
	}
	else if(params_state == 0) {
		std::cout << "Capacity: " << capacity << std::endl;

		std::cout << "Number of items: " << objects << std::endl; 
		
		std::cout << "Weights: ";
		for(auto weight = weights.begin(); weight != weights.end(); weight++) {
			std::cout << *weight << " ";
		}
		std::cout << std::endl;

		std::cout << "Profits: ";
		for(auto profit = profits.begin(); profit != profits.end(); profit++) {
			std::cout << *profit << " ";
		}
		std::cout << std::endl;

		Bird bird(capacity, objects, weights);
		std::cout << "Configuration: " << bird.get_config() << std::endl;
		std::cout << "Load: " << bird.get_load(weights) << std::endl;
		std::cout << "Profit: " << bird.get_profit(profits) << std::endl;
	}

	return 0;
}