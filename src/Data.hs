module Data (
    Skip(..),
    Utility(..),
    Tool(..),
    SpecialParser,
    emptySpecialParser,
    CommandLine(..)
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

gitState :: String -> String
gitState "M" = "modified"
gitState "A" = "added"
gitState "D" = "deleted"
gitState "R" = "renamed"
gitState "C" = "copied"
gitState "U" = "unmerged"
gitState "?" = "untracked"
gitState "!" = "ignored"
gitState _ = []

data FileStatus = FileStatus {
  status :: String,
  file :: String
} deriving (Show)
