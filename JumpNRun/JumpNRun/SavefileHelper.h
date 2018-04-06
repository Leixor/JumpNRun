#pragma once
#include <fstream>
#include "UnorderdMap.h"
class SavefileHelper
{
public:
	SavefileHelper();
	~SavefileHelper();

	string encryptDecrypt(string toEncrypt);
	int i;
};

