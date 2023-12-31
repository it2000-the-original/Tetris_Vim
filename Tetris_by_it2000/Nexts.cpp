#include "Nexts.hpp"
#include "Piece.hpp"
#include "Tetris.hpp"

array<array<Block, 4>, 3> Nexts::blocks;

void Nexts::init() {

	for (int i = 0; i < nexts.size(); i++) {

		// The number of times witch
		// the piece is repeated in nexts array

		do nexts[i] = rand() % 7;
		while (checkRepeats(nexts[i], i) > 2);
	}
}

void Nexts::update() {

	for (int i = 0; i < blocks.size(); i++) {

		int w = findWidth(nexts[i + 1]);
		int h = findHeight(nexts[i + 1]);

		for (int j = 0; j < blocks[i].size(); j++) {

			blocks[i][j].x = CX + (CS - w) / 2 + int(PB * SC) * (pieces[nexts[i + 1]][j] % 4);
			blocks[i][j].y = CY + CS * i + (CS - h) / 2 + int(PB * SC) * (pieces[nexts[i + 1]][j] / 4);
		}
	}
}

void Nexts::draw() {
	
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

void Nexts::generate() {

	for (int i = 0; i < nexts.size() - 1; i++) {

		nexts[i] = nexts[i + 1];
	}

	do nexts[3] = rand() % 7;
	while (checkRepeats(nexts[3], 3) > 2);
}

int Nexts::get() {

	return nexts[0];
}

int Nexts::checkRepeats(int n, int p) {

	int times = 0;

	for (int i = p; i >= 0; i--) {

		if (nexts[i] == n) times++;
	}

	return times;
}

int Nexts::findWidth(int p) {

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

int Nexts::findHeight(int p) {

	int height = 0;

	for (int i = 0; i < 4; i++) {

		if (pieces[p][i] / 4 > height) {

			height = pieces[p][i] / 4;
		}
	}

	height = (height + 1) * int(PB * SC);

	return height;
}
