#include <vector>

class Generator {

private:

	const std::vector<int> bag = { 0, 1, 2, 3, 4, 5, 6 };
	std::vector<int> tetrominoes;

public:

	void generate();
	int getNext();
};