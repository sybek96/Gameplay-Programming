#include "Game.h"

bool flip = false;
int current = 1;

Game::Game(sf::ContextSettings settings) :
	window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close, settings),
	primatives(2),
	m_zoom(true)
{
	index = glGenLists(primatives);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) 
	{

		std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				isRunning = false;
				break;
			case sf::Event::KeyPressed :
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					m_zoom = !m_zoom;
					break;
				case sf::Keyboard::Up:
					m_transform = Matrix3::scale(1.1, 1.1);
					for (auto &pt : m_shape1)
					{
						pt = m_transform * pt;
					}
					for (auto &pt : m_shape2)
					{
						pt = m_transform * pt;
					}
					updateShape1();
					updateShape2();
					break;
				case sf::Keyboard::Down:
					m_transform = Matrix3::scale(0.9, 0.9);
					for (auto &pt : m_shape1)
					{
						pt = m_transform * pt;
					}
					for (auto &pt : m_shape2)
					{
						pt = m_transform * pt;
					}
					updateShape1();
					updateShape2();
					break;
				case sf::Keyboard::Right:
					m_transform = Matrix3::rotation(Matrix3::Axis::Z, -10);
					for (auto &pt : m_shape1)
					{
						pt = m_transform * pt;	//matrix rotation
					}
					for (auto &pt : m_shape2)
					{
						pt = m_toRotate.rotate(pt, 45);	//quaternion rotation
					}
					updateShape1();
					updateShape2();
					break;
				case sf::Keyboard::Left:
					m_transform = Matrix3::rotation(Matrix3::Axis::Z, 10);
					for (auto &pt : m_shape1)
					{
						pt = m_transform * pt;	//matrix rotation
					}
					for (auto &pt : m_shape2)
					{
						pt = m_toRotate.rotate(pt, -45); //quaternion rotation
					}
					updateShape1();
					updateShape2();
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;
	m_shape1[0] = Vector3(0.0, 2.0, -5.0);
	m_shape1[1] = Vector3(-2.0, -2.0, -5.0);
	m_shape1[2] = Vector3(2.0, -2.0, -5.0);
	m_shape2[0] = Vector3(0.2, 0.0, -2.0);
	m_shape2[1] = Vector3(-2.0, -2.0, -2.0);
	m_shape2[2] = Vector3(2.0, -2.0, -2.0);
	m_zAxis = Vector3(0, 0, 1);
	m_toRotate = Quaternion(0,m_zAxis);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);


	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		for (auto &pt : m_shape1)
		{
			glVertex3d(pt.getX(), pt.getY(), pt.getZ());
		}
	}
	glEnd();
	glEndList();

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		for (auto &pt : m_shape2)
		{
			glVertex3d(pt.getX(), pt.getY(), pt.getZ());
		}
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > primatives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.05f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	std::cout << "Update up" << std::endl;
}

void Game::draw()
{
	std::cout << "Draw up" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Investigate Here!!!!!
	if (m_zoom)
	{
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);
	}
	else
	{
		glTranslatef(0.0f, 0.0f, -0.2f); //moving camera about x,y,z currently z (which makes the projected things smaller as camera is further away)
	}
	//glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);	//rotating camera around x,y,z at an angle of "rotationAngle"
	//glScalef(0.5f, 0.7f, 1.0f);		//makes camera bigger in the x,y,z
	std::cout << "Drawing Primative " << current << std::endl;
	glCallList(current);

	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}

void Game::updateShape1()
{
	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		for (auto &pt : m_shape1)
		{
			glVertex3d(pt.getX(), pt.getY(), pt.getZ());
		}
	}
	glEnd();
	glEndList();
}

void Game::updateShape2()
{
	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		for (auto &pt : m_shape2)
		{
			glVertex3d(pt.getX(), pt.getY(), pt.getZ());
		}
	}
	glEnd();
	glEndList();
}


