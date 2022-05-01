/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N de Sujet : 2                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse adresse IP                                              *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :  Jeanjean Patrick                                            *
*                                                                             *
*  Nom-prénom2 : Poghosyan Sergey                                             *
*                                                                             *
*  Nom-prénom3 : Paul Mendy                                                   *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : main.c                                                    *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <inttypes.h> // bibliothèque pour utiliser les uint

int isIpCorrecte(uint8_t ip[]);
int findClass(uint8_t ip[]);
int typeAdrIP(uint8_t ip[]);
void adresse(uint8_t ip[], int masque);

void main(){
    uint8_t ip[4];     // tableau de 4 octet permetent de contenir chaque partie de l'ip
    int masque;

    printf("Entrez une adresse IP et son masque (format : 0.0.0.0/0):");

    scanf("%hhu.%hhu.%hhu.%hhu/%d", &ip[0], &ip[1], &ip[2], &ip[3], &masque);

    //enregistrement des résultats dans un fichier
    FILE* fichier;
    fichier = fopen("InfoIP.txt", "w");
    if (fichier == NULL) {
    printf("Erreur à l'ouverture du fichier f1\n");
    } else {
        printf("Ouverture du fichier infoIP réussie\n");
        fprintf(fichier, "%s", "Informations sur l'adresse IP renseignée\n\n");
        fprintf(fichier, "**************************************************************************\n");
    }

    if (isIpCorrecte(ip) == 1){
        printf("L'adresse IP renseignée n'est pas correcte");
    } else {
        printf("**************************************************************************\n");
        printf("Adresse IP saisie au clavier : %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
        printf("Masque (en notation CIDR) %d\n", masque);
        printf("**************************************************************************\n");

        if (findClass(ip) == 1){
            printf("Adresse IP de classe A, ");
            fprintf(fichier, "Adresse IP de classe A, ");
        } else {
            if (findClass(ip) == 2){
                printf("Adresse IP de classe B, ");
                fprintf(fichier, "Adresse IP de classe B, ");
            } else if (findClass(ip) == 3){
                printf("Adresse IP de classe C, ");
                fprintf(fichier, "Adresse IP de classe C, ");
            } else if (findClass(ip) == 4){
                printf("Adresse IP de classe D");
                fprintf(fichier, "Adresse IP de classe D, ");
            } else if (findClass(ip) == 5){
                printf("Adresse IP de classe E");
                fprintf(fichier, "Adresse IP de classe E, ");
            }
        }
        if (typeAdrIP(ip) == 0 || typeAdrIP(ip) == 1 || typeAdrIP(ip) == 2){
            printf("privé \n");
            fprintf(fichier, "privé \n");
        } else {
            if (typeAdrIP(ip) == 3){
                printf("localhost \n");
                fprintf(fichier, "localhost \n");
            } else if (typeAdrIP(ip) == 4){
                printf("multicast \n");
                fprintf(fichier, "localhost \n");
            } else if (typeAdrIP(ip) == 5){
                printf("broadcast \n");
                fprintf(fichier, "broadcat \n");
            } else if (typeAdrIP(ip) == 6){
                printf("publique \n");
                fprintf(fichier, "publique \n");
            }
        }
        adresse(ip, masque);
        
    }
    fclose(fichier);
}