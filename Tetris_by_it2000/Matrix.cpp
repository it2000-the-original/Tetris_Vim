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

			Tetris::window.draw(Tetris::blocks);
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
}

void Matrix::del(int l) {

	for (int i = 0; i < W; i++) matrix[i][l] = -1;

	for (int i = 0; i < W; i++)
	for (int j = l - 1; j >= 0; j--) {

		matrix[i][j + 1] = matrix[i][j];
	}

	Tetris::status.lines++;
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