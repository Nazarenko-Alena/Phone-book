#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>
#include <iostream>
#include <list>

class PhoneBook
{
public:
  struct record_t
  {
    std::string name;
    std::string phoneNumber;
  };

  using iterator = std::list<record_t>::iterator;
  using const_iterator = std::list<record_t>::const_iterator;

  iterator insertBefore(const iterator it, const record_t& record);
  iterator insertAfter(const iterator it, const record_t& record);
  void pushBack(const record_t& record);
  bool empty() const;
  iterator end();
  const_iterator end() const;
  iterator begin();
  const_iterator begin() const;
  iterator remove(iterator it);
private:
  std::list<record_t> list_;
};

#endif

