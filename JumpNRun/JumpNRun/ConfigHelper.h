#pragma once
#include <fstream>
#include "UnorderdMap.h"
class ConfigHelper
{
public:
	ConfigHelper(string toReadFrom, char pSectionBegin = '[', char pSectionEnd = '#');
	~ConfigHelper();

	// Öffentliche Helferfunktionen
	void readComplete();
	string get(string container, string variableName);
	void write(string container, string variableName, string variableValue);



private:
	// Filename
	string textFileName;

	// Config wird hier abgespeichert
	UnorderdMap<string, UnorderdMap<string, string>*> cfgTable;

	// Helferfunkion zu rausfiltern der Chars
	std::string RemoveChars(const std::string& source, const std::string& chars);

	// Chars zum abgrenzen der Sektionen
	char sectionBegin;
	char sectionEnd;
};

