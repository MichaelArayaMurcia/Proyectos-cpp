#include<SFML/Graphics.hpp>
bool onscreen = true;
sf::RenderWindow window(sf::VideoMode(400, 400), "Arkanoid");

class Bird {
public:
	float x, y, r;
	float dy = 0.30f;
	Bird(float,float,float);
	void show();
};
Bird::Bird(float _x, float _y, float _r) {
	x = _x;
	y = _y;
	r = _r;
}
void Bird::show() {
	y += dy;
	sf::CircleShape pajaro(r);
	pajaro.setPosition({x,y});
	pajaro.setFillColor({255,255,0});
	window.draw(pajaro);
}

Bird bird(15.f, 200.f, 10.f);

class Pipe {
public:
	float x, y, largo, ancho,dx,gap;
	bool touch = false;
	Pipe(float,float,float,float);
	void show();
};
Pipe::Pipe(float _x, float _y, float _largo,float _ancho) {
	x = _x;
	y = _y;
	largo = _largo;
	ancho = _ancho;
	dx = 0.30f;
	gap = 100;
	touch = false;
}
void Pipe::show() {
	sf::RectangleShape tuboa({largo,ancho});
	sf::RectangleShape tubob({largo,ancho});
	x -= dx;
	//--------------- Verificar si esta en pantalla ---------
	if (x + largo > 0) { onscreen = true; }
	else { onscreen = false; }
	//--------------- Verificar si lo toco -------------------
	if (bird.x >= x && bird.y <= ancho) { touch = true; }
	else if (bird.x >= x && bird.y >= y + gap + ancho) { touch = true; }
	else { touch = false; }
	//--------------- Cambiar acorde a lo detectado ----------
	if (onscreen == true && touch == false) { 
		tuboa.setFillColor({0,255,0}); 
		tubob.setFillColor({0,255,0});
		tuboa.setPosition({x,y});
		tubob.setPosition({x,(y + gap + ancho)});
		tubob.setSize({ largo,(400 - gap + ancho)});
	}
	if (onscreen == true && touch == true) {
		tuboa.setFillColor({255,0,0});
		tubob.setFillColor({255,0,0});
		tuboa.setPosition({x,y});
		tubob.setPosition({x,y + gap + ancho});
		tubob.setSize({ largo,(400 - gap + ancho) });
	}
	if (onscreen == false) {
		x = 100;
		ancho = rand() % 100 + 100;
		onscreen = true;
	}
	//---------------- dibujar -------------------------------
	window.draw(tuboa);
	window.draw(tubob);
}

Pipe pipe1(10,0,10,50);
Pipe pipe2(60,0,10,50);

void update() {
	bird.show();
	pipe1.show();
	pipe2.show();
	window.display();
	window.clear();
}

int main() {
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