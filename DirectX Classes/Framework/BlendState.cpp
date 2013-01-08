#include "Includes\BlendState.h"

BlendState::BlendState() : state(nullptr), descriptor()
{
}

void BlendState::enableBlend(int i)
{
	if(state != nullptr)
		return;

	descriptor.RenderTarget[i].BlendEnable = true;
	descriptor.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

void BlendState::setColorBlend(int i, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend)
{
	if(state != nullptr)
		return;

	descriptor.RenderTarget[i].BlendOp = blendOperation;
	descriptor.RenderTarget[i].SrcBlend = sourceBlend;
	descriptor.RenderTarget[i].DestBlend = destinationBlend;
}

void BlendState::setAlphaBlend(int i, D3D11_BLEND_OP blendOperation, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend)
{
	if(state != nullptr)
		return;

	descriptor.RenderTarget[i].BlendOpAlpha = blendOperation;
	descriptor.RenderTarget[i].SrcBlendAlpha = sourceBlend;
	descriptor.RenderTarget[i].DestBlendAlpha = destinationBlend;
}