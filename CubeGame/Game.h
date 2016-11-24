#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>


class Game
{
public:
	Game(sf::ContextSettings);
	~Game();
	void run();
private:
	sf::Window m_window;
	bool m_isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	const int PRIMITIVES;

	GLuint m_index;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	float m_rotationAngle = 0.0f;
};