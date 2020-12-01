#include "FileManager.h"
#include <sstream>
#include <fstream>


std::string FileManager::readFile(std::string pFileName)
{
	std::ifstream t(pFileName);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
