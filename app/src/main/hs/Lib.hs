module Lib where

import Foreign.C (CString, newCString)
import System.Directory
import Data.List

-- | export haskell function @chello@ as @hello@.
foreign export ccall "hello" chello :: IO CString

-- | Tiny wrapper to return a CString
chello = do
    dirContents <- getDirectoryContents "/sdcard" >>= return . filter (`notElem` [".", ".."])
    let outputStr = intercalate ", " dirContents
    newCString ("/sdcard 's children : \n" ++ outputStr)
-- chello = newCString "sdgsdgdsg"

-- | Pristine haskell function.
--hello = "Hello from Haskell shareLib by ghc-armv7-android ndk14 supportApi=16"
