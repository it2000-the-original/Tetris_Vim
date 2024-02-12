#include "Controls.hpp"
#include "Preview.hpp"
#include "Status.hpp"
#include "Tetris.hpp"
#include "Piece.hpp"
#include "Hold.hpp"

using namespace sf;

void Controls::checkInputs() {

	_checkHorizontalMoves();

	if (_checkDownInputs()) moveDown();

	if (_checkUpInputs()) rotate();
	else rotated = false;

	if (_checkSpaceInputs()) drop();
	else dropped = false;

	if (_checkHoldInputs()) hold();
}

bool Controls::isStepReady() {

	return sclock.getElapsedTime() > Tetris::sTime or skClock;
}

void Controls::enableHold() {

	holdEnb = true;
}

void Controls::resetStep() {

	sclock.restart();
	skClock = false;
}

bool Controls::lookDown() {

	if (Tetris::piece.getPiece() == 0) {

		return Tetris::piece.check(0, 3);
	}

	else {

		return Tetris::piece.check(0, 2);
	}
}

void Controls::moveRight() {
	
	if (rclock.getElapsedTime() > rTime or !rmoved) {

		Tetris::piece.move(1, 0);
		rclock.restart();
		_checkLookDown();
		rmoved = true;
	}

	if (prclock.getElapsedTime() <= prTime) {
		
		rclock.restart();
	}
}

void Controls::moveLeft() {
	
	if (lclock.getElapsedTime() > lTime or !lmoved) {

		Tetris::piece.move(-1, 0);
		lclock.restart();
		_checkLookDown();
		lmoved = true;
	}

	if (plclock.getElapsedTime() <= plTime) {

		lclock.restart();
	}
}

void Controls::moveDown() {

	if (dclock.getElapsedTime() > dTime) {

		if (Tetris::piece.move(0, 1)) {
			Tetris::status.score++;
			dclock.restart();
			sclock.restart();
		}
	}
}

void Controls::rotate() {

	if (!rotated) {

		if (Tetris::piece.rotate()) {

			rotated = true;
			_checkLookDown();
		}
	}
}

void Controls::drop() {

	if (!dropped) {

		Tetris::status.score += Tetris::piece.fall() * 2;
		dropped = true;
		skClock = true;
	}
}

void Controls::hold() {

	if (holdEnb) {

		int tetromino = Tetris::piece.getPiece();

		if (Tetris::hold.get() != -1) {

			Tetris::piece.set(Tetris::hold.get());
		}

		else {
			Tetris::preview.generate();
			Tetris::piece.set(Tetris::preview.get());
		}

		Tetris::hold.set(tetromino);
		holdEnb = false;
	}
}

void Controls::_checkHorizontalMoves() {

	if (_checkRightInputs() xor _checkLeftInputs()) {

		if (_checkRightInputs()) moveRight(); else _resetRightMove();
		if (_checkLeftInputs())  moveLeft();  else _resetLeftMove();
	}

	else {
		_resetRightMove();
		_resetLeftMove();
	}
}

void Controls::_resetRightMove() {

	prclock.restart();
	rmoved = false;
}

void Controls::_resetLeftMove() {

	plclock.restart();
	lmoved = false;
}

void Controls::_checkLookDown() {

	if (!lookDown()) {

		if (moves < MOVES) {
			sclock.restart();
			moves++;
			return;
		}
	}

	else moves = 0;
}

bool Controls::_checkSpaceInputs() {

	return Keyboard::isKeyPressed(Keyboard::Space);
}

bool Controls::_checkRightInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::Right) or
		Keyboard::isKeyPressed(Keyboard::L);
}

bool Controls::_checkLeftInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::Left) or
		Keyboard::isKeyPressed(Keyboard::H);
}

bool Controls::_checkDownInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::Down) or
		Keyboard::isKeyPressed(Keyboard::J);
}

bool Controls::_checkHoldInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::C) or
		Keyboard::isKeyPressed(Keyboard::U);
}

bool Controls::_checkUpInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::Up) or
		Keyboard::isKeyPressed(Keyboard::K);
}


