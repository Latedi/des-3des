#include "des.h"

DES::DES()
{
}

DES::~DES()
{
}

/*
	-- Permutation tables etc --
*/

const int DES::PC1[] =	{57,49,41,33,25,17,9,
						1,58,50,42,34,26,18,
						10,2,59,51,43,35,27,
						19,11,3,60,52,44,36,
						63,55,47,39,31,23,15,
						7,62,54,46,38,30,22,
						14,6,61,53,45,37,29,
						21,13,5,28,20,12,4};

const int DES::PC2[] =	{14,17,11,24,1,5,
						3,28,15,6,21,10,
						23,19,12,4,26,8,
						16,7,27,20,13,2,
						41,52,31,37,47,55,
						30,40,51,45,33,48,
						44,49,39,56,34,53,
						46,42,50,36,29,32};

const int DES::subkeyShifts[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

const int DES::IP[] =	{58,50,42,34,26,18,10,2,
						60,52,44,36,28,20,12,4,
						62,54,46,38,30,22,14,6,
						64,56,48,40,32,24,16,8,
						57,49,41,33,25,17,9,1,
						59,51,43,35,27,19,11,3,
						61,53,45,37,29,21,13,5,
						63,55,47,39,31,23,15,7};

const int DES::IPinverse[] =	{40,8,48,16,56,24,64,32,
								39,7,47,15,55,23,63,31,
								38,6,46,14,54,22,62,30,
								37,5,45,13,53,21,61,29,
								36,4,44,12,52,20,60,28,
								35,3,43,11,51,19,59,27,
								34,2,42,10,50,18,58,26,
								33,1,41,9,49,17,57,25};

const int DES::E[] =	{32,1,2,3,4,5,
						4,5,6,7,8,9,
						8,9,10,11,12,13,
						12,13,14,15,16,17,
						16,17,18,19,20,21,
						20,21,22,23,24,25,
						24,25,26,27,28,29,
						28,29,30,31,32,1};

const int DES::P[] =	{16,7,20,21,
						29,12,28,17,
						1,15,23,26,
						5,18,31,10,
						2,8,24,14,
						32,27,3,9,
						19,13,30,6,
						22,11,4,25};

const std::bitset<4> DES::S1[] =	{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
									0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
									4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
									15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

const std::bitset<4> DES::S2[] =	{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
									3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
									0,14,7,17,10,4,13,1,5,8,12,6,9,3,2,15,
									13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

const std::bitset<4> DES::S3[] =	{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
									13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
									13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
									1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

const std::bitset<4> DES::S4[] =	{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
									13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
									10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
									3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

const std::bitset<4> DES::S5[] =	{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
									14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
									4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
									11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

const std::bitset<4> DES::S6[] =	{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
									10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
									9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
									4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

const std::bitset<4> DES::S7[] =	{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
									13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
									1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
									6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

const std::bitset<4> DES::S8[] =	{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
									1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
									7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
									2,1,14,7,4,10,8,13,15,2,9,0,3,5,6,11};

/*
	-- The core of the DES functionality --
*/

//Encrypt or decrypt a 64 bit long message
std::bitset<64> DES::encryptDecryptBlock64(std::bitset<64> msgBlock, std::vector<std::bitset<48>> subkeys, FunctionMode mode)
{
	//Permute the message
	msgBlock = permuteIP(msgBlock);
	std::bitset<32> L, R;

	//Split it in half
	for(int i = 0; i < 32; i++)
	{
		L[i] = msgBlock[i+32];
		R[i] = msgBlock[i];
	}

	//The core of DES. L(n) = R(n-1), R(n) = L(n-1) XOR f(R(n-1), K(n)). Repeat 16 times.
	for(int i = 0; i < 16; i++)
	{
		std::bitset<32> oldL = L;
		L = R;
		if(mode == this->ENCRYPT)
		{
			R = oldL ^ feistel(R, subkeys[i]);
		}
		else if(mode == this->DECRYPT)
		{
			R = oldL ^ feistel(R, subkeys[15-i]);
		}
	}

	//Put left and right together again in the wrong order
	std::bitset<64> cipherBlock;
	for(int i = 0; i < 32; i++)
	{
		cipherBlock[i+32] = R[i];
		cipherBlock[i] = L[i];
	}

	//Do one final permutation
	cipherBlock = permuteIPinverse(cipherBlock);
	return cipherBlock;
}

//The Feistel function
std::bitset<32> DES::feistel(std::bitset<32> halfBlock, std::bitset<48> key)
{
	//Expand the key using E and XOR with the key
	std::bitset<48> expandedBlock = permuteE(halfBlock);
	expandedBlock ^= key;

	//Split the XORed key into blocks of 6
	std::vector<std::bitset<6>> splitBlock;
	for(int i = 0; i < 8; i++)
	{
		std::bitset<6> part;
		for(int j = 0; j < 6; j++)
		{
			part[j] = expandedBlock[i * 6 + j];
		}

		splitBlock.insert(splitBlock.begin(), part);
	}

	//Create references to the S-boxes
	static const std::bitset<4> *Sboxes[8] = {S1, S2, S3, S4, S5, S6, S7, S8};
	std::vector<std::bitset<4>> reducedBlock;
	for(int i = 0; i < 8; i++)
	{
		//Bit 1 and 6 is the row of the S-box
		std::bitset<2> row;
		row[0] = splitBlock[i][0];
		row[1] = splitBlock[i][5];

		//Bits 2 through 5 is the column
		std::bitset<4> col;
		for(int j = 1; j < 5; j++)
		{
			col[j-1] = splitBlock[i][j];
		}

		//Get the current S-box
		const std::bitset<4>* currentTable = Sboxes[i];

		//Make life easier
		int rowint = row.to_ulong();
		int colint = col.to_ulong();

		//Copy from the calculated Sbox address to a new bitset<4>.
		const std::bitset<4> *sboxval = currentTable + rowint * 16 + colint;
		std::bitset<4> sboxcopy;
		for(int k = 0; k < 4; k++)
		{
				sboxcopy[k] = (*sboxval)[k];
		}
		int xboxxczxc = sboxcopy.to_ulong();

		//Push the value into the vector
		reducedBlock.push_back(sboxcopy);
	}

	//Put  all the pieces together in one container
	std::bitset<32> output;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			output[28-i*4+j] = reducedBlock[i][j];
		}
	}

	//And do one final permutation
	output = permuteP(output);
	return output;
}

//Generate the subkeys
std::vector<std::bitset<48>> DES::generateSubkeys(std::bitset<64> key64)
{
	//Permute the key and shorten it, create arrays for C, D 0-16
	std::bitset<56> key56 = permuteKeyPC1(key64);
	std::bitset<28> C[17], D[17];

	//Split the key into two
	for(int i = 0; i < 28; i++)
	{
		C[0][i] = key56[i+28];
		D[0][i] = key56[i];
	}

	//Rotate the key for all C, D
	for(int i = 1; i < 17; i++)
	{
		C[i] = C[i-1];
		D[i] = D[i-1];

		rotateLeft28(C[i], subkeyShifts[i-1]);
		rotateLeft28(D[i], subkeyShifts[i-1]);
	}

	//Put the keys back together and permute them again, add to return vector
	std::vector<std::bitset<48>> subkeys48;
	for(int i = 1; i < 17; i++)
	{
		std::bitset<56> subkey56;
		for(int j = 0; j < 28; j++)
		{
			subkey56[j+28] = C[i][j];
			subkey56[j] = D[i][j];
		}

		subkeys48.push_back(permuteKeyPC2(subkey56));
	}

	return subkeys48;
}

/*
	-- Smaller functions for applying permutations and rotating bits --
*/

//Shift a key and put the out of bounds bits on the right instead
void DES::rotateLeft28(std::bitset<28> &bits, int amount)
{
	amount %= 28;
	if(amount == 0)
		return;
	std::bitset<28> rotation = bits >> (28 - amount);
	bits = bits << amount;
	bits |= rotation;
}

std::bitset<48> DES::permuteE(std::bitset<32> halfBlock)
{
	std::bitset<48> ret;
	for(int i = 0; i < 48; i++)
	{
		int eval = E[i];
		bool blockval = halfBlock[32-eval];
		ret[47-i] = blockval;
	}
	return ret;
}

std::bitset<64> DES::permuteIP(std::bitset<64> msg)
{
	std::bitset<64> ret;
	for(int i = 0; i < 64; i++)
	{
		int ipval = IP[i];
		bool msgval = msg[64-ipval];
		ret[63-i] = msgval;
	}
	return ret;
}

std::bitset<64> DES::permuteIPinverse(std::bitset<64> cipherText)
{
	std::bitset<64> ret;
	for(int i = 0; i < 64; i++)
	{
		int ipival = IPinverse[i];
		bool cipherval = cipherText[64-ipival];
		ret[63-i] = cipherval;
	}
	return ret;
}

std::bitset<56> DES::permuteKeyPC1(std::bitset<64> key)
{
	std::bitset<56> ret;
	for(int i = 0; i < 56; i++)
	{
		int pc1val = PC1[i];
		bool keyval = key[64-pc1val];
		ret[55-i] = keyval;
	}
	return ret;
}

std::bitset<48> DES::permuteKeyPC2(std::bitset<56> key)
{
	std::bitset<48> ret;
	for(int i = 0; i < 48; i++)
	{
		ret[47-i] = key[56-PC2[i]];
	}
	return ret;
}

std::bitset<32> DES::permuteP(std::bitset<32> halfBlock)
{
	std::bitset<32> ret;
	for(int i = 0; i < 32; i++)
	{
		int pval = P[i];
		bool blockval = halfBlock[32-pval];
		ret[31-i] = blockval;
	}
	return ret;
}

/*
	-- The public wrapper functions for encryption and decryption --
*/

//Encrypt a hexadecimal string of arbitrary length using a 64-bit key
//ex input "0123456789ABCDEF", "133457799BBCDFF1" outputs "85E813540F0AB405"
//Returns empty if the key in invalid
std::string DES::encrypt(std::string message, std::string key)
{
	std::string ret = "";
	int strlen = message.length();

	//Verify the key and generate the subkeys
	Helpers h = Helpers();
	if(!h.verifyDESHexKey(key))
		return ret;
	std::bitset<64> key64 = h.strToBitset64(key);
	std::vector<std::bitset<48>> subkeys = generateSubkeys(key64);

	//Check that the message only contains valid values
	if(!h.verifyIsAllHex(message))
		return ret;

	//Loop through the message 64 bits at a time and encrypt them
	int index = 0;
	while(index < strlen)
	{
		//If the message is not divisible by 16 we need to pad it with 0s.
		//This is not secure enough for usage in any real setting.
		std::string block;
		if(index + 16 <= strlen)
		{
			block = message.substr(index, 16);
		}
		else
		{
			int diff = strlen - index;
			block = message.substr(index, diff);
			for(int i = 0; i < 16 - diff; i++)
				block += "0";
		}

		//Encrypt the 64-bit block and add it to the return value
		std::bitset<64> block64 = h.strToBitset64(block);
		std::bitset<64> cipher64 = encryptDecryptBlock64(block64, subkeys, this->ENCRYPT);
		ret += h.bitset64ToStr(cipher64);

		//Progress through the indices
		index += 16;
	}

	return ret;
}

//Decrypt a hexadecimal string of arbitrary length using a 64-bit key
//ex input "85E813540F0AB405", "133457799BBCDFF1" outputs "0123456789ABCDEF"
//Returns empty if the key or cipher text is invalid
std::string DES::decrypt(std::string ciphertext, std::string key)
{
	std::string ret = "";

	//Verify the key and generate the subkeys
	Helpers h = Helpers();
	if(!h.verifyDESHexKey(key))
		return ret;
	std::bitset<64> key64 = h.strToBitset64(key);
	std::vector<std::bitset<48>> subkeys = generateSubkeys(key64);

	//If the message length is not divisible by 16, it is invalid or damaged
	int cipherlen = ciphertext.length();
	if(cipherlen % 16 != 0)
		return ret;

	//Check that the cipher text only contains valid values
	if(!h.verifyIsAllHex(ciphertext))
		return ret;

	//Loop through the message 64 bits at a time and decrypt them
	int index = 0;
	while(index < cipherlen)
	{
		//The length is always divisible by 16 here, so just retrieve the substring
		std::string block = ciphertext.substr(index, 16);

		//Decrypt the 64-bit block and add it to the return value
		std::bitset<64> block64 = h.strToBitset64(block);
		std::bitset<64> msg64 = encryptDecryptBlock64(block64, subkeys, this->DECRYPT);
		ret += h.bitset64ToStr(msg64);

		//Progress through the indices
		index += 16;
	}

	return ret;
}