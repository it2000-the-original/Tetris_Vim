#include "Tetromino.hpp"
#include "Sounds.hpp"
#include "Matrix.hpp"
#include "Tetris.hpp"
#include "Status.hpp"

using namespace sf;
using namespace std;

void Matrix::init() {

	comboCount = -1;

	for (auto& column : matrix)
	for (auto& box    : column) {

		box = -1;
	}
}

void Matrix::draw() {

	for (int i = 0; i < W; i++)
	for (int j = 0; j < H; j++) {

		if (!empty(Block(i, j))) {

			Tetris::blocks.setTextureRect(IntRect(matrix[i][j] * PB, 0, PB, PB));

			Tetris::blocks.setPosition(Vector2f(
				float(MX + PB * i),
				float(MY + PB * j)
			));

			Tetris::window->draw(Tetris::blocks);
		}
	}
}

void Matrix::checkLines() {

	int removedLines = 0;

	for (int i = 0; i < H; i++) if (_isLineFull(i)) {

		removedLines++;
		remove(i);
		i--;
	}

	_checkLinesScore(removedLines);
	_checkComboScore(removedLines);
	_checkTSpinScore(removedLines);
	_playLinesSounds(removedLines);
}

void Matrix::remove(int l) {

	for (int i = 0; i < W; i++) {
		
		matrix[i][l] = -1;
	}

	for (int i = 0; i < W; i++)

	for (int j = l - 1; j >= 0; j--) {
	
		matrix[i][j + 1] = matrix[i][j];
	}

	Tetris::status.lines++;
	Tetris::status.level_count++;
}

int Matrix::get(Block block) {

	if (block.x < 0 or block.x >= W or block.y >= H) {

		return 0;
	}

	if (block.y < 0) return -1;

	return matrix[block.x][block.y];
}

bool Matrix::empty(Block block) {

	return get(block) == -1;
}

bool Matrix::exist(Block block) {

	if (block.x >= 0 and block.x < W and 
		block.y >= 0 and block.y < H) {

		return true;
	}

	return false;
}

bool Matrix::set(Block block, int value) {

	if (!exist(block)) {

		return false;
	}

	matrix[block.x][block.y] = value;
	return true;
}

void Matrix::_checkLinesScore(int rLines) {

	switch (rLines) {
	case 1: Tetris::status.score += SINGLE * Tetris::status.level; break;
	case 2: Tetris::status.score += DOUBLE * Tetris::status.level; break;
	case 3: Tetris::status.score += TRIPLE * Tetris::status.level; break;
	case 4: Tetris::status.score += TETRIS * Tetris::status.level; break;
	}
}

void Matrix::_checkComboScore(int rLines) {

	if (rLines > 0) {

		comboCount++;
		Tetris::status.score += COMBO * comboCount * Tetris::status.level;
	}

	else comboCount = -1;
}

void Matrix::_checkTSpinScore(int rLines) {

	int score = 0;

	if (Tetris::tetromino.checkTSpin()) {

		score = _checkNormalTSpin(rLines);
	}

	else if (Tetris::tetromino.checkMiniTSpin()) {

		score = _checkMiniTSpin(rLines);
	}

	Tetris::status.score += score;
}

void Matrix::_playLinesSounds(int rLines) {

	if (rLines == 4) {

		Tetris::sounds.playTetrisSound();
	}

	else if (rLines > 0) {

		Tetris::sounds.playRemovedLineSound();
	}
}

bool Matrix::_isLineFull(int line) {

	for (int i = 0; i < W; i++) {

		if (matrix[i][line] == -1) {

			return false;
		}
	}

	return true;
}

int Matrix::_checkNormalTSpin(int rLines) {

	int score = 0;

	switch (rLines) {
	case 0: score = T_SPIN  * Tetris::status.level; break;
	case 1: score = TSINGLE * Tetris::status.level; break;
	case 2: score = TDOUBLE * Tetris::status.level; break;
	case 3: score = TTRIPLE * Tetris::status.level; break;
	}

	return score;
}

int Matrix::_checkMiniTSpin(int rLines) {

	int score = 0;

	switch (rLines) {
	case 0: score = MT_SPIN  * Tetris::status.level; break;
	case 1: score = MTSINGLE * Tetris::status.level; break;
	case 2: score = MTDOUBLE * Tetris::status.level; break;
	}

	return score;
}