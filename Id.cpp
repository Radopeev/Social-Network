#include "Id.h"


size_t readIdFromFile(const char* fileName) {
	size_t id;
	std::ifstream in(fileName);
	in >> id;
	in.close();
	return id;
}
void writeIdToFile(const char* fileName, size_t id) {
	std::ofstream out(fileName);
	out << id;
	out.close();
}