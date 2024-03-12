#include "Tetromino.hpp"
#include "Tetris.hpp"
#include "Hold.hpp"

using namespace sf;

void Hold::init() {

	holdText.setString("Hold");
	holdText.setCharacterSize(S);
	holdText.setFont(Tetris::font);
	holdText.setColor(Color::Yellow);
	holdText.setPosition(Vector2f(
		float(PX + (PW - holdText.getLocalBounds().width) / 2),
		float(PY + (TH - holdText.getLocalBounds().height) / 2)
	));
	
	tetromino = -1;
}

void Hold::update() {
	
	if (tetromino != -1) {

		int w = int(Tetromino::getWidth(tetromino) * PB * SC);
		int h = int(Tetromino::getHeight(tetromino) * PB * SC);

		for (int i = 0; i < blocks.size(); i++) {

			blocks[i].x = int(PX + (PW - w) / 2 + t::tetrominos[tetromino][i] % 4 * PB * SC);
			blocks[i].y = int(PY + (PW - h) / 2 + t::tetrominos[tetromino][i] / 4 * PB * SC + TH);
		}
	}
}

void Hold::draw() {

	Tetris::window->draw(holdText);

	if (tetromino != -1) {

		Tetris::blocks.setScale(Vector2f(SC, SC));
		Tetris::blocks.setTextureRect(IntRect(tetromino * PB, 0, PB, PB));

		for (auto& block : blocks) {

			Tetris::blocks.setPosition(Vector2f(float(block.x), float(block.y)));
			Tetris::window->draw(Tetris::blocks);
		}

		Tetris::blocks.setScale(Vector2f(1.f, 1.f));
	}
}

int Hold::get() {
	
	return tetromino;
}

void Hold::set(int t) {
	
	tetromino = t;
}
