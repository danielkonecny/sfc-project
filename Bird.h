class Bird {
private:
	std::vector<int> configuration;

public:
	Bird(int, int, std::vector<int>);
	int get_profit(std::vector<int>);
	int get_load(std::vector<int>);
	std::string get_config();
};