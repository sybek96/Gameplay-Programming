#include "Game.h"

bool flip = false;
int current = 1;

Game::Game(sf::ContextSettings settings) : m_window(sf::VideoMode(800, 600), "OpenGL Cube"), PRIMITIVES(1)
{
	m_index = glGenLists(PRIMITIVES);
	m_points[0] = Vector3(1.0, 1.0, 1.0);		//tr f 0
	m_points[1] = Vector3(-1.0, 1.0, 1.0);		//tl f 1
	m_points[2] = Vector3(-1.0, -1.0, 1.0);	//bl f 2
	m_points[3] = Vector3(1.0, -1.0, 1.0);		//br f 3
	m_points[4] = Vector3(1.0, 1.0, -1.0);		//tr b 4
	m_points[5] = Vector3(-1.0, 1.0, -1.0);	//tl b 5
	m_points[6] = Vector3(-1.0, -1.0, -1.0);	//bl b 6
	m_points[7] = Vector3(1.0, -1.0, -1.0);	//br b 7

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
			if (event.key.code)
			{
				//if (sf::Keyboard::Up)
				//{
				//	m_scale = Matrix3::scale(1.1, 1.1, 1.1);
				//	for (auto & point : m_points)
				//	{
				//		point = m_scale * point;
				//	}
				//	updateCube();
				//}
				//if (sf::Keyboard::Down)
				//{
				//	m_scale = Matrix3::scale(0.9, 0.9, 0.9);
				//	for (auto & point : m_points)
				//	{
				//		point = m_scale * point;
				//	}
				//	updateCube();
				//}
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					m_scale = Matrix3::scale(1.1, 1.1);
					for (auto &pt : m_points)
					{
						pt = m_scale * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::Down:
					m_scale = Matrix3::scale(0.9, 0.9);
					for (auto &pt : m_points)
					{
						pt = m_scale * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::Left:
					m_rotate = Matrix3::rotation(Matrix3::Axis::X, 10);
					for (auto &pt : m_points)
					{
						pt = m_rotate * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::Right:
					m_rotate = Matrix3::rotation(Matrix3::Axis::X, -10);
					for (auto &pt : m_points)
					{
						pt = m_rotate * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::W:
					m_translate = Matrix3::translate(0,0.1);
					for (auto &pt : m_points)
					{
						pt = m_translate * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::S:
					m_translate = Matrix3::translate(0, -0.1);
					for (auto &pt : m_points)
					{
						pt = m_translate * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::D:
					m_translate = Matrix3::translate(0.1, 0);
					for (auto &pt : m_points)
					{
						pt = m_translate * pt;
					}
					updateCube();
					break;
				case sf::Keyboard::A:
					m_translate = Matrix3::translate(-0.1, 0);
					for (auto &pt : m_points)
					{
						pt = m_translate * pt;
					}
					updateCube();
					break;
				default:
					break;
				}
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
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

		//Complete the faces of the Cube
		//Left Face
		glColor3f(0.0f, 0.0f, 1.0f); //green
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2

		//Right face
		glColor3f(0.0f, 1.0f, 0.0f); //blue
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

		//top face
		glColor3f(1.0f, 0.0f, 0.0f);	//red
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0

		//bottom face
		glColor3f(1.0f, 0.5f, 0.0f); //orange
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

		//Front Face
		glColor3f(1.0f, 1.0f, 0.0f); //yellow
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
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
	//glRotatef(m_rotationAngle, 1, 0, 0); // Rotates the camera on Y Axis
	glTranslatef(0.0f, 0.0f, -10.0f);
	glCallList(current);

	m_window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}

void Game::updateCube()
{
	glNewList(m_index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Back Face
		glColor3f(1.0f, 1.0f, 1.0f); //white
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

																				//Complete the faces of the Cube
																				//Left Face
		glColor3f(0.0f, 0.0f, 1.0f); //green
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2

																				//Right face
		glColor3f(0.0f, 1.0f, 0.0f); //blue
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

																				//top face
		glColor3f(1.0f, 0.0f, 0.0f);	//red
		glVertex3d(m_points[4].getX(), m_points[4].getY(), m_points[4].getZ()); //tr b4
		glVertex3d(m_points[5].getX(), m_points[5].getY(), m_points[5].getZ()); //tl b5
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0

																				//bottom face
		glColor3f(1.0f, 0.5f, 0.0f); //orange
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2
		glVertex3d(m_points[6].getX(), m_points[6].getY(), m_points[6].getZ()); //bl b6
		glVertex3d(m_points[7].getX(), m_points[7].getY(), m_points[7].getZ()); //br b7

																				//Front Face
		glColor3f(1.0f, 1.0f, 0.0f); //yellow
		glVertex3d(m_points[0].getX(), m_points[0].getY(), m_points[0].getZ());	//tr f0
		glVertex3d(m_points[1].getX(), m_points[1].getY(), m_points[1].getZ()); //tl f1
		glVertex3d(m_points[2].getX(), m_points[2].getY(), m_points[2].getZ()); //bl f2
		glVertex3d(m_points[3].getX(), m_points[3].getY(), m_points[3].getZ()); //br f3
	}
	glEnd();
	glEndList();
}

