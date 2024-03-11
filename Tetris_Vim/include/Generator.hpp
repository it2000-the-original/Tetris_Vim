#include <vector>

using Bag = std::vector<int>;

class Generator {

private:

	const Bag bag = { 0, 1, 2, 3, 4, 5, 6 };
	Bag tetrominoes;

public:

	void generate();
	int getNext();
};