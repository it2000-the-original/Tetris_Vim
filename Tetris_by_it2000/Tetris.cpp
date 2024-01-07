#include "Preview.hpp"
#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Status.hpp"
#include "Piece.hpp"
#include "Nexts.hpp"

RenderWindow Tetris::window;
Preview Tetris::preview;
Status Tetris::status;
Matrix Tetris::matrix;
Sprite Tetris::blocks;
Piece Tetris::piece;
Nexts Tetris::nexts;
Event Tetris::event;

Tetris::Tetris() {}

void Tetris::init(const int FPS, std::string title) {

	window.create(VideoMode(619, 768), title, Style::Default);
	window.setFramerateLimit(FPS);
	window.setActive(true);

	// Defining the textures

	Texture* wTexture = new Texture();
	Texture* bTexture = new Texture();

	if (!wTexture->loadFromFile(WPath) or
		!bTexture->loadFromFile(BPath)) {

		window.close();
		return;
	}

	background.setTexture(*wTexture);
	blocks.setTexture(*bTexture);
	piece.set(nexts.get());
	sTime = seconds(0.5f);

	matrix.init();
	status.init();
	nexts.init();

	std::cout << "Window has been created" << std::endl;
}

void Tetris::update() {

	icheck();

	if (last) {

		if (fclock.getElapsedTime() < fTime) {
			if (rotated or rmoved or lmoved)
				sclock.restart();
		}
		
		else jumpStep = true;
	}

	if (sclock.getElapsedTime() > sTime or jumpStep) {

		step();
		sclock.restart();
		jumpStep = false;
	}

	checkLast();
	matrix.check();
	nexts.update();
	status.update();
	preview.update();
}

void Tetris::echeck() {
	
	while (window.pollEvent(event)) {

		switch (event.type) {

		case Event::Closed:
			window.close();
			break;
		}
	}
}

void Tetris::icheck() {

	rmoving = false;
	lmoving = false;
	rotating = false;
	falling = false;

	if (Keyboard::isKeyPressed(Keyboard::Up) or 
		Keyboard::isKeyPressed(Keyboard::K)) rotate();

	if (Keyboard::isKeyPressed(Keyboard::Space)) fall(); 

	if (Keyboard::isKeyPressed(Keyboard::Right) or 
		Keyboard::isKeyPressed(Keyboard::L)) moveRight(); 

	if (Keyboard::isKeyPressed(Keyboard::Left) or 
		Keyboard::isKeyPressed(Keyboard::H)) moveLeft();

	if (Keyboard::isKeyPressed(Keyboard::Down) or
		Keyboard::isKeyPressed(Keyboard::J)) moveDown();

	if (!rmoving) rmoved = false;
	if (!lmoving) lmoved = false;
	if (!rotating) rotated = false;
	if (!falling) fallen = false;	
}

void Tetris::render() {
	
	window.clear();

	window.draw(background);
	matrix.draw();
	preview.draw();
	piece.draw();
	nexts.draw();
	status.draw();

	window.display();
}

void Tetris::moveRight() {

	if (!lmoved and (!rmoved or prclock.getElapsedTime() >= prTime) and piece.check(1, 0)) {

		if (!rmoved or rclock.getElapsedTime() >= rTime) {

			piece.move(1, 0);
			rclock.restart();
		}

		if (!rmoved) prclock.restart();

		rmoved = true;
	}

	rmoving = true;
}

void Tetris::moveLeft() {

	if (!rmoved and (!lmoved or plclock.getElapsedTime() >= plTime) and piece.check(-1, 0)) {

		if (!lmoved or lclock.getElapsedTime() >= lTime) {

			piece.move(-1, 0);
			lclock.restart();
		}

		if (!lmoved) plclock.restart();

		lmoved = true;
	}

	lmoving = true;
}

void Tetris::moveDown() {

	if (dclock.getElapsedTime() > dTime and piece.check(0, 1)) {
		piece.move(0, 1);
		dclock.restart();
		sclock.restart();
	}
}

void Tetris::rotate() {

	if (!rotated) {

		if (piece.rotate()) 
			rotated = true;
	}

	rotating = true;
}

void Tetris::fall() {

	if (!fallen) {
		piece.fall();
		fallen = true;
		jumpStep = true;
	}

	falling = true;
}

void Tetris::step() {

	if (!piece.check(0, 1)) {

		piece.depose();
		nexts.generate();
		piece.set(nexts.get());

		// Game over

		if (!piece.check(0, 0)) restart();
	}

	else {

		piece.move(0, 1);
	}
}

bool Tetris::isRunning() {

	return window.isOpen();
}

void Tetris::checkLast() {

	if (!piece.check(0, 1) and !lasted) {

		fclock.restart();
		last = true;
		lasted = true;
	}

	else if (piece.check(0, 3)) {
		last = false;
		lasted = false;
	}
}

void Tetris::restart() {

	matrix.init();
	nexts.init();
	piece.set(nexts.get());
	sclock.restart();


	sTime = seconds(0.5f);
}
