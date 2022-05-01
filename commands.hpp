#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iostream>
#include "bookmarkInterface.hpp"
#include "phoneBook.hpp"

namespace command
{
  void add(BookmarkInterface& phoneBook, std::ostream&, const PhoneBook::record_t& record);
  void store(BookmarkInterface& phoneBook, std::ostream& out, std::string& mark, std::string& newMark);
  void insertAfter(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, const PhoneBook::record_t& record);
  void insertBefore(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, const PhoneBook::record_t& record);
  void remove(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark);
  void show(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark);
  void invalidCommand(BookmarkInterface&, std::ostream& out);
  void invalidStep(BookmarkInterface&, std::ostream& out);
  void moveBySteps(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, int step);
  void moveToPos(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, BookmarkInterface::MovePosition& pos);
}

#endif
