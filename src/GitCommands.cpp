#include "GitCommands.hpp"

GitAgent::GitAgent()
{
    int error = git_repository_open(&_repo, ".");
    if (error != 0)
        throw GitiException(6);
    error = git_reference_name_to_id(&_oid, _repo, "HEAD");
    if (error != 0)
        throw GitiException(6);
    error = git_commit_lookup(&_commit, _repo, &_oid);
    if (error != 0)
        throw GitiException(6);
    _signature = git_commit_author(_commit);
    error = git_repository_index(&_index, _repo);
    if (error != 0)
        throw GitiException(6);
    error = git_index_write_tree_to(_tree_id, _index, _repo);
    if (error != 0)
        throw GitiException(6);
    error = git_tree_lookup(&_tree, _repo, _tree_id);
    if (error != 0)
        throw GitiException(6);
}

GitAgent::~GitAgent()
{
    git_tree_free(_tree);
    git_commit_free(_commit);
    git_repository_free(_repo);
}

void GitAgent::addFileToIndex(std::string const &file)
{
    int error = git_index_add_bypath(_index, file.c_str());
    if (error != 0)
        throw GitiException(7);
}

void GitAgent::removeFileFromIndex(std::string const &file)
{
    int error = git_index_remove_bypath(_index, file.c_str());
    if (error != 0)
        throw GitiException(7);
}

void GitAgent::commit(std::string const &message)
{
    const git_commit *parents = nullptr;
    int error = git_commit_create(&_commit_id, _repo, "HEAD", _signature, _signature, nullptr, message.c_str(), _tree, 1, &parents);
    if (error != 0)
        throw GitiException(7);
    git_commit_free(_commit);
    error = git_commit_lookup(&_commit, _repo, &_commit_id);
    if (error != 0)
        throw GitiException(7);
}

void GitAgent::loadStatus()
{
    git_status_list *status = nullptr;
    git_status_options opts = GIT_STATUS_OPTIONS_INIT;
    int error = git_status_list_new(&status, _repo, &opts);
    if (error != 0)
        throw GitiException(7);

    size_t status_count = git_status_list_entrycount(status);
    for (size_t i = 0; i < status_count; ++i) {
        const git_status_entry *entry = git_status_byindex(status, i);
        _gitStatus.push_back(entry->head_to_index->new_file.path);
    }

    git_status_list_free(status);
}
