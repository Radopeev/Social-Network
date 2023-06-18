#include "SocialNetwork.h"

using namespace Commands;
using namespace Constants;

void SocialNetwork::run() {
	std::cout << "|Press 1 for help|" << std::endl;
	while (true) {
		std::cout << ">";
		char command[MAX_COMMAND_SIZE];
		std::cin >> command;
		std::cin.ignore();
		if (strcmp(command, SIGNUP) == 0) {
			signUp();
		}
		else if (strcmp(command, LOGIN) == 0) {
			login();
		}
		else if (strcmp(command, EXIT) == 0) {
			break;
		}
		else if (strcmp(command, ONE) == 0) {
			printHelpInTheBeginning();
		}
	}
}
void SocialNetwork::printHelpInTheBeginning()const{
	std::cout << "You can choose :" << std::endl;
	std::cout << ">>login - log in existing profile" << std::endl;
	std::cout << ">>signup - create new profile" << std::endl;
	std::cout << ">>exit - exit the app" << std::endl<<std::endl;
}
void SocialNetwork::printHelpInTopic()const {
	std::cout << "You can choose :" << std::endl;
	std::cout << ">>list - list all the posts in the topic" << std::endl;
	std::cout << ">>post - create new post" << std::endl;
	std::cout << ">>p_open (name or id) - to open specific post" << std::endl;
	std::cout << ">>quit - leave the topic" << std::endl << std::endl;
}
void SocialNetwork::printHelpInPost()const {
	std::cout << "You can choose :" << std::endl;
	std::cout << ">>comment - add new comment" << std::endl;
	std::cout << ">>reply -  reply specific comment" << std::endl;
	std::cout << ">>comments - see all the comments in the post" << std::endl;
	std::cout << ">>upvote - give upvote to specific comment" << std::endl;
	std::cout << ">>downvote - give downvote to specific comment" << std::endl << std::endl;
}
void SocialNetwork::printHelpInLogin()const {
	std::cout << "You can choose :" << std::endl;
	std::cout << ">>search - search for topics" << std::endl;
	std::cout << ">>create -  create new topic" << std::endl;
	std::cout << ">>comments - see all the comments in the post" << std::endl;
	std::cout << ">>open(name or id) - open specific topic" << std::endl;
	std::cout << ">>whoami - see your information" << std::endl;
	std::cout << ">>logout - logout" << std::endl<<std::endl;
}
void SocialNetwork::successfullOpenTopic() {
	while (true) {
		std::cout << ">";
		char buffer[MAX_COMMAND_SIZE], command[MAX_COMMAND_SIZE];
		std::cin.getline(buffer, MAX_COMMAND_SIZE);
		std::stringstream ss(buffer);
		ss >> command;
		if (strcmp(command, LIST) == 0) {
			currTopic.listPost();
		}
		else if (strcmp(command, POST) == 0) {
			std::cout << "Enter your question: ";
			char buffer[MAX_COMMAND_SIZE];
			std::cin.getline(buffer, MAX_COMMAND_SIZE);
			if (!currTopic.isUniquePost(buffer)) {
				std::cout << "This question alredy exits" << std::endl << std::endl;
				continue;
			}
			currTopic.addPost(buffer);
			std::cout << ">Success!" << std::endl <<std::endl;
		}
		else if (strcmp(command, P_OPEN) == 0) {
			char openType[MAX_ID_SIZE];
			ss.getline( openType,MAX_ID_SIZE);
			if (isStringNumber(openType)) {
				if (currTopic.openPost(stringToSize_t(openType))) {
					std::cout << "Q: " << currTopic.getCurrPostTitle() << std::endl << std::endl;
					successfullOpenPost();
				}
				else
					std::cout << "No post found" << std::endl << std::endl;
			}
			else {
				if (currTopic.openPost(openType)) {
					std::cout << "Q: " << currTopic.getCurrPostTitle() << std::endl << std::endl;
					successfullOpenPost();
				}
				else
					std::cout << "No post found" << std::endl << std::endl;
			}
		}
		else if (strcmp(command, QUIT) == 0) {
			std::cout << ">You just left topic , " << "\"" << currTopic.getTitle() << "\"!" << std::endl << std::endl;
			topicManager.updateTopic(std::move(currTopic), currTopicIndex);
			break;
		}
		else if (strcmp(command, ONE) == 0) {
			printHelpInTopic();
		}
	}
}
void SocialNetwork::successfullOpenPost() {
	while (true) {
		std::cout << ">";
		char buffer[MAX_COMMAND_SIZE], command[MAX_ID_SIZE];
		std::cin.getline(buffer, MAX_COMMAND_SIZE);
		std::stringstream ss(buffer);
		ss >> command;
 		if (strcmp(command, COMMENT) == 0) {
			std::cout << ">Say something: ";
			char buffer[MAX_COMMAND_SIZE];
			std::cin.getline(buffer, MAX_COMMAND_SIZE);
			currTopic.addComment(buffer);
			currUser.addPoints();
			std::cout << ">Posted" << std::endl << std::endl;
		}
		else if (strcmp(command, COMMENTS) == 0) {
			currTopic.showComments();
		}
		else if (strcmp(command, REPLY) == 0) {
			char idFromTheConsole[MAX_ID_SIZE];
			ss >> idFromTheConsole;
			size_t id = stringToSize_t(idFromTheConsole);
			int doesIdExits=currTopic.getCurrPost().searchCommentById(id);
			if (doesIdExits != -1) {
				std::cout << "Say something: ";
				char newBuffer[MAX_COMMAND_SIZE];
				std::cin.getline(newBuffer, MAX_COMMAND_SIZE);
				SharedPointer<Comment> newComment(new Comment(newBuffer));
				currTopic.addReply(id, std::move(newComment));
				std::cout << "Posted" << std::endl << std::endl;
				currUser.addPoints();
			}
			else 
				std::cout << "There is no comment with that id" << std::endl << std::endl;
		}
		else if (strcmp(command, UPVOTE) == 0) {
			char idFromTheConsole[MAX_ID_SIZE];
			ss >> idFromTheConsole;
			size_t id = stringToSize_t(idFromTheConsole);
			int doesIdExits = currTopic.getCurrPost().searchCommentById(id);
			if (doesIdExits != -1) {
				if (!currUser.hasUserUpvotedCurrComment(id)) {
					currTopic.getCurrPost().addUpvoteToComment(id);
					currUser.addUpvotedCommentId(id);
				}
				else {
					currTopic.getCurrPost().removeUpvoteFromComment(id);
					currUser.removeUpvotedCommentId(id);
				}
			}
			else
				std::cout << "There is no comment with that id" << std::endl << std::endl;
		}
		else if (strcmp(command, DOWNVOTE) == 0) {
			char idFromTheConsole[MAX_ID_SIZE];
			ss >> idFromTheConsole;
			size_t id = stringToSize_t(idFromTheConsole);
			int doesIdExits = currTopic.getCurrPost().searchCommentById(id);
			if (doesIdExits != -1) {
				if (!currUser.hasUserDownvotedCurrComment(id)) {
					currTopic.getCurrPost().addDownvoteToComment(id);
					currUser.addDownvotedCommentId(id);
				}
				else {
					currTopic.getCurrPost().removeDownvoteFromComment(id);
					currUser.removeDownvotedCommentId(id);
				}
			}
			else
				std::cout << "There is no comment with that id" << std::endl << std::endl;
		}
		else if (strcmp(command, P_CLOSE) == 0) {
			std::cout << "You just left , " << "\"" << currTopic.getCurrPost().getTitle() << "\"" << std::endl << std::endl;
			currTopic.updatePost(std::move(currTopic.getCurrPost()), currTopic.getCurrPostIndex());
			break;
		}
		else if (strcmp(command, ONE) == 0) {
			printHelpInPost();
		}
	}
}
void SocialNetwork::successfullLogIn() {
	while (true) {
		std::cout << ">";
		char buffer[MAX_COMMAND_SIZE],command[MAX_ID_SIZE];
		std::cin.getline(buffer, MAX_COMMAND_SIZE);
		std::stringstream ss(buffer);
		ss >> command;
		if (strcmp(command, SEARCH) == 0) {
			char topicTitle[MAX_ID_SIZE];
			ss.getline(topicTitle, MAX_ID_SIZE);
			topicManager.searchTopic(topicTitle);
		}
		else if (strcmp(command, CREATE) == 0) {
			create();
		}
		else if (strcmp(command, OPEN) == 0) {
			char openType[MAX_COMMAND_SIZE];
			ss.getline(openType, MAX_COMMAND_SIZE);
			if (isStringNumber(openType)) {
				open(stringToSize_t(openType));
			}
			else {
				open(openType);
			}
		}
		else if (strcmp(command, WHOAMI) == 0) {
			std::cout << currUser.getFirstName() << " " << currUser.getLastName() << ", having " << currUser.getPoints() << " points." << std::endl << std::endl;
		}
		else if (strcmp(command, LOGOUT) == 0) {
			std::cout << "Goodbye, " << currUser.getFirstName() << " " << currUser.getLastName() << std::endl << std::endl;
			userManager.updateUser(std::move(currUser), currUserIndex);
			break;
		}
		else if (strcmp(command, ABOUT) == 0) {
			char idFromTheConsole[MAX_ID_SIZE];
			ss >> idFromTheConsole;
			size_t id = stringToSize_t(idFromTheConsole);
			topicManager.printTopicById(id);
		}
		else if (strcmp(command, ONE) == 0) {
			printHelpInLogin();
		}
	}
}

