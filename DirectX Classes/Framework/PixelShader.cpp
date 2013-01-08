#include "Includes\PixelShader.h"
#include "Includes\ShaderResource.h"
#include "Includes\SamplerState.h"

PixelShader::PixelShader(const CComPtr<ID3D11PixelShader>& ps, const CComPtr<ID3D11DeviceContext>& dc) : shader(ps), deviceContext(dc)
{
}

void PixelShader::setResource(int slot, const unique_ptr<ShaderResource>& shaderResource)
{
	deviceContext->PSSetShaderResources(slot, 1, &(shaderResource->view.p));
}

void PixelShader::setResources(int firstSlot, const vector<unique_ptr<ShaderResource> >& shaderResources)
{
	int count = shaderResources.size();

	if(count == 1)
	{
		this->setResource(firstSlot, shaderResources[0]);
		return;
	}

	vector<ID3D11ShaderResourceView*> nativeViews;
	for(int i=0; i<count; i++)
		nativeViews.push_back(shaderResources[i]->view.p);

	deviceContext->PSSetShaderResources(firstSlot, count, &nativeViews[0]);
}

void PixelShader::setSampler(int slot, const unique_ptr<SamplerState>& samplerState)
{
	deviceContext->PSSetSamplers(slot, 1, &(samplerState->state.p));
}

void PixelShader::setSamplers(int firstSlot, const vector<unique_ptr<SamplerState> >& samplerStates)
{
	int count = samplerStates.size();

	if(count == 1)
	{
		this->setSampler(firstSlot, samplerStates[0]);
		return;
	}

	vector<ID3D11SamplerState*> nativeSamplers;
	for(int i=0; i<count; i++)
		nativeSamplers.push_back(samplerStates[i]->state);

	deviceContext->PSSetSamplers(firstSlot, count, &nativeSamplers[0]);
}