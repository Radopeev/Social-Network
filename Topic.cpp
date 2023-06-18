#include "Topic.h"

size_t Topic::topicIdentificator = readIdFromFile("topicIdentificator.txt");

Topic::Topic(const MyString& title, const MyString& author,const MyString& description) {
	setTitle(title);
	setAuthor(author);
	setDesc(description);
	id = topicIdentificator++;
}

void Topic::addPost(const MyString& title) {
	posts.pushBack(Post(title));
}
const MyString& Topic::getTitle()const {
	return title;
}
const MyString& Topic::getAuthor()const {
	return author;
}
const MyString& Topic::getDesc()const {
	return description;
}
size_t Topic::getID()const {
	return id;
}
size_t Topic::getIdentificator()const {
	return topicIdentificator;
}
Post& Topic::getCurrPost() {
	return currPost;
}
size_t Topic::getCurrPostIndex()const {
	return currPostIndex;
}
void Topic::setTitle(const MyString& title) {
	this->title = title;
}
void Topic::setAuthor(const MyString& author) {
	this->author = author;
}
void Topic::setDesc(const MyString& description) {
	this->description = description;
}
bool Topic::openPost(const char* title) {
	title++;
	for (size_t i = 0; i < posts.getSize(); i++) {
		if (strcmp(posts[i].getTitle().c_str(), title) == 0) {
			currPost = posts[i];
			currPostIndex = i;
			return true;;
		}
	}
	return false;
}
bool Topic::isUniquePost(const MyString& post)const {
	for (size_t i = 0; i < posts.getSize(); i++) {
		if (posts[i].getTitle() == post)
			return false;
	}
	return true;
}
bool Topic::openPost(size_t id) {
	for (size_t i = 0; i < posts.getSize(); i++) {
		if (posts[i].getId() == id) {
			currPost = posts[i];
			currPostIndex = i;
			return true;
		}
	}
	return false;
}
void Topic::addComment(const MyString& newComment) {
	currPost.addComments(Comment(newComment));
}
void Topic::showComments()const {
	currPost.showComments();
}
void Topic::listPost()const {
	for (size_t i = 0; i < posts.getSize(); i++) {
		std::cout << posts[i].getTitle() << "{id:" << posts[i].getId() << "}" << std::endl;
	}
	std::cout << std::endl;
}
void Topic::addReply(size_t id,SharedPointer<Comment>&& reply) {
	currPost.addReply(id,std::move(reply));
}

const MyString& Topic::getCurrPostTitle()const {
	return currPost.getTitle();
}
const Vector<Post>& Topic::getPosts()const {
	return posts;
}
void Topic::updatePost(Post&& post, size_t index) {
	posts[index] = std::move(post);
}
const Post& Topic::getSpecificPost(const Post& post) {
	for (size_t i = 0; i < posts.getSize(); i++) {
		if (posts[i].getTitle() == post.getTitle())
			return posts[i];
	}
	std::cout << "No post found" << std::endl << std::endl;
}
size_t Topic::getSpecificPostIndex(const Post& post) {
	for (size_t i = 0; i < posts.getSize(); i++) {
		if (posts[i].getTitle() == post.getTitle())
			return i;
	}
	std::cout << "No post found" << std::endl << std::endl;
}

std::ofstream& operator<<(std::ofstream& out, const Topic& topic) {
	writeMyStringToFile(topic.title, out);
	writeMyStringToFile(topic.author, out);
	writeMyStringToFile(topic.description, out);
	out.write((const char*)&topic.id, sizeof(size_t));
	writeVectorToFile(topic.posts, out);
	return out;
}
std::ifstream& operator>>(std::ifstream& in, Topic& topic) {
	topic.title=readMyStringFromFile(in);
	topic.author =readMyStringFromFile(in);
	topic.description =readMyStringFromFile(in);
	in.read((char*)&topic.id, sizeof(size_t));
	readVectorFromFile(topic.posts,in);
	return in;
}