void SocialNetwork::signUp() {
	MyString firstName, lastName, password;
	std::cout << ">Enter your first name: ";
	std::cin >> firstName;
	std::cout << ">Enter last name: ";
	std::cin >> lastName;
	std::cout << ">Enter password: ";
	std::cin >> password;
	User userForCheck(firstName, lastName, password);
	if (!userManager.isUniqueUser(userForCheck)) {
		std::cout << "This user already exits!" << std::endl << std::endl;
		return;
	}
	userManager.addUser(std::move(userForCheck));
	std::cout << "Success!" << std::endl<<std::endl;
}
bool SocialNetwork::login(){
	MyString name, password;
	std::cout << "name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	std::cin.ignore();
	User userForCheck(name, password);
	if (userManager.logInCheck(userForCheck)) {
		currUserIndex = userManager.getSpecificUserIndex(userForCheck);
		currUser = std::move(userManager.getSpecificUser(userForCheck));
		std::cout << "Welcome back, " << currUser.getFirstName() << " " << currUser.getLastName() << "! " << std::endl << std::endl;
		successfullLogIn();
		return true;
	}
	else {
		std::cout << "No user found! You can try again. " << std::endl<<std::endl;
		return false;
	}
}

void SocialNetwork::open(const char* topicTitle) {
	if (topicManager.searchTopicForCheck(topicTitle)) {
		currTopicIndex = topicManager.getTopicIndexByTitle(topicTitle);
		currTopic = std::move(topicManager.openTopicByTitle(topicTitle));
		std::cout << "Welcome to " << currTopic.getTitle() << std::endl << std::endl;
		successfullOpenTopic();
	}
	else {
		std::cout << "No topic found" << std::endl << std::endl;
	}
}
void SocialNetwork::open(size_t id){
	if (topicManager.searchTopicForCheck(id)) {
		currTopic = std::move(topicManager.openTopicById(id));
		currTopicIndex = topicManager.getTopicIndexById(id);
		std::cout << "Welcome to " << currTopic.getTitle() << std::endl << std::endl;
		successfullOpenTopic();
	}
	else {
		std::cout << "No topic found" << std::endl << std::endl;
	}
}
void SocialNetwork::create() {
	MyString topicTitle, topicDesc;
	std::cout << ">Enter topic title: ";
	getline(std::cin, topicTitle);
	std::cout << ">Enter topic description: ";
	getline(std::cin,topicDesc);
	if (!topicManager.isUniqueTopic(topicTitle)) {
		std::cout << "Topic with this title already exists" << std::endl << std::endl;
	}
	else {
		topicManager.addTopic(Topic(topicTitle, currUser.getFirstName(), topicDesc));
		std::cout << "Success!" << std::endl << std::endl;
	}
}
