#include "Tetromino.hpp"
#include "Controls.hpp"
#include "Preview.hpp"
#include "Sounds.hpp"
#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Status.hpp"
#include "Ghost.hpp"
#include "Hold.hpp"

using namespace sf;

RenderWindow* Tetris::window;
Sprite Tetris::blocks;
Event Tetris::event;
Font Tetris::font;

Tetromino Tetris::tetromino;
Controls Tetris::controls;
Preview Tetris::preview;
Sounds Tetris::sounds;
Status Tetris::status;
Matrix Tetris::matrix;
Ghost Tetris::ghost;
Hold Tetris::hold;

Tetris::Tetris() {}

void Tetris::init(const int FPS, std::string title) {

	window = new RenderWindow(VideoMode(WW, WH), title, Style::Default);
	WView = window->getDefaultView();
	window->setFramerateLimit(FPS);
	window->setActive(true);

	loadTextures();
	loadFont();
	loadIcon();

	matrix.init();
	status.init();
	preview.init();
	sounds.init();
	hold.init();

	tetromino.set(preview.get());
	controls.setStepTime();
	sounds.playMusic();

	std::cout << "Window has been created" << std::endl;
}

void Tetris::update() {

	controls.update();
	ghost.update();
	preview.update();
	status.update();
	hold.update();
}

void Tetris::echeck() {
	
	while (window->pollEvent(event)) {

		switch (event.type) {

		case Event::Closed:
			window->close();
			break;

		case Event::Resized:
			checkWindowSize(event.size.width, event.size.height);
			break;
		}
	}
}

void Tetris::render() {
	
	window->clear(WColor);
	window->draw(background);

	matrix.draw();
	ghost.draw();
	tetromino.draw();
	preview.draw();
	status.draw();
	hold.draw();

	window->display();
}

void Tetris::checkWindowSize(int _w, int _h) {

	int w = 0;
	int h = 0;

	if (_w >= MWW) w = _w; else w = MWW;
	if (_h >= MWH) h = _h; else h = MWH;

	window->setSize(Vector2u(w, h));

	resetView(w, h);
}

void Tetris::resetView(int w, int h) {

	float WHF = float(WW) / float(WH); // Window Height Fraction
	float _WHF= float(w) / float(h);   // Window Height Fraction of the resized window

	if (_WHF > WHF) {

		WView.setViewport(FloatRect((1.f - 1.f / _WHF) / 2.f, 0.f, 1.f / _WHF, 1.f));
	}

	else {

		WView.setViewport(FloatRect(0.f, (1.f - _WHF) / 2.f, 1.f, _WHF));
	}
	
	window->setView(WView);
}

void Tetris::loadTextures() {

	// Defining the textures
	Texture* wTexture = new Texture();
	Texture* bTexture = new Texture();

	if (!wTexture->loadFromFile(WPath) or
		!bTexture->loadFromFile(BPath)) {

		window->close();
	}

	background.setTexture(*wTexture);
	blocks.setTexture(*bTexture);
}

void Tetris::loadFont() {

	if (!font.loadFromFile(FPath)) {

		window->close();
	}

	#ifdef SMOTH_TEXT 

	font.setSmooth(false); // Does not exist on Linux

	#endif
}

void Tetris::loadIcon() {

	sf::Image icon;

	if (!icon.loadFromFile("icon.png")) {

		window->close();
	}

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

bool Tetris::isRunning() {

	return window->isOpen();
}

void Tetris::reset() {

	hold.init();
	matrix.init();
	preview.init();
	status.reset();
	tetromino.set(preview.get());
}
