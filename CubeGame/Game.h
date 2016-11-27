#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Matrix3.h"


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
	void updateCube();
	const int PRIMITIVES;

	GLuint m_index;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	float m_rotationAngle = 0.0f;
	Vector3 m_points[8];
	Matrix3 m_scale;
	Matrix3 m_rotate;
	Matrix3 m_translate;
};