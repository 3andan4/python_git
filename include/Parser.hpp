//
// Created by maximelb on 29/07/23.
//

#ifndef GITI_PARSER_HPP
    #define GITI_PARSER_HPP
    #include "lib.pch"
    #include "StaticVar.hpp"
    #include "GitiExceptions.hpp"
    namespace po = boost::program_options;


    class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void parse(int ac, char **av);
        std::unordered_map<std::string, bool> _u_options;
        std::unordered_map<std::string, bool> _t_options;
        std::unordered_map<std::string, bool> _c_options;
        po::options_description _all_options;
        bool _error = false;
        bool _utility = false;
        bool _tool = false;
        bool _comments = false;
        std::string _tag;
        std::vector<std::string> _files;
    };

#endif //GITI_PARSER_HPP
