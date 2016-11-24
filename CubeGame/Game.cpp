#include "Game.h"

bool flip = false;
int current = 1;

Game::Game(sf::ContextSettings settings) : m_window(sf::VideoMode(800, 600), "OpenGL Cube"), PRIMITIVES(1)
{
	m_index = glGenLists(PRIMITIVES);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	sf::Event event;

	while (m_isRunning){

		std::cout << "Game running..." << std::endl;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	m_isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, m_window.getSize().x / m_window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(m_index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Back Face
		glColor3f(1.0f, 1.0f, 1.0f); //white
		glVertex3f(1.0f, 1.0f, -15.0f); //tr b
		glVertex3f(-1.0f, 1.0f, -15.0f); //tl b
		glVertex3f(-1.0f, -1.0f, -15.0f); //bl b
		glVertex3f(1.0f, -1.0f, -15.0f); //br b

		//Complete the faces of the Cube
		//Left Face
		glColor3f(0.0f, 0.0f, 1.0f); //green
		glVertex3f(-1.0f, 1.0f, -5.0f); //tl f
		glVertex3f(-1.0f, 1.0f, -15.0f); //tl b
		glVertex3f(-1.0f, -1.0f, -15.0f); //bl b
		glVertex3f(-1.0f, -1.0f, -5.0f); //bl f

		//Right face
		glColor3f(0.0f, 1.0f, 0.0f); //blue
		glVertex3f(1.0f, 1.0f, -15.0f); //tr b
		glVertex3f(1.0f, 1.0f, -5.0f);	//tr f
		glVertex3f(1.0f, -1.0f, -5.0f); //br f
		glVertex3f(1.0f, -1.0f, -15.0f); //br b

		//top face
		glColor3f(1.0f, 0.0f, 0.0f);	//red
		glVertex3f(1.0f, 1.0f, -15.0f); //tr b
		glVertex3f(-1.0f, 1.0f, -15.0f); //tl b
		glVertex3f(-1.0f, 1.0f, -5.0f); //tl f
		glVertex3f(1.0f, 1.0f, -5.0f);	//tr f

		//bottom face
		glColor3f(1.0f, 0.5f, 0.0f); //orange
		glVertex3f(1.0f, -1.0f, -5.0f); //br f
		glVertex3f(-1.0f, -1.0f, -5.0f); //bl f
		glVertex3f(-1.0f, -1.0f, -15.0f); //bl b
		glVertex3f(1.0f, -1.0f, -15.0f); //br b

		//Front Face
		glColor3f(1.0f, 1.0f, 0.0f); //yellow
		glVertex3f(1.0f, 1.0f, -5.0f);	//tr f
		glVertex3f(-1.0f, 1.0f, -5.0f); //tl f
		glVertex3f(-1.0f, -1.0f, -5.0f); //bl f
		glVertex3f(1.0f, -1.0f, -5.0f); //br f
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	m_elapsed = m_clock.getElapsedTime();

	if (m_elapsed.asSeconds() >= 1.0f)
	{
		m_clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > PRIMITIVES)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		m_rotationAngle += 0.05f;

		if (m_rotationAngle > 360.0f)
		{
			m_rotationAngle -= 360.0f;
		}
	}
	
	std::cout << "Update up" << std::endl;
}

void Game::draw()
{
	std::cout << "Drawing" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::cout << "Drawing Cube " << current << std::endl;
	glLoadIdentity();
	glRotatef(m_rotationAngle, 1, 0, 0); // Rotates the camera on Y Axis
	glTranslatef(0.0f, 0.0f, -2.0f);
	glCallList(current);

	m_window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}

