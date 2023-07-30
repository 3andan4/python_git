//
// Created by maximelb on 29/07/23.
//

#include "Parser.hpp"

void Parser::parse(int ac, char **av) {
    _options = {
            {"version",         false},
            {"test",            false},
            {"no-commit",       false},
            {"no-title",        false},
            {"no-title-commit", false},
            {"all",             false},
            {"makefile",        false},
            {"header",          false},
            {"update",          false},
            {"force-update",    false},
            {"remove",          false},
            {"igit",            false},
            {"del",             false},
            {"help",            false},
            {"error",           false}
    };
    po::options_description _desc("Giti Interactive Commit Tool", 120);
    po::options_description _utility_options("Utility options");
    _utility_options.add_options()
    ("update,u", "Update GITI if an update is available")
    ("force-update,F", "Remove current GITI version and reinstall the remote version")
    ("remove,R", "Remove GITI from your system")
    ("igit,i", "Commit .gitignore file(s)")
    ("help,h", "Display this help");
    po::options_description _tool_options("Tool options");
    _tool_options.add_options()
    ("all,a", "Commit all modified files automatically")
    ("del,d", "Commit deleted file(s)")
    ("makefile,m", "Commit all Makefile & CMakeFile in the repo")
    ("header,H", "Commit all header files (.h, .hpp)");
    po::options_description _comments_options("Comments options");
    _comments_options.add_options()
    ("no-commit,c", "Do not prompt for a commit comment")
    ("no-title,t", "Do not prompt for a title")
    ("no-title-commit,x", "Do not prompt for anything");

    _desc.add(_utility_options).add(_tool_options).add(_comments_options);
    _all_options.add(_desc);

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(ac, av, _all_options), vm);
        po::notify(vm);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        _options["error"] = true;
        return;
    }
    _options["version"] = (bool) vm.count("version");
    _options["test"] = (bool) vm.count("test");
    _options["no-commit"] = (bool) vm.count("no-commit");
    _options["no-title"] = (bool) vm.count("no-title");
    _options["no-title-commit"] = (bool) vm.count("no-title-commit");
    _options["all"] = (bool) vm.count("all");
    _options["makefile"] = (bool) vm.count("makefile");
    _options["header"] = (bool) vm.count("header");
    _options["update"] = (bool) vm.count("update");
    _options["force-update"] = (bool) vm.count("force-update");
    _options["remove"] = (bool) vm.count("remove");
    _options["igit"] = (bool) vm.count("igit");
    _options["del"] = (bool) vm.count("del");
    _options["help"] = (bool) vm.count("help");

    // If there is more than one option, it's an error !
    int count = 0;
    for (auto &option : _options) {
        if (option.second)
            count++;
    }
    if (count > 1) {
        // set error to false
        for (auto &option : _options)
            if (option.second)
                option.second = false;
        _options["error"] = true;
    }
    return;
}