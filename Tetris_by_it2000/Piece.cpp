#include "Piece.hpp"
#include "Matrix.hpp"
#include "Tetris.hpp"

using namespace std;

void Piece::set(int p) {

	piece = p;

	x = (Tetris::matrix.matrix.size() - 4) / 2;
	y = 0;

	for (int i = 0; i < 4; i++) {

		blocks[i].x = pieces[piece][i] % 4 + x;
		blocks[i].y = pieces[piece][i] / 4;
	}
}

bool Piece::move(int _x, int _y) {

	if (check(_x, _y)) {

		for (auto& block : blocks) {

			block.x += _x;
			block.y += _y;
		}

		x += _x;
		y += _y;

		return true;
	}

	return false;
}

bool Piece::rotate() {
	
	if (piece != 3) {

		int size;

		array<Block, 4> _blocks = blocks;

		if (piece != 0) size = 2;

		else size = 3;

		for (auto& block : _blocks) {

			int _x = size - (block.y - y) + x;
			int _y = block.x - x + y;
			block.x = _x;
			block.y = _y;
		}

		vector<Block> corrections = { 
			{0, 0}, {1, 0}, {-1, 0}, {0, -1}, 
			{2, 0}, {-2, 0}, {0, -2} 
		};

		for (auto c : corrections) {

			if (check(_blocks, c.x, c.y)) {
				
				blocks = _blocks;
				move(c.x, c.y);
				return true;
			}
		}
	}

	return false;
}

void Piece::fall() {

	while (check(0, 1)) {
		
		move(0, 1);
	}
}

bool Piece::check(array<Block, 4> _blocks, int _x, int _y) {

	bool status = true;

	for (auto& block : _blocks) {

		if (block.x + _x < 0 or block.x + _x >= Tetris::matrix.matrix.size() or
			block.y + _y < 0 or block.y + _y >= Tetris::matrix.matrix[0].size() or
			Tetris::matrix.matrix[block.x + _x][block.y + _y] != -1) {

			status = false;
			break;
		}
	}

	return status;
}

bool Piece::check(array<Block, 4> _blocks) {

	bool status = true;

	for (auto& block : _blocks) {

		if (block.x < 0 or block.x >= Tetris::matrix.matrix.size() or
			block.y < 0 or block.y >= Tetris::matrix.matrix[0].size() or
			Tetris::matrix.matrix[block.x][block.y] != -1) {

			status = false;
			break;
		}
	}

	return status;
}

bool Piece::check(int _x, int _y) {

	bool status = true;

	for (auto& block : blocks) {

		if (block.x + _x < 0 or block.x + _x >= Tetris::matrix.matrix.size() or
			block.y + _y < 0 or block.y + _y >= Tetris::matrix.matrix[0].size() or
			Tetris::matrix.matrix[block.x + _x][block.y + _y] != -1) {

			status = false;
			break;
		}
	}

	return status;
}

void Piece::depose() {

	for (auto& block : blocks) {

		Tetris::matrix.matrix[block.x][block.y] = piece;
	}
}

void Piece::draw() {

	Tetris::blocks.setTextureRect(IntRect(piece * PB, 0, PB, PB));

	for (auto& block : blocks) {

		Tetris::blocks.setPosition(Vector2f(
			float(MX + block.x * PB),
			float(MY + block.y * PB)
		));

		Tetris::window.draw(Tetris::blocks);
	}
}

array<Block, 4> Piece::getBlocks() {

	return blocks;
}

int Piece::getPiece() {

	return piece;
}
