#ifndef DIRECTX_VERTEX_SHADER
#define DIRECTX_VERTEX_SHADER

#include <D3D11.h>
#include <atlbase.h>
#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;

class Buffer;

class VertexShader
{
	friend class Device;

	private:
		CComPtr<ID3D11VertexShader> shader;
		CComPtr<ID3DBlob> compiledShaderData;
		CComPtr<ID3D11DeviceContext> deviceContext;

		VertexShader(const CComPtr<ID3D11VertexShader>& vertexShader, const CComPtr<ID3DBlob>& compiledShaderData, const CComPtr<ID3D11DeviceContext>& deviceContext);
	public:
		void setConstantBuffer(int slot, const unique_ptr<Buffer>& constantBuffer);
		void setConstantBuffers(int firstSlot, const vector<unique_ptr<Buffer> >& constantBuffers);
};

#endif