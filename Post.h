#pragma once
#include "Comment.h"
#include "Vector.hpp"
#include "MyString.h"
#include "UtilityFunctions.h"

class Post
{
	size_t id = 0;
	MyString title;
	Vector<Comment> comments;
	static size_t postIdentificator;
public:
	Post() = default;
	Post(const MyString& title);
	size_t getId()const;
	size_t getCommentsSize()const;
	const MyString& getTitle()const;
	size_t getIdentificator()const;
	const Vector<Comment>& getComments()const;
	Vector<Comment>& getComments();

	void showComments()const;
	bool checkId(size_t id)const;
	void addComments(Comment&& newComment);
	void addReply(size_t id,SharedPointer<Comment>&& newReply);
	void addUpvoteToComment(size_t id);
	void addDownvoteToComment(size_t id);
	void removeUpvoteFromComment(size_t id);
	void removeDownvoteFromComment(size_t id);
	int searchCommentById(size_t id)const;
	void printPost()const;

	
	friend std::ofstream& operator<<(std::ofstream& out, const Post& post);
	friend std::ifstream& operator>>(std::ifstream& in, Post& post);
};

std::ofstream& operator<<(std::ofstream& out, const Post& post);
std::ifstream& operator>>(std::ifstream& in, Post& post);
