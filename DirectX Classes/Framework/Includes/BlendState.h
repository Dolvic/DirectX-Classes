#ifndef DIRECTX_BLEND_STATE
#define DIRECTX_BLEND_STATE

#include <D3D11.h>
#include <atlbase.h>

class BlendState
{
	friend class Device;

	private:
		CComPtr<ID3D11BlendState> state;
		D3D11_BLEND_DESC descriptor;
	public:
		BlendState();

		void enableBlend(int index);
		void setColorBlend(int index, D3D11_BLEND_OP blendOperator, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend);
		void setAlphaBlend(int index, D3D11_BLEND_OP blendOperator, D3D11_BLEND sourceBlend, D3D11_BLEND destinationBlend);
};

#endif