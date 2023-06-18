#include "Comment.h"
#include "Id.h"

size_t Comment::commentIdentificator=readIdFromFile(FileNames::commentIdentificatorFileName);

Comment::Comment(const MyString& comment) {
	this->comment = comment;
	id = commentIdentificator++;
}
size_t Comment::getId()const {
	return id;
}
const MyString& Comment::getComment()const {
	return comment;
}
size_t Comment::getIdentificator()const{
	return commentIdentificator;
}
void Comment::replyToReply(size_t id,SharedPointer<Comment>&& newReply) {
	for (int i = 0; i < replies.getSize(); i++) {
		if (replies[i]->getId() == id) {
			replies[i]->addReply(std::move(newReply));
			break;
		}
		else 
			replies[i]->replyToReply(id, std::move(newReply));
	}
}
int Comment::searchInReplies(size_t id)const{
	for (int i = 0; i < replies.getSize(); i++) {
		if (replies[i]->getId() == id)
			return i;
		replies[i]->searchInReplies(id);;
	}
}
void Comment::addUpvoteToReply(size_t id) {
	for (size_t i = 0; i < replies.getSize(); i++) {
		if (replies[i]->id == id) {
			replies[i]->upvoteCount++;
			break;
		}
		else {
			replies[i]->addUpvoteToReply(id);
		}
	}
}
void Comment::addDownvoteToReply(size_t id) {
	for (size_t i = 0; i < replies.getSize(); i++) {
		if (replies[i]->id == id) {
			replies[i]->downvoteCount++;
			break;
		}
		else {
			replies[i]->addDownvoteToReply(id);
		}
	}
}
void Comment::removeUpvoteFromReply(size_t id) {
	for (size_t i = 0; i < replies.getSize(); i++) {
		if (replies[i]->id == id) {
			replies[i]->upvoteCount--;
			break;
		}
		else {
			replies[i]->removeUpvoteFromReply(id);
		}
	}
}
void Comment::removeDownvoteFromReply(size_t id) {
	for (size_t i = 0; i < replies.getSize(); i++) {
		if (replies[i]->id == id) {
			replies[i]->downvoteCount--;
			break;
		}
		else {
			replies[i]->removeDownvoteFromReply(id);
		}
	}
}
const Vector<SharedPointer<Comment>>& Comment::getReplies()const {
	return replies;
}
void Comment::addReply(SharedPointer<Comment>&& reply) {
	replies.pushBack(std::move(reply));
}
size_t Comment::getUpvoteCount()const {
	return upvoteCount;
}
size_t Comment::getDownvoteCount()const {
	return downvoteCount;
}
void Comment::showReplies(const MyString& offset)const {
	for (int i = 0; i < replies.getSize(); i++) {
		std::cout << offset << " >>" << replies[i]->comment << " {id: " << replies[i]->id << "}{upvote: " << replies[i]->upvoteCount
			<< "}{downvote: " << replies[i]->downvoteCount<<"}" << std::endl;
		replies[i].operator->()->showReplies(offset+"  ");
	} 
}
void Comment::addUpvote() {
	upvoteCount++;
}
void Comment::addDownvote() {
	downvoteCount++;
}
void Comment::removeUpvote() {
	upvoteCount--;
}
void Comment::removeDownvote() {
	downvoteCount--;
}
void Comment::readRepliesFromFile(std::ifstream& in) {
	if (in) {
		size_t size = 0;
		in.read((char*)(&size), sizeof(size_t));
		replies.reserve(size);
		for (int i = 0; i < size; i++) {
			replies[i] = new Comment;
			in>>*(replies[i]);
		}
	}
}
void Comment::writeRepliesToFile( std::ofstream& out)const {
	if (out) {
		size_t size = replies.getSize();
		out.write((const char*)&size, sizeof(size_t));
		for (int i = 0; i < size; i++) {
			out<< *(replies[i]);
		}
	}
}
std::ofstream& operator<<(std::ofstream& out, const Comment& comment) {
	out.write((const char*)&comment.id, sizeof(size_t));
	writeMyStringToFile(comment.comment, out);
	comment.writeRepliesToFile(out);
	out.write((const char*)&comment.upvoteCount, sizeof(size_t));
	out.write((const char*)&comment.downvoteCount, sizeof(size_t));
	return out;
}
std::ifstream& operator>>(std::ifstream& in,Comment& comment) {
	in.read((char*)&comment.id, sizeof(size_t));
	comment.comment = readMyStringFromFile(in);
	comment.readRepliesFromFile(in);
	in.read((char*)&comment.upvoteCount, sizeof(size_t));
	in.read((char*)&comment.downvoteCount, sizeof(size_t));
	return in;
}