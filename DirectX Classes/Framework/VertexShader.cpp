#include "Includes\VertexShader.h"
#include "Includes\DirectXException.h"
#include "Includes\Buffer.h"

VertexShader::VertexShader(const CComPtr<ID3D11VertexShader>& vs, const CComPtr<ID3DBlob>& csd, const CComPtr<ID3D11DeviceContext>& dc) : shader(vs), compiledShaderData(csd), deviceContext(dc)
{
}

void VertexShader::setConstantBuffer(int slot, const unique_ptr<Buffer>& constantBuffer)
{
	deviceContext->VSSetConstantBuffers(slot, 1, &(constantBuffer->buffer.p));
}

void VertexShader::setConstantBuffers(int firstSlot, const vector<unique_ptr<Buffer> >& constantBuffers)
{
	int count = constantBuffers.size();

	if(count == 1)
	{
		this->setConstantBuffer(firstSlot, constantBuffers[0]);
		return;
	}

	vector<ID3D11Buffer*> nativeBuffers;
	for(int i=0; i<count; i++)
		nativeBuffers.push_back(constantBuffers[i]->buffer.p);

	deviceContext->VSSetConstantBuffers(firstSlot, count, &nativeBuffers[0]);
}