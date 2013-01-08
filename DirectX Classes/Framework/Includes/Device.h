#ifndef DIRECTX_DEVICE
#define DIRECTX_DEVICE

#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <atlbase.h>
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class BlendDescriptor;
class BlendState;
class Buffer;
class InputElement;
class InputLayout;
class PixelShader;
class RenderTarget;
class Resource;
class SamplerDescriptor;
class SamplerState;
class ShaderResource;
class SwapChain;
class VertexShader;
class ViewPort;

class Device
{
	private:
		CComPtr<ID3D11Device> device;
		CComPtr<ID3D11DeviceContext> deviceContext;
	public:
		Device(unique_ptr<SwapChain>& swapChain);

		void setBlendState(unique_ptr<BlendState>& blendState, float blendFactor[4]);
		void setRenderTarget(unique_ptr<RenderTarget>& renderTarget);
		void setRenderTargets(vector<unique_ptr<RenderTarget> >& renderTargets);
		void setViewPort(const ViewPort& viewPort);
		void setViewPorts(const vector<ViewPort>& viewPorts);

		unique_ptr<Buffer>			createConstantBuffer(int bufferSize);
		unique_ptr<InputLayout>		createInputLayout(const vector<InputElement>& inputElements, const unique_ptr<VertexShader>& vertexShader);
		unique_ptr<PixelShader>		createPixelShader(const char* filename, const char* entryPoint, const char* shaderVersion);
		unique_ptr<SamplerState>	createSamplerState(const SamplerDescriptor& samplerDescriptor);
		unique_ptr<ShaderResource>	createShaderResource(const char* fileName);
		unique_ptr<Buffer>			createVertexBuffer(int bufferSize, const void* bufferData);
		unique_ptr<VertexShader>	createVertexShader(const char* filename, const char* entryPoint, const char* shaderVersion);

		void draw(int vertexCount, int offset);
		void setInputLayout(const unique_ptr<InputLayout>& inputLayout);
		void setPixelShader(const unique_ptr<PixelShader>& pixelShader);
		void setTopology(D3D_PRIMITIVE_TOPOLOGY topology);
		void setVertexBuffer(int slot, const unique_ptr<Buffer>& vertexBuffer, unsigned int stride, unsigned int offset);
		void setVertexBuffers(int firstSlot, const vector<unique_ptr<Buffer> >& vertexBuffers, vector<unsigned int>& strides, vector<unsigned int>& offsets);
		void setVertexShader(const unique_ptr<VertexShader>& vertexShader);
};
#endif