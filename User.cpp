#include "User.h"
#include <fstream>
size_t User::userIdentidicator = readIdFromFile("userIdentificator.txt");

User::User(const MyString& firstName, const MyString& lastName, const MyString& password){
	setFirstName(firstName);
	setLastName(lastName);
	setPassword(password);
	id=userIdentidicator++;
	setAllElementsToZero(upvotedComments);
	setAllElementsToZero(downvotedComments);
}

User::User(const MyString& name, const MyString& password) {
	setFirstName(name);
	setPassword(password);
}

void User::setFirstName(const MyString& firstName) {
	this->firstName = firstName;
}
void User::setLastName(const MyString& lastName) {
	this->lastName = lastName;
}
void User::setPassword(const MyString& password) {
	this->password = password;
}
void User::addPoints() {
	points++;

}
bool User::hasUserUpvotedCurrComment(size_t id) {
	return binarySearch(upvotedComments, id);
}
bool User::hasUserDownvotedCurrComment(size_t id) {
	return binarySearch(downvotedComments, id);
}
void User::addUpvotedCommentId(size_t id) {
	upvotedComments.pushBack(id);
}
void User::removeUpvotedCommentId(size_t id) {
	for (size_t i = 0; i < upvotedComments.getSize(); i++) {
		if (upvotedComments[i] == id) {
			upvotedComments.popAt(i);
			return;
		}
	}
}
void User::addDownvotedCommentId(size_t id) {
	downvotedComments.pushBack(id);
}
void User::removeDownvotedCommentId(size_t id) {
	for (size_t i = 0; i < upvotedComments.getSize(); i++) {
		if (downvotedComments[i] == id) {
			downvotedComments.popAt(i); 
			return;
		}
	}
}
const MyString& User::getFirstName()const {
	return firstName;
}
const MyString& User::getLastName()const {
	return lastName;
}

size_t User::getId()const {
	return id;
}

size_t User::getPoints()const {
	return points;
}

size_t User:: getIdentificator()const {
	return userIdentidicator;
}
std::ifstream& operator>>(std::ifstream& in, User& user){
	user.firstName = readMyStringFromFile(in);
	user.lastName = readMyStringFromFile(in);
	user.password = readMyStringFromFile(in);
	in.read((char*)&user.id, sizeof(size_t));
	in.read((char*)&user.points, sizeof(size_t));
	readVectorFromFile(user.upvotedComments,in);
	readVectorFromFile(user.downvotedComments, in);
	return in;
}
std::ofstream& operator<<(std::ofstream& out, const User& user) {
	writeMyStringToFile(user.firstName, out);
	writeMyStringToFile(user.lastName, out);
	writeMyStringToFile(user.password, out);
	out.write((const char*)&user.id, sizeof(size_t));
	out.write((const char*)&user.points, sizeof(size_t));
	writeVectorToFile(user.upvotedComments, out);
	writeVectorToFile(user.downvotedComments, out);
	return out;
}
bool operator==(const User& lhs, const User& rhs) {
	return ((lhs.firstName == rhs.firstName) && (lhs.password == rhs.password));
}