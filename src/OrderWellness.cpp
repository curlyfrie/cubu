#include "OrderWellness.h"


OrderWellness::OrderWellness(int _wellness_id, std::string _name, std::string _datum)
{
	
	wellness_id = _wellness_id;
	datum = _datum;
	name = _name;
	
}


int OrderWellness::getWellnessId()
{
	
	return wellness_id;
}

std::string OrderWellness::getDatum()
{

	return datum;
}
std::string OrderWellness::getName()
{

	return name;
}