#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	Vector2D& getPosition() { return m_position; }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	int m_currentRow;
	int m_currentFrame;

protected:
	Vector2D m_position;		// 위치 값
	Vector2D m_velocity;		// 속도 값
	Vector2D m_acceleration;	// 가속도 값

	int m_width;
	int m_height;
	int m_numFrames;

	std::string m_textureID;
};