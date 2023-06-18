#pragma once
#include "UserManagement.h"
#include "TopicsManagement.h"
#include "constants.h"
#include <sstream>

class SocialNetwork
{
	UserManagement userManager;
	TopicsManagement topicManager;
	size_t currUserIndex;
	size_t currTopicIndex;
	User currUser;
	Topic currTopic;
	void printHelpInTheBeginning()const;
	void printHelpInLogin()const;
	void printHelpInPost()const;
	void printHelpInTopic()const;
	void successfullLogIn();
	void successfullOpenTopic();
	void successfullOpenPost();
	void open(const char* topicTitle);
	void open(size_t id);
	void create();
	void signUp();
	bool login();
public:
	void run();
};

