#include "InvalidArgumentError.h"

InvalidArgumentError::InvalidArgumentError(const std::string commandName, const std::string requiredFormat)
	: std::invalid_argument("Invalid argument. Need: " + commandName + " " + requiredFormat)
{
}
