# Chorus



## Granulateur

La synthèse granulaire est une technique de synthèse sonore consistant en la création d'un signal sonore complexe en combinant des grains, c'est-à-dire des échantillons sonores de l'ordre de la milliseconde (10 à 100 ms). On contrôle globalement la densité des grains, leur hauteur, leur longueur, leur enveloppe, leur spatialisation, leur phase, le plus souvent sous la forme d'intervalles dans lesquels le programme de synthèse choisit des valeurs de manière aléatoire. Le son obtenu est une sorte de nuage, composé de l'ensemble des grains.

## Algorithme

On va utiliser un granulateur pour créer un effet entre le chorus et le shimmer / reverb.

À chaque tick, un certain nombre de grains vont être détruits et remplis avec un nouvel échantillon du signal. La densité des grains définie à quelle fréquence ils sont crées, leur longueur est tirée aléatoirement.
Pour chaque block, on élit un certain nombre de grains parmis ceux en stock, que l'on somme en sortie.

Le remplissage des grains se fait en copiant une portion du signal d'entrée + feedback.

Il est possible d'ajouter une modulation sur la vitesse de lecture des grains. (fonction du délai ??)

