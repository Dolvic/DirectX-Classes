#include "Includes\Buffer.h"

Buffer::Buffer(const CComPtr<ID3D11Buffer>& buf, const CComPtr<ID3D11DeviceContext>& dc) : buffer(buf), deviceContext(dc)
{
}

void Buffer::update(const void* data)
{
	deviceContext->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
}