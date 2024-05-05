// TelnetForums_Plugin.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "TelnetForums_Plugin.h"
#include <string> // Include the <string> header
#include <vector> // Include vector for collection
#include <functional> // Include the <functional> header for std::hash
#include <sstream> // Include the <sstream> header for std::stringstream
#include <Windows.h>


//    
//     ___       _     _              ___    __
//    / __|  ___| |_  | |_ ___   __ _( _ )  / /
//    \__ \ / -_)  _| |  _/ _ \  \ \ / _ \ / _ \
//    |___/ \___|\__|  \__\___/  /_\_\___/ \___/
//    (set to x86)
//    


// Declare the functions with extern "C" to prevent name mangling
extern "C" {


    __declspec(dllexport) const char* StringProcessFunction(const char* input) {
        std::string inputStr = input;
        std::istringstream iss(inputStr);
        std::string token;
        std::vector<std::string> words;

        // Tokenize the input string and store words in the vector
        while (std::getline(iss, token, ' ')) {
            words.push_back(token);
        }

        // Ensuring the result still begins with '#' prevents mimicking
        std::string result;
        for (const auto& word : words) {
            if (word.size() > 0 && word[0] == '#') {
                std::hash<std::string> hashFunc;
                size_t hashedValue = hashFunc(word);
                std::stringstream ss;
                ss << "#" << hashedValue << " ";
                result += ss.str();
            }
            else {
                result += word + ' ';
            }
        }

        // Remove trailing space
        if (!result.empty()) {
            result.pop_back();
        }
         
        char* returnString = new char[result.size() + 1];
        std::copy(result.begin(), result.end(), returnString);
        returnString[result.size()] = '\0'; // Null-terminate the string

        return returnString; // Return the modified wide character string
    }

    // TelnetForums requires a plugin to have a plugin description
    extern const char* PLUGIN_DESCRIPTION = "This plugin hashes words beginning with #";

    __declspec(dllexport) const char* PluginDescription() {
        return PLUGIN_DESCRIPTION;
    }
}