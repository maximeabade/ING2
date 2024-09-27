{- |
  Module : Statistic.Huffman
  Description : A module containing specifics for the Huffman compression method
  Maintainer : ???
-}
module Statistic.Huffman (tree) where

import Statistic.EncodingTree
import Data.List (sortOn)
import Statistic.Source

-- New type: PriorityQueueNode (Frequency) (Leaf)
-- Help building the tree
data PriorityQueueNode a = PriorityQueueNode Int (EncodingTree a)
  deriving (Eq, Show)

-- | Huffman tree generation
-- Parameter : List of something
-- Return : Huffman Tree
tree :: Ord a => [a] -> Maybe (EncodingTree a)
tree [] = Nothing
tree symbols = buildHuffmanTree priorityQueueList
  where
    -- Transform txt into list : [(a, Int)]
    lst = orderedCounts (zip symbols (repeat 1))
    priorityQueueList = buildPriorityQueue lst

-- Merge 2 PriorityQueue Nodes into one, summing frequencies
-- Parameters: Priority Queue Node with lowest frequency
-- Return : Merged Priority Queue Node
mergeNodes :: PriorityQueueNode a -> PriorityQueueNode a -> PriorityQueueNode a
mergeNodes (PriorityQueueNode freq1 tree1) (PriorityQueueNode freq2 tree2) =
  PriorityQueueNode (freq1 + freq2) (EncodingNode (freq1 + freq2) tree1 tree2)

-- Transform the original [(Symbol, Occurrence)] list into a list of PriorityQueueNodes
-- Parameter : [(Symbol, Occurrence)] list
-- Return : List of PriorityQueueNode
buildPriorityQueue :: Ord a => [(a, Int)] -> [PriorityQueueNode a]
buildPriorityQueue = map (\(x, f) -> PriorityQueueNode f (EncodingLeaf f x)) . sortOn snd

-- Generate the Huffman Tree by adding each lowest PriorityQueueNode frequency
-- Parameter : PriorityQueueNode list
-- Return : Huffman Tree
buildHuffmanTree :: Ord a => [PriorityQueueNode a] -> Maybe (EncodingTree a)
buildHuffmanTree [node] = Just $ case node of  -- handle last element, tree is done
  PriorityQueueNode _ tree -> tree
buildHuffmanTree (node1 : node2 : rest) =       -- with 2 elements or more
  buildHuffmanTree $ sortOn (\(PriorityQueueNode freq _) -> freq) (mergeNodes node1 node2 : rest) -- sort on the frequency with the new element merged
buildHuffmanTree _ = Nothing   -- Empty tree returns Maybe Nothing
