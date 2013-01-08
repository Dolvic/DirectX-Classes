#ifndef DIRECTX_RENDER_TARGET
#define DIRECTX_RENDER_TARGET

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
using std::unique_ptr;

class Resource;

class RenderTarget
{
	friend class Device;

	private:
		CComPtr<ID3D11RenderTargetView> view;
		const unique_ptr<Resource> resource;

		CComPtr<ID3D11DeviceContext> deviceContext;
	public:
		RenderTarget(unique_ptr<Resource>& resource);

		void fillColor(float color[4]);
};

#endif