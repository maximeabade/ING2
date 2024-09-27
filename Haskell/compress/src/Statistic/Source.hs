module Statistic.Source where

import Data.List (sortBy)
import Data.Map (Map, fromList, toList)

-- Function to count symbol occurrences
occurrences :: Ord a => [a] -> Map a Int
occurrences message =
  let charCounts = map (\c -> (c, length (filter (== c) message))) (support message)
  in fromList charCounts

-- Function to remove duplicates from a list
support :: Ord a => [a] -> [a]
support = foldr (\x xs -> if x `elem` xs then xs else x : xs) []

-- | List of occurrences ordered by count
orderedCounts :: Ord a => [(a, Int)] -> [(a, Int)]
orderedCounts elements =
  sortBy (\(w1, count1) (w2, count2) -> compare count1 count2) elements

-- Function to calculate Shannon entropy
shannonEntropy :: Map a Int -> Double
shannonEntropy counts =
  let total = fromIntegral (sum (map snd (toList counts)))  -- Total count of symbols
      probabilities = map (\(_, count) -> fromIntegral count / total) (toList counts)
      log2Base = logBase 2  -- Or `log2` if available
      entropy = sum $ map (\p -> if p == 0 then 0 else -p * log2Base p) probabilities
  in entropy

-- Example usage (assuming main is defined elsewhere)
main = do
  let message = "je comprends pas"
  let counts = occurrences message
  print counts
  let result = orderedCounts (toList counts)
  print result
  let entropy = shannonEntropy counts
  print entropy
