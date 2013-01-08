#include "Includes\InputElement.h"

InputElement::InputElement() : descriptor()
{
}

InputElement::InputElement(D3D11_INPUT_ELEMENT_DESC desc) : descriptor(desc)
{
}

InputElement::InputElement(const char* elementName, int elementIndex, DXGI_FORMAT format, int inputSlot, int byteOffset, bool perVertex, int stepRate) : descriptor()
{
	setElementName(elementName);
	setElementIndex(elementIndex);
	setFormat(format);
	setInputSlot(inputSlot);
	setByteOffset(byteOffset);
	setPerVertex(perVertex);
	setStepRate(stepRate);
}

void InputElement::setElementName(const char* name)
{
	descriptor.SemanticName = name;
}

const char* InputElement::getElementName()
{
	return descriptor.SemanticName;
}

void InputElement::setElementIndex(int index)
{
	descriptor.SemanticIndex = index;
}

int InputElement::getElementIndex()
{
	return descriptor.SemanticIndex;
}

void InputElement::setFormat(DXGI_FORMAT format)
{
	descriptor.Format = format;
}

DXGI_FORMAT InputElement::getFormat()
{
	return descriptor.Format;
}

void InputElement::setInputSlot(int inputSlot)
{
	descriptor.InputSlot = inputSlot;
}

int InputElement::getInputSlot()
{
	return descriptor.InputSlot;
}

void InputElement::setByteOffset(int byteOffset)
{
	descriptor.AlignedByteOffset = byteOffset;
}

int InputElement::getByteOffset()
{
	return descriptor.AlignedByteOffset;
}

void InputElement::setPerVertex(bool perVertex)
{
	if(perVertex)
		descriptor.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	else
		descriptor.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
}

bool InputElement::isPerVertex()
{
	return descriptor.InputSlotClass == D3D11_INPUT_PER_VERTEX_DATA ? true : false;
}

void InputElement::setStepRate(int stepRate)
{
	descriptor.InstanceDataStepRate = stepRate;
}

int InputElement::getStepRate()
{
	return descriptor.InstanceDataStepRate;
}