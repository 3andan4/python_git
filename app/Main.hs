module Main (main) where

import Data
import System.Environment (getArgs)
import Parser
import GitOps (gitPorcelain, buildObjects)

-- | Converts a list of lists of strings into a list of tuples.
-- Each inner list is expected to have exactly two elements.
-- The first element of each inner list becomes the first element of the tuple,
-- and the second element becomes the second element of the tuple.
makeTupple :: [[String]] -> [(String, String)]
makeTupple = map (\ x -> (head x, last x))

-- | Filters out the inner lists that do not have exactly two elements,
-- and converts the remaining lists into tuples using the 'makeTupple' function.
tuppleAll :: [[String]] -> [(String, String)]
tuppleAll [] = []
tuppleAll list@(x:xs)
    | length x == 2 = makeTupple list
    | otherwise = tuppleAll xs

-- | The 'parseArgs' function takes a list of command line arguments
-- and parses them using 'commandLineParser'. If parsing is successful,
-- it prints the 'skip', 'tag', and 'files' fields of the resulting command.
-- If parsing fails, it prints an error message.
parseArgs :: [String] -> IO ()
parseArgs args = case commandLineParser args of
    Left err -> putStrLn err
    Right cmd -> putStrLn (show (skip cmd) ++ " " ++ show (tag cmd)
        ++ " " ++ show (files cmd))

-- | The 'buildAndPrintObjects' function takes a string representation
-- of the output from 'git status --porcelain' and builds a list of objects
-- from it using 'buildObjects' and 'tuppleAll'. If building is successful,
-- it prints the resulting list of objects. If building fails, it prints an error message.
buildAndPrintObjects :: String -> IO ()
buildAndPrintObjects porcelain = 
    let objs = buildObjects $ tuppleAll $
            map (words . dropWhile (==' ')) (lines porcelain)
    in case objs of
        Left err -> putStrLn err
        Right items -> print items

-- | The 'main' function gets the command line arguments, parses them,
-- gets the output from 'git status --porcelain', and builds and prints a list of objects from it.
main :: IO ()
main = do
    args <- getArgs
    parseArgs args
    porcelain <- gitPorcelain
    buildAndPrintObjects porcelain