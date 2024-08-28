#pragma once
#include<iostream>


class Logger
{
	Logger();
public:
	static void SendError(std::string message, std::string fileName, int line);
};

