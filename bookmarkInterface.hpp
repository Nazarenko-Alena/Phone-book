#ifndef BOOKMARK_INTERFACE_HPP
#define BOOKMARK_INTERFACE_HPP

#include <map>
#include "phoneBook.hpp"

class BookmarkInterface
{
public:

  enum class MovePosition
  {
    first,
    last
  };

  BookmarkInterface();
  void moveMarks();
  void add(const PhoneBook::record_t& record);
  void store(const std::string& mark, const std::string& newMark, std::ostream& out);
  void insertBefore(const std::string& mark, const PhoneBook::record_t& record, std::ostream& out);
  void insertAfter(const std::string& mark, const PhoneBook::record_t& record, std::ostream& out);
  void deleteRecord(const std::string& mark, std::ostream& out);
  void show(const std::string& mark, std::ostream& out) const;
  void move(const std::string& mark, int step, std::ostream& out);
  void move(const std::string& mark, MovePosition& pos, std::ostream& out);
  bool empty() const;
private:
  PhoneBook book_;
  std::map<std::string, PhoneBook::iterator> marks_;
};

#endif
