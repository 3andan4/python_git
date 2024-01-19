module Data (
    Skip(..),
    Utility(..),
    Tool(..),
    SpecialParser,
    emptySpecialParser,
    CommandLine(..),
    gitState,
    FileStatus(..)
    ) where

data Skip = Skip {
  title :: Bool,
  commit :: Bool
} deriving (Show)


-- SpecialParser

data Utility = Utility {
  allFiles :: Bool,
  make :: Bool,
  ignore :: Bool,
  delete :: Bool,
  header :: Bool
} deriving (Show)

data Tool = Tool {
  version :: Bool,
  update :: Bool,
  forceUpdate :: Bool,
  remove :: Bool,
  help :: Bool
} deriving (Show)

data CommandLine = CommandLine {
  skip :: Skip,
  tag :: String,
  files :: [String]
} deriving (Show)

type SpecialParser = (Utility, Tool)

emptySpecialParser :: SpecialParser
emptySpecialParser = (Utility False False False False False,
    Tool False False False False False)

gitState :: String -> Either String String
gitState "M" = Right "modified"
gitState "A" = Right "added"
gitState "D" = Right "deleted"
gitState "R" = Right "renamed"
gitState "C" = Right "copied"
gitState "U" = Right "unmerged"
gitState "?" = Right "untracked"
gitState "!" = Right "ignored"
gitState _ = Left "Unknown state"

data FileStatus = FileStatus {
  status :: String,
  file :: String
}

instance Show FileStatus where
    show (FileStatus s f) = f ++ ": " ++ s
