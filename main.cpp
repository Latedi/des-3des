#include "des.h"
#include "des3.h"
#include "tests.h"

#include <iostream>
#include <string>

const std::string helpstr = "This is a simple implementation of DES and 3DES using 0 padding\n"
							"Supply only hexadecimal strings such as \"ABC123\" and make sure that: all"
							" DES keys are of length 16 (number of hexadecimal characters), all 3DES "
							"keys are of length 32 and all ciphertexts are of a length divisible by 16.\n\n"
							"\"-h\" print this message\n"
							"\"-t\" run unit tests\n"
							"\"-e <key> <msg>\" encrypt a message msg with a key using DES\n"
							"\"-e3 <key> <msg>\" encrypt a message msg with a key using 3DES\n"
							"\"d <key> <msg>\" decrypt a message msg with a key using DES\n"
							"\"-d3 <key> <msg>\" decrypt a message msg with a key using 3DES\n\n"
							"Some examples:\n"
							"-t\n"
							"-e ABCDEF1234567890 A1B2C3D4E5F6A890\n"
							"-d3 ABCDEF12345678901840EABC0173B7B1 A1B2C3D4E5F6A890\n";

//It works
int main(int argc, char* argv[])
{
	for(int i = 0; i < argc; i++)
	{
		//Run the tests
		if(strcmp(argv[i], "-t") == 0)
		{
			runTests();
			return 0;
		}
		//Encrypt with DES
		if(strcmp(argv[i], "-e") == 0)
		{
			if(i + 2 < argc)
			{
				DES des = DES();
				std::string key = argv[i+1];
				std::string msg = argv[i+2];
				std::string output = des.encrypt(msg, key);
				if(output != "")
					std::cout << output;
				else
					std::cout << "Invalid input\n";
				return 0;
			}
		}
		//Encrypt with 3DES
		if(strcmp(argv[i], "-e3") == 0)
		{
			if(i + 2 < argc)
			{
				DES3 des3 = DES3();
				std::string key = argv[i+1];
				std::string msg = argv[i+2];
				std::string output = des3.encrypt(msg, key);
				if(output != "")
					std::cout << output;
				else
					std::cout << "Invalid input\n";
				return 0;
			}
		}
		//Decrypt with DES
		if(strcmp(argv[i], "-d") == 0)
		{
			if(i + 2 < argc)
			{
				DES des = DES();
				std::string key = argv[i+1];
				std::string cipher = argv[i+2];
				std::string output = des.decrypt(cipher, key);
				if(output != "")
					std::cout << output;
				else
					std::cout << "Invalid input\n";
				return 0;
			}
		}
		//Decrypt with 3DES
		if(strcmp(argv[i], "-d3") == 0)
		{
			if(i + 2 < argc)
			{
				DES3 des3 = DES3();
				std::string key = argv[i+1];
				std::string cipher = argv[i+2];
				std::string output = des3.decrypt(cipher, key);
				if(output != "")
					std::cout << output;
				else
					std::cout << "Invalid input\n";
				return 0;
			}
		}
	}

	//That thing about -h was a lie, let's just print it at the end
	std::cout << helpstr;
	return 0;
}