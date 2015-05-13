#include "tests.h"

//Assert successful encryption and decryption of a message with a given key
bool assertEncDec(std::string msg, std::string key, DES *des)
{
	//Encrypt and decrypt the message
	std::string data = des->encrypt(msg, key);
	data = des->decrypt(data, key);

	//Remove any potential zeroes by changing the size to be equal to the input
	if(data.length() != msg.length())
	{
		data = data.substr(0, msg.length());
	}

	//And compare the results.
	if(msg == data)
	{
		std::cout << "ENCRYPTION AND DECRYPTION SUCCESS " << msg << " " << key << "\n";
		return true;
	}
	else
		std::cout << "ENCRYPTION AND DECRYPTION FAILED " << msg << " " << key << "\n";
	return false;
}

//Assert failure of encryption or decryption and an empty return value
bool assertEncFail(std::string msg, std::string key, DES *des)
{
	std::string output = des->encrypt(msg, key);
	std::string asd = des->decrypt(output, key);
	if(output == "")
	{
		std::cout << "ENCRYPTION FAILED AS EXPECTED " << msg << " " << key << "\n";
		return true;
	}
	return false;
}

//Assert error upon decryption
bool assertDecFail(std::string msg, std::string key, DES *des)
{
	std::string output = des->decrypt(msg, key);
	if(output == "")
	{
		std::cout << "DECRYPTION FAILED AS EXPECTED " << msg << " " << key << "\n";
		return true;
	}
	return false;
}

bool runTests()
{
	DES des = DES();
	Helpers h = Helpers();

	//If these are the same at the end, all tests succeded
	//Return -1 if any one test fail
	int potentialMax = 0;
	int successes = 0;

	std::cout << "TESTING STARTED\n";
	std::cout << "TESTING DES...\n";

	//64, 128, 96 and 32 bit messages
	std::string sMsgs[] = {"0123456789ABCDEF", "AA22DD44EE88BB00CC11", "1273AFEB9054CDAE1234", "1234ABCD"};
	//And their keys
	std::string sKeys[] = {"133457799BBCDFF1", "A7E6DE8123B2BE00", "1893B5E9AD90017C", "D7E9A4C1B0F3F6E2"};

	//These should all be successful
	for(int i = 0; i < 4; i++)
	{
		potentialMax++;
		if(assertEncDec(sMsgs[i], sKeys[i], &des))
			successes++;
	}

	if(potentialMax != successes)
	{
		std::cout << "ASSERTING ENCRYPTION/DECRYPTION OF MESSAGES FAILED\n";
		return false;
	}

	//Message values under 0, between 9 and A and over A
	//They are used for failing both encrpytion and decryption since theyre 16 characters in length
	std::string fMsgs[] = {"012+456789ABCDEF", "0123456789=BCDEF", "0123456j89ABCDEF", };
	std::string fKey ="133457799BBCDFF1";
	//These should all fail
	for(int i = 0; i < 3; i++)
	{
		potentialMax += 2;
		if(assertEncFail(fMsgs[i], fKey, &des))
			successes++;
		if(assertDecFail(fMsgs[i], fKey, &des))
			successes++;
	}

	if(potentialMax != successes)
	{
		std::cout << "ASSERT CORRECT MESSAGE VALUES FAILED\n";
		return false;
	}

	//Invalid cipher text lengths 15, 17 and 0
	std::string fCipherLens[] = {"0123456789ABCDE", "0123456789ABCDEFA", ""};
	for(int i = 0; i < 3; i++)
	{
		potentialMax++;
		if(assertDecFail(fCipherLens[i], fKey, &des))
			successes++;
	}

	if(potentialMax != successes)
	{
		std::cout << "ASSERT CORRECT CIPHER TEXT LENGTHS FAILED\n";
		return false;
	}

	//Invalid key lengths 15, 17, 0 and invalid values under 0, between 9 and A and over A
	std::string fKeys2[] =	{"133457799BBCDFF", "133457799BBCDFF1A", "",
								"1334577+9BBCDFF1", "133=57799BBCDFF1", "133457799BBCDjF1"};
	std::string fMsg = "0123456789ABCDEF";
	for(int i = 0; i < 6; i++)
	{
		potentialMax++;
		//Encryption and decryption checks keys exacty the same
		if(assertEncFail(fMsg, fKeys2[i], &des))
			successes++;
	}

	if(potentialMax != successes)
	{
		std::cout << "ASSERT INVALID KEYS FAILED\n";
		return false;
	}

	std::cout << "TESTING DES COMPLETED\n";
	std::cout << "TESTING 3DES...\n";

	//3DES works if DES does. So only the wrapper functions need to be tested.
	//Error handling is also the same.
	DES3 des3 = DES3();
	std::string f3Msg = "0123456789ABCDEF";
	std::string f3Key = "133457799BBCDFF11893B5E9AD90017C";
	potentialMax++;
	std::string output = des3.decrypt(des3.encrypt(f3Msg, f3Key), f3Key);
	if(output == f3Msg)
	{
		std::cout << "3DES ENCRYPTION AND DECRYPTION SUCCESS " << f3Msg << " " << f3Key << "\n";
		successes++;
	}
	else
	{
		std::cout << "3DES ENCRYPTION AND DECRYPTION FAILED " << f3Msg << " " << f3Key << "\n";
		return false;
	}


	std::cout << "\nALL TESTS, " << successes << " OF " << potentialMax << " SUCCEDED\n";

	return true;
}