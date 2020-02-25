## La bibliothéque CImg

Pour visualiser les formes, on utilise la librairie /CImg/
[[http://cimg.eu/]]. La librairie est composée d'un seul fichier
CImg.h qu'il faut inclure dans notre programme.

La documentation de la librairie est fourni dans
[docs/CImg_reference.pdf](docs/CImg_reference.pdf).


# Noms
### Nassim ARAB
### Mohamed CHABANE


# Description du travail:
Dans ce TP nous avons mise en place une hiérarchie de classe `Shape` et des classes `Circle`, `Rectangle`, `Triangle` et `ShapeGroup` qui héritent de la classe `Shape`. Avec la possibilité de créer, séléctionner, déplacer et supprimer les formes.
Nous avons aussi rajouter des tests pour les fonction move, select et is_Inside 
Pour éxécuter le programme il suffit de lancer la commande `make` puis `./shape_main` et les tests avec `./shape_test`

## Question 1 : Les formes
- la fonction `draw` dois être virtuelle car elle est implémentée différenment pour chaque forme ainsi que la fonction `move` afin de pouvoir déplacer les forme au milieu.

## Question 2 : Mémoriser les formes
- dessiner les forme avec la foncton `draw`.

## Question 3 : Déplacer une forme
- la fonction `is_inside()` est virtuelle.
- les fonction `select()` et `is_selected()` ne sont pas virtuelle.

## Question 4 : Créer, deplacer, effacer des formes
- Pour créer une forme on utilisent les bouton `r`,`t`,`c` respictivement pour rectangle, triangle et cercle.
- Pour déplacer une forme il faut la séléctionné puis on clic sur `m`.
- Pour supprimer une forme il faut la séléctionné et clic sur `d`.

## Question 5 : Regrouper des formes
- Pour créer un groupe on utilise la touche `g`.
- Pour décomposer un groupe on utilise la touche `u`.
- Pour supprimer un groupe on utilise la touche `d`.
