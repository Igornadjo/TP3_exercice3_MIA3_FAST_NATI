# Université : gestion du personnel avec polymorphisme

Application console en C++ (norme C++98, compatible Dev-C++) qui gère le personnel d'une université. Une classe `Universite` possède une collection d'agents de plusieurs catégories et en calcule la masse salariale grâce à la liaison dynamique.

## Fonctionnalités

- Création de trois catégories de personnel : professeurs, administratifs, techniciens de laboratoire
- Calcul du salaire propre à chaque catégorie
- Affichage détaillé de chaque agent
- Calcul de la masse salariale totale de l'université
- Recherche de l'agent ayant le salaire le plus élevé

## Modèle de classes

| Classe | Type | Description |
|---|---|---|
| `Personnel` | abstraite | matricule, nom, prénom, salaire de base ; méthodes virtuelles pures `calculerSalaire()`, `getType()`, `afficherDetails()` |
| `Professeur` | dérivée | heures supplémentaires, taux horaire, indemnité de logement |
| `Administratif` | dérivée | prime de rendement (en % du salaire de base), prime de transport |
| `TechnicienLabo` | dérivée | prime de risque, nombre et montant des astreintes |
| `Universite` | gestionnaire | possède un `vector<Personnel*>` (agrégation), libère la mémoire dans son destructeur |

Relations : héritage `Personnel ◁── Professeur / Administratif / TechnicienLabo`, agrégation `Universite ◇── Personnel (0..*)`. Le diagramme est fourni en image (`diagramme_classes_v2.png`) et en source PlantUML (`diagramme_classes_v2.puml`).

## Formules de salaire

| Catégorie | Salaire |
|---|---|
| Professeur | base + heures sup. × taux horaire + indemnité de logement |
| Administratif | base + base × taux de rendement / 100 + prime de transport |
| TechnicienLabo | base + prime de risque + nombre d'astreintes × montant |

## Choix de conception

- **Patron « méthode » pour l'affichage** : `Personnel::afficher()` affiche la partie commune, puis délègue la partie spécifique à `afficherDetails()`, redéfinie dans chaque classe fille.
- **Propriété de la mémoire** : `Universite` détruit les objets qu'elle contient. Sa copie est interdite pour éviter une double destruction.
- **Destructeur virtuel** dans `Personnel` pour détruire le bon type d'objet via un pointeur de la classe mère.

## Compilation et exécution

```bash
g++ -std=c++98 -Wall -pedantic -o universite gestion_universite_v2.cpp
./universite
```

Avec Dev-C++ : ouvrir `gestion_universite_v2.cpp`, puis **F11**. Sur Linux ou macOS, la ligne `system("pause")` n'a pas d'effet utile et peut être supprimée.

## Exemple de sortie

```
[PROFESSEUR] P-1024 - Gbaguidi Romaric
   Salaire de base : 520000 FCFA
   Heures sup. : 12 h x 6000 FCFA
   Indemnite de logement : 70000 FCFA
   >> Salaire net a payer : 662000 FCFA
...
Masse salariale totale : 2408800 FCFA
Salaire le plus eleve  : Gbaguidi Romaric (662000 FCFA)
```

## Contenu du dépôt

```
.
├── gestion_universite_v2.cpp
├── diagramme_classes_v2.puml
├── diagramme_classes_v2.png
└── README.md
```

## Notions illustrées

Héritage, classe abstraite, méthodes virtuelles pures, redéfinition, polymorphisme, liaison dynamique, agrégation, destructeur virtuel, gestion manuelle de la mémoire (`new` / `delete`).
