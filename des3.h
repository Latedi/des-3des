#ifndef DES3_H
#define DES3_H

#include "des.h"
#include "helpers.h"
#include <string>

class DES3
{
public:
	DES3();
	~DES3();
	std::string encrypt(std::string message, std::string key);
	std::string decrypt(std::string ciphertext, std::string key);
};

#endif