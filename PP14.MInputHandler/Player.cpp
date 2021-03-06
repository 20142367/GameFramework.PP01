#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	m_currentFrame = int((SDL_GetTicks() / 100) % 6);

	handleInput();	// 입력을 지속적으로 업데이트

	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput() 
{
	// 키보드 입력
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}
}