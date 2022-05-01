#include "commands.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include "bookmarkInterface.hpp"

void command::add(BookmarkInterface& phoneBook, std::ostream&, const PhoneBook::record_t& record)
{
  phoneBook.add(record);
}

void command::store(BookmarkInterface& phoneBook, std::ostream& out, std::string& mark, std::string& newMark)
{
  phoneBook.store(mark, newMark, out);
}

void command::insertAfter(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, const PhoneBook::record_t& record)
{
  phoneBook.insertAfter(mark, record, out);
}

void command::insertBefore(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, const PhoneBook::record_t& record)
{
  phoneBook.insertBefore(mark, record, out);
}

void command::remove(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark)
{
  if (phoneBook.empty())
  {
    throw std::runtime_error("The phonebook is empty");
  }
  phoneBook.deleteRecord(mark, out);
}

void command::show(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark)
{
  phoneBook.show(mark, out);
}

void command::invalidCommand(BookmarkInterface&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void command::invalidStep(BookmarkInterface&, std::ostream& out)
{
  out << "<INVALID STEP>\n";
}

void command::moveBySteps(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, int step)
{
  phoneBook.move(mark, step, out);
}

void command::moveToPos(BookmarkInterface& phoneBook, std::ostream& out, const std::string& mark, BookmarkInterface::MovePosition& pos)
{
  phoneBook.move(mark, pos, out);
}

