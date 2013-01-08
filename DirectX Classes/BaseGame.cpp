#include "Includes\BaseGame.h"

BaseGame::BaseGame() : device(nullptr), swapChain(nullptr), backBuffer(nullptr)
{
}

BaseGame::~BaseGame()
{
	shutdown();
}

bool BaseGame::initialize(HINSTANCE instance, HWND window)
{
	this->instance = instance;
	this->window = window;

	RECT dimensions;
	GetClientRect(window, &dimensions);
	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	swapChain.reset(new SwapChain());
	swapChain->setBufferSize(width, height);
	swapChain->setRefreshRate(60);
	swapChain->setOutputWindow(window);
	device.reset(new Device(swapChain));

	backBuffer.reset(new RenderTarget(swapChain->getBackBuffer()));
	device->setRenderTarget(backBuffer);

	ViewPort viewPort;
	viewPort.setSize(width, height);
	viewPort.setDepth(0.0f, 1.0f);
	viewPort.setOrigin(0, 0);
	device->setViewPort(viewPort);

	return loadContent();
}

void BaseGame::shutdown()
{
	unloadContent();

	backBuffer.reset(nullptr);
	swapChain.reset(nullptr);
	device.reset(nullptr);
}

bool BaseGame::loadContent()
{
	return true;
}

void BaseGame::unloadContent()
{
}