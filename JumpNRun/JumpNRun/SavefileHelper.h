#pragma once
#include "StandardInclude.h"

class SavefileHelper
{
public:
	SavefileHelper();
	~SavefileHelper();

	string encryptDecrypt(string toEncrypt);
	int i;
};

