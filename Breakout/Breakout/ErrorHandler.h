#pragma once

#include <string>

extern "C" {
#include <stdlib.h>
}

#ifndef NDEBUG
// print error with file name and line number in debug mode - file name and line number would be written wrong(always the same value no metter where throw happened) without using macros
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: In file\n\n" + std::string(__FILE__) + "\nat line " + std::to_string((long long)(__LINE__)) + "\n\n" + x)
#else
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: " + std::string(x))
#endif
#define THROW_FAILURE(x) (throw std::string(FILE_AND_LINE_ERR_MSG(x)))