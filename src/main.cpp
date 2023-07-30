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
#include "StaticVar.hpp"
#include "Parser.hpp"

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
        Changelog changelog(JSON_LOCAL("/home/" + std::string(getenv("USER")) + "/."));
        if (ac == 1) {
            git_libgit2_shutdown();
            return 0;
        }
        Parser here = Parser();
        here.parse(ac, av);
        if (here._options["help"] || here._options["error"]) {
            git_libgit2_shutdown();
            std::cout << here._all_options << std::endl;
            return (here._options["error"] ? 84 : 0);
        }
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
