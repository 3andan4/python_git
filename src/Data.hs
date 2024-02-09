-------------------------------------------------------------------------------
-- |
-- Module: Data
-- Description: Contains the data types used in the application
-- License: MIT
-- Maintainer: maxoulebesnerais@gmail.com
-- Stability: Experimental
-- Portability: POSIX
--
-- Contains the data types used in the application
--
-------------------------------------------------------------------------------

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

-- | data type that represents the skip arguments
data Skip = Skip {
  title :: Bool,
  commit :: Bool
} deriving (Show)


-- SpecialParser
-- | data type that represents the special arguments
data Utility = Utility {
  allFiles :: Bool,
  make :: Bool,
  ignore :: Bool,
  delete :: Bool,
  header :: Bool
} deriving (Show)

-- | data type that represents the tools arguments
data Tool = Tool {
  version :: Bool,
  update :: Bool,
  forceUpdate :: Bool,
  remove :: Bool,
  help :: Bool
} deriving (Show)

-- | data type that represents the command line arguments
data CommandLine = CommandLine {
  skip :: Skip,
  tag :: String,
  files :: [String]
} deriving (Show)

-- | data type that represents the special arguments parser (Utility, Tool)
type SpecialParser = (Utility, Tool)

-- | create an empty special parser
emptySpecialParser :: SpecialParser
emptySpecialParser = (Utility False False False False False,
    Tool False False False False False)

-- | Convert a git state to a human readable string
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

-- | data type that represents the file status
data FileStatus = FileStatus {
  status :: String,
  file :: String
}

-- | Show instance for the FileStatus data type
instance Show FileStatus where
    show (FileStatus s f) = f ++ ": " ++ s
