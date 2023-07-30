//
// Created by maximelb on 29/07/23.
//

#include "Parser.hpp"


// Information:
//     -v, --version            Show the version of giti
//     -u, --update             Update giti
//     -U, --force-update       Force update giti
//     -r, --remove             Remove giti

// Tools:
//     -a, --all              Commit all files
//     -i, --igit             Commit .gitignore
//     -d, --deleted          Commit deleted files
//     -l, --header           Commit header files
//     -m, --make             Commit makefile

// bool _version = false;
//         bool _test = false;
//         bool _no_commit = false;
//         bool _no_title = false;
//         bool _no_title_commit = false;
//         bool _all = false;
//         bool _makefile = false;
//         bool _header = false;
//         bool _update = false;
//         bool _force_update = false;
//         bool _remove = false;
//         bool _igit = false;
//         bool _del = false;
//         bool _help = false;
//         bool _error = false;

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
    po::options_description desc("Allowed options");
    desc.add_options()("version,v", "Display the current version of GITI on your system")
    ("test,t", "just a test option")
    ("no-commit,nc", "Do not prompt for a commit comment")
    ("no-title,nt", "Do not prompt for a title")
    ("no-title-commit,nct,ntc", "Do not prompt for anything")
    ("all,a", "Commit all modified files automatically")
    ("makefile,m", "Commit all Makefile & CMakeFile in the repo")
    ("header,H", "Commit all header files (.h, .hpp)")
    ("update,u", "Update GITI if an update is available")
    ("force-update,fu", "Remove current GITI version and reinstall the remote version")
    ("remove,r", "Remove GITI from your system")
    ("igit,i", "Commit .gitignore file(s)")
    ("del,d", "Commit deleted file(s)")
    ("help,h", "Display this help");

    po::variables_map vm;
    try {
    po::store(po::parse_command_line(ac, av, desc), vm);
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
        for (auto &option : _options) {
            if (option.second)
                option.second = false;
        }
        _options["error"] = true;
    }
    return;
}