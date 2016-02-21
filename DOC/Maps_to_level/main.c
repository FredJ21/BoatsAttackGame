#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define level_NB        10
#define map_nb_ligne    19

#define FILE_SRC        "../../jni/src/level.c"
#define FILE_TMP        "../../jni/src/level.c.new"

#define true            1
#define false           0

int main()
{

    char    level_filename[level_NB+1][30];
    int     aaa;
    int     character_position;
    int     line_ok;

    char    character;
    char    ch[3];

    int     flag_section_start = false;
    int     flag_section_stop  = false;

    FILE * pFile_map;
    FILE * pFile_source;
    FILE * pFile_tmp;


/********************************************************************
        Ouverture du fichier temporaire pour écriture
*********************************************************************/
  pFile_tmp = fopen (FILE_TMP,"w");
  if (pFile_tmp == NULL) {
        printf ("Impossible de creer le fichier ");
        printf (FILE_TMP);
        printf ("\n");
        exit (1);
  }

/********************************************************************
        Lecture du fichier source jusqu'a la balise START
*********************************************************************/

    pFile_source = fopen (FILE_SRC,"r");
    if (pFile_source == NULL) {
            printf ("Fichier source ");
            printf (FILE_SRC);
            printf (" introuvable !!!\n");
            exit(1);
    }
    printf ("\nLecture du fichier ");
    printf (FILE_SRC);
    printf ("\n");

    line_ok = 0;
    do {
            // Lecture d'une ligne
            char    line[1000] = {};
            character_position = 0;
            do {
                character = getc(pFile_source);
                line[character_position] = character;
                character_position++;
            } while ((character != '\n') && (character != EOF));

            //printf ("%s", line);
            fputs (line,pFile_tmp);
            line_ok++;

            if ( strncmp(line,"// START Auto-generated section", 10) == 0 ) {  flag_section_start = true; }

    } while (character != EOF && flag_section_start != true);

    //printf("\n");
    fputs ("\n",pFile_tmp);
    printf ("\t--> %d lignes\n\n", line_ok);

/********************************************************************
        Traitement des fichiers MAP
*********************************************************************/

    for (aaa=1; aaa < level_NB+1; aaa++) {

        sprintf(level_filename[aaa],"../Maps/map-%d.txt", aaa);


        pFile_map = fopen (level_filename[aaa],"r");
        if (pFile_map!=NULL) {


            // Lecture du fichier
            line_ok = 0;
            do {
                    // Lecture d'une ligne
                    char    line[256] = {};
                    character_position = 0;
                    do {
                        character = getc(pFile_map);
                        line[character_position] = character;
                        character_position++;
                    } while ((character != '\n') && (character != EOF));

                    // analyse de la ligne
                    if (line[0] >= 48 &&  line[0] <= 57) {  // premier caractere entre 0 et 9

                        if (line_ok == 0 ) {
                                                            //printf("\tint DataMap_1[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {\n");
                                                            fputs ("\tint DataMap_",pFile_tmp);
                                                            sprintf(ch,"%d",aaa);
                                                            fputs (ch,pFile_tmp);
                                                            fputs ("[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {\n",pFile_tmp);
                        }
                        if (line_ok == map_nb_ligne ) {
                                                            //printf("};\n");
                                                            fputs ("};\n",pFile_tmp);
                                                            //printf("\tint DataMap_1_Layer2[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {\n");
                                                            fputs ("\tint DataMap_",pFile_tmp);
                                                            sprintf(ch,"%d",aaa);
                                                            fputs (ch,pFile_tmp);
                                                            fputs ("_Layer2[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {\n",pFile_tmp);
                        }


                        //printf("\t\t\t%s",line);
                        fputs ("\t\t\t",pFile_tmp);
                        fputs (line, pFile_tmp);

                        if (line_ok == (map_nb_ligne *2) - 1 ) {
                                //printf("};\n");
                                fputs ("};\n",pFile_tmp);
                        }

                        line_ok++;
                    }

            } while (character != EOF);

            fclose (pFile_map);
            printf ("Level %d : [%s]  --> OK --> %d lignes\n", aaa, level_filename[aaa], line_ok) ;

        } else {

           printf ("Level %d : [%s]  --> Fichier abscent\n", aaa, level_filename[aaa]) ;
           fclose (pFile_map);
        }

    }


/********************************************************************
        MAPS VIDES
*********************************************************************/
   for (aaa=level_NB+1; aaa < 51; aaa++) {

        fputs ("\tint DataMap_",pFile_tmp);
        sprintf(ch,"%d",aaa);
        fputs (ch,pFile_tmp);
        fputs ("[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {};\n",pFile_tmp);

        fputs ("\tint DataMap_",pFile_tmp);
        sprintf(ch,"%d",aaa);
        fputs (ch,pFile_tmp);
        fputs ("_Layer2[MAP_NB_TILE_X * MAP_NB_TILE_Y] = {};\n",pFile_tmp);


   }

/********************************************************************
        Lecture du fichier source depuis la balise STOP
*********************************************************************/

    printf ("\nLecture du fichier ");
    printf (FILE_SRC);
    printf ("\n");

    line_ok = 0;
    do {
            // Lecture d'une ligne
            char    line[1000] = {};
            character_position = 0;
            do {
                character = getc(pFile_source);
                line[character_position] = character;
                character_position++;
            } while ((character != '\n') && (character != EOF));

            if ( strncmp(line,"// STOP Auto-generated section", 10) == 0 ) {  flag_section_stop = true; }

            if ( flag_section_stop && character != EOF) {
                    //printf ("%s", line);
                    fputs (line,pFile_tmp);
                    line_ok++;
            }


    } while (character != EOF);

    printf ("\t--> %d lignes\n\n", line_ok);

    fclose(pFile_source);


/********************************************************************
        FIN
*********************************************************************/

    fclose(pFile_tmp);
    exit(0);
}
