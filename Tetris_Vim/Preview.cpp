#include "Tetromino.hpp"
#include "Generator.hpp"
#include "Preview.hpp"
#include "Tetris.hpp"

using namespace sf;
using namespace std;

Generator Preview::generator;
Tetrominos Preview::tetrominos;

void Preview::init() {

	generator.generate();

	for (auto& n : next) {

		n = generator.getNext();
	}
}

void Preview::update() {

	for (int i = 0; i < tetrominos.size(); i++) {

		int w = Tetromino::getWidth (next[i + 1]) * PB * SC;
		int h = Tetromino::getHeight(next[i + 1]) * PB * SC;

		for (int j = 0; j < 4; j++) {

			// Set the position of the block in the preview panel
			tetrominos[i][j].x = PX + (PS - w) / 2 + int(PB * SC) * (t::tetrominos[next[i + 1]][j] % 4);
			tetrominos[i][j].y = PY + (PS - h) / 2 + int(PB * SC) * (t::tetrominos[next[i + 1]][j] / 4) + PS * i;
		}
	}
}

void Preview::draw() {
	
	Tetris::blocks.setScale(Vector2f(SC, SC));

	for (int i = 0; i < tetrominos.size(); i++) {

		Tetris::blocks.setTextureRect(IntRect(next[i + 1] * PB, 0, PB, PB));

		for (auto& block : tetrominos[i]) {

			Tetris::blocks.setPosition(Vector2f(block.x, block.y));
			Tetris::window->draw(Tetris::blocks);
		}
	}

	Tetris::blocks.setScale(Vector2f(1.0f, 1.0f));
}

void Preview::generate() {

	for (int i = 0; i < next.size() - 1; i++) {

		next[i] = next[i + 1];
	}

	next[next.size() - 1] = generator.getNext();
}

int Preview::get() {

	return next[0];
}
