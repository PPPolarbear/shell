#include <iostream>
#include <string>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  while(1)
  {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);



    if (input == "exit") 
    {
      break;
    }
    else if (!input.find("echo"))
    {
      std::cout << input.substr(5) << std::endl;
      continue;
    }


    std::cout << input  << ": command not found" <<std::endl;


  }
  return 0;
  }
