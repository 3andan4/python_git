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
        Changelog changelog(JSON_LOCAL_DEBUG);
        std::cout << changelog._currentVersion.__str__() << std::endl;
        if (ac == 1) {
            git_libgit2_shutdown();
            return 0;
        }
        Parser here = Parser();
        here.parse(ac, av);
        if (here._u_options["help"] || here._error["error"]) {
            git_libgit2_shutdown();
            std::cout << here._all_options << std::endl;
            return (here._error ? 84 : 0);
        }
        if (here._utility) {
            // TODO: add utility command → Not a commit command
        }
        if (here._tool) {
            // TODO: add tool command → Is a commit command wrapper
        }
        if (here._comments) {
            // TODO: add comments command → Is a direct commit command
        }
    } catch (GitiException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    git_libgit2_shutdown(); // not mandatory as linux will do it for us, but it's good practice
    return 0;
}
