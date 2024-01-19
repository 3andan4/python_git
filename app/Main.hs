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

main :: IO ()
main = do
    args <- getArgs
    case commandLineParser args of
        Left err -> putStrLn err
        Right cmd -> putStrLn (show (skip cmd) ++ " " ++ show (tag cmd) ++ " " ++ show (files cmd))
    porcelain <- gitPorcelain
    let objs = buildObjects $ tuppleAll $ map (words . dropWhile (==' ')) (lines porcelain)
    case objs of
        Left err -> putStrLn err
        Right items -> print items

