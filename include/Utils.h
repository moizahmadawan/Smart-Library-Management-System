#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

// Convert a string to lowercase (used for case-insensitive title/author compare)
inline std::string toLower(std::string s) {
    for (char &c : s) c = (char)tolower((unsigned char)c);
    return s;
}

// Print a prompt and read a full line
inline std::string readLine(const std::string &prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// Print a prompt and read a valid integer (asks again on bad input)
inline int readInt(const std::string &prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try { return std::stoi(s); }
        catch (...) { std::cout << "  Please enter a valid number.\n"; }
    }
}

#endif
