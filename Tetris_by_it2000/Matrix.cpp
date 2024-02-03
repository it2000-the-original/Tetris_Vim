#include "Piece.hpp"
#include "Matrix.hpp"
#include "Tetris.hpp"
#include "Status.hpp"

void Matrix::init() {

	comboCount = -1;

	for (auto& column : matrix)
	for (auto& box : column) {

		box = -1;
	}
}

void Matrix::draw() {

	for (int i = 0; i < W; i++)
	for (int j = 0; j < H; j++) {

		if (matrix[i][j] != -1) {

			Tetris::blocks.setTextureRect(IntRect(matrix[i][j] * PB, 0, PB, PB));

			Tetris::blocks.setPosition(Vector2f(
				float(MX + PB * i),
				float(MY + PB * j)
			));

			Tetris::window->draw(Tetris::blocks);
		}
	}
}

void Matrix::check() {

	int removedLines = 0;

	for (int i = 0; i < H; i++) {

		bool full = true;

		for (int j = 0; j < W; j++) {

			if (matrix[j][i] == -1) {

				full = false;
				break;
			}
		}

		if (full) {
			removedLines++;
			del(i);
			i--;
		}
	}

	checkLinesScore(removedLines);
	checkComboScore(removedLines);
	checkTSpinScore(removedLines);
}

void Matrix::del(int l) {

	for (int i = 0; i < W; i++) matrix[i][l] = -1;

	for (int i = 0; i < W; i++)
	for (int j = l - 1; j >= 0; j--) {

		matrix[i][j + 1] = matrix[i][j];
	}

	Tetris::status.lines++;
}

bool Matrix::empty(int x, int y) {

	if (x >= 0 and x < W and y < H) {

		if (y >= 0) {

			if (matrix[x][y] == -1)
				return true;
		}

		else return true;
	}

	return false;
}

void Matrix::checkLinesScore(int rLines) {

	switch (rLines) {
	case 1: Tetris::status.score += SINGLE * Tetris::status.level; break;
	case 2: Tetris::status.score += DOUBLE * Tetris::status.level; break;
	case 3: Tetris::status.score += TRIPLE * Tetris::status.level; break;
	case 4: Tetris::status.score += TETRIS * Tetris::status.level; break;
	}
}

void Matrix::checkComboScore(int rLines) {

	if (rLines > 0) {

		comboCount++;
		Tetris::status.score += COMBO * comboCount * Tetris::status.level;
	}

	else comboCount = -1;
}

void Matrix::checkTSpinScore(int rLines) {

	int score = 0;

	if (Tetris::piece.checkTSpin()) {

		switch (rLines) {
		case 0: score = T_SPIN  * Tetris::status.level; break;
		case 1: score = TSINGLE * Tetris::status.level; break;
		case 2: score = TDOUBLE * Tetris::status.level; break;
		case 3: score = TTRIPLE * Tetris::status.level; break;
		}
	}

	else if (Tetris::piece.checkMiniTSpin()) {

		switch (rLines) {
		case 0: score = MT_SPIN  * Tetris::status.level; break;
		case 1: score = MTSINGLE * Tetris::status.level; break;
		case 2: score = MTDOUBLE * Tetris::status.level; break;
		}
	}

	Tetris::status.score += score;
}