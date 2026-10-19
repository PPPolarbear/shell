#include <iostream>
#include <string>
#include <map>

std::map<std::string,int> builtin = {{"exit",0},{"echo",1},{"type",2}}; // 内建命令


int find_in_built(const std::string& a) // 实际上是轮询找命令
{
  int index = 9999;
  for(auto i:builtin)
  {
    if(i.first == a)
    {
      index = i.second;
    }
  }
  return index;
}

void exec_command(const std::string& command,const std::string& text)
{
  int Command_int = find_in_built(command);

  switch(Command_int)
  {
    case 1: // echo
    {
      std::cout << text << std::endl;
      break;      
    }



    case 2: // type
    {
      int Type = 0; // 0代表unknown，1为builtin
      if(find_in_built(text) != 9999) // 结果是已有的命令
      {
        std::cout << text << " is a shell builtin" << std::endl;
      }
      else
      {
        std::cout << text << ": command not found" <<std::endl;
      }
      break;
    }

    // case 3:

    //   break;



    case 9999: // 没找到
    {
      std::cout << command << ": command not found" <<std::endl;
      break;
    }
  }
}


int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string input; // 用户输入
  std::string command; // 命令格式切分：【类型】【内容】
  std::string text; // 命令格式切分：【类型】【内容】  

  while(1)
  {
    std::cout << "$ ";
    input.clear();
    std::getline(std::cin, input);



    if (input == "exit") 
    {
      break;
    }


    
    if(!(input.find(" ") == std::string::npos)) // 非纯命令
    {
      command = input.substr(0,input.find(" "));
      text = input.substr(input.find(" ")+1);
      
      exec_command(command,text);
    }
    else // 纯命令
    {
      command = input;
      text = "";
      exec_command(command,text);
    }

  }


  return 0;
  }
