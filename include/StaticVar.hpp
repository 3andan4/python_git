/*
** EPITECH PROJECT, 2023
** giti
** File description:
** StaticVar.hpp
*/

// https://raw.githubusercontent.com/MaximeLeBesnerais/giti_super/main/versions_changelog.json
// installation path: /home/$USER/.giti/versions_changelog.json

#ifndef GITI_STATICVAR_HPP
    #define GITI_STATICVAR_HPP
    #define JSON_LOCAL(home) home + "giti/versions_changelog.json"
    #define JSON_HOME JSON_LOCAL("/home" + std::string(getenv("USER")) + "/")
    #define JSON_LOCAL_DEBUG JSON_LOCAL(std::string("/home/perso/"))
    #define JSON_REMOTE "https://raw.githubusercontent.com/MaximeLeBesnerais/giti_super/main/versions_changelog.json"
#endif // GITI_STATICVAR_HPP
