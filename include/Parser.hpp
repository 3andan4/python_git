//
// Created by maximelb on 29/07/23.
//

#ifndef GITI_PARSER_HPP
    #define GITI_PARSER_HPP
    #include "lib.pch"
    namespace po = boost::program_options;


    class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        void parse(int ac, char **av);

    private:
    };

#endif //GITI_PARSER_HPP
