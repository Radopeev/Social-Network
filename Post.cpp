#include "Post.h"
#include "Id.h"
#include<sstream>

size_t Post::postIdentificator=readIdFromFile("postIdentificator.txt");

size_t Post::getId()const {
	return id;
}
const MyString& Post::getTitle()const {
	return title;
}
size_t Post::getCommentsSize()const {
	return comments.getSize();
}
size_t Post::getIdentificator()const {
	return postIdentificator;
}
const Vector<Comment>& Post::getComments()const {
	return comments;
}
Vector<Comment>& Post::getComments() {
	return comments;
}
void Post::showComments()const {
	for (size_t i = 0; i < comments.getSize(); i++) {
		std::cout << comments[i].getComment()<<" {id: "<<comments[i].getId()<<"}{upvote: "<<comments[i].getUpvoteCount()
			<<"}{downvote: "<< comments[i].getDownvoteCount()<<"}" << std::endl;
		comments[i].showReplies("  ");
	}
	std::cout << std::endl;
}
bool Post::checkId(size_t id)const {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id)
			return true;
		if (comments[i].getReplies().getSize() > 0) {
			for(size_t i=0;i< comments[i].getReplies().getSize();i++){
			}
		}
	}
}

Post::Post(const MyString& title) {
	this->title = title;
	id = postIdentificator++;
}
void Post::addComments(Comment&& newComment) {
	comments.pushBack(std::move(newComment));
}
void Post::addUpvoteToComment(size_t id) {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			comments[i].addUpvote();
			break;
		}
		else {
			comments[i].addUpvoteToReply(id);
		}
	}
}
void Post::addDownvoteToComment(size_t id) {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			comments[i].addDownvote();
			break;
		}
		else {
			comments[i].addDownvoteToReply(id);
		}
	}
}
void Post::removeUpvoteFromComment(size_t id) {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			comments[i].removeUpvote();
			break;
		}
		else {
			comments[i].removeUpvoteFromReply(id);
		}
	}
}
void Post::removeDownvoteFromComment(size_t id) {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			comments[i].removeDownvote();
		}
		else {
			comments[i].removeDownvoteFromReply(id);
		}
	}
}
void Post::addReply(size_t id,SharedPointer<Comment>&& newReply) {
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			comments[i].addReply(std::move(newReply));
			break;
		}
		else {
			comments[i].replyToReply(id,std::move(newReply));
		}
	}
}
int Post::searchCommentById(size_t id) const{
	for (size_t i = 0; i < comments.getSize(); i++) {
		if (comments[i].getId() == id) {
			return i;
		}
		else if(comments[i].getReplies().getSize()>0){
			int flag = comments[i].searchInReplies(id);
			if (flag == -1) {
				continue;
			}
			else
				return flag;
		}
	}
	return -1;
}
void Post::printPost()const {
	std::cout<< title << "{id " << id << "}" << std::endl;
}
std::ofstream& operator<<(std::ofstream& out, const Post& post) {
	out.write((const char*)&post.id, sizeof(post.id));
	writeMyStringToFile(post.title, out);
	writeVectorToFile(post.comments,out);
	return out;
}
std::ifstream& operator>>(std::ifstream& in, Post& post) {
	in.read((char*)&post.id, sizeof(post.id));
	post.title=readMyStringFromFile(in);
	readVectorFromFile(post.comments, in);
	return in;
}