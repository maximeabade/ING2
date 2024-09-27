# RECHERCHE DES NOMBRES PREMIERS DANS UN INTERVALLE 

## Objectif
On veut chercher tous les nombres premiers dans un intervalle passé en paramètre.

Pour ce faire, on relègue la tâche de recherche à un nombre de processus défini par l'utilisateur. Chaque processus se voit attribuer un intervalle de recherche. Les processus communiquent entre eux pour éviter de chercher des nombres déjà trouvés.

## Compilation
Pour compiler le programme, il suffit de lancer la commande 
``` gcc nombrePremier.c -o exec -lm ```

## Utilisation
Pour lancer le programme, il suffit de lancer la commande 
``` ./exec ```
et se laisser guider par les instructions afichées.