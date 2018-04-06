#include "Logger.h"

// Default value for file is "log.log"
Logger::Logger(string file)
{
	log_file.open(file + ".log");
}

Logger::~Logger()
{
	log_file.close();
}

void Logger::log(string message)
{
	cout << message << endl;
	this->log_file << message << endl;
}