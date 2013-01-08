#include "Includes\RenderTarget.h"
#include "Includes\Resource.h"
#include "Includes\DirectXException.h"
using std::move;

RenderTarget::RenderTarget(unique_ptr<Resource>& res) : view(nullptr), resource(move(res)), deviceContext(nullptr)
{
}

void RenderTarget::fillColor(float color[4])
{
	if(deviceContext == nullptr)
		throw DirectXException("Render Target not initialized properly!");

	deviceContext->ClearRenderTargetView(view, color);
}