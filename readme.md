PATCHWORK
=========

modes console, graphique et client-serveur
------------------------------------------

La totalité du sujet peut-être retrouvé avec un compte UPEM sur <https://elearning.u-pem.fr/pluginfile.php/45760/mod_resource/content/2/Projet%20Patchwork.pdf>.

L'objectif est de créer un programme fonctionnel en C++ utilisant les concepts de la P.O.O.

L'application devra simuler la réalisation d'une grande fresque murale réalisée à partir de plusieurs dessins d'enfants.

Les enfants (les clients) envoient à leur maîtresse (le serveur) leurs dessins afin de recueillir son avis et ses suggestions d'amélioration. La maîtresse retourne à l'élève son dessin accompagné de ses annotations. La maîtresse peut à tout moment retrouver le dessin d'un enfant.

Les dessins modifiés sont renvoyés à la maîtresse qui, une fois tous les dessins reçus dans leur version définitive, les assemble afin d'en obtenir un plus grand qui constituera la fresque murale.

Une gestion de la *concurrence* devra être mis en place côté serveur.

Il est demandé une version en *mode console* des interactions élèves-maîtresse.

Une seconde version en *mode graphique* pourra être réalisée (affichage d'une palette de formes et couleur, positionnement des points, mode glisser-déposer,  ...).

 * Les dessins sont constitués de formes géométriques élémentaires et colorées : lignes,  polygones,  cercles, ellipses.
 * Les calculs du périmètre et de l'aire sont requis. L'aire d'un polygone quelconque peut être calculée par triangulation.
 * Les formes géométriques peuvent se transformer par homothétie, se déplacer par translation, par rotation, par symétries centrale et axiale.
 * Une image peut également contenir des images de plus petite taille (aire).
 * On souhaite pouvoir ordonner les formes selon plusieurs critères: leur périmètre, leur aire et leur distance à l'origine. Les relations d'ordre devront utiliser la notation <=.
 * Aucun doublon de forme géométrique ne peut exister.
 * Le nombre total de chaque forme géométrique de la grande fresque murale doit pouvoir être déterminé afin de procéder à des statistiques (histogramme, fréquence). Il en est de même pour les couleurs.

Penser à mettre en place une *gestion d'exceptions* lorsque cela s'avère nécessaire.

Vos tests devront être les plus exhaustifs possibles.

Dans le cadre du dialogue client-serveur, un format des images est à définir.
