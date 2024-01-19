module Parser (
    specialParserFunc,
    typeParser,
    skipParser,
    commandLineParser
    ) where

import Data

-- | Parse the special arguments
specialParserFunc :: [String] -> SpecialParser -> Either String SpecialParser
specialParserFunc [] sp = Right sp
specialParserFunc (x:xs) (u, t) = case x of
    "-a" -> specialParserFunc xs (u {allFiles = True}, t)
    "--all" -> specialParserFunc xs (u {allFiles = True}, t)
    "-m" -> specialParserFunc xs (u {make = True}, t)
    "--make" -> specialParserFunc xs (u {make = True}, t)
    "-i" -> specialParserFunc xs (u {ignore = True}, t)
    "--igit" -> specialParserFunc xs (u {ignore = True}, t)
    "-d" -> specialParserFunc xs (u {delete = True}, t)
    "--del" -> specialParserFunc xs (u {delete = True}, t)
    "-hd" -> specialParserFunc xs (u {header = True}, t)
    "--header" -> specialParserFunc xs (u {header = True}, t)
    -- Tools
    "-v" -> specialParserFunc xs (u, t {version = True})
    "--version" -> specialParserFunc xs (u, t {version = True})
    "-u" -> specialParserFunc xs (u, t {update = True})
    "--update" -> specialParserFunc xs (u, t {update = True})
    "-fu" -> specialParserFunc xs (u, t {forceUpdate = True})
    "--force-update" -> specialParserFunc xs (u, t {forceUpdate = True})
    "-r" -> specialParserFunc xs (u, t {remove = True})
    "--remove" -> specialParserFunc xs (u, t {remove = True})
    "-h" -> specialParserFunc xs (u, t {help = True})
    "--help" -> specialParserFunc xs (u, t {help = True})
    _ -> Left ("Unknown argument: " ++ x)

-- | Parse the type of the commit (feat, fix, etc.)
typeParser :: [String] -> Either String (String, [String])
typeParser [] = Left "Not enough arguments"
typeParser (x:xs) = Right (x, xs)

-- | Parse the skip arguments: -nt, -nc, -nct, -ntc
skipParser :: [String] -> Either String (Skip, [String])
skipParser [] = Left "Not next argument"
skipParser (x:xs) = case x of
    "-nt" -> Right (Skip True False, xs)
    "-nc" -> Right (Skip False True, xs)
    "-nct" -> Right (Skip True True, xs)
    "-ntc" -> Right (Skip True True, xs)
    _ -> Right (Skip False False, x:xs)

-- | Parse the regular arguments; usual giti usage
commandLineParser :: [String] -> Either String CommandLine
commandLineParser [] = Left "Not enough arguments"
commandLineParser (x:xs) = case skipParser (x:xs) of
        Left err -> Left err
        Right (_, []) -> Left "No type or files specified"
        Right (s, ys) -> case typeParser ys of
            Left err -> Left err
            Right (_, []) -> Left "No files specified"
            Right (t, zs) -> Right (CommandLine s t zs)
