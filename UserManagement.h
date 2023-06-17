#pragma once
#include <fstream>
#include "Vector.hpp"
#include "User.h"
#include "Id.h"
#include "constants.h"
class UserManagement
{
	Vector<User> users;
public:
	UserManagement();
	void addUser(User&& newUser);
	bool logInCheck(const User& user);
	User& getSpecificUser(const User& user);
	size_t getSpecificUserIndex(const User& user);
	void updateUser(User&& user, size_t index);
	bool isUniqueUser(const User& user)const;
	~UserManagement();
};

