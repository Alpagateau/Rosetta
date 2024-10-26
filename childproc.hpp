#pragma once 
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include "languagelist.hpp"
#include <sstream>

std::string replace_all(
    const std::string & str ,   // where to work
    const std::string & find ,  // substitute 'find'
    const std::string & replace //      by 'replace'
) {
    using namespace std;
    string result;
    size_t find_len = find.size();
    size_t pos,from=0;
    while ( string::npos != ( pos=str.find(find,from) ) ) {
        result.append( str, from, pos-from );
        result.append( replace );
        from = pos + find_len;
    }
    result.append( str, from , string::npos );
    return result;
/*
    This code might be an improvement to James Kanze's
    because it uses std::string methods instead of
    general algorithms [as 'std::search()'].
*/
}

std::vector<char*> parseCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<char*> args;
    std::string arg;

    // Split the command string into arguments
    while (iss >> arg) {
        args.push_back(const_cast<char*>(arg.c_str()));
    }
    
    args.push_back(nullptr);  // Last element must be nullptr for execvp
    return args;
}

int runExec(lgn l) {
    std::system(replace_all(l.exec, "¤", "temp."+l.ext).c_str());
    /* 
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Fork failed
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    } else if (pid == 0) {
        // This is the child process
        // Replace the child process with "python main.py"
        std::vector<char*> args = parseCommand(
          replace_all(
            l.cmd,
            "¤", 
            "temp."+l.ext
          )
        );

        // Execute the command
        execvp(args[0], args.data());

        // If execvp fails
        std::cerr << "Exec failed!" << std::endl;
        return 1;
    } else {
        // This is the parent process
        waitpid(pid, nullptr, 0);  // Wait for the child process to finish
        std::cout << "Parent process: Child has finished." << std::endl;
    }
    */
    return 0;
}

