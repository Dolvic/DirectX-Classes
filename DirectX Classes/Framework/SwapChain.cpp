#include "Includes\SwapChain.h"
#include "Includes\Resource.h"
#include "Includes\DirectXException.h"

SwapChain::SwapChain() : swapChain(nullptr), descriptor()
{
	this->setBufferCount(1);
	this->setBufferFormat(DXGI_FORMAT_R8G8B8A8_UNORM);
	this->setBufferUsage(DXGI_USAGE_RENDER_TARGET_OUTPUT);
	this->setMultiSampling(1, 0);
	this->setWindowed(true);
}

unique_ptr<Resource> SwapChain::getBackBuffer()
{
	if(swapChain == nullptr)
		throw DirectXException("Cannot get back buffer, swap chain not initialized!");

	CComPtr<ID3D11Resource> backBuffer(nullptr);
	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
	return unique_ptr<Resource>(new Resource(backBuffer));
}

void SwapChain::rotate()
{
	if(swapChain != nullptr)
		swapChain->Present(0, 0);
}

void SwapChain::setBufferCount(int count)
{
	if(swapChain == nullptr)
		descriptor.BufferCount = count;
}

int SwapChain::getBufferCount()
{
	return descriptor.BufferCount;
}

void SwapChain::setBufferFormat(DXGI_FORMAT format)
{
	if(swapChain == nullptr)
		descriptor.BufferDesc.Format = format;
}

DXGI_FORMAT SwapChain::getBufferFormat()
{
	return descriptor.BufferDesc.Format;
}

void SwapChain::setBufferSize(int width, int height)
{
	if(swapChain == nullptr)
	{
		descriptor.BufferDesc.Width = width;
		descriptor.BufferDesc.Height = height;
	}
}

int SwapChain::getBufferWidth()
{
	return descriptor.BufferDesc.Width;
}

int SwapChain::getBufferHeight()
{
	return descriptor.BufferDesc.Height;
}

void SwapChain::setBufferUsage(DXGI_USAGE usage)
{
	if(swapChain == nullptr)
		descriptor.BufferUsage = usage;
}

DXGI_USAGE SwapChain::getBufferUsage()
{
	return descriptor.BufferUsage;
}

void SwapChain::setMultiSampling(int count, int quality)
{
	if(swapChain == nullptr)
	{
		descriptor.SampleDesc.Count = count;
		descriptor.SampleDesc.Quality = quality;
	}
}

int SwapChain::getMultiSamplingCount()
{
	return descriptor.SampleDesc.Count;
}

int SwapChain::getMultiSamplingQuality()
{
	return descriptor.SampleDesc.Quality;
}

void SwapChain::setOutputWindow(HWND window)
{
	if(swapChain == nullptr)
		descriptor.OutputWindow = window;
}

HWND SwapChain::getOutputWindow()
{
	return descriptor.OutputWindow;
}

void SwapChain::setRefreshRate(double refreshRate)
{
	if(swapChain != nullptr)
		return;

	double fractionalRate = refreshRate - static_cast<int>(refreshRate);
	int denominator = 1;
	while(fractionalRate > 0)
	{
		denominator *= 10;
		fractionalRate *= 10;
		fractionalRate -= static_cast<int>(fractionalRate);
	}

	descriptor.BufferDesc.RefreshRate.Numerator = static_cast<int>(refreshRate * denominator);
	descriptor.BufferDesc.RefreshRate.Denominator = denominator;
}

double SwapChain::getRefreshRate()
{
	return static_cast<double>(descriptor.BufferDesc.RefreshRate.Numerator)/descriptor.BufferDesc.RefreshRate.Denominator;
}

void SwapChain::setWindowed(bool windowed)
{
	if(swapChain == nullptr)
		descriptor.Windowed = windowed;
}

bool SwapChain::isWindowed()
{
	return descriptor.Windowed;
}