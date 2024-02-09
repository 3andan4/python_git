{-|
Module      : Parser
Description : Command Line Argument Parsing for the Application
Copyright   : Maxime Le Besnerais
License     : BSD3
Maintainer  : maxoulebesnerais@gmail.com
Stability   : experimental
Portability : POSIX

This module provides functions for parsing command line arguments and 
building objects from the output of 'git status --porcelain'. 
It is used in the 'main' function of the application.
-}
module Parser (
    specialParserFunc,
    typeParser,
    skipParser,
    commandLineParser
    ) where

import Data

-- | Parse the special arguments for user options.
userOptionParser :: [String] -> SpecialParser -> Either String SpecialParser
userOptionParser [] sp = Right sp
userOptionParser (x:xs) (u, t) = case x of
    "-a" -> userOptionParser xs (u {allFiles = True}, t)
    "--all" -> userOptionParser xs (u {allFiles = True}, t)
    "-m" -> userOptionParser xs (u {make = True}, t)
    "--make" -> userOptionParser xs (u {make = True}, t)
    _ -> userOptionParserPt2 (x:xs) (u, t)

-- | Parse the remaining special arguments for user options.
userOptionParserPt2 :: [String] -> SpecialParser -> Either String SpecialParser
userOptionParserPt2 [] sp = Right sp
userOptionParserPt2 (x:xs) (u, t) = case x of
    "-i" -> userOptionParser xs (u {ignore = True}, t)
    "--igit" -> userOptionParser xs (u {ignore = True}, t)
    "-d" -> userOptionParser xs (u {delete = True}, t)
    "--del" -> userOptionParser xs (u {delete = True}, t)
    "-hd" -> userOptionParser xs (u {header = True}, t)
    "--header" -> userOptionParser xs (u {header = True}, t)
    _ -> toolOptionParser (x:xs) (u, t)

-- | Parse the special arguments for tool options.
toolOptionParser :: [String] -> SpecialParser -> Either String SpecialParser
toolOptionParser [] sp = Right sp
toolOptionParser (x:xs) (u, t) = case x of
    "-v" -> toolOptionParser xs (u, t {version = True})
    "--version" -> toolOptionParser xs (u, t {version = True})
    "-u" -> toolOptionParser xs (u, t {update = True})
    "--update" -> toolOptionParser xs (u, t {update = True})
    _ -> toolOptionParserPt2 (x:xs) (u, t)

-- | Parse the remaining special arguments for tool options.
toolOptionParserPt2 :: [String] -> SpecialParser -> Either String SpecialParser
toolOptionParserPt2 [] sp = Right sp
toolOptionParserPt2 (x:xs) (u, t) = case x of
    "-fu" -> toolOptionParser xs (u, t {forceUpdate = True})
    "--force-update" -> toolOptionParser xs (u, t {forceUpdate = True})
    "-r" -> toolOptionParser xs (u, t {remove = True})
    "--remove" -> toolOptionParser xs (u, t {remove = True})
    "-h" -> toolOptionParser xs (u, t {help = True})
    "--help" -> toolOptionParser xs (u, t {help = True})
    _ -> Left ("Unknown argument: " ++ x)

-- | Parse the type of the commit (feat, fix, etc.).
typeParser :: [String] -> Either String (String, [String])
typeParser [] = Left "Not enough arguments"
typeParser (x:xs) = Right (x, xs)

-- | Parse the skip arguments: -nt, -nc, -nct, -ntc.
skipParser :: [String] -> Either String (Skip, [String])
skipParser [] = Left "Not next argument"
skipParser ("-nt":xs) = Right (Skip True False, xs)
skipParser ("-nc":xs) = Right (Skip False True, xs)
skipParser ("-nct":xs) = Right (Skip True True, xs)
skipParser ("-ntc":xs) = Right (Skip True True, xs)
skipParser (('-':e):_) = Left ("Unknown argument: " ++ e)
skipParser (x:xs) = Right (Skip False False, x:xs)

-- | Parse the regular arguments; usual giti usage.
commandLineParser :: [String] -> Either String CommandLine
commandLineParser [] = Left "Not enough arguments"
commandLineParser (x:xs) = case skipParser (x:xs) of
        Left err -> Left err
        Right (_, []) -> Left "No type or files specified"
        Right (s, ys) -> case typeParser ys of
            Left err -> Left err
            Right (_, []) -> Left "No files specified"
            Right (t, zs) -> Right (CommandLine s t zs)

-- | Parse the special arguments for user options.
specialParserFunc :: [String] -> SpecialParser -> Either String SpecialParser
specialParserFunc = userOptionParser
