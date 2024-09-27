module LZ.LZW(compress, uncompress) where
import Data.Char (chr)
import Data.List (isPrefixOf)
import Data.Maybe (fromMaybe)
import LZ.Dictionaries (empty, ascii, zeroAsChar)

-- | Fonction de compression LZW
compress :: String -> [Int]
compress str = compress' str initDict []

-- | Dictionnaire initial
initDict :: [(String, Int)]
initDict = zip (map return ['\0'..'\xFF']) [0..255]

-- | Fonction de compression récursive
compress' :: String -> [(String, Int)] -> [Int] -> [Int]
compress' "" _ encoded = encoded
compress' str dict encoded =
  let
    (prefix, rest) = findLongestPrefix str dict
    (Just newEntry) = lookup prefix dict
    newEncoded = encoded ++ [newEntry]
    newDict = if null rest
              then dict
              else (prefix ++ [head rest], length dict) : dict
  in compress' rest newDict newEncoded

-- | Fonction pour trouver la plus longue chaîne préfixée dans un dictionnaire
findLongestPrefix :: String -> [(String, Int)] -> (String, String)
findLongestPrefix str dict = go str ""
  where
    go [] prefix = (prefix, [])
    go (c:cs) prefix = case lookup (prefix ++ [c]) dict of
      Just _ -> go cs (prefix ++ [c])
      Nothing -> (prefix, c:cs)

-- | LZW uncompress method
-- Si l'entrée ne peut pas être décompressée, retourne `Nothing`


-- Convertir le dictionnaire ascii en [(Int, [Char])]
asciiDict :: [(Int, [Char])]
asciiDict = zip [0..255] (map return ['\0'..'\xFF'])


--- Décompression d'une liste d'entiers en chaîne de caractères
uncompress :: [Int] -> IO (Maybe String)
uncompress [] = do
  putStrLn "Décompression terminée avec succès."
  return $ Just ""

uncompress code = go 1 code asciiDict ""
  where
    go _ [] _ output = do
      putStrLn "Décompression terminée avec succès."
      return $ Just output
    go step (codeNr:rest) dict output = do
      putStrLn $ "Étape " ++ show step ++ ":"
      putStrLn $ "  Code actuel: " ++ show codeNr
      case lookup codeNr dict of
        Just phrase -> do
          putStrLn $ "  Phrase trouvée dans le dictionnaire: " ++ show phrase
          case rest of
            [] -> go (step + 1) rest dict (output ++ phrase)
            (nextCode:_) -> do
              let nextPhrase = fromMaybe [] (lookup nextCode dict)
              let newEntry = (length dict, phrase ++ [head nextPhrase])
              putStrLn $ "  Ajout d'une nouvelle entrée au dictionnaire: " ++ show newEntry
              go (step + 1) rest (dict ++ [newEntry]) (output ++ phrase)
        Nothing -> do
          putStrLn $ "  Code non trouvé dans le dictionnaire."
          case rest of
            [] -> do
              putStrLn "  Impossible de décompresser la liste d'entiers."
              return Nothing
            (nextCode:_) -> do
              let nextPhrase = fromMaybe [] (lookup nextCode dict)
              let newEntry = (length dict, nextPhrase)
              putStrLn $ "  Ajout d'une nouvelle entrée au dictionnaire: " ++ show newEntry
              go (step + 1) rest (dict ++ [newEntry]) (output ++ nextPhrase)
