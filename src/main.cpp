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

void helpExit(bool with_error = false) {
    std::cout << "Usage for GITI:" << std::endl;
    std::cout << "\tgiti                        → Interactive mode" << std::endl;
    std::cout << "\tgiti [special command]      → Run a special command" << std::endl;
    std::cout << "\tgiti [opt] <tag> <files>    → Run the default command with options" << std::endl;
    std::cout << std::endl;
    std::cout << "Special Commands:" << std::endl;
    std::cout << "\t\t --all, -a              → Commit all modified files automatically" << std::endl;
    std::cout << "\t\t --makefile, -m         → Commit all Makefile & CMakeFile in the repo" << std::endl;
    std::cout << "\t\t --header, -H           → Commit all header files in the repo" << std::endl;
    std::cout << "\t\t --update, -u           → Update GITI if an update is available" << std::endl;
    std::cout << "\t\t --force-update, --fu    → Remove current GITI version and reinstall the remote version" << std::endl;
    std::cout << "\t\t --remove, -r           → Remove GITI from your system" << std::endl;
    std::cout << "\t\t --igit, -i             → Commit .gitignore file(s)" << std::endl;
    std::cout << "\t\t --del, -d              → Commit deleted file(s)" << std::endl;
    std::cout << "\t\t --help, -h             → Display this help" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t\t--no-commit, --nc        → Do not commit changes" << std::endl;
    std::cout << "\t\t--no-title, --nt         → Do not ask for a commit title" << std::endl;
    std::cout << "\t\t--no-title-commit, --ntc → Do not ask for a commit title and do not commit changes" << std::endl;
    exit((with_error ? 84 : 0));
}

int main(int ac, char **av) {
    git_libgit2_init(); // mandatory to use libgit2
    try{
        if (!isInGitRepo())
            throw GitiException(1);
        Changelog changelog(std::string(getenv("HOME")) + "/.giti/versions_changelog.json");
        if (ac == 1) {
            git_libgit2_shutdown();
            return 0;
        }
        Parser here = Parser();
        here.parse(ac, av);
        if (here._options["help"] || here._options["error"]) {
            git_libgit2_shutdown();
            helpExit(static_cast<bool>(here._options["error"]));
            return here._options["error"];
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
