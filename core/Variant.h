#ifndef CORE_VARIANT_H_
#define CORE_VARIANT_H_


namespace radium
{

class Variant
{
public:
	enum Type
	{
		NONE,
		INT,
		BOOL
	};
	Variant() {}
	Variant(int n);
	Variant(bool b);

	operator int();
	operator bool();

	Type getType() const { return m_type; }

	void operator=(bool b);
	void operator=(int n);
private:

	union
	{
		int _int;
		bool _bool;
	};

	Type m_type = NONE;


};

}





#endif // CORE_VARIANT_H_