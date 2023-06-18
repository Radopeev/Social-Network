#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include<fstream>
#include <memory>
#include "UtilityFunctions.h"
#include "SharedPointer.hpp"
#include"constants.h"

class Comment{
	size_t id = 0;
	MyString comment;
	Vector<SharedPointer<Comment>> replies;
	size_t upvoteCount = 0;
	size_t downvoteCount = 0;
	static size_t commentIdentificator;

	void readRepliesFromFile(std::ifstream& in);
	void writeRepliesToFile(std::ofstream& out)const;
public:
	Comment() = default;
	Comment(const MyString& comment);
	const MyString& getComment()const;
	size_t getId()const;
	size_t getIdentificator()const;
	size_t getUpvoteCount()const;
	size_t getDownvoteCount()const;

	void addUpvote();
	void addDownvote();
	void removeUpvote();
	void removeDownvote();
	void addUpvoteToReply(size_t id);
	void addDownvoteToReply(size_t id);
	void removeUpvoteFromReply(size_t id);
	void removeDownvoteFromReply(size_t id);

	int searchInReplies(size_t id)const;
	void replyToReply(size_t id, SharedPointer<Comment>&& reply);
	void showReplies(const MyString& offset)const;
	const Vector<SharedPointer<Comment>>& getReplies()const;
	void addReply(SharedPointer<Comment>&& reply);

	friend std::ofstream& operator<<(std::ofstream& out, const Comment& comment);
	friend std::ifstream& operator>>(std::ifstream& in,Comment& comment);
};
std::ofstream& operator<<(std::ofstream& out, const Comment& comment);
std::ifstream& operator>>(std::ifstream& in, Comment& comment);