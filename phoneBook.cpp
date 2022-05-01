#include "phoneBook.hpp"

PhoneBook::iterator PhoneBook::insertBefore(const PhoneBook::iterator it, const PhoneBook::record_t& record)
{
  return list_.insert(it, record);
}

PhoneBook::iterator PhoneBook::insertAfter(const PhoneBook::iterator it, const PhoneBook::record_t& record)
{
  return list_.insert(std::next(it), record);
}

void PhoneBook::pushBack(const record_t& record)
{
  list_.push_back(record);
}

bool PhoneBook::empty() const
{
  return list_.empty();
}

PhoneBook::iterator PhoneBook::end()
{
  return list_.end();
}

PhoneBook::const_iterator PhoneBook::end() const
{
  return list_.end();
}

PhoneBook::iterator PhoneBook::begin()
{
  return list_.begin();
}

PhoneBook::const_iterator PhoneBook::begin() const
{
  return list_.begin();
}

PhoneBook::iterator PhoneBook::remove(PhoneBook::iterator it)
{
  return list_.erase(it);
}
