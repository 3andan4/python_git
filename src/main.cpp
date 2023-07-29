/*
** EPITECH PROJECT, 2023
** giti
** File description:
** main.cpp
*/

#include <iostream>
#include "lib.pch"
#include "Update.hpp"
#include "GitiExceptions.hpp"

// https://raw.githubusercontent.com/MaximeLeBesnerais/giti_super/main/versions_changelog.json
// installation path: /home/$USER/.giti/versions_changelog.json

bool isInGitRepo() {
    git_repository *repo = nullptr;
    int error = git_repository_open_ext(&repo, ".", 0, nullptr);

    if (error == 0) {
        git_repository_free(repo);
        return true;
    }
    return false;
}

int main(int ac, char **av) {
    git_libgit2_init(); // mandatory to use libgit2
    try{
        if (!isInGitRepo())
            throw GitiException(1);
    auto changelog = Changelog(std::string(getenv("HOME")) + "/.giti/versions_changelog.json");
    if (ac == 1) {
        // TODO: GITI interactive mode
        return 0;
    }
    // TODO: Parse arguments into an object
    // TODO: If help needed, display help
    // TODO: If special command, run it
    // TODO: If no special command, run default command using provided arguments
    std::cout << "Hello, World!" << std::endl;
    } catch (GitiException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    git_libgit2_shutdown(); // not mandatory as linux will do it for us, but it's good practice
    return 0;
}
