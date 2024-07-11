#ifndef GRAPHICS_INTERFACE_ADAPTER_H_
#define GRAPHICS_INTERFACE_ADAPTER_H_

#include <vector>
#include <string>
namespace radium
{

/*
	PURPOSE
		Collect/Hold information about available graphics
		adapters
		Stores a ID => Display Name map
*/
class AdapterList
{
public:

	AdapterList() : m_gAdapterMap{}, m_monitorMap{}
	{
	}
	~AdapterList() = default;


	int detectAdapters();
	int detectDisplays();
	bool isValidAdapter(unsigned int id);



private:
	std::vector<std::string> m_gAdapterMap;
	std::vector<std::string> m_monitorMap;
};


} // radium


#endif // GRAPHICS_INTERFACE_ADAPTER_H_ 