#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Vector3.h"
#include "Matrix3.h"
#include "Quaternion.h"


class Game
{
public:
	Game(sf::ContextSettings);
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	void updateShape1();
	void updateShape2();
	const int primatives;

	GLuint index;
	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;
	bool m_zoom;
	Vector3 m_shape1[3];
	Vector3 m_shape2[3];
	Matrix3 m_transform;
};