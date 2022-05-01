#include "bookmarkInterface.hpp"
#include <iostream>
#include <iterator>
#include <string>

const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";

BookmarkInterface::BookmarkInterface()
{
  marks_["current"] = book_.end();
}

void BookmarkInterface::moveMarks()
{
  if (std::next(book_.begin()) == book_.end())
  {
    for (auto i = marks_.begin(); i != marks_.end(); i++)
    {
      i->second = book_.begin();
    }
  }
}

void BookmarkInterface::add(const PhoneBook::record_t& record)
{
  book_.pushBack(record);
  moveMarks();
}

void BookmarkInterface::store(const std::string& mark, const std::string& newMark, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  marks_[newMark] = iterator->second;
}

void BookmarkInterface::insertBefore(const std::string& mark, const PhoneBook::record_t& record, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  if (iterator->second == book_.end())
  {
    add(record);
    return;
  }

  book_.insertBefore(iterator->second, record);
  moveMarks();
}

void BookmarkInterface::insertAfter(const std::string& mark, const PhoneBook::record_t& record, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  if (iterator->second == book_.end())
  {
    add(record);
    return;
  }

  if (std::next(iterator->second) == book_.end())
  {
    book_.pushBack(record);
    return;
  }

  book_.insertAfter(iterator->second, record);
  moveMarks();
}

void BookmarkInterface::deleteRecord(const std::string& mark, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  auto tmp = iterator->second;
  for (auto i = marks_.begin(); i != marks_.end(); i++)
  {
    if (i->second == tmp)
    {
      if ((i->second != std::prev(book_.end())) || (tmp == book_.begin()))
      {
        i->second++;
      }
      else
      {
        i->second--;
      }
    }
  }

  book_.remove(tmp);
}

void BookmarkInterface::show(const std::string& mark, std::ostream& out) const
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  if (book_.empty())
  {
    out << EMPTY;
    return;
  }

  out << iterator->second->phoneNumber << " " << iterator->second->name << '\n';
}

void BookmarkInterface::move(const std::string& mark, int step, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  if (step > 0)
  {
    if (std::distance(iterator->second, --book_.end()) < step)
    {
      iterator->second = --book_.end();
    }
    iterator->second = std::next(iterator->second, step);
  }
  else
  {
    if (std::distance(book_.begin(), iterator->second) < -step)
    {
      iterator->second = book_.begin();
    }
    iterator->second = std::prev(iterator->second, -step);
  }
}

void BookmarkInterface::move(const std::string& mark, BookmarkInterface::MovePosition& pos, std::ostream& out)
{
  auto iterator = marks_.find(mark);

  if (iterator == marks_.end())
  {
    out << INVALID_BOOKMARK;
    return;
  }

  if (pos == MovePosition::first)
  {
    iterator->second = book_.begin();
  }
  else if (pos == MovePosition::last)
  {
    iterator->second = --book_.end();
  }
}

bool BookmarkInterface::empty() const
{
  return book_.empty() && marks_.empty();
}
