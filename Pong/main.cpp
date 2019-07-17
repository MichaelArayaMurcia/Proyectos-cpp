#include <SFML/Graphics.hpp>
//------------ Variables ------------
float iy = 200.f;
float dy = 200.f;
float by = 200.f;
float bx = 200.f;
float vx = 0.5f;
float vy = 0.3f;
float v = 12.f;
//------------ Objetos --------------
sf::RenderWindow window(sf::VideoMode(400, 400), "Pong");
sf::RectangleShape paddle1{ {10.f,50.f} };
sf::RectangleShape paddle2{ {10.f,50.f} };
sf::CircleShape ball{ {10.f} };
//------------ Main -----------------
int main() {
	//----------------------- Posiciones iniciales ----------
	ball.setPosition({ 200.f,200.f });
	paddle2.setPosition({ 390.f,dy});
	paddle1.setPosition({ 0.f,iy});
	//----------------------- Bucle principal ---------------
	while(window.isOpen()) {
		//------------------- Eventos -----------------------
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//----------------- Paddle derecho -------------------
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				dy -= v;
				if (dy <= -v) {
					dy += v;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				dy += v;
				if (dy >= 360) {
					dy -= v;
				}
			}
			//----------------- Paddle izquierdo -----------------
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				iy -= v;
				if (iy <= -v) {
					iy += v;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				iy += v;
				if (iy >= 360) {
					iy -= v;
				}
			}
		}
		//------------ Rebotar --------------
		//------------ Pong Derecha -------------------
		if (bx >= 380 && by >= dy && by <= dy + 50) {
			vx = -vx;
		}
		//------------ Pong Izquierda -----------------
		if (bx <= 10 && by >= iy && by <= iy + 50) {
			vx = -vx;
		}
		//-------------- Vertical ----------------
		if (by >= 400 || by <= 0) {
			vy = -vy;
		}
		//-------------- Reiniciar ---------------
		if (bx > 400 || bx < 0) {
			bx = 200;
			by = 200;
		}
		//-------------- Movimiento --------------
		bx += vx;
		by += vy;
		ball.setPosition({bx,by});
		paddle1.setPosition({ 0.f,iy });
		paddle2.setPosition({ 390.f,dy });
		//-------------- Funciones ---------------
		window.clear();
		window.draw(paddle1);
		window.draw(paddle2);
		window.draw(ball);
		window.display();
	}

	return 0;
}