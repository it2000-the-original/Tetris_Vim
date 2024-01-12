#include "Generator.hpp"
#include <cstdlib>

void Generator::generate() {

	tetrominoes.clear();
	std::vector<int> _bag = bag;

	for (int i = 0; i < 7; i++) {

		int tetro = rand() % _bag.size();
		tetrominoes.push_back(_bag[tetro]);
		_bag.erase(_bag.begin() + tetro);
	}
}

int Generator::getNext() {

	tetrominoes.erase(tetrominoes.begin());

	if (tetrominoes.size() == 0) {
		generate();
	}

	return tetrominoes[0];
}
