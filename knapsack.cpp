#include<iostream>
#include<string>
#include<vector>

#include"Bird.h"
#include"params.h"

int main(int argc, char *argv[])
{
	const int neighbor_count = 3;

	int params_state;

	int capacity;
	int item_count;
	std::vector<int> weights;
	std::vector<int> profits;

	params_state = parse_params(argc, argv, &capacity, &item_count, &weights, &profits);

	if(params_state < 0) {
		return params_state;
	}
	else if(params_state == 0) {
		Mbo mbo(capacity, item_count, weights, profits);

		mbo.printMe();

		Bird bird(mbo);
		bird.initBird();
		bird.printMe();

		std::vector<Bird> neighbors(neighbor_count, bird);

		bird.findNeighbors(&neighbors);

		for(auto &neighbor : neighbors)
			neighbor.printMe();

		/*
		Bird neighbor(mbo);
		bird.findNeighbors(&neighbor);
		neighbor.printMe();
		*/

		/*
		Bird neighbor(mbo);
		neighbor.findNeighbors(capacity, item_count, weights, configuration);
		neighbor.printMe();
		*/
	}

	return 0;
}