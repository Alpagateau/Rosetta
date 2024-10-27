#pragma once 
#include <string>
#include <vector>
#include <fstream>
struct lgn 
{
  std::string id;
  std::string fullname;
  std::string ext;
  std::string cmt;
  //use the ¤ to inplace of the source file name
  std::string exec;
  std::vector<std::string> args;
};


bool findFile(std::string path)
{
  struct stat buffer;   
  return (stat (path.c_str(), &buffer) == 0); 
}

std::vector<std::string> split(std::string &val)
{
  std::vector<std::string> o;
  std::string buffer;
  for(int i = 0; i < val.size(); i++)
  {
    if(val[i] == ' ')
    {
      if(buffer != ""){
        o.push_back(buffer);
        buffer = "";
      }
    }
    else
    {
      buffer += val[i];
    }
  }
  if(buffer != "")
  {
    o.push_back(buffer);
  }
  return o;
}

std::vector<lgn> loadConfig()
{
  const std::string home = getenv("HOME");
  std::vector<lgn> config;
  if(!findFile(home + "/.config/rosetta/config.txt"))
  {
    std::cout << "No config file found, faling on standart. Use -h for more information" << std::endl;
    return {
        {"cpp","cpp",".cpp", "//","g++",  {"¤", "-o", "rcompiled"}},
        {"python", "python",".py", "#","python", {"¤"}},
        {"ipython", "python", "", "#","python", {"-i", "-m", "¤"}},
      };
  }
  else 
  {
    std::ifstream configfile(home + "/.config/rosetta/config.txt");
    std::string l;
    while(std::getline(configfile, l))
    {
      lgn _lgn;
      std::vector<std::string> lan = split(l);
      if(l[0] != '#'){
        if(lan.size() >= 5)
        {
          _lgn.id = lan[0];
          _lgn.fullname = lan[1];
          _lgn.ext = (lan[2] == "£" ? "" : lan[2]);
          _lgn.cmt = lan[3];
          _lgn.exec = lan[4];
          for(int i = 0; i < lan.size() - 5; i++)
          {
            _lgn.args.push_back(lan[5+i]);
          }
        }
        config.push_back(_lgn);
        _lgn.args.clear();
      }
    }
    return config;
  }
}

lgn findLang(std::string lang)
{
    std::vector<lgn> alllang = loadConfig();
    
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
