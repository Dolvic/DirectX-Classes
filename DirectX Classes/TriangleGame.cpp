#include "Includes\TriangleGame.h"

TriangleGame::Vertex::Vertex() : position(), color()
{
}

TriangleGame::Vertex::Vertex(const XMFLOAT3& position, const XMFLOAT4& color) : position(position), color(color)
{
}

void TriangleGame::Vertex::setPosition(const XMFLOAT3& position)
{
	this->position = position;
}

XMFLOAT3 TriangleGame::Vertex::getPosition()
{
	return position;
}

void TriangleGame::Vertex::setColor(const XMFLOAT4& color)
{
	this->color = color;
}

XMFLOAT4 TriangleGame::Vertex::getColor()
{
	return color;
}

TriangleGame::TriangleGame() : vertexShader(nullptr), inputLayout(nullptr), pixelShader(nullptr), vertexBuffer(nullptr)
{
}


TriangleGame::~TriangleGame()
{
}

bool TriangleGame::loadContent()
{
	vertexShader = device->createVertexShader("TriangleShader.fx", "VS_Main", "vs_4_0");

	vector<InputElement> inputElements;
	inputElements.push_back(InputElement("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, true, 0));
	inputElements.push_back(InputElement("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, true, 0));
	inputLayout = device->createInputLayout(inputElements, vertexShader);

	pixelShader = device->createPixelShader("TriangleShader.fx", "PS_Main", "ps_4_0");

	float minX = -0.5f;
	float maxX = 0.5f;
	float minY = -1.0f;
	float maxY = 1.0f;
	XMFLOAT4 red(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue(0.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 cyan(0.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 magenta(1.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 white(1.0f, 1.0f, 1.0f, 1.0f);

	vector<Vertex> vertices;
	vertices.push_back(Vertex(XMFLOAT3(minX, maxY, 0.5f), red));
	vertices.push_back(Vertex(XMFLOAT3(maxX, maxY, 0.5f), green));
	vertices.push_back(Vertex(XMFLOAT3(minX, 0.0f, 0.5f), blue));
	vertices.push_back(Vertex(XMFLOAT3(maxX, 0.0f, 0.5f), yellow));
	vertices.push_back(Vertex(XMFLOAT3(minX, minY, 0.5f), cyan));
	vertices.push_back(Vertex(XMFLOAT3(maxX, minY, 0.5f), magenta));
	vertexBuffer = device->createVertexBuffer(vertices.size() * sizeof(Vertex), &vertices[0]);

	return true;
}

void TriangleGame::unloadContent()
{
	vertexBuffer.reset(nullptr);
	pixelShader.reset(nullptr);
	inputLayout.reset(nullptr);
	vertexShader.reset(nullptr);
}

void TriangleGame::update(float deltaTime)
{
}

void TriangleGame::render()
{
	if(backBuffer == nullptr)
		return;

	float black[4] = { 0.0f, 0.0f, 0.f, 1.f };
	backBuffer->fillColor(black);

	device->setInputLayout(inputLayout);
	device->setVertexBuffer(0, vertexBuffer, sizeof(Vertex), 0);
	device->setTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	device->setVertexShader(vertexShader);
	device->setPixelShader(pixelShader);

	device->draw(6, 0);

	swapChain->rotate();
}