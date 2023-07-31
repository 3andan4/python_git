//
// Created by maximelb on 29/07/23.
//

#include "Parser.hpp"

void Parser::parse(int ac, char **av) {
    _u_options = {
            {"version",         false},
            {"update",          false},
            {"force-update",    false},
            {"remove",          false},
            {"igit",            false},
            {"help",            false},
            {"error",           false}
    };
    _t_options = {
            {"all",      false},
            {"del",      false},
            {"makefile", false},
            {"header",   false}
    };
    _c_options = {
            {"title",   false},
            {"message", false}
    };

    po::options_description _type1("Regular command");
    po::options_description _optional("Optional arguments");
    _optional.add_options()
    ("no-commit,c", "Do not prompt for a commit comment")
    ("no-title,t", "Do not prompt for a title")
    ("no-title-commit,x", "Do not prompt for anything");
    po::options_description _positional("Positional arguments");
    _positional.add_options()
    ("Tag", po::value<std::string>()->required(), "Tag of the commit")
    ("Files", po::value<std::vector<std::string>>()->required(), "Files to commit");
    _type1.add(_optional).add(_positional);

    po::options_description _super("Super command");
    po::options_description _type2("Utility commands");
    _type2.add_options()
    ("update,u", "Update GITI if an update is available")
    ("force-update,F", "Remove current GITI version and reinstall the remote version")
    ("remove,R", "Remove GITI from your system")
    ("igit,i", "Commit .gitignore file(s)")
    ("help,h", "Display this help");
    po::options_description _type3("Tool commands");
    _type3.add_options()
    ("all,a", "Commit all modified files automatically")
    ("del,d", "Commit deleted file(s)")
    ("makefile,m", "Commit all Makefile & CMakeFile in the repo")
    ("header,H", "Commit all header files (.h, .hpp)");
    _super.add(_type2).add(_type3);

    _all_options.add(_type1).add(_super);

    po::variables_map regular_vm;
    po::variables_map type2_and_3_vm;

    try {
        po::store(po::parse_command_line(ac, av, _super), type2_and_3_vm);
        po::notify(type2_and_3_vm);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        _error = true;
    }

    if (!_error) {
        _u_options["version"] = (bool) type2_and_3_vm.count("version");
        _u_options["update"] = (bool) type2_and_3_vm.count("update");
        _u_options["force-update"] = (bool) type2_and_3_vm.count("force-update");
        _u_options["remove"] = (bool) type2_and_3_vm.count("remove");
        _u_options["igit"] = (bool) type2_and_3_vm.count("igit");
        _u_options["help"] = (bool) type2_and_3_vm.count("help");
        _t_options["all"] = (bool) type2_and_3_vm.count("all");
        _t_options["del"] = (bool) type2_and_3_vm.count("del");
        _t_options["makefile"] = (bool) type2_and_3_vm.count("makefile");
        _t_options["header"] = (bool) type2_and_3_vm.count("header");

        int count = std::count_if(_u_options.begin(), _u_options.end(), [](auto &option) { return option.second; });
        int count2 = std::count_if(_t_options.begin(), _t_options.end(), [](auto &option) { return option.second; });

        if (count > 1 || count2 > 1 || (count > 0 && count2 > 0)) {
            _error = true;
            return;
        }

        _utility = count > 0;
        _tool = count2 > 0;

        if (_utility && _tool) {
            _error = true;
            return;
        }

        if (_utility || _tool)
            return;
    }

    _error = false;

    try {
        po::store(po::parse_command_line(ac, av, _type1), regular_vm);
        po::notify(regular_vm);
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        _error = true;
        return;
    }

    if (regular_vm.count("Tag") && regular_vm.count("Files")) {
        _tag = regular_vm["Tag"].as<std::string>();
        _files = regular_vm["Files"].as<std::vector<std::string>>();
    } else {
        _error = true;
        return;
    }

    _c_options["title"] = (bool) regular_vm.count("no-title") || (bool) regular_vm.count("no-title-commit");
    _c_options["message"] = (bool) regular_vm.count("no-commit") || (bool) regular_vm.count("no-title-commit");

    if (_c_options["title"] || _c_options["message"])
        _comments = true;

    return;
}