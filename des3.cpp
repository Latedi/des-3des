#include "des3.h"

DES3::DES3()
{
}

DES3::~DES3()
{
}

/*
	Naming it 3DES caused some problems with the header, so 3DES is now named DES3
	Also the implementation is simple, its just a wrapper for DES doing 3 passes with
	2 keys. For encryption we have E(D(E(M, K1), K2), K1) and the reverse for decryption.
*/

std::string DES3::encrypt(std::string message, std::string key)
{
	std::string output;
	//Check the key first
	Helpers h = Helpers();
	if(!h.verify3DESHexKey(key))
		return output;

	std::string key1 = key.substr(0, 16);
	std::string key2 = key.substr(16, 16);

	//Should any stage fail we need to return an empty value so that stage 3 doesn't
	//just pad it and encrypt garbage by mistake.
	DES des = DES();
	output = des.encrypt(message, key1);
	if(output == "") return output;
	output = des.decrypt(output, key2);
	if(output == "") return output;
	output = des.encrypt(output, key1);

	return output;
}

//This is the same as encryption, but the encryption/decryption has been reversed
std::string DES3::decrypt(std::string ciphertext, std::string key)
{
	std::string output;
	Helpers h = Helpers();
	if(!h.verify3DESHexKey(key))
		return output;

	std::string key1 = key.substr(0, 16);
	std::string key2 = key.substr(16, 16);

	DES des = DES();
	output = des.decrypt(ciphertext, key1);
	if(output == "") return output;
	output = des.encrypt(output, key2);
	if(output == "") return output;
	output = des.decrypt(output, key1);

	return output;
}