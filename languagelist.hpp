#pragma once 
#include <string>
#include <vector>
struct lgn 
{
  std::string id;
  std::string ext;
  std::string cmt;
  //use the ¤ to inplace of the source file name
  std::string exec;
  std::vector<std::string> args;
};

lgn findLang(std::string lang)
{
    std::vector<lgn> alllang = 
      {
        {"cpp", ".cpp", "//","g++",  {"¤", "-o", "rcompiled"}},
        {"python", ".py", "#","python", {"¤"}},
        {"ipython", "", "#","python", {"-i", "-m", "¤"}},
      };
    
    for(int i = 0; i<alllang.size(); i++)
    {
      if(alllang[i].id == lang)
      {
        return alllang[i];
      }
    }
    std::cout << "Unknown language " << lang << std::endl;
    return (lgn){"", "", ""};
}
