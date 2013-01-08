#ifndef DIRECTX_EXCEPTION
#define DIRECTX_EXCEPTION

#include <exception>
using std::exception;

class DirectXException : public exception
{
	private:
		const char* errorMessage;
	public:
		DirectXException();
		DirectXException(const char* reason);

		virtual const char* what();
};

#endif