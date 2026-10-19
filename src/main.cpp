#include <iostream>
#include <string>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  while(1)
  {
    std::cout << "$ ";
    std::string input;
    std::cin >> input;


    if (input == "exit") 
    {
      break;
    }


    std::cout << input  << ": command not found" <<std::endl;

    
  }
  return 0;
  }
