#pragma once
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <cctype>
#include <locale>
#include "languagelist.hpp"

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

bool isBlock(std::string l)
{
  std::string strt = l.substr(0, 3);
  return (strt == "```");
}

std::string getLanguage(std::string l)
{
  if(!isBlock(l))
    return "";

  std::string lgn = trim_copy(l.substr(3));
  return lgn;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool createTempFile(std::string path, lgn language)
{
  std::string line;
  std::ifstream markdownFile(path);
  std::ofstream tempFile("temp"+language.ext);
  bool inBlock = false;
  std::vector<std::string> blocks = {""};
  bool usable = true;
  int currentidx = -1;
  std::string currentBlock = "";
  while(std::getline(markdownFile, line))
  { 
    if(isBlock(line))
    {
      if(inBlock)
      {
        inBlock = false;
        if(usable)
        {
          if(currentidx == -1)
          {
            blocks.push_back(currentBlock);
          }else{
            blocks.insert(blocks.begin()+currentidx, currentBlock);
          }
        }
        currentBlock = "";
        currentidx = -1;
      }else 
      {
        if(getLanguage(line) == language.fullname)
        {
            inBlock = true;
        }
      }
    }else{
      if(inBlock)
      {
        currentBlock += line + "\n";
        std::cout << "New Line : " << line << std::endl;
        if(line.substr(0, language.cmt.size()) == language.cmt)
        {
          std::string comment = trim_copy(line.substr(language.cmt.size()));
          if(is_number(comment))
          {
            currentidx = std::stoi(comment);
          }
          else if(comment == "rignore")
          {
            usable = false;
          }
        }
      }
    }
  }

  for(int i = 0; i < blocks.size(); i++)
  {
    tempFile << blocks[i] << std::endl;
  }
  markdownFile.close();
  tempFile.close();
  return true;
}
