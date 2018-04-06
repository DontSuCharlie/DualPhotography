#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
Outputs messages to both the console and a log file.

## Example
```
#include "logger.h"
Logger debug;
debug.log("Hello World!"); // prints to both console and debugging.log in the directory the program runs in
```

*/
class Logger
{
public:
	// Don't include the file extension. For example, if you want "debugging.log", just put in "debugging" as the argument
	Logger(string file="debugging");
	~Logger();
	// Appends a newline to your messages by default
	void log(string message);
private:
	ofstream log_file;
};