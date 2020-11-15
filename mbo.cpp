#include<iostream>
#include<cstring>
#include<vector>

#include"params.h"

int main(int argc, char *argv[])
{
	int params_state;

	int capacity;
	std::vector<int> weights;
	std::vector<int> prices;

	params_state = parse_params(argc, argv, &capacity, &weights, &prices);

	if(params_state < 0) {
		return params_state;
	}
	else if(params_state == 0) {
		std::cout << "Capacity: " << capacity << std::endl;
		
		std::cout << "Weights: ";
		for(auto weight = weights.begin(); weight != weights.end(); weight++) {
			std::cout << *weight << " ";
		}
		std::cout << std::endl;

		std::cout << "Prices: ";
		for(auto price = prices.begin(); price != prices.end(); price++) {
			std::cout << *price << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}