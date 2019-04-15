#include "Material/MaterialInput.h"

void MaterialInputNode::fill(XMFLOAT4 value)
{
	this->r = value.x;
	this->g = value.y;
	this->b = value.z;
	this->a = value.w;
}
