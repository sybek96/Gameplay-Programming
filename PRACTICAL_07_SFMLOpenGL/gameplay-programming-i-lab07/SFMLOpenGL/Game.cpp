#include <Game.h>

bool flip = false;
int current = 1;

Game::Game(sf::ContextSettings settings) : window(sf::VideoMode(800, 600), "OpenGL Cube", sf::Style::Default, settings)
{

}
Game::~Game() {}
const unsigned int VERTICES_SIZE = 24u;
const unsigned int VERTEX_SIZE = 3u;
float vertices[VERTICES_SIZE] = { //FRONT
					 1.0f,  1.0f,  1.0f, //TR f 0
					-1.0f,  1.0f,  1.0f, //TL f 1
					-1.0f, -1.0f,  1.0f, //BL f 2
					 1.0f, -1.0f,  1.0f, //BR f	3	
					 //BACK
					 1.0f,  1.0f, -1.0f, //TR b	4
					-1.0f,  1.0f, -1.0f, //TL b 5
					-1.0f, -1.0f, -1.0f, //BL b 6
					 1.0f, -1.0f, -1.0f, //BR b 7

};


float colors[] = {  1.0f, 0.0f, 0.0f,	//R
					0.0f, 1.0f, 0.0f,	//G
					0.0f, 0.0f, 1.0f,	//B

					1.0f, 1.0f ,0.0f,	//Y

					1.0f, 1.0f ,0.0f,	//Y
					0.0f, 0.0f, 1.0f,	//B
					0.0f, 1.0f, 0.0f,	//G
		
					1.0f, 0.0f, 0.0f,	//R

					};

const unsigned int INDEX_SIZE = 36u;
unsigned int vertex_index[INDEX_SIZE] = { 
	0, 1, 2, //Front
	3, 0, 2, 

	5 ,1 ,0, //top
	5, 0, 4,

	7, 4, 0, //right
	7, 0, 3,

	2, 1, 5, //left
	2, 5, 6,

	2, 6, 7, //bottom
	2, 7, 3,

	6, 5, 4, //back
	6, 4, 7
};

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		std::cout << "Game running..." << std::endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			switch (event.key.code)
			{
			case sf::Keyboard::Q:
				m_scale = Matrix3::scale(1.1, 1.1, 1.1);
				applyTransformation(m_scale);
				break;
			case sf::Keyboard::E:
				m_scale = Matrix3::scale(0.9, 0.9, 0.9);
				applyTransformation(m_scale);
				break;
			case sf::Keyboard::Left:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, -3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::Right:
				m_rotate = Matrix3::rotation(Matrix3::Axis::Y, 3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::W:
				m_translate = Matrix3::translate(0, 0.1);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::S:
				m_translate = Matrix3::translate(0, -0.1);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::D:
				m_translate = Matrix3::translate(0.1, 0);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::A:
				m_translate = Matrix3::translate(-0.1, 0);
				applyTransformation(m_translate);
				break;
			case sf::Keyboard::Up:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, -3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::Down:
				m_rotate = Matrix3::rotation(Matrix3::Axis::X, 3);
				applyTransformation(m_rotate);
				break;
			case sf::Keyboard::Space:
				for (unsigned int i = 0u; i < VERTICES_SIZE; i += VERTEX_SIZE)
				{
					Vector3 point = Vector3(vertices[i], vertices[i + 1u] + 0.1, vertices[i + 2u]);
					vertices[i] = point.getX();
					vertices[i + 1u] = point.getY();
					vertices[i + 2u] = point.getZ();
				}
				break;
			default:
				break;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	glEnable(GL_CULL_FACE);
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -5.0f);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	glCullFace(GL_BACK);
	std::cout << "Update up" << std::endl;
}

void Game::render()
{
	std::cout << "Drawing" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(VERTEX_SIZE, GL_FLOAT, 0, &vertices);
	glColorPointer(VERTEX_SIZE, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, INDEX_SIZE, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	window.display();

}

void Game::unload()
{
	std::cout << "Cleaning up" << std::endl;
}
/// <summary>
/// Method to apply transformations
/// </summary>
/// <param name="transform"></param>
void Game::applyTransformation(const Matrix3 & transform)
{
	for (unsigned int i = 0u; i < VERTICES_SIZE; i += VERTEX_SIZE)
	{
		Vector3 point  = Vector3(vertices[i], vertices[i + 1u], vertices[i + 2u]);
		point = transform * point;
		vertices[i] = point.getX();
		vertices[i + 1u] = point.getY();
		vertices[i + 2u] = point.getZ();
	}
}

