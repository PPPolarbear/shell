#include <iostream>
#include <string>
#include <map>
#include <cstring>

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


void single_deal(const char* line)
{
  const char* last = NULL;
  for(const char* i = line; *i != '\0'; ++i)
  {
    if(*i == '/') last = i;
  }
  std::string suffix(last ? last + 1 : line);
  if(find_in_built(suffix) == 9999) 
  {
    int o = 0;
    for(const auto p:builtin) o++;
    builtin.insert(std::pair(suffix,o));
  }
}


void Add_path_to_builtin(const char* path)
{
  // 对path字符串处理，把环境变量加入到内建命令字典中去
  std::string Path = path;
  char* token = std::strtok(Path.data(), ":");
  while (token != nullptr)
  {
    single_deal(token); // 处理单行环境变量
    token = std::strtok(nullptr, ":");
  } 
  
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
        std::cout << text << ": not found" <<std::endl;
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
  const char* Temp_path = std::getenv("PATH"); // 提取环境变量
  std::string Env_path = Temp_path ? Temp_path : "";
  if(Temp_path) Add_path_to_builtin(Temp_path);

  std::cout << Env_path << std::endl;

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
