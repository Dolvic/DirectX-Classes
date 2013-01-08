#include "Includes\Device.h"
#include "Includes\DirectXException.h"

#include "Includes\BlendState.h"
#include "Includes\Buffer.h"
#include "Includes\InputElement.h"
#include "Includes\InputLayout.h"
#include "Includes\PixelShader.h"
#include "Includes\RenderTarget.h"
#include "Includes\Resource.h"
#include "Includes\SamplerDescriptor.h"
#include "Includes\SamplerState.h"
#include "Includes\ShaderResource.h"
#include "Includes\SwapChain.h"
#include "Includes\VertexShader.h"
#include "Includes\ViewPort.h"

Device::Device(unique_ptr<SwapChain>& swapChain) : device(nullptr), deviceContext(nullptr)
{
	if(swapChain == nullptr)
		throw DirectXException("Swap chain not ready for initialization!");
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &(swapChain->descriptor), &(swapChain->swapChain), &device, nullptr, &deviceContext);
	if(FAILED(result))
		throw DirectXException("Exception while initializing device and swap chain!");
}

void Device::setBlendState(unique_ptr<BlendState>& blendState, float blendFactor[4])
{
	HRESULT result = device->CreateBlendState(&(blendState->descriptor), &(blendState->state));
	if(FAILED(result))
		throw DirectXException("Exception while creating blend state!");

	deviceContext->OMSetBlendState(blendState->state, blendFactor, 0xFFFFFFFF);
}

void Device::setRenderTarget(unique_ptr<RenderTarget>& renderTarget)
{
	if(renderTarget == nullptr)
		throw DirectXException("No render target passed!");

	HRESULT result = device->CreateRenderTargetView(renderTarget->resource->resource, nullptr, &(renderTarget->view));
	if(FAILED(result))
		throw DirectXException("Exception while setting render target!");

	renderTarget->deviceContext = deviceContext;
	deviceContext->OMSetRenderTargets(1, &(renderTarget->view.p), nullptr);
}

void Device::setRenderTargets(vector<unique_ptr<RenderTarget> >& renderTargets)
{
	int count = renderTargets.size();
	if(count == 1)
	{
		this->setRenderTarget(renderTargets[0]);
		return;
	}

	vector<ID3D11RenderTargetView*> nativeViews;
	for(int i=0; i<count; i++)
	{
		unique_ptr<RenderTarget>& renderTarget = renderTargets[i];
		HRESULT result = device->CreateRenderTargetView(renderTarget->resource->resource, nullptr, &(renderTarget->view));
		if(FAILED(result))
			throw DirectXException("Exception while setting render target!");

		renderTarget->deviceContext = deviceContext;
		nativeViews.push_back(renderTarget->view);
	}
	deviceContext->OMSetRenderTargets(count, &nativeViews[0], nullptr);
}

void Device::setViewPort(const ViewPort& viewPort)
{
	deviceContext->RSSetViewports(1, &(viewPort.viewPort));
}

void Device::setViewPorts(const vector<ViewPort>& viewPorts)
{
	int count = viewPorts.size();

	if(count == 1)
	{
		setViewPort(viewPorts[0]);
		return;
	}

	vector<D3D11_VIEWPORT> nativePorts;
	for(int i=0; i<count; i++)
		nativePorts.push_back(viewPorts[i].viewPort);

	deviceContext->RSSetViewports(count, &nativePorts[0]);
}

unique_ptr<Buffer> Device::createConstantBuffer(int bufferSize)
{
	D3D11_BUFFER_DESC descriptor;
	ZeroMemory(&descriptor, sizeof(descriptor));
	descriptor.Usage = D3D11_USAGE_DEFAULT;
	descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	descriptor.ByteWidth = bufferSize;

	CComPtr<ID3D11Buffer> buffer;
	device->CreateBuffer(&descriptor, nullptr, &buffer);

	return unique_ptr<Buffer>(new Buffer(buffer, deviceContext));
}

unique_ptr<InputLayout> Device::createInputLayout(const vector<InputElement>& inputElements, const unique_ptr<VertexShader>& vertexShader)
{
	ID3DBlob* compiledShader = vertexShader->compiledShaderData;
	CComPtr<ID3D11InputLayout> inputLayout(nullptr);

	vector<D3D11_INPUT_ELEMENT_DESC> vertexProperties;
	for(int i=0; i<inputElements.size(); i++)
		vertexProperties.push_back(inputElements[i].descriptor);

	HRESULT result = device->CreateInputLayout(&vertexProperties[0], vertexProperties.size(), compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &inputLayout);
	if(FAILED(result))
		throw DirectXException("Exception while creating input layout!");

	return unique_ptr<InputLayout>(new InputLayout(inputLayout));
}

