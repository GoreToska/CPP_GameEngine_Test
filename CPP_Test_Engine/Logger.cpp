#include "Logger.h"
#include "Typography.hpp"


void Logger::SendError(std::string message,std::string fileName, int line)
{
	std::cout << red << message <<reset<<" | At file: " << fileName << " | Line: " << line << "\n";
}
