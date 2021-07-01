#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"header.h"

void switchCase(int n){

    switch(n){

    case 1:
        system("cls");
        addAlbum();
        break;

    case 2:
        system("cls");
        printAlbums();
        break;

    case 3:
        system("cls");
        deleteAlbum();
        break;

    case 4:
        system("cls");
        artistPrint();
        break;

    case 5:
        system("cls");
        genrePrint();
        break;

    case 6:
        system("cls");
        albumSearch();
        break;

    case 7:
        system("cls");
        deleteFile();
        break;

    case 8:
        system("cls");
        searchInRepository();
        break;

    case 9:
        system("cls");
        exitProgram();
        break;
    }
}

void artistPrint(){
    char artist[30];
    int n,i,flag=0,index=0;

    FILE* fp=fopen("album.bin","rb");
    if(fp==NULL){
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    ALBUM* sAlbum=(ALBUM*)malloc(n*sizeof(ALBUM));
    if(sAlbum==NULL){
        printf("Error");
        return 1;
    }
    printf("Enter artist name: ");
    scanf(" %29[^\n]", artist);
    printf("\n");
    fread(sAlbum,sizeof(ALBUM),n,fp);
    for(int i=0;i<n;i++){
        if(strcmp((sAlbum+i)->artist,artist)==0){
            index++;
            if(index==1){
                printf("*Available %s albums*\n",artist);
            }
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;

        }
    }
        if(flag==0){
            printf("%s's albums are not available in repository!", artist);
        }
        fclose(fp);
        free(sAlbum);
        getch();
        system("cls");
}



void genrePrint(){
    char genre[30];
    int n,i,flag=0,index=0;

    FILE* fp=fopen("album.bin","rb");
    if(fp==NULL){
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    ALBUM* sAlbum=(ALBUM*)malloc(n*sizeof(ALBUM));
    if(sAlbum==NULL){
        printf("Error");
        return 1;
    }
    printf("Enter genre name: ");
    scanf(" %29[^\n]", genre);
    printf("\n");
    fread(sAlbum,sizeof(ALBUM),n,fp);
    alphabeticalSort(sAlbum,n);

    for(int i=0;i<n;i++){
        if(strcmp((sAlbum+i)->genre,genre)==0){
            index++;
            if(index==1){
                printf("*Available %s albums*\n",genre);
            }
            printf("\nArtist: %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;

        }
    }
        if(flag==0){
            printf("%s's albums are not available in repository!", genre);
        }
        fclose(fp);
        free(sAlbum);
        getch();
        system("cls");
}

void addAlbum() {
	FILE* fp = NULL;
	int n;
	ALBUM* nAlbum = (ALBUM*)malloc(sizeof(ALBUM));
	if (nAlbum == NULL) {
        printf("Error");
		return 1;
	}

		printf("Enter name of artist: ");
		scanf(" %29[^\n]", nAlbum->artist);
		printf("Enter name of album: ");
		scanf(" %29[^\n]", nAlbum->album);
		printf("Enter name of genre: ");
		scanf(" %29[^\n]", nAlbum->genre);
		printf("Enter name of format: ");
		scanf(" %29[^\n]", nAlbum->format);


		fp = fopen("album.bin", "rb");
		if (fp == NULL) {
			fp = fopen("album.bin", "wb");
			n = 1;
			fwrite(&n, sizeof(int), 1, fp);
			fwrite(nAlbum, sizeof(ALBUM), 1, fp);
			fclose(fp);
		}
		else {
			fclose(fp);
			fp = fopen("album.bin", "rb+");
			if (fp == NULL) {
				printf("Error");
			}
			else {
				fseek(fp, 0, SEEK_SET);
				fread(&n, sizeof(int), 1, fp);
				n++;
				fseek(fp, 0, SEEK_SET);
				fwrite(&n, sizeof(int), 1, fp);
				fseek(fp, 0, SEEK_END);
				fwrite(nAlbum, sizeof(ALBUM), 1, fp);
				fclose(fp);
			}
		}


	fclose(fp);
	free(nAlbum);
    system("cls");

    return 0;
}

void printAlbums(){
    int n,i;
	FILE* fp = NULL;
	ALBUM* pAlbum = NULL;
	fp = fopen("album.bin", "rb");
	if (fp == NULL) {
		printf("Repository is empty, might try option 1");
		getch();
        system("cls");
        return;
	}
		fread(&n, sizeof(int), 1, fp);
		if (n == 0) {
			printf("Repository is empty,might try option 1.\n\n");
			getch();
            system("cls");
            return;
		}
		pAlbum = (ALBUM*)malloc(n*sizeof(ALBUM));
        if (pAlbum == NULL) {
			printf("Error");
			return 1;
		}
		fread(pAlbum, sizeof(ALBUM), n, fp);

		alphabeticalSort(pAlbum,n);


        printf("*You have %d albums in repository*", n);

        for (i = 0; i < n; i++){
            printf("\n\nArtist:%s", (pAlbum+i)->artist);
            printf("\nAlbum:%s", (pAlbum+i)->album);
            printf("\nGenre:%s",(pAlbum+i)->genre);
            printf("\nFormat:%s",(pAlbum+i)->format);
        }
    fclose(fp);
	free(pAlbum);
    getch();
    system("cls");

	return;
}

void alphabeticalSort(ALBUM* pAlbum,int n){
    int k, j,i;
    ALBUM *temp=(ALBUM*)malloc(n*sizeof(ALBUM));


        for(i = 0; i <  n; ++i) {
        for(j = i + 1; j < n; j++) {
            if(strcmp(pAlbum[i].artist, pAlbum[j].artist) > 0) {
                strcpy(temp, pAlbum[i].artist);
                strcpy(pAlbum[i].artist, pAlbum[j].artist);
                strcpy(pAlbum[j].artist, temp);

                strcpy(temp, pAlbum[i].album);
                strcpy(pAlbum[i].album, pAlbum[j].album);
                strcpy(pAlbum[j].album, temp);

                strcpy(temp, pAlbum[i].genre);
                strcpy(pAlbum[i].genre, pAlbum[j].genre);
                strcpy(pAlbum[j].genre, temp);

                strcpy(temp, pAlbum[i].format);
                strcpy(pAlbum[i].format, pAlbum[j].format);
                strcpy(pAlbum[j].format, temp);
            }
        }
    }
    free(temp);

}

void albumSearch(){
    char searchedWord[30];
    int n,i,flag=0;

    FILE* fp=fopen("album.bin","rb");
    if(fp==NULL){
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;

    }

    fread(&n, sizeof(int), 1, fp);

    ALBUM* sAlbum=(ALBUM*)malloc(n*sizeof(ALBUM));
    if(sAlbum==NULL){
        printf("Error");
        return 1;
    }
    printf("Enter album name: ");
    scanf(" %29[^\n]", searchedWord);
    fread(sAlbum,sizeof(ALBUM),n,fp);

    for(int i=0;i<n;i++){
        if(strcmp((sAlbum+i)->album,searchedWord)==0){
            printf("\nArtist %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n\n", (sAlbum+i)->format);
            flag=1;
            printf("Album is available!\n");
        }
    }


    if(flag==0){
        printf("Searched album doesn't exist in repository!");
    }
    fclose(fp);
	free(sAlbum);
    getch();
    system("cls");

}

void deleteAlbum(){
	ALBUM* dAlbum = NULL;
	int n,index,flag=0;
	char s[30];
	FILE* fp = fopen("album.bin", "rb");
	if (fp == NULL) {
		printf("Repository is empty, might try option 1!");
		getch();
        system("cls");
        return;
	}
	else {
		fread(&n, sizeof(int), 1, fp);
		dAlbum = (ALBUM*)malloc(n * sizeof(ALBUM));
        if (dAlbum == NULL) {
			printf("Error");
			return 1;
		}
		else {
			fread(dAlbum, sizeof(ALBUM), n, fp);
			fclose(fp);
			system("cls");
			printf("Enter name of album to be deleted: ");
			scanf(" %29[^\n]", s);
			for (int i = 0; i < n; i++) {
				if (strcmp((dAlbum + i)->album, s) == 0) {
                    index = i;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				printf("\nAlbum is not available ");
			}
			else {
				fclose(fp);
				fp = fopen("album.bin", "wb");
				if (fp == NULL) {
					perror("Error");
					exit(EXIT_FAILURE);
				}
				else {
					n--;
					fwrite(&n, sizeof(int), 1, fp);
					for (int i = 0; i < n + 1; i++) {
						if (i == index) {
							continue;
						}
						else {
							fwrite((dAlbum + i), sizeof(ALBUM), 1, fp);
						}
					}
					printf("\nAlbum is deleted\n");
					fclose(fp);
					free(dAlbum);
				}
			}
		}
	}
}

void searchInRepository(){

    char searchedWord[30];
    int n,i,flag=0;

    FILE* fp=fopen("album.bin","rb");
    if(fp==NULL){
        printf("Repository is empty, might try option 1");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    ALBUM* sAlbum=(ALBUM*)malloc(n*sizeof(ALBUM));
    if(sAlbum==NULL){
        printf("Error");
        return 1;
    }
    printf("Enter searched word: ");
    scanf(" %29[^\n]", searchedWord);
    fread(sAlbum,sizeof(ALBUM),n,fp);
    alphabeticalSort(sAlbum,n);
    for(int i=0;i<n;i++){
        if(strcmp((sAlbum+i)->artist,searchedWord)==0){
            printf("\nArtist %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;

        }else if(strcmp((sAlbum+i)->album,searchedWord)==0){
            printf("\nArtist  %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;

        }else if(strcmp((sAlbum+i)->genre,searchedWord)==0){
            printf("\nArtist %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;

        }else if(strcmp((sAlbum+i)->format,searchedWord)==0){
            printf("\nArtist %s", (sAlbum+i)->artist);
            printf("\nAlbum: %s", (sAlbum+i)->album);
            printf("\nGenre: %s", (sAlbum+i)->genre);
            printf("\nFormat: %s\n", (sAlbum+i)->format);
            flag=1;
        }
    }
        if(flag==0){
            printf("Searched word doesn't exist in repository!");
        }

        fclose(fp);
        free(sAlbum);
        getch();
        system("cls");
}

void exitProgram() {
    char verification;
    printf("\nAre you sure you want to end the program ?(Y/N): ");


    while(1){
    scanf("%c", &verification);
    if((verification == 'Y') || (verification == 'N')){
        break;
    }
    printf("Wrong entry,try->Y/N: ");
    scanf("%c",&verification);
    }

    if(verification == 'Y'){
            exit(0);
        }

    else if(verification =='N'){
            int n;

            do{
                system("cls");

                printf("\n1) Add album \n");
                printf("2) Print all albums \n");
                printf("3) Delete album \n");
                printf("4) Print artist \n");
                printf("5) Print genre \n");
                printf("6) Album search \n");
                printf("7) Delete repository \n");
                printf("8) Search \n");
                printf("9) Save changes & Exit \n");

                do {
                    printf("\nEnter number: ");
                    scanf("%d", &n);
                    getchar();
                }while (n<1 || n>9);



                switchCase(n);
            }while(n!=9);
    }

}

void deleteFile() {

    printf("Do you really want to delete repository?\n");
    printf("Enter Y/N: ");
    int x;
    char verification;
    char filename[] = "album.bin";

    while(1){
    scanf("%c", &verification);
    if((verification == 'Y') || (verification == 'N')){
        break;
    }
    printf("Wrong entry,try->Y/N: ");
    scanf("%c",&verification);
    }
    if ('Y'== verification){
        x=remove(filename);
        if(x==0){
            printf("Successfully deleted repository");
            getch();
            system("cls");
            return;
        }else{
            printf("Failed to delete repository");
            getch();
            system("cls");
            return;
        }
    }
    if ('N'== verification){
        system("cls");
        return;
    }
}
