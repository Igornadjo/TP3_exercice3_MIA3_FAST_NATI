// Exercice 3 - Gestion d'un personnel universitaire (version 2)
// Compatible Dev-C++ (C++98) : sans override, auto, unique_ptr...

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// ===============================================================
// Classe mere abstraite : Personnel
// ===============================================================
class Personnel {
protected:
    string matricule;
    string nom;
    string prenom;
    double salaireBase;

public:
    Personnel(const string& mat, const string& n, const string& p, double base)
        : matricule(mat), nom(n), prenom(p), salaireBase(base) {}

    virtual ~Personnel() {}

    // Methodes virtuelles pures : chaque categorie definit les siennes
    virtual double calculerSalaire() const = 0;
    virtual string getType() const = 0;
    virtual void afficherDetails() const = 0;

    // Affichage complet : partie commune + partie specifique (appel virtuel)
    void afficher() const {
        cout << "[" << getType() << "] " << matricule << " - "
             << nom << " " << prenom << "\n";
        cout << fixed << setprecision(0);
        cout << "   Salaire de base : " << salaireBase << " FCFA\n";
        afficherDetails();
        cout << "   >> Salaire net a payer : " << calculerSalaire() << " FCFA\n";
    }

    const string& getNom() const { return nom; }
    const string& getPrenom() const { return prenom; }
    const string& getMatricule() const { return matricule; }
};

// ===============================================================
// Professeur : heures supplementaires + indemnite de logement
// ===============================================================
class Professeur : public Personnel {
private:
    int    heuresSup;
    double tauxHoraire;
    double indemniteLogement;

public:
    Professeur(const string& mat, const string& n, const string& p, double base,
               int hSup, double taux, double logement)
        : Personnel(mat, n, p, base),
          heuresSup(hSup), tauxHoraire(taux), indemniteLogement(logement) {}

    double calculerSalaire() const {
        return salaireBase + heuresSup * tauxHoraire + indemniteLogement;
    }

    string getType() const { return "PROFESSEUR"; }

    void afficherDetails() const {
        cout << "   Heures sup. : " << heuresSup << " h x " << tauxHoraire << " FCFA\n"
             << "   Indemnite de logement : " << indemniteLogement << " FCFA\n";
    }
};

// ===============================================================
// Administratif : prime de rendement (en %) + prime de transport
// ===============================================================
class Administratif : public Personnel {
private:
    double tauxRendement;   // en pourcentage du salaire de base
    double primeTransport;

public:
    Administratif(const string& mat, const string& n, const string& p, double base,
                  double taux, double transport)
        : Personnel(mat, n, p, base),
          tauxRendement(taux), primeTransport(transport) {}

    double calculerSalaire() const {
        return salaireBase + salaireBase * tauxRendement / 100.0 + primeTransport;
    }

    string getType() const { return "ADMINISTRATIF"; }

    void afficherDetails() const {
        cout << "   Prime de rendement : " << tauxRendement << " % du salaire de base\n"
             << "   Prime de transport : " << primeTransport << " FCFA\n";
    }
};

// ===============================================================
// TechnicienLabo : prime de risque + astreintes
// ===============================================================
class TechnicienLabo : public Personnel {
private:
    double primeRisque;
    int    nbAstreintes;
    double montantAstreinte;

public:
    TechnicienLabo(const string& mat, const string& n, const string& p, double base,
                   double risque, int nbAst, double montant)
        : Personnel(mat, n, p, base),
          primeRisque(risque), nbAstreintes(nbAst), montantAstreinte(montant) {}

    double calculerSalaire() const {
        return salaireBase + primeRisque + nbAstreintes * montantAstreinte;
    }

    string getType() const { return "TECHNICIEN"; }

    void afficherDetails() const {
        cout << "   Prime de risque : " << primeRisque << " FCFA\n"
             << "   Astreintes : " << nbAstreintes << " x " << montantAstreinte << " FCFA\n";
    }
};

// ===============================================================
// Universite : gere la collection heterogene de Personnel*
// ===============================================================
class Universite {
private:
    string nomUniversite;
    vector<Personnel*> equipe;

    // Copie interdite (la classe possede les objets pointes)
    Universite(const Universite&);
    Universite& operator=(const Universite&);

public:
    Universite(const string& nom) : nomUniversite(nom) {}

    ~Universite() {
        for (size_t i = 0; i < equipe.size(); i++)
            delete equipe[i];   // destructeur virtuel => bon type detruit
    }

    void ajouter(Personnel* p) { equipe.push_back(p); }

    void afficherTous() const {
        cout << "======== " << nomUniversite << " : LISTE DU PERSONNEL ========\n\n";
        for (size_t i = 0; i < equipe.size(); i++) {
            equipe[i]->afficher();   // liaison dynamique
            cout << "\n";
        }
    }

    double masseSalariale() const {
        double total = 0;
        for (size_t i = 0; i < equipe.size(); i++)
            total += equipe[i]->calculerSalaire();   // liaison dynamique
        return total;
    }

    const Personnel* plusHautSalaire() const {
        const Personnel* meilleur = NULL;
        for (size_t i = 0; i < equipe.size(); i++)
            if (meilleur == NULL || equipe[i]->calculerSalaire() > meilleur->calculerSalaire())
                meilleur = equipe[i];
        return meilleur;
    }
};

// ===============================================================
// Programme principal
// ===============================================================
int main() {
    Universite uni("Universite d'Abomey-Calavi");

    uni.ajouter(new Professeur("P-1024", "Gbaguidi", "Romaric", 520000, 12, 6000, 70000));
    uni.ajouter(new Professeur("P-1031", "Tchibozo", "Fatima", 480000, 8, 6000, 60000));
    uni.ajouter(new Administratif("A-2057", "Akpovi", "Rachelle", 260000, 10, 20000));
    uni.ajouter(new Administratif("A-2063", "Zinsou", "Daniel", 240000, 12, 18000));
    uni.ajouter(new TechnicienLabo("T-3011", "Sagbo", "Ibrahim", 230000, 35000, 4, 8000));
    uni.ajouter(new TechnicienLabo("T-3019", "Houngbo", "Josiane", 215000, 30000, 3, 8000));

    uni.afficherTous();

    cout << fixed << setprecision(0);
    cout << "Masse salariale totale : " << uni.masseSalariale() << " FCFA\n";

    const Personnel* top = uni.plusHautSalaire();
    if (top != NULL)
        cout << "Salaire le plus eleve  : " << top->getNom() << " " << top->getPrenom()
             << " (" << top->calculerSalaire() << " FCFA)\n";

    system("pause");
    return 0;
}
