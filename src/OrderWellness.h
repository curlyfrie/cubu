#include <iostream>
#include <string>
#include "Wellness.h"

class OrderWellness {
	
	
private:

	int wellness_id;
	std::string datum;
	std::string name;
public:
	
	OrderWellness(int wellness_id, std::string name, std::string datum);

	int getWellnessId();
	std::string getDatum();
	std::string getName();
	
	~OrderWellness();
	
	
};