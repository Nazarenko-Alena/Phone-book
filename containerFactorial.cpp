#include "containerFactorial.hpp"
#include <iterator>
#include <stdexcept>
#include <climits>

ContainerFactorial::IteratorFactorial::IteratorFactorial(const unsigned long long index, const value_type val) :
  index_(index),
  value_(val)
{
  if (index_ > maxCount_)
  {
    throw std::out_of_range("Incorrect index");
  }
}

ContainerFactorial::IteratorFactorial::value_type ContainerFactorial::IteratorFactorial::operator*()
{
  return value_;
}

ContainerFactorial::IteratorFactorial& ContainerFactorial::IteratorFactorial::operator++()
{
  if (index_ == maxCount_)
  {
    throw std::out_of_range("Index became invalid");
  }

  ++index_;
  value_ *= index_;
  return *this;
}

ContainerFactorial::IteratorFactorial& ContainerFactorial::IteratorFactorial::operator--()
{
  if (index_ == 0)
  {
    throw std::out_of_range("Index became invalid");
  }

  value_ /= index_;
  --index_;
  return *this;
}

ContainerFactorial::IteratorFactorial ContainerFactorial::IteratorFactorial::operator++(int)
{
  IteratorFactorial tmp = *this;
  ++(*this);
  return tmp;
}

ContainerFactorial::IteratorFactorial ContainerFactorial::IteratorFactorial::operator--(int)
{
  IteratorFactorial tmp = *this;
  --(*this);
  return tmp;
}

bool ContainerFactorial::IteratorFactorial::operator==(const ContainerFactorial::IteratorFactorial& other) const
{
  return (index_ == other.index_);
}

bool ContainerFactorial::IteratorFactorial::operator!=(const ContainerFactorial::IteratorFactorial& other) const
{
  return !(*this == other);
}

unsigned long long calculateFactorial(unsigned long long index)
{
  if (index > 1)
  {
    unsigned long long value = 2;

    for (unsigned long long i = 3; i <= index; i++)
    {
      if (value > (ULLONG_MAX / i))
      {
        throw std::overflow_error("Type overflow occurred");
      }

      value *= i;
    }

    return value;
  }
  else
  {
    return 1;
  }
}

ContainerFactorial::ContainerFactorial(const unsigned long long max_index) :
  maxIndex_(max_index)
{
  maxValue_ = calculateFactorial(max_index + 1);
}

ContainerFactorial::const_iterator ContainerFactorial::begin() const
{
  return IteratorFactorial(1, 1);
}

ContainerFactorial::const_iterator ContainerFactorial::end() const
{
  return IteratorFactorial(maxIndex_ + 1, maxValue_);
}

ContainerFactorial::const_reverse_iterator ContainerFactorial::rbegin() const
{
  return std::make_reverse_iterator(end());
}

ContainerFactorial::const_reverse_iterator ContainerFactorial::rend() const
{
  return std::make_reverse_iterator(begin());
}
