#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"

const std::string PlayState::s_playID = "PLAY";

PlayState* PlayState::s_pInstance = 0;

PlayState::PlayState()
{
}

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	for (int i = 0; i < m_balls.size(); i++)
	{
		m_balls[i]->update();
	}
/*
	for (int i = 0; i < m_balls.size(); i++)
	{
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[1]), dynamic_cast<SDLGameObject*>(m_balls[i])))
		{
			
		}
	}*/

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(new PauseState());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	for (int i = 0; i < m_balls.size(); i++)
	{
		m_balls[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
/*
	if (!TheTextureManager::Instance()->load("assets/helicopter2.png", "helicopter2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}*/

	if (!TextureManager::Instance()->load("Assets/ball.png", "ball", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("Assets/wall.png", "wall", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
	//GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));
	GameObject* wall = new Wall(new LoaderParams(400, 150, 100, 100, "wall"));

	m_gameObjects.push_back(player);
	m_gameObjects.push_back(wall);

	std::cout << "entering PlayState" << std::endl;
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	std::cout << "exiting PlayState" << std::endl;
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}

PlayState* PlayState::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new PlayState();
		return s_pInstance;
	}
	return s_pInstance;
}