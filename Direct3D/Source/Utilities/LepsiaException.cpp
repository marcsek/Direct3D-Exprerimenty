#include "LepsiaException.h"
#include <sstream>

LepsiaException::LepsiaException(int line, const char* file) noexcept
	:
	line(line), file(file)
{}

const char* LepsiaException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* LepsiaException::GetType() const noexcept
{
	return "Lepsia Exception";
}

int LepsiaException::GetLine() const noexcept
{
	return line;
}

const std::string& LepsiaException::GetFile() const noexcept
{
	return file;
}


std::string LepsiaException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << GetFile() << std::endl << "[iLine]" << GetLine();
	return oss.str();
}






