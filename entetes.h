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
#include <inttypes.h> // bibliothèque pour utilisé les uint

//permet de vérifier la bonne validité des chiffres saisie au clavier
//nécessite une adresse ip
//renvoie 1 si l'IP entrée n'est pas correcte
int isIpCorrecte(uint8_t ip[]);

//permet de trouver la classe d'une adresse IP
//nécessite une adresse IP valide
//renvoie 1 si l'adresse IP est de classe A
//renvoie 2 si classe B
//renvoie 3 si classe C
//renvoie 4 si classe D
//renvoie 5 si classe E
int findClass(uint8_t ip[]);

//permet de trouver le type (privé, publique, localhost, broadcast ou multicast)) d'une adresse IP
//nécessite une adresse IP
//renvoie 0 si il s'agit d'une adresse IP privé de classe A
//renvoie 1 si adresse IP privé de classe B
//renvoie 2 si adresse IP privé de classe C
//renvoie 3 si adresse IP localhost
//renvoie 4 si adresse IP multicast
//renvoie 5 si boradcast
//renvoie 6 si l'adresse IP est publique
int typeAdrIP(uint8_t ip[]);

//permet de calculer l'adresse réseau et la première adresse machine
//nécessite une adresse IP de type uint8_t et un masque de type int
//affiche et permet de créer le fichier texte des informations de l'adresse IP
//affiche l'adresse réseau et la première adresse machine
void adresse(uint8_t ip[], int masque);