module GitOps (
    gitPorcelain,
    getState,
    buildObjects
    ) where

import Data
import System.Exit (ExitCode(..))
import System.Process (readProcessWithExitCode)

gitPorcelain :: IO String
gitPorcelain = do
    (exitCode, stdout, stderr) <- readProcessWithExitCode "git" ["status", "--porcelain"] ""
    case exitCode of
        ExitSuccess -> return stdout
        ExitFailure e -> return ("git status failed with exit code " ++ show e ++ ":\n" ++ stderr)

getState :: [Char] -> Either String String
getState [] = Right []
getState [x] = case gitState [x] of
    Left e -> Left e
    Right s -> Right s
getState (x:xs) = case gitState [x] of
    Left e -> Left e
    Right s -> case getState xs of
        Left e -> Left e
        Right ss -> do
            if s == ss
                then Right s
                else Right (s ++ " then " ++ ss)

buildObjects :: [(String, String)] -> Either String [FileStatus]
buildObjects [] = Right []
buildObjects [(x, y)] = case getState x of
    Left e -> Left e
    Right s -> Right [FileStatus s y]
buildObjects ((x, y):xs) = case getState x of
    Left e -> Left e
    Right s -> case buildObjects xs of
        Left e -> Left e
        Right ss -> Right (FileStatus s y : ss)
