#include "parser.hpp"
#include <sstream>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include "commands.hpp"

bool readNumber(std::stringstream& in, std::string& str)
{
  in >> std::ws >> str;

  if (!in || (str.empty()))
  {
    return false;
  }

  auto check = [&](auto digit) { return isdigit(digit); };
  auto iter = std::find_if(str.begin(), str.end(), check);

  if (iter == str.end())
  {
    return false;
  }

  return true;
}

bool readName(std::stringstream& in, std::string& str)
{
  in >> std::ws;

  if (in.peek() != '"')
  {
    return false;
  }

  in.get();

  std::string tmp;

  std::getline(in, tmp);

  for (size_t i = 0; i != tmp.length(); i++)
  {
    if (tmp[i] == '\\')
    {
      if (tmp[i + 1] == '\"')
      {
        str += tmp[i + 1];
        i++;
      }
      else
      {
        str += tmp[i];
      }
    }
    else
    {
      str += tmp[i];
    }
  }

  str.pop_back();

  if (!in || (str.empty()))
  {
    return false;
  }
  return true;
}

bool readMark(std::stringstream& in, std::string& str)
{
  in >> std::ws >> str;

  if (!in || (str.empty()))
  {
    return false;
  }

  for (size_t i = 0; i < str.length(); i++)
  {
    if ((!isalnum(str[i])) && (str[i] != '-'))
    {
      throw std::invalid_argument("Incorrect argument");
    }
  }

  return true;
}

CommandFunction parse(std::stringstream& stream)
{
  using MapType = const std::unordered_map<std::string, CommandFunction(*) (std::stringstream&)>;

  MapType commands
  {
    {"add", &parseAdd},
    {"store", &parseStore},
    {"insert", &parseInsert},
    {"delete", &parseDelete},
    {"show", &parseShow},
    {"move", &parseMove}
  };

  std::string command;
  stream >> command;

  if (!stream)
  {
    throw std::runtime_error("Reading failed");
  }

  auto it = commands.find(command);

  if (it != commands.end())
  {
    return it->second(stream);
  }
  else
  {
    return &command::invalidCommand;
  }
}

CommandFunction parseAdd(std::stringstream& stream)
{
  std::string number;
  if (readNumber(stream, number) && (stream.rdbuf()->sgetc() != '\n'))
  {
    std::string name;
    if (readName(stream, name))
    {
      PhoneBook::record_t record{ name, number };
      return std::bind(&command::add, std::placeholders::_1, std::placeholders::_2, record);
    }
  }
  return &command::invalidCommand;
}

CommandFunction parseStore(std::stringstream& stream)
{
  std::string mark;
  if (readMark(stream, mark) && (stream.rdbuf()->sgetc() != '\n'))
  {
    std::string newMark;
    if (readMark(stream, newMark))
    {
      return std::bind(&command::store, std::placeholders::_1, std::placeholders::_2, mark, newMark);
    }
  }

  return &command::invalidCommand;
}

CommandFunction parseInsert(std::stringstream& stream)
{
  std::string pos;
  if ((stream >> pos) && (stream.rdbuf()->sgetc() != '\n'))
  {
    std::string mark;
    if (readMark(stream, mark) && (stream.rdbuf()->sgetc() != '\n'))
    {
      std::string number;
      if (readNumber(stream, number) && (stream.rdbuf()->sgetc() != '\n'))
      {
        std::string name;
        if (readName(stream, name))
        {
          PhoneBook::record_t record{ name, number };

          if (pos == "after")
          {
            return std::bind(&command::insertAfter, std::placeholders::_1, std::placeholders::_2, mark, record);
          }
          else if (pos == "before")
          {
            return std::bind(&command::insertBefore, std::placeholders::_1, std::placeholders::_2, mark, record);
          }
          else return &command::invalidCommand;
        }
      }
    }
  }

  return &command::invalidCommand;
}

CommandFunction parseDelete(std::stringstream& stream)
{
  std::string mark;
  if (readMark(stream, mark))
  {
    return std::bind(&command::remove, std::placeholders::_1, std::placeholders::_2, mark);
  }

  return &command::invalidCommand;
}

CommandFunction parseShow(std::stringstream& stream)
{
  std::string mark;
  if (readMark(stream, mark))
  {
    return std::bind(&command::show, std::placeholders::_1, std::placeholders::_2, mark);
  }

  return &command::invalidCommand;
}

CommandFunction parseMove(std::stringstream& stream)
{
  std::string mark;
  if (readMark(stream, mark) && (stream.rdbuf()->sgetc() != '\n'))
  {
    std::string pos;
    if (stream >> pos)
    {
      if (pos == "first")
      {
        return std::bind(&command::moveToPos, std::placeholders::_1, std::placeholders::_2, mark, BookmarkInterface::MovePosition::first);
      }
      else if (pos == "last")
      {
        return std::bind(&command::moveToPos, std::placeholders::_1, std::placeholders::_2, mark, BookmarkInterface::MovePosition::last);
      }
      else
      {
        char* end;
        int step = std::strtol(pos.c_str(), &end, 10);
        if (pos.empty() || *end != '\0')
        {
          return &command::invalidStep;
        }
        return std::bind(&command::moveBySteps, std::placeholders::_1, std::placeholders::_2, mark, step);
      }
    }
  }

  return &command::invalidCommand;
}

