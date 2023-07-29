/*
** EPITECH PROJECT, 2023
** giti
** File description:
** GitiExceptions.cpp
*/

#include "GitiExceptions.hpp"

GitiException::GitiException(int code) {
    std::unordered_map<int, std::string> _errors = {
        {1, "GitiException: Not a git repository (or any of the parent directories): .git"},
    };
    auto it = _errors.find(code);
    if (it != _errors.end())
        _message = it->second;
    else
        _message = "GitiException: Unknown error";
}