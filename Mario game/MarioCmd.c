#include <stdio.h>    // Bibliothèque pour l'affichage (printf) et la lecture (scanf)
#include <stdlib.h>   // Bibliothèque pour la génération de nombres aléatoires (rand, srand) et la sortie du programme (exit)
#include <time.h>     // Bibliothèque pour utiliser l'heure de l'ordinateur, notamment pour initialiser le hasard

// --- Déclaration des prototypes des fonctions ---
// Permet au programme de savoir que ces fonctions existent avant de les lire en détail.
int init_carte (int tab [20][20]);
int affiche_carte (int tab [20][20], int pos [2]);
int deplace_personnage (int tab [20][20], int pos [2]);
int delai (int s); // Fonction utilitaire pour faire une pause

// --- Raccourcis pour les couleurs dans le terminal ---
// Ces codes spéciaux (séquences d'échappement ANSI) permettent de changer la couleur du texte.
#define cd "\033[0m" // Couleur par défaut (blanc/gris)
#define cr "\033[31m" // Rouge
#define cv "\033[32m" // Vert
#define cj "\033[33m" // Jaune
#define cb "\033[34m" // Bleu
#define cm "\033[35m" // Magenta
#define cc "\033[36m" // Cyan

/**
 * @brief Prépare le terrain de jeu.
 * * Remplit la carte de 20x20 avec des éléments (herbe, arbres, rochers...)
 * de manière aléatoire. Elle construit aussi un "donjon" spécial gardé
 * par des monstres et place une clé au hasard.
 * * @param tab Le tableau 20x20 représentant la carte.
 */
int init_carte (int tab [20][20]) {
	int i, j, n, d, p;

	// --- Remplissage aléatoire de la carte ---
	for (i = 0 ; i < 20 ; i++) {
		for (j = 0 ; j < 20 ; j++) {
			n = rand() % 1000; // Génère un nombre entre 0 et 999 pour décider quel élément placer
			
			// Distribution des éléments par probabilité
			if (0 < n && n < 900) { n = 0; }        // 90% de chance d'avoir de l'herbe (0)
			else if (900 < n && n < 920) { n = 1; }  // 2% de chance d'avoir une fleur (1)
			else if (920 < n && n < 935) { n = 2; }  // 1.5% de chance d'avoir un arbre (2)
			else if (935 < n && n < 950) { n = 3; }  // 1.5% de chance d'avoir un rocher (3)
			else if (950 < n && n < 970) { n = 5; }  // 2% de chance d'avoir de l'or (5)
			else if (970 < n && n < 985) { n = 7; }  // 1.5% de chance d'avoir un piège (7)
			else { n = 8; }                         // 1.5% de chance d'avoir un monstre (8)
			
			tab [i][j] = n; // Place l'élément sur la carte
		}
	}
	tab [0][0] = 0; // Le point de départ du joueur est toujours une case d'herbe sûre.

	// --- Création du donjon ---
	d = rand() % 15; // Coordonnée de départ (ligne) du donjon, pour qu'il ne sorte pas de la carte.
	
	// Place des monstres (ou de l'herbe) en guise de première ligne de défense avant le donjon.
	for (i = d ; i <= d+5 ; i++) {
		if (rand() % 2 == 1) { tab [i][15] = 8; } else { tab [i][15] = 0; }
	}

	// Construit les murs du donjon avec des rochers (3)
	for (i = d+1 ; i <= d+4 ; i++) {
		tab [i][16] = 3; // Mur gauche
		tab [i][19] = 3; // Mur droit
	}
    for (j = 17; j <= 18; j++) {
        tab[d+1][j] = 3; // Mur du haut
        tab[d+4][j] = 3; // Mur du bas
    }
	
	// Place le trésor (4 pièces d'or) au cœur du donjon.
	for (i = d+2 ; i <= d+3 ; i++){
		for (j = 17 ; j <= 18 ; j++) {
			tab [i][j] = 5;
		}
	}

	// Crée une entrée pour le donjon
	p = d + 2 + rand() % 2; // Choisit une position aléatoire pour la porte sur le mur gauche.
	tab [p][15] = 0;        // S'assure que la case devant la porte est libre.
	tab [p][16] = 6;        // Place la porte (6)

	// Place une clé (4) quelque part sur la carte (en dehors de la zone du donjon).
	tab [1 + rand() % 19][1 + rand() % 14] = 4;
    return 0;
}

