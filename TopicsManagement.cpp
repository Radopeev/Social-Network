#include "TopicsManagement.h"

TopicsManagement::TopicsManagement() {
	std::ifstream in(FileNames::topicsBinaryFile,std::ios::in | std::ios::binary);
	readVectorFromFile(topics, in);
	in.close();
}
bool TopicsManagement::isUniqueTopic(const MyString& topic)const {
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (topics[i].getTitle() == topic)
			return false;
	}
	return true;
}
Topic& TopicsManagement::openTopicByTitle(const char* topicTitle) {
	topicTitle++;
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (strcmp(topics[i].getTitle().c_str(),topicTitle) == 0) {
			return topics[i];
		}
	}
	std::cout << "No topic found" << std::endl << std::endl;
}
Topic& TopicsManagement::openTopicById(size_t id) {
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (topics[i].getID()==id ) {
			return topics[i];
		}
	}
	std::cout << "No topic found" << std::endl << std::endl;
}
size_t TopicsManagement::getTopicIndexByTitle(const char* topicTitle) {
	topicTitle++;
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (strcmp(topics[i].getTitle().c_str(), topicTitle) == 0) {
			return i;
		}
	}
}
size_t  TopicsManagement::getTopicIndexById(size_t id) {
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (topics[i].getID() == id) {
			return i;
		}
	}
}
void TopicsManagement::updateTopic(Topic&& topic, size_t index) {
	topics[index] = std::move(topic);
}
void TopicsManagement::searchTopic(const char* topicForSearch)const {
	topicForSearch++;
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (strcmp(topics[i].getTitle().c_str(), topicForSearch) == 0){
			std::cout << " >>" << topics[i].getTitle() << "{id:" << topics[i].getID() << "}" << std::endl;
		}
		else if (topics[i].getTitle().isWordPresent(topicForSearch)) {
			std::cout << " >>" << topics[i].getTitle()<<"{id:"<<topics[i].getID()<<"}" << std::endl;
		}
	}
	std::cout << std::endl;
}

bool TopicsManagement::searchTopicForCheck(const char* topicForSearch)const {
	topicForSearch++;
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (strcmp(topics[i].getTitle().c_str(), topicForSearch) == 0) {
			return true;
		}
	}
	return false;
}

bool TopicsManagement::searchTopicForCheck(size_t topicForSearch)const {
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (topics[i].getID() == topicForSearch) {
			return true;
		}
	}
	return false;
}

void TopicsManagement::printTopicById(size_t id)const{
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (topics[i].getID() == id) {
			std::cout << " >> Name: " << topics[i].getTitle() << std::endl;
			std::cout << " >> Description: " << topics[i].getDesc() << std::endl;
			std::cout << " >> Created: " << topics[i].getAuthor() << std::endl;
			std::cout << " >> Questions asked: " << topics[i].getPosts().getSize() << std::endl << std::endl;
			break;
		}
	}
}
void TopicsManagement::addTopic(Topic&& topic) {
	topics.pushBack(std::move(topic));
}

TopicsManagement::~TopicsManagement() {
	std::ofstream out(FileNames::topicsBinaryFile,std::ios::out | std::ios::binary);
	writeIdToFile(FileNames::topicsIdetificatorFileName, topics[0].getIdentificator());
	writeIdToFile(FileNames::postIdentificatorFileName, topics[0].getPosts()[0].getIdentificator());
	writeIdToFile(FileNames::commentIdentificatorFileName, topics[0].getPosts()[0].getComments()[0].getIdentificator());
	writeVectorToFile(topics, out);
	out.close();
}