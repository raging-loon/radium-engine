#include "core/Variant.h"

using radium::Variant;

/********** VARIANT CONTRUCTORS **********/
Variant::Variant(int n)
{
	m_type = INT;
	_int = n;
}

Variant::Variant(bool b)
{
	m_type = BOOL;
	_bool = b;
}

/********** VARIANT OPERATORS **********/

Variant::operator int() { return _int; }
Variant::operator bool() { return _bool; }

void Variant::operator=(bool b)
{
	m_type = BOOL;
	_bool = b;
}

void Variant::operator=(int n)
{
	m_type = INT;
	_int = n;
}