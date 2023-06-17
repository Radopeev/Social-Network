#pragma once
#include "MyString.h"
#include "UtilityFunctions.h"
#include "Id.h"

class User
{
private:
	MyString firstName;
	MyString lastName;
	MyString password;
	size_t id;
	size_t points=0;
	Vector<size_t> upvotedComments;
	Vector<size_t> downvotedComments;

	static size_t userIdentidicator;
public:
	User() = default;
	User(const MyString& firstName, const MyString& lastName, const MyString& password);
	User(const MyString& name, const MyString& password);

	const MyString& getFirstName()const;
	const MyString& getLastName()const;
	size_t getId()const;
	size_t getPoints()const;
	size_t getIdentificator()const;
	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& firstName);
	void setPassword(const MyString& firstName);
	void setId();
	void addPoints();
	bool hasUserUpvotedCurrComment(size_t id);
	bool hasUserDownvotedCurrComment(size_t id);
	void addUpvotedCommentId(size_t id);
	void removeUpvotedCommentId(size_t id);
	void addDownvotedCommentId(size_t id);
	void removeDownvotedCommentId(size_t id);
	friend std::ifstream& operator>>(std::ifstream& in,User& user);
	friend std::ofstream& operator<<(std::ofstream& out, const User& user);
	friend bool operator==(const User& lhs, const User& rhs);
};
bool operator==(const User& lhs, const User& rhs);
std::ifstream& operator>>(std::ifstream& in, User& user);
std::ofstream& operator<<(std::ofstream& out, const User& user);