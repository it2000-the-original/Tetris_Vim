#include "Controls.hpp"
#include "Status.hpp"
#include "Tetris.hpp"
#include "Piece.hpp"

using namespace sf;

void Controls::checkInputs() {

	if (_checkRightInputs() xor _checkLeftInputs()) {

		if (_checkRightInputs()) moveRight(); else prclock.restart();
		if (_checkLeftInputs()) moveLeft();   else plclock.restart();
	}

	else {
		prclock.restart();
		plclock.restart();
	}

	if (_checkDownInputs()) moveDown();

	if (_checkUpInputs()) rotate();
	else rotated = false;

	if (_checkSpaceInputs()) drop();
	else dropped = false;
}

bool Controls::isStepReady() {

	return sclock.getElapsedTime() > Tetris::sTime or skClock;
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
	
	if (rclock.getElapsedTime() > rTime) {

		Tetris::piece.move(1, 0);
		rclock.restart();
		_checkLookDown();
	}

	if (prclock.getElapsedTime() <= prTime) {
		
		rclock.restart();
	}
}

void Controls::moveLeft() {
	
	if (lclock.getElapsedTime() > lTime) {

		Tetris::piece.move(-1, 0);
		lclock.restart();
		_checkLookDown();
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

bool Controls::_checkUpInputs() {

	return
		Keyboard::isKeyPressed(Keyboard::Up) or
		Keyboard::isKeyPressed(Keyboard::K);
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
