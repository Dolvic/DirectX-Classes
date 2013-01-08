#ifndef DIRECTX_SWAPCHAIN
#define DIRECTX_SWAPCHAIN

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
using std::unique_ptr;

class Resource;

class SwapChain
{
	// can change buffer count, size, format, refresh rate, windowed status without recreating
	friend class Device;

	private:
		CComPtr<IDXGISwapChain> swapChain;
		DXGI_SWAP_CHAIN_DESC descriptor;
	public:
		SwapChain();

		unique_ptr<Resource> getBackBuffer();
		void rotate();

		void setBufferCount(int count);
		int getBufferCount();

		void setBufferFormat(DXGI_FORMAT format);
		DXGI_FORMAT getBufferFormat();

		void setBufferSize(int width, int height);
		int getBufferWidth();
		int getBufferHeight();

		void setBufferUsage(DXGI_USAGE usage);
		DXGI_USAGE getBufferUsage();

		void setMultiSampling(int count, int quality);
		int getMultiSamplingCount();
		int getMultiSamplingQuality();

		void setOutputWindow(HWND window);
		HWND getOutputWindow();

		void setRefreshRate(double refreshRate);
		double getRefreshRate();

		void setWindowed(bool windowed);
		bool isWindowed();
};

#endif