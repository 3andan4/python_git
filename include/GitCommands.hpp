/*
** EPITECH PROJECT, 2023
** giti
** File description:
** GitCommands.hpp
*/

#ifndef GITI_GITCOMMANDS_HPP
    #define GITI_GITCOMMANDS_HPP
    #include "lib.pch"
    #include "StaticVar.hpp"
    #include "GitiExceptions.hpp"
    /**
     * @brief Using libgit2, this class will be used to execute git commands
     */
    class GitAgent {
        public:
        GitAgent();
        ~GitAgent();
        void commit(std::string const &message);

        git_repository *_repo = nullptr;
        const git_signature *_signature = nullptr;
        git_tree *_tree = nullptr;
        git_oid *_tree_id;
        git_oid _oid;
        git_oid _commit_id;
        git_index *_index = nullptr;
        git_commit *_commit = nullptr;
    };
#endif //GITI_GITCOMMANDS_HPP