/**
 * @brief Affiche la carte et la position du joueur.
 * * Parcourt le tableau et affiche chaque élément avec son symbole et sa couleur.
 * Le joueur est représenté par un 'X' vert.
 * * @param tab La carte du jeu.
 * @param pos Les coordonnées [x, y] du joueur.
 */
int affiche_carte (int tab [20][20], int pos [2]) {
	int i, j;
	for (i = 0 ; i < 20 ; i++) { // Parcours des lignes
		for (j = 0 ; j < 20 ; j++) { // Parcours des colonnes
			if (pos [0] == j && pos [1] == i) {
				printf("%sX %s", cv, cd); // Affiche le joueur 'X' en vert à sa position
			}
			else {
				// Utilise un switch pour afficher le bon symbole selon le numéro dans la case
				switch (tab [i][j]) {
					case 0 : printf("%s. %s", cv, cd); break; // Herbe
					case 1 : printf("%sF %s", cc, cd); break; // Fleur
					case 2 : printf("A "); break;             // Arbre
					case 3 : printf("R "); break;             // Rocher
					case 4 : printf("%sC %s", cm, cd); break; // Clé
					case 5 : printf("%sO %s", cj, cd); break; // Or
					case 6 : printf("%s0 %s", cm, cd); break; // Porte
					case 7 : printf("%sP %s", cr, cd); break; // Piège
					case 8 : printf("%sM %s", cr, cd); break; // Monstre
				}
			}
		}
		printf("\n"); // Nouvelle ligne à la fin de chaque rangée de la carte
	}
    return 0;
}

/**
 * @brief Gère les déplacements du joueur.
 * * Demande au joueur où il veut aller, vérifie si le mouvement est possible
 * (pas de sortie de carte, pas d'obstacle) et met à jour sa position.
 * * @param tab La carte du jeu.
 * @param pos Les coordonnées [x, y] du joueur (qui seront modifiées).
 * @return La valeur de la case sur laquelle le joueur arrive, ou -1 si le joueur quitte.
 */
int deplace_personnage (int tab [20][20], int pos [2]) {
	int r = 1, x = pos [0], y = pos [1];

	while (r != 0) {
		printf("Ou voulez vous aller ? (8=haut, 2=bas, 6=droite, 4=gauche, 0=quitter)\n");

		// Vérifie si l'entrée est bien un nombre pour éviter un crash.
		if(scanf("%d", &r) != 1) {
			printf("%sERREUR, commande invalide. Le jeu va s'arrêter.%s\n", cr, cd);
			delai (3);
			exit(EXIT_FAILURE); // Termine le programme en cas d'erreur critique
		}

		switch (r) {
			case 8 : // HAUT
				if (y == 0 || tab [y-1][x] == 2 || tab [y-1][x] == 3) { // Bloque si bordure ou obstacle
					printf("%sObstacle !%s\n", cr, cd);
					delai (1);
				} else { y = y - 1; } // Met à jour la coordonnée y
				break;
			case 2 : // BAS
				if (y == 19 || tab [y+1][x] == 2 || tab [y+1][x] == 3) {
					printf("%sObstacle !%s\n", cr, cd);
					delai (1);
				} else { y = y + 1; }
				break;
			case 6 : // DROITE
				if (x == 19 || tab [y][x+1] == 2 || tab [y][x+1] == 3) {
					printf("%sObstacle !%s\n", cr, cd);
					delai (1);
				} else { x = x + 1; }
				break;
			case 4 : // GAUCHE
				if (x == 0 || tab [y][x-1] == 2 || tab [y][x-1] == 3) {
					printf("%sObstacle !%s\n", cr, cd);
					delai (1);
				} else { x = x - 1; }
				break;
			case 0 : // QUITTER
				printf("Au revoir !\n");
				delai (2);
				return -1; // Valeur spéciale pour dire à la boucle principale de s'arrêter
		}
		// Met à jour la position du joueur et retourne ce qu'il y a sur sa nouvelle case
		pos [0] = x;
		pos [1] = y;
		return tab [y][x];
	}
    return 0;
}

/**
 * @brief Crée une pause de 's' secondes.
 * * Bloque l'exécution du programme pendant un temps donné.
 * @param s Le nombre de secondes à attendre.
 */
int delai (int s) {
	int temps_fin = time(0) + s;
	while (time(0) < temps_fin); // Boucle vide qui attend que le temps soit écoulé
    return 0;
}


