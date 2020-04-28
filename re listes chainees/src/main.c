#include <stdlib.h>   /* Pour la fonction system. */
#include <stdio.h>
#include "Pile.h"

int main()
{
        pile *MaPile = NULL;   /* Impératif de l'initialiser à NULL */

        Push(&MaPile, 10);
        Push(&MaPile, 25);
        Push(&MaPile, 33);
        Push(&MaPile, 12);      /* Empile 4 valeurs. */

        puts("Affichage de la pile :");
        View(MaPile);       /* Affiche la totalité de la pile. */
        puts("------");

        printf("Nb d'elements : %d\n",Length(MaPile));
        puts("------");

        puts("Deux valeurs soutirees de la pile :");
        printf("%d\n",Pop(&MaPile));   /* Affiche deux valeurs */
        printf("%d\n",Pop(&MaPile));   /* soutirées de la pile. */
        puts("------");

        puts("Affichage de la pile :");
        View(MaPile);       /* Affiche la totalité de la pile. */
        puts("------");

        Clear(&MaPile);        /* Vide la pile. */

        Push(&MaPile, 18);      /* Empile une valeur. */

        puts("Affichage de la pile apres vidage et ajout d'une valeur :");
        View(MaPile);       /* Affiche la totalité de la pile. */
        puts("------\n");

        Clear(&MaPile);    /* Vider la pile avant de quitter. */

#ifdef _WIN32
        system("PAUSE");  /* Pour la console Windows. */
#endif
        return 0;
}
