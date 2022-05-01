#include <iostream>
#include <stdexcept>
#include <sstream>

void taskOne(std::istream& in, std::ostream& out);
void taskTwo(std::ostream& out);

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Incorrect argc";
      return 1;
    }

    std::stringstream stream(argv[1]);

    int task;
    stream >> task;

    if (!stream)
    {
      std::cerr << "Reading failed";
      return 1;
    }

    switch (task)
    {
    case 1:
      taskOne(std::cin, std::cout);
      break;
    case 2:
      taskTwo(std::cout);
      break;
    default:
      std::cerr << "Incorrect task number";
      return 1;
    }
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::runtime_error& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::out_of_range& error)
  {
    std::cerr << error.what();
    return 1;
  }
  return 0;
}
