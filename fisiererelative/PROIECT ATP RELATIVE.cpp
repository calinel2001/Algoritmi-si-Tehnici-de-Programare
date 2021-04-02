#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>

typedef struct
{
	int cod;
	char denumire[20];
	float pret;
	int cantitate[3];
	int is;
} produs;

//CULORI

void red() {
	printf("\033[1;31m");
}
void yellow()
{
	printf("\033[1;33m");
}
void cyan()
{
	printf("\033[1;36m");
}
void green() {
	printf("\033[1;32m");
}
void purple() {
	printf("\033[1;35m");
}
void reset() {
	printf("\033[0m");
}
//SFARSIT CULORI

int nrarticole(FILE* f, int lungime)
{
	int c = ftell(f);
	fseek(f, 0, 2);
	int nr = ftell(f) / lungime;
	fseek(f, c, 0);
	return nr;
}

//1
void crearefisier(FILE* f, char* denumire)
{
	produs x;
	int i;
	int codprodus;
	printf("Codul produsului: ");
	scanf("%d", &codprodus);
	while (!feof(stdin))
	{
		int nr = nrarticole(f, sizeof(produs));

		if (codprodus >= nr)
		{
			fseek(f, 0, 2);
			x.is = 0;
			for (i = nr; i <= codprodus; i++)
				fwrite(&x, sizeof(produs), 1, f);
		}
		fseek(f, codprodus * sizeof(produs), 0);
		fread(&x, sizeof(produs), 1, f);

		if (x.is == 1)
			printf("\nExista deja ");
		else
		{
			x.cod = codprodus;
			printf("Denumire: ");
			gets_s(x.denumire);
			gets_s(x.denumire);
			printf("Pret: ");
			scanf("%f", &x.pret);
			for (int i = 0; i < 3; i++) {
				printf("Cantitate[%d]= ", i);
				scanf("%d", &x.cantitate[i]);
			}
			x.is = 1;
			fseek(f, codprodus * sizeof(produs), 0);
			fwrite(&x, sizeof(produs), 1, f);
		}
		printf("\nCodul produsului: ");
		scanf("%d", &codprodus);
	}
}

