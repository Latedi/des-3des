#include "helpers.h"
#include <stdio.h>
#include <iostream>

Helpers::Helpers()
{
}

Helpers::~Helpers()
{
}

/*
	These methods are needed, but doesn't have with DES to do directly
*/

std::bitset<64> Helpers::strToBitset64(std::string str)
{
	std::bitset<64> ret;
	if(str.length() < 16)
		return ret;

	//Convert ascii hex value to a value in the range 0-15 as a bitset<4> and put into return value
	for(int i = 0; i < 16; i++)
	{
		int val = (int) str[i];
		if(val <= 57)
			val = val - (int) '0';
		else
			val = val - (int) 'A' + 10;

		 std::bitset<4> bitval = std::bitset<4>(val);
		 //Magic
		 for(int j = 0; j < 4; j++)
		 {
			 ret[63-i*4-j] = bitval[3-j];
		 }
	}

	return ret;
}

std::string Helpers::bitset64ToStr(std::bitset<64> bits)
{
	std::string ret = "";

	for(int i = 0; i < 16; i++)
	{
		//Retrieve part of the bitset at a time
		std::bitset<4> bitval;
		for(int j = 0; j < 4; j++)
		{
			bitval[3-j] = bits[63-i*4-j];
		}

		int hexval = bitval.to_ulong();

		//Convert the 4-bit part to a hexadecimal char and add to return value
		char c;
		if(hexval < 10)
			c = (char) hexval + '0';
		else
			c = (char) hexval + 'A' - 10;

		ret += c;
	}

	return ret;
}

//Check that a key is hexadecimal and of a certain length
bool Helpers::verifyHexKey(std::string key, int keylen)
{
	//Length check
	if(key.length() != keylen)
		return false;
	//Character check
	for(int i = 0; i < 16; i++)
	{
		if(!isHex(key[i]))
			return false;
	}

	return true;
}

bool Helpers::verifyDESHexKey(std::string key)
{
	return verifyHexKey(key, 16);
}

bool Helpers::verify3DESHexKey(std::string key)
{
	return verifyHexKey(key, 32);
}

bool Helpers::isHex(char c)
{
	int val = (int) c;
	//If value is not in ascii range 48-57 (0-9) or range 65-70 (A-F) return false
	if(!((val >= (int) '0' && val <= (int) '9') || (val >= (int) 'A' && val <= 'F')))
		return false;
}

bool Helpers::verifyIsAllHex(std::string data)
{
	for(int i = 0; i < data.length(); i++)
	{
		if(!isHex(data[i]))
			return false;
	}
	return true;
}