<div align="center">
  <h1 align="center">🪙 Le Chercheur d'Or</h1>
  <p align="center">
    <strong>Un jeu d'aventure 2D style Mario en mode texte, développé en C, où vous explorez un monde généré aléatoirement à la recherche de trésors directement dans votre terminal.</strong>
    <br />
    <br />
.
    <a href="https://github.com/VOTRE_NOM/VOTRE_REPO/blob/main/projet.c"><strong>👨‍💻 Consulter le code source</strong></a>
            <a href="https://github.com/Aybskt/Checker-Beautifier-in-Java-for-python-language/releases"><strong>🚀 Télécharger la dernière version</strong></a>
.
    ·
    <a href="https://github.com/VOTRE_NOM/VOTRE_REPO/issues"><strong>🛑 Signaler un Bug</strong></a>
  </p>
</div>

<div align="center">
  <img src="https://img.shields.io/github/last-commit/VOTRE_NOM/VOTRE_REPO?style=for-the-badge&logo=github&color=blue" />
  <img src="https://img.shields.io/github/repo-size/VOTRE_NOM/VOTRE_REPO?style=for-the-badge&logo=github" />
  <img src="https://img.shields.io/github/languages/top/VOTRE_NOM/VOTRE_REPO?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/github/license/VOTRE_NOM/VOTRE_REPO?style=for-the-badge&color=green" />
</div>
<br>

---
### ## Table des matières

1.  [🌟 À propos du projet](#-à-propos-du-projet)
2.  [✨ Fonctionnalités](#-fonctionnalités)
3.  [📸 Aperçu du jeu](#-aperçu-du-jeu)
4.  [🛠️ Environnement de Développement](#️-environnement-de-développement)
5.  [🚀 Démarrage rapide](#-démarrage-rapide)
6.  [💻 Utilisation](#-utilisation)
7.  [🗺️ Légende de la carte](#️-légende-de-la-carte)
8.  [📚 Documentation](#-documentation)
9.  [📜 Licence](#-licence)
---
### ## 🌟 À propos du projet

"Le Chercheur d'Or" est un projet de jeu vidéo textuel développé en **C standard**. Il s'inspire de l'esprit des jeux de plateforme 2D classiques comme Mario pour proposer une expérience simple, directe et rejouable.

L'objectif est d'offrir un jeu léger, fonctionnant entièrement dans un terminal, qui met en œuvre des concepts de base de la programmation en C : gestion de tableaux 2D, génération procédurale et logique de jeu. L'utilisation de **codes de couleur ANSI** vise à rendre l'expérience plus immersive et visuellement claire, rappelant les couleurs vives des jeux d'antan.

---

### ## ✨ Fonctionnalités

* 🗺️ **Niveaux Toujours Renouvelés :** Chaque partie est unique ! La carte du monde est générée aléatoirement à chaque lancement.
* 🏰 **Château Secret :** Une zone spéciale, comme un château de fin de niveau, est créée à chaque partie et renferme un précieux trésor.
* ⭐ **Système de Collecte Simple :** Gérez vos vies, collectez l'or et trouvez la clé pour déverrouiller le château.
* 🐢 **Dangers et Obstacles :** Évitez les monstres et les pièges pour survivre, tout en contournant les obstacles du décor.
* 🎮 **Interface en Ligne de Commande :** Un gameplay pur et rétro, contrôlé entièrement au clavier pour une sensation arcade.
* 🎨 **Visuels Colorés :** Utilisation des couleurs ANSI pour distinguer facilement les différents éléments du jeu directement dans votre terminal.
* ✅ **Défi Garanti :** Le jeu s'assure que chaque carte générée contient le bon nombre de pièces d'or pour que l'objectif soit toujours atteignable.

---

### ## 📸 Aperçu du jeu

*(💡 **Conseil :** Remplacez ces images par vos propres captures d'écran !)*

<table>
  <tr>
    <td><img src="https://i.imgur.com/8aV4iYk.png" alt="Début de partie et instructions"></td>
    <td><img src="https://i.imgur.com/uN6G7FV.png" alt="Exploration du monde"></td>
  </tr>
  <tr>
    <td align="center"><em>Début de partie et instructions</em></td>
    <td align="center"><em>Exploration du monde</em></td>
  </tr>
</table>

---

### ## 🛠️ Environnement de Développement

* **Langage :** C (C99)
* **Compilateur :** `gcc` (recommandé)
* **Bibliothèques :** Uniquement des bibliothèques standards (`stdio.h`, `stdlib.h`, `time.h`)
* **Terminal :** Tout terminal compatible avec les séquences d'échappement ANSI (couleurs).

---

### ## 🚀 Démarrage rapide

Pour jouer, vous avez simplement besoin d'un compilateur C.

#### **Prérequis**
* Un compilateur C comme `gcc`.
    * Vérifiez s'il est installé avec la commande :
        ```sh
        gcc --version
        ```

#### **Compilation**
1.  Clonez ou téléchargez ce dépôt.
2.  Ouvrez un terminal et naviguez jusqu'au dossier du projet.
3.  Compilez le fichier `projet.c` avec la commande suivante :
    ```sh
    gcc projet.c -o chercheur_or
    ```

---

### ## 💻 Utilisation

Une fois la compilation terminée, lancez le jeu avec la commande :
```sh
./chercheur_or
```

#### **Contrôles du jeu**
Utilisez les chiffres du clavier pour vous déplacer, puis appuyez sur `Entrée` :
-   `8` : Se déplacer vers le **haut**
-   `2` : Se déplacer vers le **bas**
-   `4` : Se déplacer vers la **gauche**
-   `6` : Se déplacer vers la **droite**
-   `0` : **Quitter** la partie

---

### ## 🗺️ Légende de la carte

| Symbole | Signification | Description |
|:---:|---|---|
| `X` | **Vous** | Le héros de l'aventure. |
| `.` | Herbe | Terrain sûr. |
| `F` | Fleur | Un joli bonus pour le décor. |
| `A` / `R`| Arbre / Rocher | Obstacles infranchissables. |
| `O` | **Or** | L'objet de votre quête. **Collectez-en 10 !** |
| `C` | **Clé** | Ouvre la porte du château. |
| `0` | **Porte** | Entrée du château, nécessite une clé. |
| `M` | Monstre | Dangereux, vous fait perdre une vie. |
| `P` | Piège | Dangereux, vous fait perdre une vie. |

---

### ## 📚 Documentation

Ce projet ne disposant pas d'une documentation externe, le code source a été **entièrement commenté** pour être aussi clair et compréhensible que possible. Chaque fonction et chaque bloc logique important est expliqué directement dans le code.

➡️ **[Explorer le code source commenté](https://github.com/VOTRE_NOM/VOTRE_REPO/blob/main/projet.c)**

---

### ## 📜 Licence

Ce projet est distribué sous la Licence MIT. Voir le fichier `LICENSE` pour plus de détails.

Copyright (c) 2025 - VOTRE NOM (VOTRE PSEUDO)
