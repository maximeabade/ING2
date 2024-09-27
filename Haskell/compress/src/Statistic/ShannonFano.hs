{- |
  Module : Statistic.ShannonFano
  Description : A module containing specifics for the Shannon-Fano compression method
  Maintainer : ???
-}
module Statistic.ShannonFano(tree) where

import Statistic.EncodingTree
import Data.List (sortOn)
import Statistic.Source



-- | Function to calculate the Shannon-Fano encoding tree
tree :: Ord a => [a] -> Maybe (EncodingTree a)
tree [] = Nothing
tree symbols = buildTree (sortOn snd lst)
  where
    lst = orderedCounts (map (\x -> (x, 1)) symbols)
-- Helper function to build the Shannon-Fano encoding tree
buildTree :: Ord a => [(a, Int)] -> Maybe (EncodingTree a)
buildTree [] = Nothing
buildTree [(x, freq)] = Just (EncodingLeaf freq x)
buildTree symbols =
  let totalFreq = sum (map snd symbols)
      (group1, group2) = splitClosest totalFreq 0 symbols
  in do
    tree1 <- buildTree group1
    tree2 <- buildTree group2
    return $ EncodingNode totalFreq tree1 tree2

-- Helper function to split the list into two groups with approximately equal frequencies
splitClosest :: Ord a => Int -> Int -> [(a, Int)] -> ([(a, Int)], [(a, Int)])
splitClosest _ _ [] = ([], [])
splitClosest totalFreq currentFreq ((x, freq):rest)
  | currentFreq + freq <= totalFreq `div` 2 =
      let (group1, group2) = splitClosest totalFreq (currentFreq + freq) rest
      in ((x, freq):group1, group2)
  | otherwise = ([], (x, freq):rest)

