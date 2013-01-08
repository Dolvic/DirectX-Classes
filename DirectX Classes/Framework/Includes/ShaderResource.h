#ifndef DIRECTX_SHADER_RESOURCE
#define DIRECTX_SHADER_RESOURCE

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
using std::unique_ptr;

class Resource;

class ShaderResource
{
	friend class Device;
	friend class PixelShader;

	private:
		CComPtr<ID3D11ShaderResourceView> view;

		ShaderResource(const CComPtr<ID3D11ShaderResourceView>& view);
	public:
		unique_ptr<Resource> getResource();
};

#endif