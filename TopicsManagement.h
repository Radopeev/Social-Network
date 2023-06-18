#pragma once
#include <fstream>
#include "Vector.hpp"
#include "Topic.h"
#include "constants.h"

class TopicsManagement
{
	Vector<Topic> topics;
public:
	bool isUniqueTopic(const MyString& topic)const;
	TopicsManagement();
	Topic& openTopicByTitle(const char* topicTitle);
	Topic& openTopicById(size_t id);
	size_t getTopicIndexByTitle(const char* topicTitle);
	size_t  getTopicIndexById(size_t id);
	bool searchTopicForCheck(size_t topicForSearch)const;
	bool searchTopicForCheck(const char* topicForSearch)const;
	void updateTopic(Topic&& topic, size_t index);
	void  searchTopic(const char* topicForSearch)const;
	void addTopic(Topic&& topic);
	void printTopicById(size_t id)const;
	~TopicsManagement();
};

