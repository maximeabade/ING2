import numpy as np
import matplotlib.pyplot as plt



## S est l ensemble des activites
## S = {C1, C2, C3, P, D, S, F}
##

##record des activites et des points associés triés
## donc pour chaque index on a et l'activité et son nombre de points accordés
Activities = ['C1', 'C2', 'C3', 'P', 'D', 'S', 'F']
Rewards = [-2,-2,-2,10,0,1,-1]

##Creation du graphe
mesChemins = []
mesChemins.append(['C1','C2',0.5])
mesChemins.append(['C1','F',0.5])
mesChemins.append(['C2','C3',0.8])
mesChemins.append(['C2','D',0.2])
mesChemins.append(['C3','P',0.4])
mesChemins.append(['C3','S',0.6])
mesChemins.append(['D','D',1])
mesChemins.append(['S','D',1])
mesChemins.append(['F','C1',0.1])
mesChemins.append(['F','F',0.9])


##print(mesChemins)

## Creation de la matrice de transition
## On a une matrice de taille 7x7
## Chaque ligne correspond à une activité
## Chaque colonne correspond à une activité
## Chaque case correspond à la probabilité de passer de l'activité de la ligne à l'activité de la colonne
## On a donc 7x7 = 49 cases
## On va remplir cette matrice avec les valeurs de mesChemins
## On va parcourir mesChemins et remplir la matrice de transition
transition = np.zeros((7,7))
for i in range(len(mesChemins)):
    transition[Activities.index(mesChemins[i][0])][Activities.index(mesChemins[i][1])] = mesChemins[i][2]
    
print(transition)

