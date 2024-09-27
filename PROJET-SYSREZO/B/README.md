# ENVOIS DE MESSAGES - ARCHITECTURE CLIENT/SERVEUR

## Messages

### Client -> Serveur
Cette partie concerne l'envoi de String simple du client vers le serveur.
On a défini une taille maximale de message de 256 caractères, typique de ce genre d'application.

On a fait le choix de ne pas envoyer de message vide, pour éviter de surcharger le serveur.
De plus, pour l'envoi de message, on a choisi de voir ça comme une file d'attente, où le serveur traite les messages les uns après les autres.

### Serveur -> Client

On renvoie la String du client à l'envers. On a choisi de renvoyer la String à l'envers pour montrer que le serveur a bien reçu le message et qu'il a bien été traité.
On affiche ensuite cette String inversée côté client.

### Compilation et exécution
#### Compilation
Pour compiler ces éléments, rentrer la commande suivante dans le terminal :
```gcc client.c -o client && gcc serveur.c -o serveur```, créant les deux exécutables nécessaires à l'exécution du programme.

#### Exécution
Pour exécuter le programme, il faut penser à lancer les deux exécutables dans deux terminaux différents.
Pour lancer le serveur, rentrer la commande suivante dans le terminal :
```./serveur```
Pour lancer le client, rentrer la commande suivante dans un autre terminal :
```./client```


## Calculs
### Client -> Serveur
On demande à l'utilisateur de rentrer un calcul simple. La structure imposée est OPERATION OPERANDE1 OPERANDE2; le calcul sera donc traité en mathématiques comme étant OPERANDE1 OPERATION OPERANDE2.
Par exemple, pour additionner 2 et 3, on rentrera + 2 3.

Cette requête est envoyée au serveur.

### Serveur -> Client
Le serveur reçoit le calcul demandé par le client.
La définition de la structure ```operation``` est telle qu'elle compte dans ses champs le résultat. Ce résultat est calculé côté serveur et affiché.
Une fois le calcul effectué, le serveur renvoie le résultat au client, qui a son tour l'affiche.

### Compilation et exécution
#### Compilation
Pour compiler ces éléments, rentrer la commande suivante dans le terminal :
```gcc math_client.c -o mClient && gcc math_serveur.c -o mServeur```, créant les deux exécutables nécessaires à l'exécution du programme.

#### Exécution
Pour exécuter le programme, il faut penser à lancer les deux exécutables dans deux terminaux différents.
Pour lancer le serveur, rentrer la commande suivante dans le terminal :
```./mServeur```
Pour lancer le client, rentrer la commande suivante dans un autre terminal :
```./mClient```
