#include "standardInclude.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std; 



ConfigHelper::ConfigHelper(string toReadFrom, char pSectionBegin, char pSectionEnd) : textFileName(toReadFrom), sectionBegin(pSectionBegin), sectionEnd(pSectionEnd)
{
	this->readComplete();	
}

void ConfigHelper::readComplete()
{
	// Clear die Tabelle
	cfgTable.clear();

	bool endSign = false;;

	int i = 0;

	// String zum durchiterieren bereitstellen
	string str;

	// File öffnen
	ifstream file(textFileName);

	// Die ganze config lesen
	while (std::getline(file, str)) 
	{
		if (str.at(0) == sectionBegin) {
			string sectionName = this->RemoveChars(str, string(1, sectionBegin));
			cfgTable.push(sectionName, new UnorderdMap<string, string>());
			while (!endSign)
			{
				getline(file, str);
				if (str.at(0) == sectionEnd)
				{
					endSign = true;
					break;
				}
				stringstream ss(str);
				getline(ss, str, ':');
				string varName = str;
				getline(ss, str);
				string varValue = str;
				cfgTable.get(i)->push(varName, varValue);
			}
			i++;
		}
		endSign = false;
	}
}


string ConfigHelper::get(string container, string variableName)
{
	return this->cfgTable.get(container)->get(variableName);
}

void ConfigHelper::write(string container, string variableName, string variableValue)
{
	bool writeSuccess = false;

	// Erstmal checken ob der Container exestiert
	for (int i = 0; i < this->cfgTable.size(); i++)
	{
		// Falls er da reinkommt exestiert der Container schonmal
		if (this->cfgTable.getIterator(i) == container)
		{
			// Checken ob die Variable schon exestiert
			for (int j = 0; j < this->cfgTable.get(i)->size(); j++)
			{
				// Falls er da reinkommt exestiert die Variable schon
				if (this->cfgTable.get(i)->getIterator(j) == variableName)
				{
					// Variable überschreiben
					this->cfgTable.get(i)->set(j, variableValue);
					writeSuccess = true;
					break;
				}
			}
			// Variable erstellen falls nicht vorhanden und füllen
			if (!writeSuccess)
			{
				this->cfgTable.get(i)->push(variableName, variableValue);
				writeSuccess = true;
				break;
			}

		}
	}
	// Wenn der Container nicht exestiert auch einen neuen Container samt Variable erstellen
	if (!writeSuccess)
	{
		this->cfgTable.push(container, new UnorderdMap<string, string>);
		this->cfgTable.get(cfgTable.size() - 1)->push(variableName, variableValue);
	}

	ofstream myfile(this->textFileName);

	for (int i = 0; i < this->cfgTable.size(); i++)
	{
		myfile << sectionBegin;
		// Erstmal Containersektion reinschreiben
		myfile << this->cfgTable.getIterator(i) << "\n";

		for (int j = 0; j < this->cfgTable.get(i)->size(); j++)
		{
			// Container füllen
			myfile << this->cfgTable.get(i)->getIterator(j) << ":" << this->cfgTable.get(i)->get(j) << "\n";
		}
		myfile << sectionEnd << "\n";
	}
	myfile.close();
}



std::string ConfigHelper::RemoveChars(const std::string& source, const std::string& chars)
{
	std::string result = "";
	for (unsigned int i = 0; i<source.length(); i++) {
		bool foundany = false;
		for (unsigned int j = 0; j<chars.length() && !foundany; j++) {
			foundany = (source[i] == chars[j]);
		}
		if (!foundany) {
			result += source[i];
		}
	}
	return result;
}


ConfigHelper::~ConfigHelper()
{

}
