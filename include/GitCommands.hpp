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
        /**
         * @brief This function will add a file to the index (staging area)
         * @param file The file to add
         */
        void addFileToIndex(std::string const &file);
        /**
         * @brief This function will remove a file from the index (staging area)
         *  This add the removal to the index, hence the file will be removed in the next commit
         * @param file
         */
        void removeFileFromIndex(std::string const &file);
        /**
         * @brief This function will commit the changes in the index (staging area)
         * @param message The commit message
         */
        void commit(std::string const &message);
        void loadStatus();

        git_repository *_repo = nullptr;
        const git_signature *_signature = nullptr;
        git_tree *_tree = nullptr;
        git_oid *_tree_id;
        git_oid _oid;
        git_oid _commit_id;
        git_index *_index = nullptr;
        git_commit *_commit = nullptr;
        std::vector<std::string> _gitStatus;
    };
#endif //GITI_GITCOMMANDS_HPP
