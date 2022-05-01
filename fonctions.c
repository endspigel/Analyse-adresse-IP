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
*  Nom du fichier : fonctions.c                                               *
*                                                                             *
******************************************************************************/
#include <stdio.h>
#include <inttypes.h>

int isIpCorrecte(uint8_t ip[]){
    if (ip[0] < 0 || ip[1] < 0 || ip[2] < 0 || ip[3] < 0 || ip[0] >= 255 || ip[1] > 256 || ip[2] > 256 || ip[3] > 256){
        return 1;
    }
}

int findClass(uint8_t ip[]){
    if (ip[0] >= 1 && ip[0] <= 126){
        return 1; //classe A
    } else {
        if (ip[0] >= 128 && ip[0] <= 191){
            return 2; //classe B
        } else if (ip[0] >= 192 && ip[1] >= 0 && ip[2] >= 1 || ip[1] <= 223 && ip[2] <= 255 && ip[3] <= 255){
            return 3; //classe C
        } else if (ip[0] >= 224 && ip[0] < 240){
            return 4; //classe D
        } else if (ip[0] >= 240 && ip[0] <= 255){
            return 5; //classe E
        }
    }
}

int typeAdrIP(uint8_t ip[]){
    if (ip[0] == 10){
        return 0; //adresse privé de classe A
    } else {
        if (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31){
            return 1; //adresse privé de classe B
        } else if (ip[0] == 192 && ip[1] == 168 && ip[2] >= 1){
            return 2; //adresse privé de classe C
        } else if (ip[0] == 127 && ip[1] == 0 && ip[2] == 0 && ip[3] == 1){
            return 3; //Adresse localhost
        } else if (ip[0] <= 224 && ip[0] >= 239){
            return 4; //Adresse multicast
        } else if (ip[3] == 255){
            return 5; //adresse broadcast
        } else {
            return 6; //adresse publique
        }
    }
}

void adresse(uint8_t ip[], int masque){
    int octetmasque[4]; // tableau contenant les 4 octets du masque
    int tmp; // variable temporaire
    int octet; // octet du masque modifié
    int k;
    int adrReseau[4]; // adresse réseau

    FILE* fichier;
    fichier = fopen("InfoIP.txt", "w");

    if (fichier == NULL) {
    printf("Erreur à l'ouverture du fichier f1\n");
    } else {
        printf("Ouverture du fichier infoIP réussie\n");
    }
    //écriture dans le fichier texte infoIP
    fprintf(fichier, "Informations sur l'adresse IP renseignée\n\n");
    fprintf(fichier, "Adresse IP saisie : %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
    fprintf(fichier, "masque (en notation CIDR) : %d\n", masque);
    fprintf(fichier, "**************************************************************************\n");


    // Cas où le masque est inférieur ou égal à 8
    if (masque <=8){
        k=0;
        octet=0;
        // Calcul de l'octet
        while(k<masque){
            tmp =1;
            tmp = tmp << (7-k);
            octet = octet+tmp;
            k+=1;
        }
        // Seul le premier octet est affecté
        octetmasque[0]=octet;
        octetmasque[1]=0;
        octetmasque[2]=0;
        octetmasque[3]=0;
    }
    
    // Cas où le masque est inférieur à 24
    if (16 <= masque && masque <24 ){
        // Les 2 premiers octets du masque sont 255
        octetmasque[0]=255;
        octetmasque[1]=255;
        masque = masque - 16;
        k=0;
        octet=0;
        while(k<masque){
            tmp =1;
            tmp =tmp<<(7-k);
            octet = octet+tmp;
            k+=1;
        }
        // Le 3 ème octet sera affecté
        octetmasque[2] = octet;
        octetmasque[3] = 0;
    }
    // Cas où le masque est inférieur à 32
    if (24 <= masque && masque <32){
        // Les 3 premiers octets sont à 255
        octetmasque[0]=255;
        octetmasque[1]=255;
        octetmasque[2] =255;
        masque = masque - 24;
        k=0;
        octet=0;
        while(k<masque){
            tmp =1;
            tmp =tmp<<(7-k);
            octet = octet+tmp;
            k+=1;
        }
        // Seul le dernier octet sera affecté
    octetmasque[3] = octet;
    }

    // Cas où le masque est à 32
    if ( masque == 32) {
        for (int x = 0; x <4; x++){
        octetmasque[x] = 255;
        }
    }
    // boucle permettant de calculer l'adresse réseau à partir de l'ip et des octets du masque
    for (int x = 0; x <4; x++){
        adrReseau[x] = ip[x]& octetmasque[x];
    }
    //printf("adresse réseau %d.%d.%d.%d\n", adrReseau[0], adrReseau[1], adrReseau[2], adrReseau[3]);
    // Calcul de l'adresse machine

    int adrMachine[4];
    if (masque <=8){
        adrMachine[0] = adrReseau[0];
        adrMachine[1] = 0;
        adrMachine[2] = 0;
        adrMachine[3] = adrReseau[3] +1;
    }
    if (16 <= masque && masque <24 ){
        adrMachine[0] = adrReseau[0];
        adrMachine[1] = adrReseau[1];
        adrMachine[2] = 0;
        adrMachine[3] = adrReseau[3] +1;
    }
    if (24 <= masque && masque <32){
        adrMachine[0] = adrReseau[0];
        adrMachine[1] = adrReseau[1];
        adrMachine[2] = adrReseau[2];
        adrMachine[3] = adrReseau[3] +1;
    }
    if ( masque == 32) {
        adrMachine[0] = ip[0];
        adrMachine[1] = ip[1];
        adrMachine[2] = ip[2];
        adrMachine[3] = ip[3] +1;
    }

    printf("Masque : %d.%d.%d.%d\n", octetmasque[0], octetmasque[1], octetmasque[2], octetmasque[3]);
    fprintf(fichier, "Masque : %d.%d.%d.%d\n", octetmasque[0], octetmasque[1], octetmasque[2], octetmasque[3]);
    printf("Adresse réseau %d.%d.%d.%d\n", adrReseau[0], adrReseau[1], adrReseau[2], adrReseau[3]);
    fprintf(fichier, "Adresse réseau %d.%d.%d.%d\n", adrReseau[0], adrReseau[1], adrReseau[2], adrReseau[3]);
    printf("Première adresse machine %d.%d.%d.%d\n", adrMachine[0], adrMachine[1], adrMachine[2], adrMachine[3]);
    fprintf(fichier, "Première adresse machine %d.%d.%d.%d\n", adrMachine[0], adrMachine[1], adrMachine[2], adrMachine[3]);
    //return ("Adresse machine %d.%d.%d.%d\n", adrMachine[0], adrMachine[1], adrMachine[2], adrMachine[3]);
}