unique_ptr<PixelShader> Device::createPixelShader(const char* filename, const char* entryPoint, const char* shaderVersion)
{
	CComPtr<ID3DBlob> compiledShader(nullptr);
	CComPtr<ID3DBlob> errorMessages(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &compiledShader, &errorMessages, nullptr);

	if(errorMessages != nullptr)
		MessageBox(nullptr, static_cast<char*>(errorMessages->GetBufferPointer()), "Shader Compile Errors", MB_OK);

	if(FAILED(result))
		throw DirectXException("Exception while compiling shader!");

	CComPtr<ID3D11PixelShader> pixelShader(nullptr);
	result = device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &pixelShader);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex shader!");

	return unique_ptr<PixelShader>(new PixelShader(pixelShader, deviceContext));
}

unique_ptr<SamplerState> Device::createSamplerState(const SamplerDescriptor& samplerDescriptor)
{
	CComPtr<ID3D11SamplerState> samplerState(nullptr);

	HRESULT result = device->CreateSamplerState(&(samplerDescriptor.descriptor), &samplerState);
	if(FAILED(result))
		throw DirectXException("Exception while creating sampler state!");

	return unique_ptr<SamplerState>(new SamplerState(samplerState));
}

unique_ptr<ShaderResource> Device::createShaderResource(const char* fileName)
{
	CComPtr<ID3D11ShaderResourceView> view(nullptr);

	HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, fileName, nullptr, nullptr, &view, nullptr);
	if(FAILED(result))
		throw DirectXException("Exception while creating Shader Resource View!");

	return unique_ptr<ShaderResource>(new ShaderResource(view));
}

unique_ptr<Buffer> Device::createVertexBuffer(int bufferSize, const void* bufferData)
{
	D3D11_BUFFER_DESC bufferDescriptor;
	ZeroMemory(&bufferDescriptor, sizeof(bufferDescriptor));

	bufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
	bufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescriptor.ByteWidth = bufferSize;

	D3D11_SUBRESOURCE_DATA subResourceData;
	ZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = bufferData;

	CComPtr<ID3D11Buffer> buffer(nullptr);
	HRESULT result = device->CreateBuffer(&bufferDescriptor, &subResourceData, &buffer);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex buffer!");

	return unique_ptr<Buffer>(new Buffer(buffer, deviceContext));
}

unique_ptr<VertexShader> Device::createVertexShader(const char* filename, const char* entryPoint, const char* shaderVersion)
{
	CComPtr<ID3DBlob> compiledShader(nullptr);
	CComPtr<ID3DBlob> errorMessages(nullptr);

	HRESULT result = D3DX11CompileFromFile(filename, nullptr, nullptr, entryPoint, shaderVersion, D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &compiledShader, &errorMessages, nullptr);

	if(errorMessages != nullptr)
		MessageBox(nullptr, static_cast<char*>(errorMessages->GetBufferPointer()), "Shader Compile Errors", MB_OK);

	if(FAILED(result))
		throw DirectXException("Exception while compiling shader!");

	CComPtr<ID3D11VertexShader> vertexShader(nullptr);
	result = device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, &vertexShader);
	if(FAILED(result))
		throw DirectXException("Exception while creating vertex shader!");

	return unique_ptr<VertexShader>(new VertexShader(vertexShader, compiledShader, deviceContext));
}

void Device::draw(int vertexCount, int offset)
{
	deviceContext->Draw(vertexCount, offset);
}

void Device::setInputLayout(const unique_ptr<InputLayout>& inputLayout)
{
	deviceContext->IASetInputLayout(inputLayout->layout);
}

void Device::setPixelShader(const unique_ptr<PixelShader>& pixelShader)
{
	deviceContext->PSSetShader(pixelShader->shader, nullptr, 0);
}

void Device::setTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	deviceContext->IASetPrimitiveTopology(topology);
}

void Device::setVertexBuffer(int slot, const unique_ptr<Buffer>& vertexBuffer, unsigned int stride, unsigned int offset)
{
	deviceContext->IASetVertexBuffers(slot, 1, &(vertexBuffer->buffer.p), &stride, &offset);
}

void Device::setVertexBuffers(int firstSlot, const vector<unique_ptr<Buffer> >& vertexBuffers, vector<unsigned int>& strides, vector<unsigned int>& offsets)
{
	int count = vertexBuffers.size();

	if(count == 1)
	{
		this->setVertexBuffer(firstSlot, vertexBuffers[0], strides[0], offsets[0]);
		return;
	}

	vector<ID3D11Buffer*> nativeBuffers;
	for(int i=0; i<count; i++)
		nativeBuffers.push_back(vertexBuffers[i]->buffer.p);

	deviceContext->IASetVertexBuffers(firstSlot, count, &nativeBuffers[0], &strides[0], &offsets[0]);
}

void Device::setVertexShader(const unique_ptr<VertexShader>& vertexShader)
{
	deviceContext->VSSetShader(vertexShader->shader.p, nullptr, 0);
}