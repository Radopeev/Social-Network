#pragma once
#include <iostream>

class MyString
{
	char* _data;
	size_t _length;

	void copyFrom(const MyString& data);
	void free();
	void move(MyString&& other)noexcept;

	explicit MyString(size_t capacity);
public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other)noexcept;
	MyString& operator=(MyString&& other)noexcept;
	size_t length() const;
	MyString& operator+=(const MyString& other);
	bool isWordPresent(const char* word)const;
	MyString substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream&, MyString& str);
	friend std::istream& getline(std::istream& is, MyString& str);
};



std::istream& getline(std::istream& is, MyString& str);
std::ostream& operator<<(std::ostream& os, const MyString& str);
void writeMyStringToFile(const MyString& str, std::ofstream& out);
MyString readMyStringFromFile(std::ifstream& in);


bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);