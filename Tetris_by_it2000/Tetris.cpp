#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Piece.hpp"

RenderWindow Tetris::window;
Matrix Tetris::matrix;
Sprite Tetris::blocks;
Piece Tetris::piece;
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

	matrix.init();

	srand(time(NULL));
	piece.set();

	std::cout << "Window has been created" << std::endl;

	piece.move(0, 1);
}

void Tetris::update() {

	icheck();

	if (sclock.getElapsedTime() > sTime or jumpStep) {

		step();
		sclock.restart();
		jumpStep = false;
	}

	matrix.check();
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

	// Rotate commands

	if (Keyboard::isKeyPressed(Keyboard::Up) or 
		Keyboard::isKeyPressed(Keyboard::K)) rotate();
	
	else rotated = false;

	// Fall commands

	if (Keyboard::isKeyPressed(Keyboard::Space)) fall(); 
	
	else fallen = false;

	// Move <- -> commands
	
	if (Keyboard::isKeyPressed(Keyboard::Right) or 
		Keyboard::isKeyPressed(Keyboard::L)) moveRight(); 
	
	else rmoved = false;

	if (Keyboard::isKeyPressed(Keyboard::Left) or 
		Keyboard::isKeyPressed(Keyboard::H)) moveLeft();
	
	else lmoved = false;

	// Move down commands

	if (Keyboard::isKeyPressed(Keyboard::Down) or
		Keyboard::isKeyPressed(Keyboard::J)) moveDown();
}

void Tetris::render() {
	
	window.clear();

	window.draw(background);
	matrix.draw();
	piece.draw();

	window.display();
}

void Tetris::moveRight() {

	if (!lmoved and (!rmoved or prclock.getElapsedTime() >= prTime)) {

		if (!rmoved or rclock.getElapsedTime() >= rTime) {

			piece.move(1, 0);
			rclock.restart();
			moves++;

			if (!piece.check(0, 1) and moves <= 15) {

				sclock.restart();
			}
		}

		if (!rmoved) prclock.restart();

		rmoved = true;
	}
}

void Tetris::moveLeft() {

	if (!rmoved and (!lmoved or plclock.getElapsedTime() >= plTime)) {

		if (!lmoved or lclock.getElapsedTime() >= lTime) {

			piece.move(-1, 0);
			lclock.restart();
			moves++;

			if (!piece.check(0, 1) and moves <= 15) {

				sclock.restart();
			}
		}

		if (!lmoved) plclock.restart();

		lmoved = true;
	}
}

void Tetris::moveDown() {

	if (dclock.getElapsedTime() > dTime) {
		piece.move(0, 1);
		dclock.restart();
		sclock.restart();
	}
}

void Tetris::rotate() {

	if (!rotated) {

		piece.rotate();
		rotated = true;
		moves++;

		if (!piece.check(0, 1) and moves <= 15) {

			sclock.restart();
		}
	}
}

void Tetris::fall() {

	if (!fallen) {
		piece.fall();
		fallen = true;
		jumpStep = true;
	}
}

void Tetris::step() {

	if (!piece.check(0, 1)) {

		piece.depose();
		piece.set();

		// Game over

		if (!piece.check(0, 0)) {

			window.close();
		}
	}

	else {
		piece.move(0, 1);
		moves = 0;
	}
}

bool Tetris::isRunning() {

	return window.isOpen();
}
