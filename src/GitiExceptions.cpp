/*
** EPITECH PROJECT, 2023
** giti
** File description:
** GitiExceptions.cpp
*/

#include "GitiExceptions.hpp"

GitiException::GitiException(int code) noexcept {
    std::unordered_map<int, std::string> _errors = {
        {1, "GitiException: Not a git repository (Giti must be run in a git repository)"},
        {2, "GitiException: Parsed version number was invalid or Date parsing failed"},
        {3, "GitiException: Can't open Local changelog - The file may have been deleted"},
        {4, "GitiException: Can't parse Local changelog - The file may have been modified"},
        {5, "GitiException: You can't use utility options and tool options at the same time."},
        {6, "GitiException: Error when exploring the git tree"},
        {7, "GitiException: Error when trying to commit"},
    };
    auto it = _errors.find(code);
    if (it != _errors.end())
        _message = it->second;
    else
        _message = "GitiException: Unknown error";
}