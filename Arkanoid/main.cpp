#include <SFML/Graphics.hpp>
#include <vector>
//------------ Variables ------------
float v = 12.f;

//--------------- Clases ------------
class Jugador {
public:
	float x, y, largo, ancho;

	Jugador(float,float,float,float);

};
class Bola {
public:
	float x, y, r;
	float vx = 0.5f;
	float vy = 0.3f;
	Bola(float,float,float);
};
class Bloque {
public:
	float x, y, largo, ancho;
	Bloque(float,float,float,float);
};

Jugador::Jugador(float _x,float _y,float _largo,float _ancho) {
	x = _x;
	y = _y;
	largo = _largo;
	ancho = _ancho;
}
Bola::Bola(float _x, float _y, float _r) {
	x = _x;
	y = _y;
	r = _r;
}
Bloque::Bloque(float _x, float _y, float _largo, float _ancho) {
	x = _x;
	y = _y;
	largo = _largo;
	ancho = _ancho;
}

Jugador jugador(200.f,390.f,50.f,10.f);
Bola bola(200.f,200.f,10.f);
Bloque bloque(0.f,10.f,30.f,10.f);
//------------ Objetos --------------
sf::RenderWindow window(sf::VideoMode(400, 400), "Arkanoid");
sf::RectangleShape player{ {jugador.largo,jugador.ancho} };
sf::CircleShape ball{ {bola.r} };
sf::RectangleShape brick{ {bloque.largo,bloque.ancho} };
//------------ Funciones ------------
std::vector<sf::RectangleShape> bloques(10);


void update() {
	//-------------- Movimiento --------------
	bola.x += bola.vx;
	bola.y += bola.vy;
	ball.setPosition({ bola.x,bola.y });
	player.setPosition({ jugador.x,390.f });
	//-------------- Funciones ---------------
	window.clear();
	window.draw(player);
	window.draw(ball);
	for (int i = 0; i < 10; i++) {
	window.draw(bloques[i]);
	}
	window.display();
}
//------------ Main -----------------
int main() {
	float j = 0.f;
	//----------------------- Posiciones iniciales ----------
	ball.setPosition({ bola.x,bola.y });
	player.setPosition({ jugador.x,jugador.y });
	//----------------------------------------
	for (int i = 0; i < 10; i++) {
		j += 1.f;
		bloques[i] = brick;
		bloque.x = (j * 40.f);
		bloques[i].setPosition({ bloque.x,bloque.y });
	}
	//----------------------- Bucle principal ---------------
	while(window.isOpen()) {
		//------------------- Eventos -----------------------
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//----------------- Jugador -----------------
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				jugador.x -= v;
				if (jugador.x <= -v) {
					jugador.x += v;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				jugador.x += v;
				if (jugador.x >= 360.f) {
					jugador.x -= v;
				}
			}
		}
		//------------ Rebotar --------------
		//------------ Jugador --------------
		if (bola.x >= jugador.x && bola.x <= jugador.x + jugador.largo && bola.y + bola.r >= 390.f ) {
			bola.vy = -bola.vy;
		}
		//-------------- Vertical ----------------
		if (bola.x + bola.r >= 400.f || bola.x <= 0.f) {
			bola.vx = -bola.vx;
		}
		if (bola.y <= 0.f) {
			bola.vy = -bola.vy;
		}
		//-------------- Rebotes Bloques -----------------
		for (int i = 0; i < 10; i++) {
			if (bola.x >= bloques[i].getPosition().x && bola.x <= bloques[i].getPosition().x + 30.f && bola.y <= bloques[i].getPosition().y + 10.f) {
				bola.vy = -bola.vy;
				bloques[i].setPosition(-100.f,0.f);
			}
		}
		//-------------- Reiniciar ---------------
		if (bola.y > 400.f) {
			bola.x = 200.f;
			bola.y = 200.f;
		}
		//-------------- Actualizar --------------
		update();
	}

	return 0;
}