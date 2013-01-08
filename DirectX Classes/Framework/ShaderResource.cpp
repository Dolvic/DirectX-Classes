#include "Includes\ShaderResource.h"
#include "Includes\DirectXException.h"
#include "Includes\Resource.h"

ShaderResource::ShaderResource(const CComPtr<ID3D11ShaderResourceView>& srv) : view(srv)
{
}

unique_ptr<Resource> ShaderResource::getResource()
{
	if(view == nullptr)
		throw DirectXException("Exception while getting resource from SRV!");

	CComPtr<ID3D11Resource> resource;
	view->GetResource(&resource);
	return unique_ptr<Resource>(new Resource(resource));
}