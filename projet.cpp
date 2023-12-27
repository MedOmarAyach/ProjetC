#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100
//strucutre pour represter un client
struct Client {
    int numero_compte;
    char nom[50];
    float solde;
};
//tableau pour enregistrer les clients
Client clients[MAX_CLIENTS];
int totalClients = 0;
//fonctin pour creer un compte
void creerCompte() {
    if (totalClients < MAX_CLIENTS) {
        printf("Entrez le num�ro de compte : ");
        scanf("%d", &clients[totalClients].numero_compte);
        printf("Entrez le nom du client : ");
        scanf("%s", clients[totalClients].nom);
        clients[totalClients].solde = 0.0;
        totalClients++;
        printf("Compte cr�� avec succ�s .\n");
    } else {
        printf("Nombre maximum de clients atteint .\n");
    }
}
//mise a jour du compte
void mettreAJourCompte() {
    int numeroCompte;
    printf("Entrez le num�ro de compte � mettre � jour : ");
    scanf("%d", &numeroCompte);
    int index = -1;
    for (int i = 0; i < totalClients; i++) {
        if (clients[i].numero_compte == numeroCompte) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        printf("Entrez le nouveau solde : ");
        scanf("%f", &clients[index].solde);
        printf("Compte mis � jour avec succ�s .\n");
    } else {
        printf("Compte non trouv� .\n");
    }
}
//affichage d'un seul compte
void afficherDetailsCompte() {
    int numeroCompte;
    printf("Entrez le num�ro de compte pour afficher les d�tails : ");
    scanf("%d", &numeroCompte);
    int index = -1;
    for (int i = 0; i < totalClients; i++) {
        if (clients[i].numero_compte == numeroCompte) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        printf("Num�ro de compte : %d\n", clients[index].numero_compte);
        printf("Nom du client : %s\n", clients[index].nom);
        printf("Solde : %.2f\n", clients[index].solde);
    } else {
        printf("Compte non trouv� .\n");
    }
}
///affichage du liste des compte
void afficherTousLesClients() {
    if (totalClients > 0) {
        printf("Liste des clients :\n");
        for (int i = 0; i < totalClients; i++) {
            printf("%d. %s\n", clients[i].numero_compte, clients[i].nom);
        }
    } else {
        printf("Aucun client disponible .\n");
    }
}
//nouveau tache: virement d'un compte vers un autre
void effectuerTransaction() {
    int numeroCompteSrc, numeroCompteDest;
    float montant;
    printf("Entrez le num�ro de compte source : ");
    scanf("%d", &numeroCompteSrc);
    int indexSrc = -1;
    for (int i = 0; i < totalClients; i++) {
        if (clients[i].numero_compte == numeroCompteSrc) {
            indexSrc = i;
            break;
        }
    }
    if (indexSrc != -1) {
        printf("Entrez le num�ro de compte de destination : ");
        scanf("%d", &numeroCompteDest);

        int indexDest = -1;
        for (int i = 0; i < totalClients; i++) {
            if (clients[i].numero_compte == numeroCompteDest) {
                indexDest = i;
                break;
            }
        }
        if (indexDest != -1) {
            printf("Entrez le montant � transf�rer : ");
            scanf("%f", &montant);

            if (montant <= clients[indexSrc].solde) {
                clients[indexSrc].solde -= montant;
                clients[indexDest].solde += montant;
                printf("Transfert r�ussi , Nouveau solde du compte source (%d) : %.2f\n", numeroCompteSrc, clients[indexSrc].solde);
                printf("Nouveau solde du compte de destination (%d) : %.2f\n", numeroCompteDest, clients[indexDest].solde);
            } else {
                printf("Fonds insuffisants dans le compte source .\n");
            }
        } else {
            printf("Compte de destination non trouv� .\n");
        }
    } else {
        printf("Compte source non trouv� .\n");
    }
}
int main() {
    int choix;
    do {
        printf("\nMenu E-Bank :\n");
        printf("1. Cr�er un nouveau compte\n");
        printf("2. Mettre � jour un compte\n");
        printf("3. Afficher les d�tails d'un compte\n");
        printf("4. Afficher tous les clients\n");
        printf("5. Effectuer une transaction\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creerCompte();
                break;
            case 2:
                mettreAJourCompte();
                break;
            case 3:
                afficherDetailsCompte();
                break;
            case 4:
                afficherTousLesClients();
                break;
            case 5:
                effectuerTransaction();
                break;
            case 6:
                printf("Fermeture d'E-Bank. Au revoir .\n");
                break;
            default:
                printf("Choix invalide , Veuillez r�essayer.\n");
        }
    } while (choix != 6);
    return 0;
}

