{- |
  Module      : RLE
  Description : An implementation of the run-length encoding method
  Maintainer  : ???
-}

module RLE(compress, uncompress) where

import qualified Data.List as List

-- | RLE compress method
compress :: Eq a => [a] -> [(a, Int)]
compress = map(\a -> (head a, length a)) . List.group

-- | RLE uncompress method
-- If input cannot be uncompressed, returns `Nothing`
uncompress :: [(a, Int)] -> Maybe [a]
uncompress xs
  | all (\(_, n) -> n > 0) xs = Just $ concatMap (\(a, n) -> replicate n a) xs
  | otherwise = Nothing