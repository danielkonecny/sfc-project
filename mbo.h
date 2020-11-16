class Mbo {
private:
	int capacity;
	int item_count;
	std::vector<int> weights;
	std::vector<int> profits;

public:
	Mbo(void);
	Mbo(int, int, std::vector<int>, std::vector<int>);

	int getCapacity();
	int getItemCount();
	std::vector<int> getWeights();
	std::vector<int> getProfits();
	int getWeight(int);
	int getProfit(int);
	void printMe();
};
