#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "Post.h"
#include "UtilityFunctions.h"
#include "Id.h"


class Topic
{
	size_t id = 0;
	size_t currPostIndex=0;
	MyString title;
	MyString author;
	MyString description;
	Vector<Post> posts;
	Post currPost;
	static size_t topicIdentificator;

public:
	Topic() = default;
	Topic(const MyString& title, const MyString& author, const MyString& descrption);
	const MyString& getTitle()const;
	const MyString& getAuthor()const;
	const MyString& getDesc()const;
	size_t getID()const;
	size_t getIdentificator()const;
	Post& getCurrPost();
	size_t getCurrPostIndex()const;

	bool isUniquePost(const MyString& post)const;
	void updatePost(Post&& post, size_t index);
	void setTitle(const MyString& title);
	void setAuthor(const MyString& author);
	void setDesc(const MyString& description);
	void addPost(const MyString& title);
	bool openPost(const char* title);
	bool openPost(size_t id);
	void addComment(const MyString& newComment);
	void showComments()const;
	void listPost()const;
	void addReply(size_t id,SharedPointer<Comment>&& reply);

	const MyString& getCurrPostTitle()const;
	const Vector<Post>& getPosts()const;
	friend std::ofstream& operator<<(std::ofstream& out, const Topic& topic);
	friend std::ifstream& operator>>(std::ifstream& in, Topic& topic);

	const Post& getSpecificPost(const Post& post);
	size_t getSpecificPostIndex(const Post& post);
};

std::ofstream& operator<<(std::ofstream& out, const Topic& topic);
std::ifstream& operator>>(std::ifstream& in, Topic& topic);