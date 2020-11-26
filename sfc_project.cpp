#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "sfc_project.h"
#include "params.h"
#include "Knapsack.h"
#include "Mbo.h"
#include "Bird.h"

// Number of birds.
#define z 71
// Number of neighbors of leader bird.
#define k 5
// Number of shared neighbors.
#define x 1
// Number of tours.
#define m 30

int main(int argc, char *argv[])
{
	Knapsack knapsack;
	int params_state = parse_params(argc, argv, &knapsack);
	int test_best = 0;
	int test_worst = 0;
	int test_sum = 0;

	// Error in input parameters.
	if(params_state < 0) {
		return params_state;
	}
	// Help or version parameter.
	else if(params_state == 1) {
		return 0;
	}

	// Run multiple times if test mode enabled.
	for(int i = 0; i < knapsack.getTestCount(); i++) {
		Mbo mbo;
		mbo.initMbo(z, k, x, m, knapsack);

		// Debug mode.
		if(params_state == 2) {
			knapsack.print();
			mbo.print();
		}
		
		mbo.optimize();

		if(params_state == 0) {
			mbo.printConfiguration();
		}
		// Debug mode.
		else if(params_state == 2) {
			mbo.printResults();
		}
		// Test mode.
		else if(params_state == 3) {
			mbo.updateStats(&test_best, &test_worst, &test_sum);
		}
	}

	// Test mode.
	if(params_state == 3) {
		std::cout << "Test Results (" << knapsack.getTestCount() << " runs):" << std::endl;
		std::cout << "- Best: " << test_best << std::endl;
		std::cout << std::fixed << std::setprecision(1);
		std::cout << "- Average: " << (double)test_sum / (double)(knapsack.getTestCount()) << std::endl;
		std::cout << "- Worst: " << test_worst << std::endl;
	}

	return 0;
}