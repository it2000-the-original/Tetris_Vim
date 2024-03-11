#include "Tetromino.hpp"
#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Ghost.hpp"

using namespace std;
using namespace sf;

array<Block, 4> Ghost::blocks;

void Ghost::update() {

	blocks = Tetris::tetromino.getBlocks();

	while (Tetris::tetromino.check(blocks, 0, 1)) {

		for (auto& b: blocks) b.y++;
	}
}

void Ghost::draw() {

	Tetris::blocks.setColor(Color(255, 255, 255, 64));
	Tetris::blocks.setTextureRect(IntRect(Tetris::tetromino.get() * PB, 0, PB, PB));

	for (auto& block : blocks) if (Tetris::matrix.exist(block)) {

		Tetris::blocks.setPosition(Vector2f(
			float(MX + block.x * PB),
			float(MY + block.y * PB)
		));

		Tetris::window->draw(Tetris::blocks);
	}

	Tetris::blocks.setColor(Color(255, 255, 255, 255));
}
