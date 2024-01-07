#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Piece.hpp"
#include "Preview.hpp"

using namespace std;

array<Block, 4> Preview::blocks;

void Preview::update() {

	blocks = Tetris::piece.getBlocks();

	while (Tetris::piece.check(blocks, 0, 1)) {

		for (auto& b: blocks) b.y++;
	}
}

void Preview::draw() {

	Tetris::blocks.setColor(Color(255, 255, 255, 64));
	Tetris::blocks.setTextureRect(IntRect(Tetris::piece.getPiece() * PB, 0, PB, PB));

	for (auto& block : blocks) {

		Tetris::blocks.setPosition(Vector2f(
			float(MX + block.x * PB),
			float(MY + block.y * PB)
		));

		Tetris::window.draw(Tetris::blocks);
	}

	Tetris::blocks.setColor(Color(255, 255, 255, 255));
}
