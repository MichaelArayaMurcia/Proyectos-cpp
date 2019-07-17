#include<SFML/Graphics.hpp>
#include <iostream>
bool onscreen = true;
sf::RenderWindow window(sf::VideoMode(280, 400), "Flappy Bird");

class Bird {
public:
	float x, y, largo,ancho;
	float dy = 0.30f;
	Bird(float,float,float,float);

};
Bird::Bird(float _x, float _y, float _largo,float _ancho) {
	x = _x;
	y = _y;
	largo = _largo;
	ancho = _ancho;
}

Bird bird(15.f, 200.f, 10.f,10.f);

class Pipe {
public:
	float x, ytop,ybot, largo, ancho,dx,gap;
	bool touch = false;
	Pipe(float,float,float,float);
};
Pipe::Pipe(float _x, float _y, float _largo,float _ancho) {
	x = _x;
	ytop = _y;
	largo = _largo;
	ancho = _ancho;
	dx = 0.30f;
	gap = 100;
	ybot = gap + ancho;
	touch = false;
}
Pipe pipe(10,0,40,50);

sf::Texture fondo;
sf::Sprite background;

sf::Texture pajaro;
sf::Sprite dove;

sf::Texture pipearriba;
sf::Sprite pipetop;

sf::Texture pipeabajo;
sf::Sprite pipebot;

void showpipes() {
	pipe.x -= pipe.dx;
	//--------------- Verificar si esta en pantalla ---------
	if (pipe.x + pipe.largo > 0) { onscreen = true; }
	else { onscreen = false; }
	//--------------- Verificar si lo toco -------------------
	if (bird.x >= pipe.x && bird.y <= pipe.ancho) { pipe.touch = true; }
	else if (bird.x >= pipe.x && bird.y >= pipe.ybot) { pipe.touch = true; }
	else { pipe.touch = false; }
	//--------------- Cambiar acorde a lo detectado ----------
	if (onscreen == true && pipe.touch == false) {
		pipetop.setPosition( pipe.x,pipe.ytop );
		pipebot.setPosition( pipe.x,pipe.ybot );
	}
	if (onscreen == true && pipe.touch == true) {
		pipetop.setPosition( pipe.x,pipe.ytop );
		pipebot.setPosition( pipe.x,pipe.ybot );
	}
	if (onscreen == false) {
		pipe.x = 100;
		pipe.ancho = rand() % 100 + 100;
		onscreen = true;
	}
	//---------------- dibujar -------------------------------
	pipetop.setTexture(pipearriba);
	pipetop.setPosition(pipe.x,pipe.ytop);
	pipetop.setScale(sf::Vector2f(1.0,1.0));

	pipebot.setTexture(pipeabajo);
	pipebot.setScale(sf::Vector2f(1.0,1.0));
	window.draw(pipetop);
	window.draw(pipebot);
}

void loadtextures() {
	fondo.loadFromFile("background-night.png");
	pajaro.loadFromFile("bird.png");
	pipearriba.loadFromFile("Top_pipe.png");
	pipeabajo.loadFromFile("Bottom_pipe.png");

	background.setTexture(fondo);
	dove.setTexture(pajaro);

}

void update() {
	bird.y += bird.dy;
	dove.setPosition(bird.x,bird.y);
	window.draw(background);
	window.draw(dove);
	showpipes();
	window.display();
	window.clear();
}

int main() {
	loadtextures();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				bird.y -= 60;
			}
		}
		update();
	}
	return 0;
}