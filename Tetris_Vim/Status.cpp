#include <iostream>

#include "Status.hpp"
#include "Tetris.hpp"
#include "Config.h"

using namespace sf;

void Status::init() {

	_setFont();
	_setFontSize();
	_setFontColor();

	scoreText.setString("score");
	levelText.setString("level");
	linesText.setString("lines");
}

void Status::update() {

	scoreNumber.setString(std::to_string(score));
	levelNumber.setString(std::to_string(level));
	linesNumber.setString(std::to_string(lines));

	if (level_count >= 10) setLevel(level + 1);

	_setPositions();
}

void Status::draw() {

	Tetris::window->draw(scoreText);
	Tetris::window->draw(levelText);
	Tetris::window->draw(linesText);
	Tetris::window->draw(scoreNumber);
	Tetris::window->draw(levelNumber);
	Tetris::window->draw(linesNumber);
}

void Status::reset() {

	score = 0;
	level = 0;
	lines = 0;
}

void Status::setLevel(int _level) {

	level = _level;
	level_count = 0;
}

void Status::_setFont() {

	scoreText.setFont(Tetris::font);
	levelText.setFont(Tetris::font);
	linesText.setFont(Tetris::font);
	scoreNumber.setFont(Tetris::font);
	levelNumber.setFont(Tetris::font);
	linesNumber.setFont(Tetris::font);
}

void Status::_setFontSize() {

	scoreText.setCharacterSize(TS);
	levelText.setCharacterSize(TS);
	linesText.setCharacterSize(TS);
	scoreNumber.setCharacterSize(NS);
	levelNumber.setCharacterSize(NS);
	linesNumber.setCharacterSize(NS);
}

void Status::_setFontColor() {

	scoreText.setFillColor(Color::Yellow);
	levelText.setFillColor(Color::Yellow);
	linesText.setFillColor(Color::Yellow);
	scoreNumber.setFillColor(Color::Yellow);
	levelNumber.setFillColor(Color::Yellow);
	linesNumber.setFillColor(Color::Yellow);
}

void Status::_setPositions() {

	scoreText.setPosition(Vector2f(float(PX + (PS - scoreText.getLocalBounds().width) / 2), float(PY + TPADDING)));
	levelText.setPosition(Vector2f(float(PX + (PS - levelText.getLocalBounds().width) / 2), float(PY + TPADDING + PS)));
	linesText.setPosition(Vector2f(float(PX + (PS - linesText.getLocalBounds().width) / 2), float(PY + TPADDING + PS * 2)));

	scoreNumber.setPosition(Vector2f(float(PX + (PS - scoreNumber.getLocalBounds().width) / 2), float(PY + NPADDING)));
	levelNumber.setPosition(Vector2f(float(PX + (PS - levelNumber.getLocalBounds().width) / 2), float(PY + NPADDING + PS)));
	linesNumber.setPosition(Vector2f(float(PX + (PS - linesNumber.getLocalBounds().width) / 2), float(PY + NPADDING + PS * 2)));
}
