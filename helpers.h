#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <bitset>

class Helpers
{
public:
	Helpers();
	~Helpers();
	std::bitset<64> strToBitset64(std::string str);
	std::string bitset64ToStr(std::bitset<64> bits);
	bool verifyHexKey(std::string key, int keylen);
	bool verifyDESHexKey(std::string key);
	bool verify3DESHexKey(std::string key);
	bool isHex(char c);
	bool verifyIsAllHex(std::string data);
};

#endif