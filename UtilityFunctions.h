#pragma once
#include <iostream>
#include <sstream>
#include "MyString.h"
#include "Vector.hpp"
bool binarySearch(const Vector<size_t>& nums, int target);
bool isdigit(char c);
bool isStringNumber(const MyString& input);
size_t stringToSize_t(const MyString& str);
void setAllElementsToZero(Vector<size_t>& vec);