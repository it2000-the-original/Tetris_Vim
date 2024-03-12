#include <cmath>

#include "Tetromino.hpp"
#include "Controls.hpp"
#include "Preview.hpp"
#include "Matrix.hpp"
#include "Sounds.hpp"
#include "Status.hpp"
#include "Tetris.hpp"
#include "Hold.hpp"

using namespace sf;

void Controls::update() {

	checkInputs();
	checkSteps();
	lockDown();
}

void Controls::checkInputs() {

	_checkHorizontalMoves();

	if (_checkDownInputs()) moveDown();

	if (_checkUpInputs()) rotate();
	else rotated = false;

	if (_checkSpaceInputs()) drop();
	else dropped = false;

	if (_checkHoldInputs()) hold();
}

void Controls::setStepTime() {

	// Setting the step time using the official formula

	sTime = seconds(float(pow(0.8f - ((Tetris::status.level - 1) * 0.007f), Tetris::status.level - 1)));

	sclock.restart();
}

void Controls::checkSteps() {

	if (sclock.getElapsedTime() > sTime) {
		
		Tetris::tetromino.move(0, 1);

		_checkDisableLocking();

		setStepTime();
	}
}

void Controls::lockDown() {

	if (locking) {

		if (pdclock.getElapsedTime() > pdTime) {

			if (!Tetris::tetromino.check(0, 1)) {

				Tetris::sounds.playSoftDropSound();
				depose();
			}
		}
	}

	_checkLocking();
}

void Controls::depose() {

	Tetris::tetromino.depose();
	Tetris::matrix.checkLines();
	Tetris::preview.generate();
	Tetris::tetromino.set(Tetris::preview.get());

	_checkGameOver();

	holdEnb = true;
	locking = false;
}

void Controls::moveRight() {
	
	if (rclock.getElapsedTime() > rTime or !rmoved) {

		if (Tetris::tetromino.move(1, 0)) {
			rclock.restart();
			rmoved = true;
			_checkLockingMoves();
		}
	}

	if (prclock.getElapsedTime() <= prTime) {
		
		rclock.restart();
	}
}

void Controls::moveLeft() {
	
	if (lclock.getElapsedTime() > lTime or !lmoved) {

		if (Tetris::tetromino.move(-1, 0)) {
			lclock.restart();
			lmoved = true;
			_checkLockingMoves();
		}
	}

	if (plclock.getElapsedTime() <= plTime) {

		lclock.restart();
	}
}

void Controls::moveDown() {

	if (dclock.getElapsedTime() > dTime) {

		if (Tetris::tetromino.move(0, 1)) {
			Tetris::status.score++;
			dclock.restart();
			sclock.restart();
		}
	}
}

void Controls::rotate() {

	if (!rotated) {

		if (Tetris::tetromino.rotate()) {

			rotated = true;
			_checkLockingMoves();
		}
	}
}

void Controls::drop() {

	if (!dropped) while (true) {

		if (!Tetris::tetromino.move(0, 1)) {

			Tetris::sounds.playHardDropSound();
			dropped = true;
			depose();
			break;
		}

		Tetris::status.score += 2;
	}
}

void Controls::hold() {

	if (holdEnb) {

		int tetromino = Tetris::tetromino.get();

		if (Tetris::hold.get() != -1) {

			Tetris::tetromino.set(Tetris::hold.get());
		}

		else {
			Tetris::preview.generate();
			Tetris::tetromino.set(Tetris::preview.get());
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

void Controls::_checkDisableLocking() {

	if (locking) {

		lsteps++;

		if (!Tetris::tetromino.check(0, 1)) lsteps = 0;

		if ((Tetris::tetromino.get() != 0 and lsteps >= 2) or
			(Tetris::tetromino.get() == 0 and lsteps >= 3)) {

			if (Tetris::tetromino.check(0, 1)) {

				locking = false;
				lsteps = 0;
			}
		}
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

void Controls::_checkLockingMoves() {

	if (locking and moves < 15) {

		pdclock.restart();
		sclock.restart();
		moves++;
	}
}

void Controls::_checkLocking() {

	if (!Tetris::tetromino.check(0, 1) and !locking) {

		moves = 0;
		locking = true;
		pdclock.restart();
	}
}

void Controls::_checkGameOver() {

	if (!Tetris::tetromino.check(0, 0)) {

		Tetris::tetromino.move(0, -1);

		if (!Tetris::tetromino.check(0, 0)) {

			Tetris::tetromino.depose();
			Tetris::sounds.playSoftDropSound();
			Tetris::sounds.playGameOverSound();
			Tetris::reset();
		}
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


