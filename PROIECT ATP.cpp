#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <cstdlib>

typedef struct {
	int numarMatricol;
	char nume[30];
	int an;
	int grupa;
	int numarNote;
	int note[15];
} student;

//1
void crearefisierbinar(FILE* f, char* denumire)
{
	student x;

	int numarmatricol;
	printf("Numarul matricol: ");
	scanf("%d", &x.numarMatricol);
	while (!feof(stdin) && x.numarMatricol != -1)
	{
		printf("Nume: ");
		gets_s(x.nume);
		gets_s(x.nume);

		printf("An: ");
		scanf("%d", &x.an);

		printf("Grupa: ");
		scanf("%d", &x.grupa);

		printf("Numar note: ");
		scanf("%d", &x.numarNote);

		printf("\n");
		for (int i = 0; i < x.numarNote; i++)
		{
			printf("Note[%d]= ", i + 1);
			scanf("%d", &x.note[i]);
		}
		fwrite(&x, sizeof(student), 1, f);

		printf("\nNumarul matricol: ");
		scanf("%d", &x.numarMatricol);
	}
	fclose(f);
}
//2
void convertireintext(FILE* f, char* denumire)
{
	student x;
	FILE* g;

	char numefisiertext[20];
	printf("Numele fisierului text este: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, "wt");
	if (!g)
	{
		printf("\nUPSI -CONVERTIRE TEXT");
	}
	else {
		fread(&x, sizeof(student), 1, f);
		fprintf(g, "NRM\t NUME\t          An     Grupa         Note\n\n\n");
		while (!feof(f)) {
			fprintf(g, "%d      %s           %d        %d ", x.numarMatricol, x.nume, x.an, x.grupa);
			for (int i = 0; i < x.numarNote; i++)
				fprintf(g, "%d ", x.note[i]);
			fprintf(g, "\n");
			fread(&x, sizeof(student), 1, f);
		}
		fclose(f);
		fclose(g);
	}
}
//3
void selectiedupanrmatricol(FILE* f, char* denumire) {
	student x;
	int nrmcautat; int gasit;
	printf("Numar matricol cautat: ");
	scanf("%d", &nrmcautat);

	while (!feof(stdin) && nrmcautat != -1) {
		rewind(f);
		gasit = 0;
		fread(&x, sizeof(student), 1, f);
		while (!feof(f) && gasit == 0)
		{
			if (nrmcautat == x.numarMatricol)
			{
				gasit = 1;
				printf("NumarM: %d Nume: %s An: %d Grupa: %d\n", x.numarMatricol, x.nume, x.an, x.grupa);
				for (int i = 0; i < x.numarNote; i++)
					printf("Note[%d]= %d ", i + 1, x.note[i]);
			}
			fread(&x, sizeof(student), 1, f);
		}
		if (gasit == 0)
			printf("Teapa fraere -selectie dupa numar matricol");

		printf("\nNumar matricol cautat: ");
		scanf("%d", &nrmcautat);
	}
	fclose(f);
}
//4
void selectiedupagrupa_fisier(FILE* f, char* denumire)
{
	student x;
	FILE* g;
	char numefisiertext[20];
	printf("Numele fisierului text: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, "wt");
	if (!g)
		printf("\nNu s-a putut deschide -selectiedupagrupa_fisier");
	else
	{
		int grupacautata, gasit;
		printf("Grupa cautata: ");
		scanf("%d", &grupacautata);

		fread(&x, sizeof(student), 1, f);
		while (!feof(stdin) && grupacautata != -1)
		{
			rewind(f);
			gasit = 0;
			while (!feof(f))
			{
				if (grupacautata == x.grupa)
				{
					gasit = 1;
					fprintf(g, "\nNumar Matricol: %d Nume: %s An: %d Grupa: %d  Note: ", x.numarMatricol, x.nume, x.an, x.grupa);
					for (int i = 0; i < x.numarNote; i++)
						fprintf(g, "%d ", x.note[i]);
				}
				fread(&x, sizeof(student), 1, f);
			}
			if (gasit == 0)
				printf("Nu s-a gasit");

			printf("\nGrupa cautata: ");
			scanf("%d", &grupacautata);
		}
		fclose(f); fclose(g);
	}
}
//5
void adaugare_modificare_articol(FILE* f, char* denumire) {
	student x;
	int nrmcautat;
	printf("Numar matricol cautat: ");
	scanf("%d", &nrmcautat);
	int gasit;
	while (!feof(stdin) && nrmcautat != -1)
	{
		rewind(f);
		gasit = 0;
		fread(&x, sizeof(student), 1, f);
		while (!feof(f) && gasit == 0)
		{
			if (nrmcautat == x.numarMatricol)
			{
				gasit = 1;
				printf("Nr Matricol: %d Nume: %s An: %d Grupa: %d \n Note: \n", x.numarMatricol, x.nume, x.an, x.grupa);
				for (int i = 0; i < x.numarNote; i++)
					printf("Note[%d]= %d \n", i + 1, x.note[i]);
				fseek(f, ftell(f) - sizeof(student), 0);
				printf("\nIntroduceti noua nota la ATP: ");
				scanf("%d", &x.note[0]);

				fwrite(&x, sizeof(student), 1, f);
				fseek(f, 0, 1);
			}
			fread(&x, sizeof(student), 1, f);
		}
		if (gasit == 0)
			printf("\nNu s-a gasit cumpanasule -adaugare_modificare_articol ");

		printf("\nNumar matricol cautat: ");
		scanf("%d", &nrmcautat);
	}
	fclose(f);
}
//6
void modificare_selectie(FILE* f, char* denumire)
{
	student x;
	int  grupacautata;
	printf("\nIntroduceti grupa cautata: ");
	scanf("%d", &grupacautata);
	int gasit;
	while (!feof(stdin) && grupacautata != -1)
	{
		rewind(f);
		gasit = 0;
		fread(&x, sizeof(student), 1, f);
		while (!feof(f)) {
			if (grupacautata == x.grupa)
			{
				gasit = 1;
				printf("\nNrM: %d Nume: %s An: %d Grupa: %d \n Note: ", x.numarMatricol, x.nume, x.an, x.grupa);
				for (int i = 0; i < x.numarNote; i++)
					printf("Note[%d]= %d ", i + 1, x.note[i]);
				printf("\nTrb sa adaugam 1 la nota de la atp\n");
				fseek(f, ftell(f) - sizeof(student), 0);
				if (x.note[0] < 10)
					x.note[0] = x.note[0] + 1;
				fwrite(&x, sizeof(student), 1, f);
				fseek(f, 0, SEEK_CUR);
			}
			fread(&x, sizeof(student), 1, f);
		}
		if (gasit == 0)
			printf("\nNu s-a gasit -modificare selectie");

		printf("\nIntroduceti grupa cautata: ");
		scanf("%d", &grupacautata);
	}
	fclose(f);
}
//7
void adaugare_infisier(FILE* f, char* denumire)
{
	student x;
	fseek(f, 0, 2);
	printf("Numar matricol: ");
	scanf("%d", &x.numarMatricol);
	while (!feof(stdin) && x.numarMatricol != -1)
	{
		printf("Nume: ");
		gets_s(x.nume);
		gets_s(x.nume);
		printf("An: ");
		scanf("%d", &x.an);
		printf("Grupa: ");
		scanf("%d", &x.grupa);
		printf("Numar note: ");
		scanf("%d", &x.numarNote);
		for (int i = 0; i < x.numarNote; i++)
		{
			printf("Note[%d]= ", i);
			scanf("%d", &x.note[i]);
		}
		fwrite(&x, sizeof(student), 1, f);
		printf("\nNumar matricol: ");
		scanf("%d", &x.numarMatricol);
	}
	fclose(f);
}
//8
void stergere_dinfisier(FILE* f, char* denumire) {
	student x;
	FILE* g;
	char numefisiertemp[20];
	int nrmcautat;
	printf("\nNumele fisierului temporar: ");
	scanf("%s", numefisiertemp);
	g = fopen(numefisiertemp, "wb");
	if (!g)
		printf("\nNu s-a putut deschide -stergere_dinfisier");
	else
	{
		printf("\nNumarul matricol cautat: ");
		scanf("%d", &nrmcautat);
	
		fread(&x, sizeof(student), 1, f);
		while (!feof(f)) 
		{
			if (nrmcautat != x.numarMatricol)
			{
				fwrite(&x, sizeof(student), 1, g);
		     }
			fread(&x, sizeof(student), 1, f);
		}
		fclose(f);
		fclose(g);

		int stergere = remove(denumire);
		if (stergere == -1)
			printf("\nNu s-a putut face stergerea ");
		int redenumire = rename(numefisiertemp, denumire);
		if (stergere == -1)
			printf("\nNu s-a putut face redenumirea ");
	}
}

int main()
{
	printf("\n\nCodurile pentru operatii sunt: ");
	printf("\n '1' -Pentru crearea unui fisier binar  ");
	printf("\n '2' -Pentru a converti fisierul binar intr-un fisier text");
	printf("\n '3' -Afisarea datelor despre studentii ale caror numere matricole sunt introduse de la tastatura");
	printf("\n '4' -Sa se scrie programul care listeaza , in fisiere text, situatia studentilor din grupele ale caror numere se introduc de la tastatura ");
	printf("\n '5'- Sa se scrie programul pentru adaugarea notei la disciplina algoritmi si tehnici de programare pentru studenul al carui numar matricol este introdus de la tastatura");
	printf("\n '6'- Sa se scrie programul pentru adaugarea punctului din oficiu la nota la ATP pentru studentii din grupa al carei numar este introdus de la tastatura");
	printf("\n '7'- Sa se scrie programul pentru adaugarea unui articol in fisier");
	printf("\n '8'-Sa se scrie programul care realizeaza stergerea unor articole din fisierul secvential ");

	FILE* f;
	student x;
	char answer;

beginning:

	printf("\n\n\nIntroduceti codul pentru operatia pe care vreti sa o faceti: ");
	int cod;
	scanf("%d", &cod);

	{
		if (cod == 1)
		{
			//CREARE FISIER BINAR
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "wb");
			if (!f) { printf("\nNu s-a putut deschide din main,cod=1"); }
			else {
				crearefisierbinar(f, numefisierbinar);
			}
		}
		if (cod == 2)
		{
			//CONSULTARE INTEGRALA
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=2");
			else
				convertireintext(f, numefisierbinar);
		}
		if (cod == 3)
		{
			//Afisarea datelor despre studentii ale caror numere matricole sunt introduse de la tastatura
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=3");
			else
				selectiedupanrmatricol(f, numefisierbinar);
		}

		if (cod == 4)
		{
			//Să se scrie programul care listează, în fişiere text, situaţia studenţilor din grupele ale căror numere se introduc de la tastatură
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=4");
			else
				selectiedupagrupa_fisier(f, numefisierbinar);
		}

		if (cod == 5)
		{
			//Sa se scrie programul pentru adaugarea notei la disciplina algoritmi si tehnici de programare pentru studenul al
			// carui numar matricol este introdus de la tastatura
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb+");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=5");
			else
				adaugare_modificare_articol(f, numefisierbinar);
		}

		if (cod == 6)
		{
			//Să se scrie programul pentru adăugarea punctului din oficiu la nota la ATP pentru studenţii
			/// din grupa al cărei număr este introdus de la tastatură.
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb+");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=6");
			else
				modificare_selectie(f, numefisierbinar);
		}

		if (cod == 7)
		{
			//Adaugare
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb+");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=7");
			else
				adaugare_infisier(f, numefisierbinar);
		}

		if (cod == 8)
		{
			//Stergere
			char numefisierbinar[20];
			printf("\nIntroduceti numele fisierului binar:  ");
			scanf("%s", numefisierbinar);
			f = fopen(numefisierbinar, "rb+");
			if (!f)
				printf("\nNu s-a putut deschide din  main cod=7");
			else
				stergere_dinfisier(f, numefisierbinar);
		}

		printf("\nPress y to continue. Press any Key To Exit ");
		
		//O litera/cifra, nu ENTER pentru ca nu o sa mearga
		scanf(" %c", &answer); 
		if (answer == 'y' || answer == 'Y')
			goto beginning;
		else
			exit(0);
	}
}
