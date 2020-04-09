



#include "VenatorUtils.h"


#include <sstream>

//using namespace Venator;

int Venator::Utils::isBigIndian(void) 
{
	union {
		uint32_t i;
		char c[4];
	} bint = {0x01020304};

	return bint.c[0] == 1;
}



void Venator::Utils::split(std::vector<Scalar>& tokens, const std::string& str, const std::string& delimiters) 
{
	//vector<int> tokens;//(10);
	//tokens.reserve(10);

	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(Venator::Utils::String2Number<Scalar>(str.substr(lastPos, pos - lastPos)));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
	// return tokens;
}



void Venator::Utils::String2Vector(const std::string& str, Scalar v[])
{
    std::istringstream sss(str);
    int i = 0;
	std::string token;
    while (!sss.eof()) {
        getline(sss, token, ',');
        v[i++] = Venator::Utils::String2Number<Scalar>(token);
    }

}

Venator::Vec3 Venator::Utils::String2Vec3(const std::string& str)
{
	Venator::Vec3 temp(0,0,0);
	std::vector<Scalar> values;
    split(values,str,",");
	if (values.size() == 3) {
		temp.x = values[0];
		temp.y = values[1];
		temp.z = values[2];
	}
	return temp;
}

Venator::Quat Venator::Utils::String2Quat(const std::string& str) 
{
	Venator::Quat temp(1,0,0,0);
	std::vector<Scalar> values;
    split(values,str,",");
	if (values.size() == 4) {
		temp.w = values[0];
		temp.x = values[1];
		temp.y = values[2];
		temp.z = values[3];
	}
	return temp;
}



std::string Venator::Utils::Vec32String(const Vec3& vector)
{
	std::string pos = Number2String(vector.x);
	pos +=",";
	pos += Number2String(vector.y);
	pos +=",";
	pos += Number2String(vector.z);	
	return pos;
}

std::string Venator::Utils::Quat2String(const Quat& quat)
{
	std::string pos = Number2String(quat.w);
	pos +=",";
	pos += Number2String(quat.x);
	pos +=",";
	pos += Number2String(quat.y);
	pos +=",";
	pos += Number2String(quat.z);	
	return pos;
}

std::string Venator::Utils::generateName(void) 
{
	static int counter = 0;
	return "auto_generated_name_" + Venator::Utils::Number2String(counter++);
}

