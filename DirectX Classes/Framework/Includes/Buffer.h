#ifndef DIRECTX_BUFFER
#define DIRECTX_BUFFER

#include <D3D11.h>
#include <atlbase.h>

class Buffer
{
	friend class Device;
	friend class VertexShader;

	private:
		CComPtr<ID3D11Buffer> buffer;
		CComPtr<ID3D11DeviceContext> deviceContext;
	
		Buffer(const CComPtr<ID3D11Buffer>& buffer, const CComPtr<ID3D11DeviceContext>& deviceContext);
	public:
		void update(const void* data);
};

#endif