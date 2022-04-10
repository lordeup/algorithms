#pragma once
#include <string>
#include <stdexcept>

class InvalidArgumentError : public std::invalid_argument
{
public:
	InvalidArgumentError(const std::string commandName, const std::string requiredFormat);
};
