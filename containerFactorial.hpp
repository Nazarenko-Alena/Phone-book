#ifndef CONTAINER_FACTORIAL_HPP
#define CONTAINER_FACTORIAL_HPP

#include <iterator>

class ContainerFactorial
{
public:

  class IteratorFactorial : public std::iterator<std::bidirectional_iterator_tag, unsigned long long, std::ptrdiff_t,
    const unsigned long long*, unsigned long long>
  {
  public:
    reference operator*();

    IteratorFactorial& operator++();
    IteratorFactorial& operator--();

    IteratorFactorial operator++(int);
    IteratorFactorial operator--(int);

    bool operator!=(const IteratorFactorial& other) const;
    bool operator==(const IteratorFactorial& other) const;
  private:
    IteratorFactorial(const unsigned long long index, const value_type val);
    const unsigned long long maxCount_ = 11;
    unsigned long long index_;
    value_type value_;
    friend ContainerFactorial;
  };

  using const_iterator = IteratorFactorial;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  ContainerFactorial(const unsigned long long max_index);
  const_iterator begin() const;
  const_iterator end() const;

  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  const unsigned long long maxIndex_;
  unsigned long long maxValue_;
};

unsigned long long calculateFactorial(unsigned long long index);

#endif
