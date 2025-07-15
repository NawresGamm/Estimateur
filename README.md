# Estimateur

Traduction et les solutions d'optimisation
1ere solution d'otimisation :
Que se passe-t-il sans référence ?
Si tu écris :
double mhat_NW0(double x, std::vector<double> X, ...) Ici, X est passé par valeur donc le compilateur fait une copie complète du vecteur X.
Si X a 1 million d’éléments, ça duplique toute la mémoire.
C’est lent et inutile, car on veut seulement lire X, pas le modifier.
La solution : passer par référence
Si tu écris :
double mhat_NW0(double x, std::vector<double>& X, ...) donc
Pas de copie.La fonction utilise directement l’objet original.
Mais problème possible : Sans const, la fonction pourrait modifier X par erreur. Encore mieux : const std::vector<double>& X
Si tu écris :
double mhat_NW0(double x, const std::vector<double>& X, ...)
Donc : Pas de copie (→ rapide, économe en mémoire). Lecture seule garantie (→ sûr) : la fonction n’a pas le droit de modifier X. Clarté pour les autres développeurs : on promet de ne pas toucher X.

2 eme solution d'optimisation :
size_t est le type standard pour les tailles et les indices en C++.
Il est non signé, donc pas de valeur négative possible.
Il évite les warnings et les erreurs de comparaison signed/unsigned.

3 eme solution 
Compiler avec -O2 ou -O3 (comme dans g++ -O3 -o myprog myprog.cpp)

Pourquoi? :
Les options -O1, -O2, -O3 sont des niveaux d’optimisation que tu donnes au compilateur (comme g++ ou clang). Elles disent au compilateur : « essaie de rendre ce code plus rapide à l’exécution ».

* -O1 = optimisation légère
* -O2 = optimisation équilibrée
* -O3 = optimisation agressive (fait tout ce que -O2 fait + encore plus)
En gros, tu demandes au compilateur de réfléchir et réécrire ton code à sa façon, pour qu’il s’exécute plus efficacement.
Exemples d’optimisations faites par -O2/-O3
Voici ce que le compilateur peut faire (automatiquement !) :
Suppression du code mort : Supprime le code inutile ou les variables inutilisées.
Inlining de fonctions : Remplace l’appel à une petite fonction par son contenu direct (évite l’overhead d’appel).
Boucles déroulées (loop unrolling) : Accélère les boucles en traitant plusieurs éléments par itération.

Ex :
au lieu de :
for (i = 0; i < 1000; i++) A\[i] += 1;

il peut faire :
for (i = 0; i < 1000; i += 4) {
A\[i] += 1; A\[i+1] += 1; A\[i+2] += 1; A\[i+3] += 1;
}
Vectorisation automatique : Utilise les instructions SIMD (comme SSE, AVX) du processeur pour faire plusieurs calculs en une seule instruction.
Mise en cache optimisée : Réorganise le code pour que les accès à la mémoire soient plus "cache-friendly", donc plus rapides.
Élimination des calculs redondants : Déplace ou supprime les calculs qui peuvent être faits une seule fois au lieu d’à chaque tour de boucle.
Pourquoi on dit « le compilateur vectorise les boucles » ?
Parce que si ton code est bien écrit (simple, sans branchements complexes), le compilateur détecte des boucles avec des opérations indépendantes — et il les réécrit pour utiliser les instructions SIMD du processeur.
Exemple : au lieu de faire :
Y\[0] = A\[0] + B\[0]
Y\[1] = A\[1] + B\[1]
Y\[2] = A\[2] + B\[2]
Y\[3] = A\[3] + B\[3]
Il utilise une seule instruction AVX qui fait les 4 additions en parallèle ! 
Quand utiliser -O2 ou -O3 ?

* Pour le développement normal → -O2 est très bien (rapide et stable)
* Pour les calculs lourds (numériques, machine learning, etc.) → -O3 peut accélérer davantage

Commande typique :

g++ -O3 -march=native -o mon\_programme mon\_code.cpp

* -O3 : optimisation agressive
* -march=native : permet d’utiliser toutes les instructions SIMD disponibles sur ton processeur

