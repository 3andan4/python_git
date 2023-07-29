/*
** EPITECH PROJECT, 2023
** giti
** File description:
** GitiExceptions.hpp
*/

#ifndef GITI_ERRORS_HPP
    #define GITI_ERRORS_HPP
    #include "lib.pch"
    class GitiException : public std::exception {
        public:
            GitiException(int code) noexcept;
            ~GitiException() noexcept override = default;
            const char *what() const noexcept override {
                return _message.c_str();
            }
        private:
            std::string _message;
    };
#endif //GITI_ERRORS_HPP
