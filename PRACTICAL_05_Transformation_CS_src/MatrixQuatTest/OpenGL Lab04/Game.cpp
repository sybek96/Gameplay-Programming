#include "Game.h"

bool flip = false;
int current = 1;

Game::Game(ContextSettings settings) :
	window(VideoMode(800, 600), "OpenGL", Style::Close, settings),
	primatives(2),
	m_zoom(true)
{
	index = glGenLists(primatives);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);


	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0, 2.0, -5.0);
		glVertex3f(-2.0, -2.0, -5.0);
		glVertex3f(2.0, -2.0, -5.0);
	}
	glEnd();
	glEndList();

	glNewList(index + 1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3d(0.2, 0.0, -2.0);
		glVertex3d(-2.0, -2.0, -2.0);
		glVertex3d(2.0, -2.0, -2.0);
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

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Draw up" << endl;

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
	cout << "Drawing Primative " << current << endl;
	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

