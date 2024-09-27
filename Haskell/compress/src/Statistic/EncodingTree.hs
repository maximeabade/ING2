{- |
  Module : Statistic.EncodingTree
  Description : A module representing a binary tree for binary encoding
  Maintainer : LATRY Ugo
-}
module Statistic.EncodingTree(EncodingTree(..), isLeaf, count, has, encode, decodeOnce, decode, meanLength, compress, uncompress) where

import Statistic.Bit

data EncodingTree a = EncodingNode Int (EncodingTree a) (EncodingTree a)
                    | EncodingLeaf Int a
  deriving (Eq, Show)

-- | Is the encoding a mere leaf ?
isLeaf :: EncodingTree a -> Bool
isLeaf (EncodingLeaf _ _) = True
isLeaf  _                 = False

-- | The length of the underlying source
count :: EncodingTree a -> Int
count (EncodingLeaf cnt _  ) = cnt
count (EncodingNode cnt _ _) = cnt

-- | Search for symbol in encoding tree
has :: Eq a => EncodingTree a -> a -> Bool
_ `has` _ = False
tree `has` symbol = case tree of
  EncodingLeaf _ s -> s == symbol
  EncodingNode _ l r -> l `has` symbol || r `has` symbol

-- | Computes the binary code of symbol using encoding tree
-- If computation is not possible, returns `Nothing`.
encode :: Eq a => EncodingTree a -> a -> Maybe [Bit]
encode tree symbol = case tree of
  EncodingLeaf _ s -> 
    if s == symbol then Just [] 
    else Nothing
  EncodingNode _ l r -> 
    if l `has` symbol then (Zero:) <$> encode l symbol
    else if r `has` symbol then (One:) <$> encode r symbol
    else Nothing

-- | Computes the first symbol from list of bits using encoding tree and also returns the list of bits still to process
-- If computation is not possible, returns `Nothing`.
decodeOnce :: EncodingTree a -> [Bit] -> Maybe (a, [Bit])
decodeOnce tree bits = case tree of
  EncodingLeaf _ s -> Just (s, bits)
  EncodingNode _ l r -> case bits of
    [] -> Nothing
    (Zero:rest) -> decodeOnce l rest
    (One:rest) -> decodeOnce r rest

-- | Computes list of symbols from list of bits using encoding tree
decode :: EncodingTree a -> [Bit] -> Maybe [a]
decode tree bits = case decodeOnce tree bits of
  Nothing -> Nothing
  Just (symbol, rest) -> case decode tree rest of
    Nothing -> Just [symbol]
    Just symbols -> Just (symbol:symbols)

-- | Mean length of the binary encoding
meanLength :: EncodingTree a -> Double
meanLength tree = fromIntegral (sumLengths tree) / fromIntegral (count tree)
  where
    sumLengths (EncodingLeaf cnt _) = cnt
    sumLengths (EncodingNode cnt l r) = cnt + sumLengths l + sumLengths r

-- | Compress method using a function generating encoding tree and also returns generated encoding tree
compress :: Eq a => ([a] -> Maybe (EncodingTree a)) -> [a] -> (Maybe (EncodingTree a), [Bit])
compress genEncodingTree input = case genEncodingTree input of
  Nothing -> (Nothing, [])
  Just encodingTree -> case traverse (encode encodingTree) input of
    Nothing -> (Nothing, [])
    Just encodedBits -> (Just encodingTree, concat encodedBits)

-- | Uncompress method using previously generated encoding tree
-- If input cannot be uncompressed, returns `Nothing`
uncompress :: (Maybe (EncodingTree a), [Bit]) -> Maybe [a]
uncompress (Nothing, _) = Nothing
uncompress (Just encodingTree, bits) = decode encodingTree bits
