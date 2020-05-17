#pragma once

#include <string>

std::string GetFileContent(const std::string& fileName);
void WriteContentIntoFile(const std::string& fileName, const std::string& result);