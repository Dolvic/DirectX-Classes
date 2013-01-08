#ifndef DIRECTX_RESOURCE
#define DIRECTX_RESOURCE

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
using std::unique_ptr;

class Texture2D;

class Resource
{
	friend class Device;
	friend class ShaderResource;
	friend class SwapChain;

	private:
		CComPtr<ID3D11Resource> resource;
	protected:
		Resource();
		Resource(const CComPtr<ID3D11Resource>& resource);
	public:
		virtual ~Resource();
		virtual unique_ptr<Texture2D> convertToTexture2D();
};

#endif