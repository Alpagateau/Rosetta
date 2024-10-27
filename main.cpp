#include <iostream>
#include <string>
#include "rosetta.hpp"
#include <sys/wait.h>
#include "languagelist.hpp" 
//#include "childproc.hpp"
#define VERSION "0.0.1.0"

int main(int argc, char *argv[])
{
  std::string mrkdwn = "";
  std::string language = "";
  bool cleanup = true;
  bool verbose = false;
  if(argc == 1)
  {
    std::cout << "Please give arguments, or use -h to see help" << std::endl;
    return 0;
  }
  for(int i = 1; i<argc; i++)
  {
      std::string arg = std::string(argv[i]);
      if(arg[0] == '-'){
        if(arg == "-h")
        {
          std::cout << "Rosetta is a tool that lets you run code from markdown files."
            << "\nUsage : \n"
            << " rosetta mardownfile language\n" 
            << "Others flags\n"
            << "> -h : Shows help\n"
            << "> -V : Shows version\n"
            << "> -v : verbose\n"
            << "> -km : keep middle files\n"
            << "\nYou can set up the compilers in ~/.config/rosetta/config.txt. If no such file is found, it will fall back on a few default setting, including cpp, python and ipython\n"
            << std::endl;
        }
        if(arg == "-V")
        {
          std::cout << "ROSETTA version : " << VERSION << std::endl;
        }
        if(arg == "-v")
        {
          verbose = true;
        }
        if(arg == "-km")
        {
          cleanup = false;
        }
      }
      else 
      {
        if(mrkdwn == "")
        {
          mrkdwn = arg;
          if(!findFile(mrkdwn))
          {
            std::cout << "Error : File Not Found at " << mrkdwn << std::endl;
            return 0;
          }
        }
        else if(language == "")
        {
          language = arg;
        }
        else  
        {
          std::cout << "Too many arguments";
          return 0;
        }
      }
  }
  //true start 
  if(mrkdwn == "")
  {
    std::cout << "No file given" << std::endl;
    return 0;
  }
  if(language == "")
  {
    std::cout << "No language given" << std::endl;
  }
  lgn l = findLang(language);
  if(l.id == "")
  {
    return 0;
  }
  createTempFile(mrkdwn, l); 
  
  int f = fork();
  if(f < 0)
  {
    std::cout << "fork failed" << std::endl;
  }
  if(f == 0)
  {
    char* program = l.exec.data();
    char *args[l.args.size()+2] = {0};
    for(int i = 0; i<l.args.size()+1; i++)
    {
      if(i > 0){
        if(l.args[i-1] != "¤")
        {
          args[i] = l.args[i-1].data();
        }
        else {
          args[i] = ("temp"+l.ext).data();
        }
      }
      else 
      {
        args[i] = l.exec.data();
      }
      if(verbose)
      {
        std::cout << "Args " << i << " = " << args[i] << std::endl;
      }
    }
    args[l.args.size()+1] = nullptr;
    execvp(program, args);
  }
  wait(&f);
  if(verbose)
  {
    std::cout << "child process ended" << std::endl;
  }
  if(cleanup)
  {
    if(verbose)
    {
      std::cout << "Cleaning middle files" << std::endl;
    }
    std::remove( ("temp"+l.ext).data() );
  }
  return 0;
}
