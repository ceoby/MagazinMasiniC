/// aplicatie de vanzari masini
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
int nr_anunt=0;
char model[100][100], descriere[100][100];
int kilometraj[100], an_fabricatie[100], pret[100];
/// functia de citire din fisier, apelata mereu la inceput de program
void read (){
    FILE *fp;
    char data[256];
    int i, j, k = 0, temp;
    fp = fopen("database.txt", "r");
    while (fgets(data, 256, fp) != NULL){
        nr_anunt += 1;
        j = 1;
        i = 0;
        while (data[i] != '/'){
            model[k][i] = data[i];
            i += 1;
            j += 1;
        }
        i += 1;
        while (data[i] != '/'){
            descriere[k][i - j] = data[i];
            i += 1;
        }
        i += 1;
        temp = 0;
        while (data[i] != '/'){
            temp *= 10;
            temp += (int)data[i] - 48;
            i += 1;
        }
        kilometraj[k] = temp;
        i += 1;
        temp = 0;
        while (data[i] != '/'){
            temp *= 10;
            temp += (int)data[i] - 48;
            i += 1;
        }
        an_fabricatie[k] = temp;
        i += 1;
        temp = 0;
        while (data[i] != '\n'){
            temp *= 10;
            temp += (int)data[i] - 48;
            i += 1;
        }
        pret[k] = temp;
        k += 1;
    }
    fclose(fp);
}
/// scrie o masina noua in database
void write (){
    FILE *fp;
    char data[256], tempc[100];
    int i, j, temp, k, nr = 0;
    fp = fopen("database.txt", "w");
    while (nr < nr_anunt)
    {
        i = 0;
        j = 0;
        while (model[nr][i]){
            data[j] = model[nr][i];
            i += 1;
            j += 1;
        }
        data[j] = '/';
        //
        j += 1;
        i = 0;
        while (descriere[nr][i]){
            data[j] = descriere[nr][i];
            i += 1;
            j += 1;
        }
        data[j] = '/';
        //
        j += 1;
        temp = kilometraj[nr];
        i = 0;
        while(temp){
            k = temp % 10;
            tempc[i] = k + '0';
            i += 1;
            temp /= 10;
        }
        while (i > 0){
            data[j] = tempc[i-1];
            i -= 1;
            j += 1;
        }
        data[j] = '/';
        //
        j += 1;
        temp = an_fabricatie[nr];
        i = 0;
        while(temp){
            k = temp % 10;
            tempc[i] = k + '0';
            i += 1;
            temp /= 10;
        }
        while (i > 0){
            data[j] = tempc[i-1];
            i -= 1;
            j += 1;
        }
        data[j] = '/';
        //
        j += 1;
        temp = pret[nr];
        i = 0;
        while(temp){
            k = temp % 10;
            tempc[i] = k + '0';
            i += 1;
            temp /= 10;
        }
        while (i > 0){
            data[j] = tempc[i-1];
            i -= 1;
            j += 1;
        }
        data[j] = '\n';
        //
        data[j + 1] = '\0';
        fprintf(fp, "%s", data);
        nr += 1;
    }
    fclose(fp);
}
/// functie de swap in lista
void swap (int i, int j){
    char tempc[100];
    int tempi;
    tempi = pret[i];
    pret[i] = pret[j];
    pret[j] = tempi;
    //
    tempi = kilometraj[i];
    kilometraj[i] = kilometraj[j];
    kilometraj[j] = tempi;
    //
    tempi = an_fabricatie[i];
    an_fabricatie[i] = an_fabricatie[j];
    an_fabricatie[j] = tempi;
    //
    strcpy(tempc, model[i]);
    strcpy(model[i], model[j]);
    strcpy(model[j], tempc);
    //
    strcpy(tempc, descriere[i]);
    strcpy(descriere[i], descriere[j]);
    strcpy(descriere[j], tempc);
}
/// toate sortarile
void sortare (int index){
    if (index==1){
       for (int i=0;i<nr_anunt-1;i++)
            for (int j=i+1;j<nr_anunt;j++)
                if(pret[i]>pret[j])
                    swap(i,j);
    }
    else if (index==2){
        for (int i=0;i<nr_anunt-1;i++)
            for (int j=i+1;j<nr_anunt;j++)
                if(kilometraj[i]>kilometraj[j])
                    swap(i,j);
    }
    else{
        for (int i=0;i<nr_anunt-1;i++)
            for (int j=i+1;j<nr_anunt;j++)
                if(an_fabricatie[i]<an_fabricatie[j]){
                    swap(i,j);
                }
    }
}
/// scoate un element din liste
void eliminare(int index){
    int i=0;
    while (pret[i]){
        if (pret[i+1]==0){
            nr_anunt -= 1;
            break;
        }
        else if (i==index){
            swap(i,i+1);
            index += 1;
        }
        i += 1;
    }
}
/// meniul de unde se apeleaza sortarile sau se intra in lista
void meniu_filtrare(){
    int check=0,prag=-1;
    char input;
    char select[5]=">>> ";
    char nselect[5]="    ";
    char optiune[5][100]={"Vizualizare lista",
    "Sorteaza lista dupa pret (mic->mare)",
    "Sorteaza lista dupa kilometri (mic->mare)",
    "Sorteaza lista dupa an (mare->mic)",
    "Afiseaza automobile sub un anumit pret"};
    char header[100]="~~~ Bun venit la meniul de filtrare! Alegeti o optiune pentru a continua ~~~";
    char bottom[100]="~~~ Apasa Escape pentru a reveni la meniul principal sau Enter pentru a selecta o optiune ~~~";
    if (nr_anunt==0){
        while(1){
            printf("%s\n", "Nu exista anunturi postate, apasati Escape pentru a reveni la meniul principal");
            input=getch();
            if (input==0 || input==0xE0){
                input=getch();
            }
            if (input==27){
                system("cls");
                break;
            }
            system("cls");
        }
    }
    else{
        while(1){
            printf("%s\n", header);
            for (int i=0;i<=4;i++){
                if (check==i){
                    printf("%s", select);
                    printf("%s\n", optiune[i]);
                }
                else{
                    printf("%s", nselect);
                    printf("%s\n", optiune[i]);
                }
            }
            printf("%s\n", bottom);
            input=getch();
            if (input==0 || input==0xE0){
                input=getch();
            }
            if (input==27){
                system("cls");
                break;
            }
            else if (input==72 && check > 0){
                check -= 1;
            }
            else if (input==80 && check < 4){
                check += 1;
            }
            else if (input==13){
                system("cls");
                if (check==0){
                    meniu_anunturi(prag);
                    if (nr_anunt==0){
                        return;
                    }
                }
                else if (check==1){
                    sortare(check);
                    check = 0;
                }
                else if (check==2){
                    sortare(check);
                    check = 0;
                }
                else if (check==3){
                    sortare(check);
                    check = 0;
                }
                else{
                    printf("insereaza pragul de pret dorit:");
                    scanf("%d", &prag);
                    system("cls");
                    meniu_anunturi(prag);
                    if (nr_anunt==0){
                        return;
                    }
                }
            }
            system("cls");
        }
    }
}
/// meniul cu lista de elemente
void meniu_anunturi (int index){
    int check=0;
    char input;
    char select[5] = ">>> ";
    char nselect[5] = "    ";
    char header[50]="~~~ Bun venit la meniul cu anunturi! ~~~";
    char bottom[100]="~~~ Apasa Escape pentru a reveni la meniul de filtrare sau Enter pentru a vedea un anunt ~~~";
    if (index!=-1){
        for (int i=0;i<nr_anunt;i++){
            if (pret[i]>=index){
                    eliminare(i);
            }
        }
    }
    while (1){
        printf("%s\n", header);
        for (int i=0;i<nr_anunt;i++){
            if (check==i){
                printf("%s", select);
                printf("%s\n", model[i]);
            }
            else{
                printf("%s", nselect);
                printf("%s\n", model[i]);
            }
        }
        printf("%s\n", bottom);
        input=getch();
        if (input==0 || input==0xE0){
            input=getch();
        }
        if (input==27){
            system("cls");
            break;
        }
        else if (input==72 && check > 0){
            check -= 1;
        }
        else if (input==80 && check < nr_anunt-1){
            check += 1;
        }
        else if (input==13){
            system("cls");
            submeniu_anunturi(check);
            check=0;
            if (nr_anunt==0){
                return 0;
            }
        }
            system("cls");
    }
}
/// submeniul unui element specific
void submeniu_anunturi (int index){
    int check = 0;
    char input;
    char select[5] = ">>> ";
    char nselect[5] = "    ";
    char optiuni[2][100] = {"Cumpara automobil", "Revenire la anunturi"};
    char header[100] = "~~~ Meniu achizitionare automobil ~~~";
    char bottom[100] = "~~~ Apasa Enter pentru a selecta o optiune ~~~";
    while (1){
        printf("%s\n", header);
        printf("Modelul automobilului:     %s\n", model[index]);
        printf("Descriere a automobilului: %s\n", descriere[index]);
        printf("Kilometraj automobil:      %d KM\n", kilometraj[index]);
        printf("An fabricatie:             %d\n", an_fabricatie[index]);
        printf("Pretul automobilului:      %d RON\n", pret[index]);
        for (int i=0;i<2;i++){
            if (check==i){
                printf("%s", select);
                printf("%s\n", optiuni[i]);
            }
            else{
                printf("%s", nselect);
                printf("%s\n", optiuni[i]);
            }
        }
        printf("%s\n", bottom);
        input=getch();
		if (input==0 || input==0xE0) input=getch();
        if (input==72 && check > 0){
            check -= 1;
        }
        else if (input==80 && check < 1){
            check += 1;
        }
        else if (input==13){
            if (check==0){
                system("cls");
                eliminare(index);
                break;
            }
            else{
                system("cls");
                break;
            }
        }
        system("cls");
    }
}
/// meniul de unde adaugam elemente in lista
void meniu_postare (){
    int check=0;
    char input;
    char temp;
    char header[50] = "~~~ Bun venit la meniul de postari! ~~~";
    char bottom[100] = "~~~ Apasa Escape pentru a reveni la meniul principal sau Enter pentru a reintroduce datele ~~~";
    while (1) {
        if (check==0){
            printf("%s\n", header);
            printf("Introduceti numele modelului de automobil:  ");
            scanf("%[^\n]", model[nr_anunt]);
            scanf("%c",&temp);
            printf("Introduceti o descriere a automobilului:    ");
            scanf("%[^\n]", descriere[nr_anunt]);
            printf("Introduceti kilometrajul automobilului:     ");
            scanf("%d", &kilometraj[nr_anunt]);
            printf("Introduceti anul fabricatiei automobilului: ");
            scanf("%d", &an_fabricatie[nr_anunt]);
            printf("Introduceti pretul automobilului (in RON):  ");
            scanf("%d", &pret[nr_anunt]);
            scanf("%c",&temp);
            check = 1;
        }
        printf("%s\n", bottom);
        input=getch();
		if (input==0 || input==0xE0) input=getch();
		system("cls");
		if (input==13) check = 0;
		else if (input==27){
            nr_anunt += 1;
            break;
		}
    }
}
/// meniul pt design interfata
void meniu_design(){
    int check = 0;
    char input;
    char header[100] = "~~~ Bun venit la meniul de design! ~~~";
    char bottom[100] = "~~~ Apasa Escape pentru a iesi din meniu sau Enter pentru a schimba interfata ~~~";
    char optiune[4][100] = {"Black - Green (default)","Black - White","White - Black","Blue - Bright_White"};
    char select[5] = ">>> ";
    char nselect[5] = "    ";
    while(1){
        printf("%s\n", header);
        for (int i=0;i<=3;i++){
            if (check==i){
                printf("%s", select);
                printf("%s\n", optiune[i]);
            }
            else{
                printf("%s", nselect);
                printf("%s\n", optiune[i]);
            }
        }
        printf("%s\n", bottom);
        input=getch();
        if (input==0 || input==0xE0){
            input=getch();
        }
        if (input==27){
            system("cls");
            break;
        }
        else if (input==72 && check > 0){
            check -= 1;
        }
        else if (input==80 && check < 3){
            check += 1;
        }
        else if (input==13){
            if (check==0){
                system("color 02");
            }
            else if (check==1)
            {
                system("color 07");
            }
            else if (check==2)
            {
                system("color 70");
            }
            else{
                system("color 1F");
            }
        }
        system("cls");
    }
}
/// meniul principal
void meniu_principal (){
    int check = 0;
    char input;
    char header[100] = "~~~ Bun venit la vanzari-automobile.ro! ~~~";
    char bottom[100] = "~~~ Apasa Escape pentru a iesi din meniu sau Enter pentru a intra intr-un submeniu ~~~";
    char optiune[3][100] = {"Vizualizeaza anunturile","Posteaza un anunt","Schimba designul interfatei"};
    char select[5] = ">>> ";
    char nselect[5] = "    ";
    while (1){
        printf("%s\n", header);
        for (int i=0;i<=2;i++){
            if (check==i){
                printf("%s", select);
                printf("%s\n", optiune[i]);
            }
            else{
                printf("%s", nselect);
                printf("%s\n", optiune[i]);
            }
        }
        printf("%s\n", bottom);
        input=getch();
        if (input==0 || input==0xE0){
            input=getch();
        }
        if (input==27){
            system("cls");
            break;
        }
        else if (input==72 && check > 0){
            check -= 1;
        }
        else if (input==80 && check < 2){
            check += 1;
        }
        else if (input==13){
            system("cls");
            if (check==0){
                meniu_filtrare();
            }
            else if (check==1)
            {
                meniu_postare();
            }
            else{
                meniu_design();
            }
        }
        system("cls");
    }
}
/// main in care apelam meniul
int main() {
    system("color 02");
    read();
    meniu_principal();
    write();
    return 0;
}
