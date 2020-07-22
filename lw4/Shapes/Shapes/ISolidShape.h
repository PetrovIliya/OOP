#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual double GetArea() const = 0;
	virtual uint32_t GetFillColor() const = 0;
	virtual ~ISolidShape() = default;
};