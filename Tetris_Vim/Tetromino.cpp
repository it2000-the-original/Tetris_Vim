#include "Tetromino.hpp"
#include "Controls.hpp"
#include "Matrix.hpp"
#include "Tetris.hpp"

using namespace std;
using namespace sf;

void Tetromino::draw() {

	Tetris::blocks.setTextureRect(IntRect(tetromino * PB, 0, PB, PB));

	for (auto& block : blocks) {

		if (Tetris::matrix.exist(block)) {

			Tetris::blocks.setPosition(Vector2f(
				float(MX + block.x * PB),
				float(MY + block.y * PB)
			));

			Tetris::window->draw(Tetris::blocks);
		}
	}
}

int Tetromino::get() {

	return tetromino;
}

void Tetromino::set(int _tetromino) {

	tetromino = _tetromino;
	rstatus = 0;

	x = (Matrix::W - 4) / 2;
	y = 0;

	for (int i = 0; i < 4; i++) {

		blocks[i].x = t::tetrominos[tetromino][i] % 4 + x;
		blocks[i].y = t::tetrominos[tetromino][i] / 4;
	}

	if (tetromino == 3) y--;
}

bool Tetromino::move(int _x, int _y) {

	if (check(_x, _y)) {

		for (auto& block : blocks) {
			block.x += _x;
			block.y += _y;
		}

		x += _x; y += _y;

		return true;
	}

	return false;
}

bool Tetromino::rotate() {
	
	int size = getWidth(tetromino) - 1;

	Blocks _blocks = blocks;

	for (auto& block : _blocks) {

		int _x = size - (block.y - y) + x;
		int _y = block.x - x + y;

		block.x = _x;
		block.y = _y;
	}

	return _checkWkicks(_blocks);
}

bool Tetromino::check(Blocks _blocks, int _x, int _y) {

	for (auto& block : _blocks) {

		if (!Tetris::matrix.empty(Block(block.x + _x, block.y + _y))) {

			return false;
		}
	}

	return true;;
}

bool Tetromino::check(Blocks _blocks) {

	for (auto& block : _blocks) {

		if (!Tetris::matrix.empty(block)) {

			return false;
		}
	}

	return true;
}

bool Tetromino::check(int _x, int _y) {

	for (auto& block : blocks) {

		if (!Tetris::matrix.empty(Block(block.x + _x, block.y + _y))) {

			return false;
		}
	}

	return true;
}

bool Tetromino::depose() {

	for (auto& block : blocks) {

		Tetris::matrix.set(block, tetromino);
	}

	return true;
}

bool Tetromino::checkTSpin() {

	if (tetromino == 5) {

		int ablocks = _TSpinABlocks(); // Anterior blocks
		int pblocks = _TSpinPBlocks(); // Posterior blocks

		if (ablocks + pblocks >= 3) {

			if (ablocks == 2 or wkick == 4) return true;
		}
	}

	return false;
}

bool Tetromino::checkMiniTSpin() {

	if (tetromino == 5) {

		int ablocks = _TSpinABlocks(); // Anterior blocks
		int pblocks = _TSpinPBlocks(); // Posterior blocks

		if (ablocks + pblocks >= 3) {

			if (pblocks == 2 and wkick != 4) return true;
		}
	}

	return false;
}

Blocks Tetromino::getBlocks() {

	return blocks;
}

int Tetromino::getWidth(int _tetromino) {

	if (_tetromino == 0 or
		_tetromino == 3) return 4;

	return 3;
}

int Tetromino::getHeight(int _tetromino) {

	if (_tetromino == 0) return 3;

	return 2;
}

bool Tetromino::_checkWkicks(Blocks _blocks) {

	Tests _WKTests = _getWKTests();
	Test test = _WKTests[rstatus];

	for (int i = 0; i < test.size(); i++) {

		if (check(_blocks, test[i].x, test[i].y)) {
		
			wkick = i;
			_confirmRotation(_blocks, test[i]);
			return true;
		}
	}

	return false;
}

void Tetromino::_confirmRotation(Blocks _blocks, Block _move) {

	blocks = _blocks;
	move(_move.x, _move.y);
	rstatus = (rstatus + 1) % 4;
}

int Tetromino::_TSpinABlocks() {

	int ablocks = 0;
	int _x, _y, x_, y_;

	switch (rstatus) {
	case 0: _x = x;     x_ = x + 2; _y = y;      y_ = y;     break;
	case 1: _x = x + 2; x_ = x + 2; _y = y;      y_ = y + 2; break;
	case 2: _x = x;     x_ = x + 2; _y = y + 2;  y_ = y + 2; break;
	case 3: _x = x;     x_ = x;     _y = y;      y_ = y + 2; break;
	}

	if (Tetris::matrix.get(Block(_x, _y)) != -1) ablocks++;
	if (Tetris::matrix.get(Block(x_, y_)) != -1) ablocks++;

	return ablocks;
}

int Tetromino::_TSpinPBlocks() {

	int pblocks = 0;
	int _x, _y, x_, y_;

	switch (rstatus) {
	case 0: _x = x;     x_ = x + 2; _y = y + 2; y_ = y + 2; break;
	case 1: _x = x;     x_ = x;     _y = y;     y_ = y + 2; break;
	case 2: _x = x;     x_ = x + 2; _y = y;     y_ = y + 2; break;
	case 3: _x = x + 2; x_ = x + 2; _y = y;     y_ = y + 2; break;
	}

	if (Tetris::matrix.get(Block(_x, _y)) != -1) pblocks++;
	if (Tetris::matrix.get(Block(x_, y_)) != -1) pblocks++;

	return pblocks;
}

Tests Tetromino::_getWKTests() {

	if (tetromino == 0) {

		return IWKTests;
	}

	return WKTests;
}
