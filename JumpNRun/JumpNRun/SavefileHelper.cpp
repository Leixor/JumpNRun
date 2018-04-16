#include "SavefileHelper.h"

SavefileHelper::SavefileHelper()
{
}

string SavefileHelper::encryptDecrypt(string toEncrypt)
{
	char key[4] = { 'K', 'C', '%', 'Q' };
	string output = toEncrypt;

	for (unsigned int i = 0; i < toEncrypt.size(); i++)
	{
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	return output;
}

SavefileHelper::~SavefileHelper()
{
}
