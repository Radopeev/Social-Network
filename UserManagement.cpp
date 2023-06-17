#include "UserManagement.h"

UserManagement::UserManagement() {
	std::ifstream in(FileNames::usersBinaryFile, std::ios::in | std::ios::binary);
	readVectorFromFile(users,in);
	in.close();
}
bool UserManagement::isUniqueUser(const User& user)const {
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i] == user)
			return false;
	}
	return true;
}
void UserManagement::addUser(User&& newUser) {
	if (isUniqueUser(newUser))
		users.pushBack(std::move(newUser));
	else
		std::cout << "This user alredy exist " << std::endl << std::endl;
}
bool UserManagement::logInCheck(const User& user) {
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]==user)
			return true;
	}
	return false;
}
User& UserManagement::getSpecificUser(const User& user) {
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i] == user)
			return users[i];
	}
	std::cout << "No user found" << std::endl << std::endl;
}
size_t UserManagement::getSpecificUserIndex(const User& user) {
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i] == user)
			return i;
	}
	std::cout << "No user found" << std::endl << std::endl;
}
void UserManagement::updateUser(User&& user,size_t index) {
	users[index] = std::move(user);
}
UserManagement::~UserManagement(){
	std::ofstream out(FileNames::usersBinaryFile, std::ios::out | std::ios::binary);
	writeIdToFile(FileNames::usersIdentificatorFileName, users[0].getIdentificator());
	writeVectorToFile(users,out);
	out.close();
}
