#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include "bookmarkInterface.hpp"

using CommandFunction = std::function<void(BookmarkInterface&, std::ostream&)>;

bool readNumber(std::stringstream& in, std::string& str);
bool readName(std::stringstream& in, std::string& str);
bool readMark(std::stringstream& in, std::string& str);
CommandFunction parse(std::stringstream& stream);
CommandFunction parseAdd(std::stringstream& stream);
CommandFunction parseStore(std::stringstream& stream);
CommandFunction parseInsert(std::stringstream& stream);
CommandFunction parseDelete(std::stringstream& stream);
CommandFunction parseShow(std::stringstream& stream);
CommandFunction parseMove(std::stringstream& stream);

#endif
