#include "Includes\BlankGame.h"

BlankGame::BlankGame()
{
}


BlankGame::~BlankGame()
{
}

bool BlankGame::loadContent()
{
	return true;
}

void BlankGame::unloadContent()
{
}

void BlankGame::update(float deltaTime)
{
}

void BlankGame::render()
{
	if(backBuffer == nullptr)
		return;

	float color[4] = { 0.0f, 0.0f, 0.f, 1.f };
	backBuffer->fillColor(color);

	swapChain->rotate();
}