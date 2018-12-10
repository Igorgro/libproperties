#include "Properties.h"
#include <fstream>
#include <streambuf>
#include <iostream>

Properties::Properties()
{

}

Properties::Properties (std::string filename)
{
    std::ifstream in (filename);
    std::string propertiesString = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    in.close();

    createPropertiesFromString(propertiesString);
}


void Properties::createPropertiesFromString (std::string propertiesString)
{
    unsigned int line_start = 0;
    unsigned int line_end = 0;
    while(true)
    {
        line_end = propertiesString.find_first_of ('\n', line_start);
        std::string propertyString = propertiesString.substr (line_start, line_end-line_start);
        if (propertyString.at (0) != '#') createPropertyFromString (propertyString);

        line_start = line_end+1;
        if (line_start >= propertiesString.length()) break;
    }
}

void Properties::createPropertyFromString (std::string propertyString)
{
    unsigned int eqSignPos = propertyString.find_first_of ('=');
    std::string key = propertyString.substr (0, eqSignPos);
    std::string value;

    if (eqSignPos != propertyString.length()-1) value = propertyString.substr (eqSignPos+1, propertyString.length()-eqSignPos);
    else value = std::string ("");

    setValue(key, value);
}

std::string Properties::getValue(std::string key)
{
    return _map.at(key);
}
void Properties::setValue (std::string key, std::string value)
{
    _map.insert(std::pair<std::string, std::string>(key, value));
}
bool Properties::contains(std::string key)
{
    return (bool) _map.count(key);
}

void Properties::storeToFile (std::string filename)
{
    std::map<std::string, std::string>::iterator iter = _map.begin();
    std::string propertiesString;
    while (iter != _map.end())
    {
        propertiesString+=iter->first;
        propertiesString+="=";
        propertiesString+=iter->second;
        propertiesString+="\n";
        iter++;
    }
    std::ofstream out (filename);
    out << propertiesString;
    out.close();
}














