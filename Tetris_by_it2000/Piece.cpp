#include "Piece.hpp"
#include "Matrix.hpp"
#include "Tetris.hpp"

using namespace std;

void Piece::set(int p) {

	piece = p;
	rstatus = 0;

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

		int size; // Size of the piece in blocks

		if (piece != 0) size = 2;
		else size = 3;

		array<Block, 4> _blocks = blocks;

		for (auto& block : _blocks) {

			int _x = size - (block.y - y) + x;
			int _y = block.x - x + y;
			block.x = _x;
			block.y = _y;
		}

		return wkicks(_blocks);
	}

	return false;
}

int Piece::fall() {

	int lines = 0;

	while (check(0, 1)) {
		
		move(0, 1);
		lines++;
	}

	return lines;
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

bool Piece::checkTSpin() {

	if (piece == 5) {

		// Anterior blocks
		int ablocks = _TSpinABlocks();

		// Posterior blocks
		int pblocks = _TSpinPBlocks();

		if (ablocks + pblocks >= 3) {

			if (ablocks == 2 or wkick == 4) return true;
		}
	}

	return false;
}

bool Piece::checkMiniTSpin() {

	if (piece == 5) {

		// Anterior blocks
		int ablocks = _TSpinABlocks();

		// Posterior blocks
		int pblocks = _TSpinPBlocks();

		if (ablocks + pblocks >= 3) {

			if (pblocks == 2 and wkick != 4) return true;
		}
	}

	return false;
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

bool Piece::wkicks(std::array<Block, 4> _blocks) {

	array<array<Block, 5>, 4> _WKTests;

	if (piece != 0) _WKTests = WKTests;
	else _WKTests = IWKTests;
	wkick = 0;

	for (auto c : _WKTests[rstatus]) {

		if (check(_blocks, c.x, c.y)) {
		
			rstatus = (rstatus + 1) % 4;
			blocks = _blocks;
			move(c.x, c.y);
			return true;
		}

		wkick++;
	}

	return false;
}

array<Block, 4> Piece::getBlocks() {

	return blocks;
}

int Piece::getPiece() {

	return piece;
}

int Piece::_TSpinABlocks() {

	int ablocks = 0;

	switch (rstatus) {

	case 0:
		if (Tetris::matrix.matrix[x][y] != -1) ablocks++;
		if (Tetris::matrix.matrix[x + 2][y] != -1) ablocks++;
		break;

	case 1:
		if (Tetris::matrix.matrix[x + 2][y] != -1) ablocks++;
		if (Tetris::matrix.matrix[x + 2][y + 2] != -1) ablocks++;
		break;

	case 2:
		if (Tetris::matrix.matrix[x][y + 2] != -1) ablocks++;
		if (Tetris::matrix.matrix[x + 2][y + 2] != -1) ablocks++;
		break;

	case 3:
		if (Tetris::matrix.matrix[x][y] != -1) ablocks++;
		if (Tetris::matrix.matrix[x][y + 2] != -1) ablocks++;
		break;
	}

	return ablocks;
}

int Piece::_TSpinPBlocks() {

	int pblocks = 0;

	switch (rstatus) {

	case 0:
		if (y + 2 >= Matrix::H) { pblocks += 2; break; }
		if (Tetris::matrix.matrix[x][y + 2] != -1) pblocks++;
		if (Tetris::matrix.matrix[x + 2][y + 2] != -1) pblocks++;
		break;

	case 1:
		if (x < 0) { pblocks += 2; break; }
		if (Tetris::matrix.matrix[x][y] != -1) pblocks++;
		if (Tetris::matrix.matrix[x][y + 2] != -1) pblocks++;
		break;

	case 2:
		if (Tetris::matrix.matrix[x][y] != -1) pblocks++;
		if (Tetris::matrix.matrix[x + 2][y] != -1) pblocks++;
		break;

	case 3:
		if (x + 2 >= Matrix::W) { pblocks += 2; break; }
		if (Tetris::matrix.matrix[x + 2][y] != -1) pblocks++;
		if (Tetris::matrix.matrix[x + 2][y + 2] != -1) pblocks++;
		break;
	}

	return pblocks;
}
