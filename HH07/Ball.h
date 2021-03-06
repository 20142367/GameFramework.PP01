#pragma once
#include "SDLGameObject.h"

class Ball : public SDLGameObject
{
public:
	Ball(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

	void Frame(int change);
};

