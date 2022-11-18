# SUJET2
Notre programme est un outil permettant l’étude et l’extraction d’informations provenant d’une adresse IP et de son masque réseau. Il reconnaît : 
- le type de l'adresse IP (publique, privé, localhost, multicast ou broadcast); 
- la classe de l'adresse (A, B, C, D, E); 
- l'adresse du réseau; 
- l'adresse de l'hôte  
Ce programme a été réalisé par Patrick JEANJEAN, Mendy PAUL et Sergey POGHOSYAN

## Documentation des fonctions

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
