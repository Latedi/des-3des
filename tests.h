#ifndef TESTS_H
#define TESTS_H

#include "des.h"
#include "des3.h"

#include <iostream>
#include <string>

bool assertEncDec(std::string msg, std::string key, DES *des);
bool assertEncFail(std::string msg, std::string key, DES *des);
bool assertDecFail(std::string msg, std::string key, DES *des);
bool runTests();

#endif