#include "Generator.hpp"
#include "Preview.hpp"
#include "Tetris.hpp"
#include "Piece.hpp"

Generator Preview::generator;
array<array<Block, 4>, 3> Preview::blocks;

void Preview::init() {

	generator.generate();

	for (int i = 0; i < nexts.size(); i++) {

		nexts[i] = generator.getNext();
	}
}

void Preview::update() {

	for (int i = 0; i < blocks.size(); i++) {

		int w = findWidth(nexts[i + 1]);
		int h = findHeight(nexts[i + 1]);

		for (int j = 0; j < blocks[i].size(); j++) {

			blocks[i][j].x = CX + (CS - w) / 2 + int(PB * SC) * (pieces[nexts[i + 1]][j] % 4);
			blocks[i][j].y = CY + CS * i + (CS - h) / 2 + int(PB * SC) * (pieces[nexts[i + 1]][j] / 4);
		}
	}
}

void Preview::draw() {
	
	Tetris::blocks.setScale(Vector2f(SC, SC));

	for (int i = 0; i < blocks.size(); i++) {

		Tetris::blocks.setTextureRect(IntRect(nexts[i + 1] * PB, 0, PB, PB));

		for (auto& b : blocks[i]) {

			Tetris::blocks.setPosition(Vector2f(float(b.x), float(b.y)));
			Tetris::window.draw(Tetris::blocks);
		}
	}

	Tetris::blocks.setScale(Vector2f(1.0f, 1.0f));
}

void Preview::generate() {

	for (int i = 0; i < nexts.size() - 1; i++) {

		nexts[i] = nexts[i + 1];
	}

	nexts[3] = generator.getNext();
}

int Preview::get() {

	return nexts[0];
}

int Preview::findWidth(int p) {

	int width = 0;

	for (int i = 0; i < 4; i++) {

		if (pieces[p][i] % 4 > width) {

			width = pieces[p][i] % 4;
		}
	}

	if (p == 3) width++;

	width = (width + 1) * int(PB * SC);

	return width;
}

int Preview::findHeight(int p) {

	int height = 0;

	for (int i = 0; i < 4; i++) {

		if (pieces[p][i] / 4 > height) {

			height = pieces[p][i] / 4;
		}
	}

	height = (height + 1) * int(PB * SC);

	return height;
}
