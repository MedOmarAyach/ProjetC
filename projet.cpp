#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct TranN {
    int transaction_id;
    char type[20];
    float amount;
    struct TranN *next;
};
struct Client{
    int account_number;
    char name[50];
    float balance;
    TranN *tran; 
};
typedef struct ClientN {
    Client client;
    struct ClientN *next;
} ClientN;
ClientN *clientList = NULL;
ClientN *createClientN(Client newClient) {
    ClientN *newNode = (ClientN *)malloc(sizeof(ClientN));
    newNode->client = newClient;
    newNode->next = NULL;
    return newNode;
}
TranN *createTranN(int transaction_id, const char *type, float amount) {
    TranN *newNode = (TranN *)malloc(sizeof(TranN));
    newNode->transaction_id = transaction_id;
    strncpy(newNode->type, type, sizeof(newNode->type) - 1);
    newNode->amount = amount;
    newNode->next = NULL;
    return newNode;
}
void creerCompte() {
    Client newClient;
    printf("Entrez le numéro de compte : ");
    scanf("%d", &newClient.account_number);
    printf("Entrez le nom du client : ");
    scanf("%s", newClient.name);
    newClient.balance = 0.0;
    newClient.tran = NULL;
    ClientN *newNode = createClientN(newClient);
    newNode->next = clientList;
    clientList = newNode;
    printf("Compte créé avec succès .\n");
}
void miseAJourCompte() {
    int numCompte;
    printf("Entrez le numéro de compte à mettre à jour : ");
    scanf("%d", &numCompte);
    ClientN *node = clientList;
    while (node != NULL && node->client.account_number != numCompte) {
        node = node->next;
    }
    if (node != NULL) {
        printf("Entrez le nouveau solde : ");
        scanf("%f", &node->client.balance);
        printf("Compte mis à jour avec succès .\n");
    } else {
        printf("Compte non trouvé .\n");
    }
}
void afficherDetailsCompte() {
    int numCompte;
    printf("Entrez le numéro de compte pour afficher les détails : ");
    scanf("%d", &numCompte);

    ClientN *node = clientList;
    while (node != NULL && node->client.account_number != numCompte) {
        node = node->next;
    }
    if (node != NULL) {
        printf("Numéro de compte : %d\n", node->client.account_number);
        printf("Nom du client : %s\n", node->client.name);
        printf("Solde : %.2f\n", node->client.balance);
    } else {
        printf("Compte non trouvé .\n");
    }
}
void afficherListeClients() {
    printf("Liste des clients :\n");
    ClientN *node = clientList;
    while (node != NULL) {
        printf("Numéro de compte : %d, Nom du client : %s\n", node->client.account_number, node->client.name);
        node = node->next;
    }
    if (clientList == NULL) {
        printf("Aucun client disponible .\n");
    }
}
void effectuerTransaction() {
    int numCompteSrc, numCompteDest;
    float montant;
    printf("Entrez le numéro de compte source : ");
    scanf("%d", &numCompteSrc);
    ClientN *nodeSrc = clientList;
    while (nodeSrc != NULL && nodeSrc->client.account_number != numCompteSrc) {
        nodeSrc = nodeSrc->next;
    }
    if (nodeSrc != NULL) {
        printf("Entrez le numéro de compte destinataire : ");
        scanf("%d", &numCompteDest);
        ClientN *nodeDest = clientList;
        while (nodeDest != NULL && nodeDest->client.account_number != numCompteDest) {
            nodeDest = nodeDest->next;
        }
        if (nodeDest != NULL) {
            printf("Entrez le montant à transférer : ");
            scanf("%f", &montant);
            if (montant <= nodeSrc->client.balance) {
                nodeSrc->client.balance -= montant;
                nodeDest->client.balance += montant;
                int transaction_id = (nodeSrc->client.tran == NULL) ? 1 : nodeSrc->client.tran->transaction_id + 1;
                TranN *tranrc = createTranN(transaction_id, "Transfert vers", montant);
                tranrc->next = nodeSrc->client.tran;
                nodeSrc->client.tran = tranrc;
                transaction_id = (nodeDest->client.tran == NULL) ? 1 : nodeDest->client.tran->transaction_id + 1;
                TranN *transactionDest = createTranN(transaction_id, "Transfert depuis", montant);
                transactionDest->next = nodeDest->client.tran;
                nodeDest->client.tran = transactionDest;
                printf("Transfert réussi ! Nouveau solde du compte source (%d) : %.2f\n", numCompteSrc, nodeSrc->client.balance);
                printf("Nouveau solde du compte destinataire (%d) : %.2f\n", numCompteDest, nodeDest->client.balance);
            } else {
                printf("Fonds insuffisants dans le compte source .\n");
            }
        } else {
            printf("Compte destinataire non trouvé .\n");
        }
    } else {
        printf("Compte source non trouvé .\n");
    }
}
void afficherHistoriquetran(int numCompte) {
    ClientN *node = clientList;
    while (node != NULL && node->client.account_number != numCompte) {
        node = node->next;
    }
    if (node != NULL) {
        printf("Historique des tran pour le compte %d :\n", numCompte);
        TranN *transaction = node->client.tran;
        while (transaction != NULL) {
            printf("ID de transaction : %d\n", transaction->transaction_id);
            printf("Type : %s\n", transaction->type);
            printf("Montant : %.2f\n", transaction->amount);
            printf("------------------------------\n");
            transaction = transaction->next;
        }
    } else {
        printf("Compte non trouvé .\n");
    }
}
void afficherHistoriquetranClients() {
    printf("Historique des tran pour tous les clients :\n");

    ClientN *node = clientList;
    while (node != NULL) {
        afficherHistoriquetran(node->client.account_number);
        node = node->next;
    }
}
void libererHistoriquetran(TranN *tete) {
    while (tete != NULL) {
        TranN *temp = tete;
        tete = tete->next;
        free(temp);
    }
}
void libererListeClients() {
    ClientN *node = clientList;
    while (node != NULL) {
        libererHistoriquetran(node->client.tran);
        ClientN *temp = node;
        node = node->next;
        free(temp);
    }
}
int main() {
    int choix;
    do {
        printf("\nMenu E-Bank :\n");
        printf("1. Créer un nouveau compte\n");
        printf("2. Mise à jour d'un compte\n");
        printf("3. Afficher les détails d'un compte\n");
        printf("4. Afficher la liste des clients\n");
        printf("5. Effectuer une transaction\n");
        printf("6. Afficher l'historique des tran pour un compte\n");
        printf("7. Afficher l'historique des tran pour tous les clients\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                creerCompte();
                break;
            case 2:
                miseAJourCompte();
                break;
            case 3:
                afficherDetailsCompte();
                break;
            case 4:
                afficherListeClients();
                break;
            case 5:
                effectuerTransaction();
                break;
            case 6:
                {
                    int numCompte;
                    printf("Entrez le numéro de compte pour afficher l'historique des tran : ");
                    scanf("%d", &numCompte);
                    afficherHistoriquetran(numCompte);
                }
                break;
            case 7:
                afficherHistoriquetranClients();
                break;
            case 8:
                libererListeClients();
                printf("Fermeture de E-Bank. Au revoir .\n");
                break;
            default:
                printf("Choix invalide ! Veuillez réessayer.\n");
        }
    } while (choix != 8);

    return 0;
}
