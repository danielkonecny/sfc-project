#ifndef KNAPSACK_H
#define KNAPSACK_H

class Knapsack {
private:
	int capacity;
	int item_count;
	std::vector<int> weights;
	std::vector<int> profits;
	std::vector<int> solutions;
	int test_count;

public:
	Knapsack(void);
	
	void initKnapsack(int, int, std::vector<int>, std::vector<int>, std::vector<int>);

	int getCapacity();
	int getItemCount();
	std::vector<int> getWeights();
	int getWeight(int);
	std::vector<int> getProfits();
	int getProfit(int);
	std::vector<int> getSolutions();
	int getTestCount();

	void setCapacity(int);
	void setItemCount(int);
	void setWeights(std::vector<int>);
	void setProfits(std::vector<int>);
	void setSolutions(std::vector<int>);
	void setTestCount(int);

	int countWeight(std::vector<int>);
	int countProfit(std::vector<int>);

	void print();
};

#endif
