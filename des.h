#ifndef DES_H
#define DES_H

#include "helpers.h"

#include <bitset>
#include <vector>
#include <string>

class DES
{
private:
	enum FunctionMode {ENCRYPT, DECRYPT};
	static const int PC1[56];
	static const int PC2[48];
	static const int subkeyShifts[16];
	static const int IP[64], IPinverse[64];
	static const int E[48];
	static const std::bitset<4> S1[64], S2[64], S3[64], S4[64], S5[64], S6[64], S7[64], S8[64];
	static const int P[32];
	void rotateLeft28(std::bitset<28> &bits, int amount);
	std::bitset<56> permuteKeyPC1(std::bitset<64> key);
	std::bitset<48> permuteKeyPC2(std::bitset<56> key);
	std::bitset<64> permuteIP(std::bitset<64> msg);
	std::bitset<64> permuteIPinverse(std::bitset<64> cipherText);
	std::bitset<32> permuteP(std::bitset<32> halfBlock);
	std::bitset<48> permuteE(std::bitset<32> halfBlock);
	std::bitset<32> feistel(std::bitset<32> halfBlock, std::bitset<48> key);
	std::vector<std::bitset<48>> generateSubkeys(std::bitset<64> key64);
	std::bitset<64> encryptDecryptBlock64(std::bitset<64> msgBlock, std::vector<std::bitset<48>> subkeys, FunctionMode mode);
public:
	DES();
	~DES();
	std::string encrypt(std::string message, std::string key);
	std::string decrypt(std::string ciphertext, std::string key);
};

#endif