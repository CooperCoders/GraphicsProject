#include "settings.h"
#include "tinyxml2.h"

Settings::Settings(std::string path)
{
	tinyxml2::XMLDocument doc;

	// Load settings file
	doc.LoadFile(path.c_str());
	tinyxml2::XMLElement * settingsElement = doc.FirstChildElement("Settings");

	// Assign settings values
	NumberOfParticles = std::stoi(settingsElement->FirstChildElement("NumberOfParticles")->GetText());
}