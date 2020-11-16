#include"mbo.h"

class Bird {
private:
	Mbo mbo;
	std::vector<int> configuration;

public:
	Bird(Mbo);

	void initBird();
	void findNeighbors(std::vector<Bird>*);
	//void findNeighbors(Bird*);
	//void findNeighbors(int, int, std::vector<int>, std::vector<int>);
	int getProfit();
	int getLoad();
	std::vector<int> getConfiguration();
	void printMe();
};