#ifndef DIRECTX_PIXEL_SHADER
#define DIRECTX_PIXEL_SHADER

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;

class ShaderResource;
class SamplerState;

class PixelShader
{
	friend class Device;

	private:
		CComPtr<ID3D11PixelShader> shader;
		CComPtr<ID3D11DeviceContext> deviceContext;

		PixelShader(const CComPtr<ID3D11PixelShader>& shader, const CComPtr<ID3D11DeviceContext>& deviceContext);
	public:
		void setResource(int slot, const unique_ptr<ShaderResource>& shaderResource);
		void setResources(int firstSlot, const vector<unique_ptr<ShaderResource> >& shaderResources);
		void setSampler(int slot, const unique_ptr<SamplerState>& samplerState);
		void setSamplers(int firstSlot, const vector<unique_ptr<SamplerState> >& samplerStates);
};

#endif