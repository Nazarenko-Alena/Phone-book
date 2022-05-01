#include <iostream>
#include <stdexcept>
#include <sstream> 
#include "commands.hpp"
#include "bookmarkInterface.hpp"
#include "parser.hpp"

void taskOne(std::istream& in, std::ostream& out)
{
  BookmarkInterface inter;
  std::string str;

  while (std::getline(in, str))
  {
    std::stringstream stream(str);

    if ((stream >> std::ws).eof())
    {
      continue;
    }

    if (!stream)
    {
      throw std::runtime_error("Reading failed");
    }

    CommandFunction command = parse(stream);
    command(inter, out);
  }

  if (!in.eof())
  {
    throw std::runtime_error("Reading failed");
  }
}
