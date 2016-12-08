#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3.h>
#include <Matrix3.h>

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
	void render();
	void unload();
	void applyTransformation(const Matrix3&);

	sf::Clock clock;
	sf::Time elapsed;
	float rotationAngle = 0.0f;
	Matrix3 m_scale;
	Matrix3 m_rotate;
	Matrix3 m_translate;
};