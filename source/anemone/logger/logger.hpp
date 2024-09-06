#pragma once
#include <vector>
#include <string>

enum LogType
{
	LOG_INFO,
	LOG_ERROR,
	LOG_WARNING
};

struct LogEntry
{
	LogType type;
	std::string message;
};

class Logger
{
public:
	static void Log(const std::string& message);
	static void Err(const std::string& message);
	static std::vector<LogEntry> mMessages;
};