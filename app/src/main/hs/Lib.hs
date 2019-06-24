module Lib where

import Foreign.C (CString, newCString)
import qualified Data.ByteString.Lazy.Char8 as BLC

-- | export haskell function @chello@ as @hello@.
foreign export ccall "hello" chello :: IO CString

-- | Tiny wrapper to return a CString
chello = newCString $ show $ readPrice $ BLC.pack "19.25"

-- | Pristine haskell function.
hello = "Hello from Haskell, ghc-v8.6.5 minSupportAPI=16 static"


readPrice :: BLC.ByteString -> Maybe Int
readPrice str =
    case BLC.readInt str of
      Nothing             -> Nothing
      Just (dollars,rest) ->
        case BLC.readInt (BLC.tail rest) of
          Nothing           -> Nothing
          Just (cents,more) ->
            Just (dollars * 100 + cents)
