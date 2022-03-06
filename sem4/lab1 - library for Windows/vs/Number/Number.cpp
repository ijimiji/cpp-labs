#include "pch.h"
#include "framework.h"
#include "Number.h"

Math::Number::Number(double value)
	:value(value)
{

}

Math::Number Math::Number::operator+(Math::Number other)
{
	return Number(this->value + other.value);
}

Math::Number Math::Number::operator-(Number other)
{
	return Number(this->value - other.value);
}

Math::Number Math::Number::operator*(Number other)
{
	return Number(this->value * other.value);
}

double Math::Number::getValue() { 
	return value; 
}

std::string Math::Number::toString()
{
	return std::to_string(value);
}

Math::Number Math::Number::operator/(Number other)
{
	return Number(this->value / other.value);
}

Math::Number Math::Number::ONE = Math::Number(1);
Math::Number Math::Number::ZERO = Math::Number(0);