//2
void listareintegrala(FILE* f, char* denumire) {
	FILE* g;
	produs x;
	char numefisiertext[20];
	printf("INTRODU NUMELE FISIERULUI TEXT: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, " wt");
	fprintf(g, "COD\tDenumire produs\tPret\tCantitati\t\t\n");
	fread(&x, sizeof(produs), 1, f);
	while (!feof(f))
	{
		if (x.is == 1) {
			fprintf(g, "COD: %d  Denumire: %s Pret: %.2f Cantitate: ", x.cod, x.denumire, x.pret);
			for (int i = 0; i < 3; i++)
				fprintf(g, "%d ", x.cantitate[i]);
			fprintf(g, "\n");
		}
		fread(&x, sizeof(produs), 1, f);
	}

	fclose(g);
}

//3
void consultareselectie(FILE* f, char* denumire)
{
	FILE* g;
	produs x;
	int i;
	char numefisiertext[20];
	printf("Introduceti numele fisierului text: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, "wt");
	if (!g)
		printf("\nAyaye -consultare selectie");
	else
	{
		float valoareMaximProduse = 0;
		float valoareprodus;
		int cod = 0;
		fread(&x, sizeof(produs), 1, f);
		while (!feof(f))
		{
			if (x.is)
			{
				valoareprodus = 0;
				for (i = 0; i < 3; i++)
				{
					valoareprodus = valoareprodus + x.pret * x.cantitate[i];
				}

				if (valoareprodus > valoareMaximProduse)
				{
					fclose(g);
					g = fopen(numefisiertext, "w");

					valoareMaximProduse = valoareprodus;
					fprintf(g, "Produsele cu val maxima %.2f sunt: ", valoareMaximProduse);
				}
				if (valoareprodus == valoareMaximProduse)
				{
					fprintf(g, "\nProdusul %s cu codul %d", x.denumire, x.cod);
				}
			}
			cod++;
			fread(&x, sizeof(produs), 1, f);
		}
		fclose(g);
	}
}
//4
void stergerearticol(FILE* f, char* denumire)
{
	int i;
	produs x;
	int luniproductienula = 0;
	FILE* g;
	char numefisiertext[20];
	printf("Numele fisierului  text: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, "wt");
	int nrprodusesterse = 0;
	fread(&x, sizeof(produs), 1, f);
	while (!feof(f))
	{
		if (x.is)
		{
			luniproductienula = 0;

			for (i = 0; i < 3 && luniproductienula == 0; i++)
			{
				if (x.cantitate[i] == 0)
					luniproductienula++;
			}

			if (luniproductienula)
			{
				green();  printf("\nSe sterge produsul %s...\n", x.denumire); reset();
				fseek(f, ftell(f) - sizeof(produs), 0);
				x.is = 0;
				fwrite(&x, sizeof(produs), 1, f);
				fprintf(g, "S-a modificat produsul %s cu codul %d\n", x.denumire, x.cod);
				fseek(f, 0, SEEK_CUR);
				nrprodusesterse++;
			}
		}
		fread(&x, sizeof(produs), 1, f);
	}
	fprintf(g, "\n Au fost sterse %d  articole ", nrprodusesterse);
	fclose(g);
}
//5
void modificarecantitate(FILE* f, char* denumire)
{
	produs x;
	int numarluna;
	FILE* g;
	char numefisiertext[20];
	printf("Introduceti numele fisierului text: ");
	scanf("%s", numefisiertext);
	g = fopen(numefisiertext, "wt");
	int codproduscautat;
	int cantitatenoua;

	printf("\nCodul produsului cautat:  ");
	scanf("%d", &codproduscautat);

	while (!feof(stdin))
	{
		int nrart = nrarticole(f, sizeof(produs));
		printf("nr articole: %d\n", nrart);

		if (codproduscautat > nrart)
			printf("\nProdusul nu exista.\n");
		else {
			fseek(f, codproduscautat * sizeof(produs), 0);
			fread(&x, sizeof(produs), 1, f);

			if (x.is)
			{
				printf("\nNumar luna a carei cantitate doriti sa o modificati :");
				scanf("%d", &numarluna);

				fseek(f, ftell(f) - sizeof(produs), 0);
				printf("\nCantitatea noua: \n");
				scanf("%d", &cantitatenoua);
				if (numarluna >= 0 && numarluna <= 3)
					x.cantitate[numarluna] = cantitatenoua;
				fwrite(&x, sizeof(produs), 1, f);
				fseek(f, 0, 1);
				fprintf(g, "Produsul %s cu codul %d a fost modificat", x.denumire, x.cod);
			}
		}
		printf("\nCodul produsului cautat:  ");
		scanf("%d", &codproduscautat);
	}
	fclose(g);
}
//6
void adaugarearticol(FILE* f, char* denumire)
{
	int i;
	produs x;
	fseek(f, 0, 2);
	int codprodusnou;
	yellow(); printf("\nCod produs nou: "); reset();
	scanf("%d", &codprodusnou);
	while (!feof(stdin))
	{
		int nr = nrarticole(f, sizeof(produs));
		if (codprodusnou >= nr)
		{
			x.is = 0;
			for (i = nr; i <= codprodusnou; i++)
				fwrite(&x, sizeof(produs), 1, f);
		}
		fseek(f, codprodusnou * sizeof(produs), 0);
		fread(&x, sizeof(produs), 1, f);

		if (x.is == 1)
			printf("\nExista deja ");
		else
		{
			x.cod = codprodusnou;
			x.is = 1;
			printf("Introduceti denumirea :");
			gets_s(x.denumire);
			gets_s(x.denumire);
			printf("Introduceti pret: ");
			scanf("%f", &x.pret);
			for (i = 0; i < 3; i++)
			{
				printf("Cantitate[%d]= ", i);
				scanf("%d", &x.cantitate[i]);
			}
			fseek(f, codprodusnou * sizeof(produs), 0);
			fwrite(&x, sizeof(produs), 1, f);
		}
		yellow(); printf("\nCod produs nou: "); reset();
		scanf("%d", &codprodusnou);
	}
}

void main()
{
	int codoperatie;
	int i;
	produs x;
	FILE* f;
	char numefb[20];
	char answer;

	purple(); printf("  \n\nCodurile pentru operatii sunt: \n"); 	reset();

	green();
	printf("\n '1'- Pentru a crea un fisier relativ binar ");
	printf("\n '2'- Pentru a trece datele din fisierul binar intr-un fisier text ");
	printf("\n '3'- Pentru a trece , intr-un fisier text, produsele cu cea mai mare valoare pe an ");
	printf("\n '4'-Pentru stergerea produselor care au inregistrat productie zero în cel putin o luna.");
	printf("\n '5'-Pentru a modifica cantitate pentru produsele ale caror coduri se introduc de la tastatura.");
	printf("\n '6'-Pentru a adauga un articol nou in fisier.");
	reset();

	do
	{

		yellow();  printf("  \n\nIntroduceti numele fisierului: "); reset();
		scanf("%s", numefb);

		cyan(); 
		printf("  \n\n Codul pentru operatia pe care vreti sa o faceti: "); reset();
		scanf("%d", &codoperatie);

		switch (codoperatie)
		{
		case 1:
		{
			f = fopen(numefb, "wb+");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=1 ");
				reset();
			}
			else
			{
				crearefisier(f, numefb);
				fclose(f);
			}
		}break;

		case 2:
		{
			f = fopen(numefb, "rb");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=2");
				reset();
			}
			else
			{
				listareintegrala(f, numefb);
				fclose(f);
			}
		}break;

		case 3:
		{
			f = fopen(numefb, "rb");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=3");
				reset();
			}
			else
			{
				consultareselectie(f, numefb);
				fclose(f);
			}
		}break;

		case 4:
		{
			f = fopen(numefb, "rb+");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=4");
				reset();
			}
			else
			{
				stergerearticol(f, numefb);
				fclose(f);
			}
		}break;

		case 5:
		{
			f = fopen(numefb, "rb+");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=5");
				reset();
			}
			else
			{
				modificarecantitate(f, numefb);
				fclose(f);
			}
		}break;

		case 6:
		{
			f = fopen(numefb, "rb+");
			if (!f)
			{
				red();
				printf("\n\nNu s-a putut deschide din main---cod=5");
				reset();
			}
			else
			{
				adaugarearticol(f, numefb);
				fclose(f);
			}
		}break;

		default: {
			red();
			printf("\n Nu ati selectat un cod valid");
			reset();
		}
		}

		printf("\nPress 'Y' or 'y' to continue. Press any other key to exit the program ");
		scanf("%c", &answer);

	} while (answer == 'Y' || answer == 'y');
}