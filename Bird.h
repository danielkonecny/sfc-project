#include"mbo.h"

class Bird {
private:
	Mbo mbo;
	std::vector<int> configuration;

public:
	Bird(Mbo);

	void initBird();
	void initBird(std::vector<std::vector<int>>);
	void findNeighbors(std::vector<Bird>*);
	void findNeighbors(std::vector<Bird>*, std::vector<Bird>*);
	void improve(Bird);
	int getProfit();
	int getLoad();
	std::vector<int> getConfiguration();
	void setConfiguration(std::vector<int>);
	void printMe();
};

void sortByProfit(std::vector<Bird> *birds);