// --- Fonction principale : le cœur du jeu ---
int main () {
	// --- Initialisation et instructions ---
	printf("Bonjour !\n- Le but du jeu est de collecter 10 pieces d'or (%sO%s).\n", cj, cd);
	printf("- La clef (%sC%s) sert a ouvrir la porte du donjon (%s0%s).\n", cm, cd, cm, cd);
	printf("- Les rochers (R) et les arbres (A) sont infranchissables.\n");
	printf("- Attention aux monstres (%sM%s) et aux pieges (%sP%s) !\n", cr, cd, cr, cd);
	printf("- Si vos vies tombent a 0, c'est GAME OVER !\n");
	printf("Bon jeu et profitez bien des fleurs (%sF%s) !\n", cc, cd);
	delai (5);

	srand(time(NULL)); // Initialise le générateur de nombres aléatoires une seule fois.

	// --- Déclaration des variables du jeu ---
	int tab [20][20];       // La carte
	int pos [2] = {0, 0};   // Position du joueur {x, y}
	int vie = 10;           // Vies du joueur
	int or = 0;             // Or collecté
	int clef = 0;           // Nombre de clés
	int jeu = 1;            // Variable qui gère la boucle principale et stocke l'objet sur la case
	int verif = 0;          // Variable pour vérifier la carte générée

	// --- Boucle de vérification de la carte ---
	// S'assure que la carte générée est gagnable (contient exactement 10 pièces d'or)
	while (verif != 10) {
		verif = 0;
		init_carte (tab); // Génère une nouvelle carte
		// Compte le nombre de pièces d'or
		for (int i = 0 ; i < 20 ; i++) {
			for (int j = 0 ; j < 20 ; j++) {
				if (tab [i][j] == 5) {
					verif = verif + 1;
				}
			}
		}
	}

	// --- Boucle principale du jeu ---
	while (jeu != -1) { // Tourne tant que le joueur ne quitte pas, ne gagne pas ou ne perd pas.
		// "Nettoie" la console en sautant des lignes pour une meilleure lisibilité
		for (int i = 0 ; i <= 20 ; i++) {
			printf("\n");
		}
		
		// Affiche l'interface (statut du joueur)
		printf("%sVie(s) : %d\t%sOr : %d\t%sClef : %d%s\n", cv, vie, cj, or, cm, clef, cd);
		
		// Affiche la carte
		affiche_carte (tab, pos);
		
		// Gère le déplacement et récupère l'objet sur la nouvelle case
		jeu = deplace_personnage (tab, pos);

		// --- Logique des interactions ---
		if (jeu == 4) { // Le joueur marche sur une clé
			clef = clef + 1;
			tab [pos [1]][pos [0]] = 0; // La clé disparaît et devient de l'herbe
		}
		if (jeu == 5) { // Le joueur marche sur de l'or
			or = or + 1;
			tab [pos [1]][pos [0]] = 0; // L'or disparaît
		}
		if (jeu == 7 || jeu == 8) { // Le joueur marche sur un piège ou un monstre
			printf("%sAttention ! Vous perdez une vie !%s\n", cr, cd);
			delai (2);
			vie = vie - 1;
			tab [pos [1]][pos [0]] = 0; // Le danger disparaît après avoir été activé
		}
		if (jeu == 6) { // Le joueur est sur une porte
			if (clef == 0) { // S'il n'a pas de clé
				printf("%sLa porte est verouillee ! Trouvez la clef.%s\n", cm, cd);
				delai (2);
				pos [0] = pos [0] - 1; // Le joueur est repoussé en arrière
			}
			else { // S'il a une clé
                printf("%sVous utilisez une clef et la porte s'ouvre !%s\n", cv, cd);
                delai(2);
				clef = clef - 1; // Utilise la clé
				tab [pos [1]][pos [0]] = 0; // La porte s'ouvre (devient de l'herbe)
			}
		}

		// --- Conditions de fin de partie ---
		if (vie == 0) { // Si le joueur n'a plus de vie
			printf("%sGAME OVER%s\n", cr, cd);
			delai (3);
			jeu = -1; // Termine la boucle de jeu
		}
		if (or == 10) { // Si le joueur a collecté tout l'or
			printf("%sBRAVO ! Vous avez trouve tout l'or !%s\n", cv, cd);
			delai (3);
			jeu = -1; // Termine la boucle de jeu
		}
	}
    return 0; // Fin du programme
}