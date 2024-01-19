module Main (main) where

import Data
import System.Environment (getArgs)
import Parser
import GitOps (gitPorcelain, buildObjects)

--  [["M", "app/Main.hs"], ["M", "src/Data.hs"]] => [("M", "app/Main.hs"), ("M", "src/Data.hs")]
makeTupple :: [[String]] -> [(String, String)]
makeTupple = map (\ x -> (head x, last x))

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

