#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 100

//Declararea structurii
typedef struct arbore{
      char matrice[3][3];//tabla de X si O
      struct arbore *next[9];//vectorul de fii
      char flag;//true sau false 
      int tip;//tipul nodului(SI sau SAU)
}arbore;

//Numara fii nodului curent(minusurile din matrice)
int minusuri(arbore *cap)
{
	int k=0;
	if(cap->matrice[0][0]=='-') k++;
	if(cap->matrice[0][1]=='-') k++;
	if(cap->matrice[0][2]=='-') k++;
	if(cap->matrice[1][0]=='-') k++;
	if(cap->matrice[1][1]=='-') k++;
	if(cap->matrice[1][2]=='-') k++;
	if(cap->matrice[2][0]=='-') k++;
        if(cap->matrice[2][1]=='-') k++;
        if(cap->matrice[2][2]=='-') k++;
	return k;
}

//In cazul in care se gasesc cate 3 de X sau O pe aceeasi linie, coloana sau diagonala
//Jocul se incheie cu victoria unuia dintre jucatori
int final(arbore *cap)
{
   if(cap->matrice[0][0]=='X'&&cap->matrice[0][1]=='X'&&cap->matrice[0][2]=='X') return 0;
   if(cap->matrice[0][0]=='O'&&cap->matrice[0][1]=='O'&&cap->matrice[0][2]=='O') return 0;
   if(cap->matrice[1][0]=='X'&&cap->matrice[1][1]=='X'&&cap->matrice[1][2]=='X') return 0;
   if(cap->matrice[1][0]=='O'&&cap->matrice[1][1]=='O'&&cap->matrice[1][2]=='O') return 0;
   if(cap->matrice[2][0]=='X'&&cap->matrice[2][1]=='X'&&cap->matrice[2][2]=='X') return 0;
   if(cap->matrice[2][0]=='O'&&cap->matrice[2][1]=='O'&&cap->matrice[2][2]=='O') return 0;
   if(cap->matrice[0][0]=='X'&&cap->matrice[1][0]=='X'&&cap->matrice[2][0]=='X') return 0;
   if(cap->matrice[0][0]=='O'&&cap->matrice[1][0]=='O'&&cap->matrice[2][0]=='O') return 0;
   if(cap->matrice[0][1]=='X'&&cap->matrice[1][1]=='X'&&cap->matrice[2][1]=='X') return 0;
   if(cap->matrice[0][1]=='O'&&cap->matrice[1][1]=='O'&&cap->matrice[2][1]=='O') return 0;
   if(cap->matrice[0][2]=='X'&&cap->matrice[1][2]=='X'&&cap->matrice[2][2]=='X') return 0;
   if(cap->matrice[0][2]=='O'&&cap->matrice[1][2]=='O'&&cap->matrice[2][2]=='O') return 0;
   if(cap->matrice[0][0]=='X'&&cap->matrice[1][1]=='X'&&cap->matrice[2][2]=='X') return 0;
   if(cap->matrice[0][0]=='O'&&cap->matrice[1][1]=='O'&&cap->matrice[2][2]=='O') return 0;
   if(cap->matrice[0][2]=='X'&&cap->matrice[1][1]=='X'&&cap->matrice[2][0]=='X') return 0;
   if(cap->matrice[0][2]=='O'&&cap->matrice[1][1]=='O'&&cap->matrice[2][0]=='O') return 0;
   return 1;
}

//Functia de constructia si afisare a arborelui
void umple(arbore *cap, char mutare, FILE *fp2,int m,char sir[100])
{
        int z,i,j,y,q;
        if(strcmp(sir,"-c1")==0)//La cerinta 1 se afiseaza arborele
        {
        for(y=0;y<m;y++)
        fprintf(fp2,"\t");//m->nivelul pe care se gaseste nodul curent
        fprintf(fp2,"%c %c %c\n",cap->matrice[0][0],cap->matrice[0][1],cap->matrice[0][2]);
        for(y=0;y<m;y++)
        fprintf(fp2,"\t");
        fprintf(fp2,"%c %c %c\n",cap->matrice[1][0],cap->matrice[1][1],cap->matrice[1][2]);
        for(y=0;y<m;y++)
        fprintf(fp2,"\t");
        fprintf(fp2,"%c %c %c\n",cap->matrice[2][0],cap->matrice[2][1],cap->matrice[2][2]);
        fprintf(fp2,"\n");
        }
        z = minusuri(cap); //numarul de fii care trebuie adaugati
        int cnt = 0; //numar de fii adaugati
        if(minusuri(cap)!=0 && final(cap)==1)//Daca inca nu a castigat niciunul si 
        {                                    //mai sunt mutari disponibile
	     for(i=0;i<3;i++)
             {
	 	for(j=0;j<3;j++)       //Parcurge matricea nodului curent
                {                   
	    	    if(cap->matrice[i][j]=='-')//Verifica daca gasesti -
                    {
             	         arbore *tmp=malloc(sizeof(arbore));
             	         memcpy(tmp->matrice,cap->matrice,9); //copiaza matricea din cap in nodul nou
                         cap->next[cnt]=tmp;                  
                         cap->next[cnt]->matrice[i][j]= mutare; //se pune mutarea facuta
                         if(mutare=='X')//Daca mutarea a fost X urmatoarea va fi O si invers
                         umple(cap->next[cnt],'O',fp2,m + 1,sir);//Se apeleaza recursiv umple, se muta la fiul nodului curent si se incrementeaza nivelul
                         if(mutare=='O')
                         umple(cap->next[cnt],'X',fp2,m + 1,sir);
                         ++ cnt;//se incrementeaza numarul de fii adaugati
            }
          }
        }
      }
}

//Nodul este de tip SI daca toti fiii lui sunt de tip SI
int si(arbore *cap)
{
     int ok=1,i;
     for(i=0;i<minusuri(cap);i++)
     {
           if(cap->next[i]->flag=='F') ok=0;
     }
     return ok;
}

//Nodul este de tip SAU daca toti fiii lui sunt de tip SAU
int sau(arbore *cap)
{
     int s=0,i;
     for(i=0;i<minusuri(cap);i++)
     {
           if(cap->next[i]->flag=='T') s++;
     }
     if(s>0) return 1;
     else return 0;
}

//Completarea si afisarea arborelui cu true-false
void task2(arbore *cap,FILE *fp2,int m)
{
        int y,i;
  	for(y=0;y<m;y++)//m->numarul nivelului curent
        fprintf(fp2,"\t");
        if(final(cap)==0||minusuri(cap)==0)//Daca nodul curent e frunza(Daca jocul
        {                                  //se incheie prin lipsa de mutari sau castig)
        {                                        
              if(m%2==1) cap->flag='T';//In functie de ultima mutare(adica de
              else cap->flag='F';      //paritatea nivelului pe care se afla se aleg T si F)
              fprintf(fp2,"%c\n",cap->flag);//Afisare Flag(T sau F)
        }
        else 
        {
          if(m%2==0) //Daca ultima mutare a fost facuta de primul jucator nodul este de tip SAU
              {      //Adica de tip 0, altfel este de tip SI, adica de tip 1
               if(m%2==0) cap->tip=0;
               if(m%2==1) cap->tip=1;
               }  
          if(m%2==1) 
               {
                if(m%2==0)  cap->tip=1;
                if(m%2==1)  cap->tip=0;
               }
        if(cap->tip==1) //Daca este de tip SI ii dam valoarea in functie de fiii sai 
           {            //Si de functia SI de mai sus
              if(si(cap)==1) cap->flag='T';
              if(si(cap)==0) cap->flag='F';
              fprintf(fp2,"%c\n",cap->flag);
           }
        if(cap->tip==0) //Daca este de tip SAU ii dam valoarea in functie de fiii sai
           {            //Si de functia SAU de mai sus
                 if(sau(cap)==1) cap->flag='T';
                 if(sau(cap)==0) cap->flag='F';
                 fprintf(fp2,"%c\n",cap->flag);
           }
        for(i=0;i<minusuri(cap);i++) //Apelam recursiv pentru toti fiii
        {                            //cu incrementarea nivelului curent
              task2(cap->next[i],fp2,m+1);
        }
     }
}

//Eliberarea recursiva a memoriei
void eliberare(arbore *cap)
{
      int i;
      for(i=0;i<minusuri(cap);i++)
      if(final(cap)==1)
      eliberare(cap->next[i]);
      free(cap);
}

int main(int argc, char *argv[])
{
   int i,j;
   //Alocare dinamica
   arbore *cap = malloc(sizeof(arbore));
   //cap = malloc(10 * sizeof(arbore));
   FILE *fp1=fopen(argv[2],"r");
   FILE *fp2=fopen(argv[3],"w");
   char *mutare= (char *) malloc (BUFFER * sizeof (char));
   char *linie1= (char *) malloc (BUFFER * sizeof (char));
   char *linie2= (char *) malloc (BUFFER * sizeof (char));
   char *linie3= (char *) malloc (BUFFER * sizeof (char));
   char *linie4= (char *) malloc (BUFFER * sizeof (char));
   char *linie5= (char *) malloc (BUFFER * sizeof (char));
   char *linie6= (char *) malloc (BUFFER * sizeof (char));
   char *linie7= (char *) malloc (BUFFER * sizeof (char));
   char *linie8= (char *) malloc (BUFFER * sizeof (char));
   char *linie9= (char *) malloc (BUFFER * sizeof (char));
   if(strcmp("-c1",argv[1])==0)
   { 
        //Citire
        fscanf(fp1,"%s",mutare);
        fscanf(fp1,"%s %s %s",linie1,linie2,linie3);
        fscanf(fp1,"%s %s %s",linie4,linie5,linie6);
        fscanf(fp1,"%s %s %s",linie7,linie8,linie9);
        //Completare matrice radacina
        cap->matrice[0][0]=*linie1;
        cap->matrice[0][1]=*linie2;
        cap->matrice[0][2]=*linie3;
        cap->matrice[1][0]=*linie4;
        cap->matrice[1][1]=*linie5;
        cap->matrice[1][2]=*linie6;
        cap->matrice[2][0]=*linie7;
        cap->matrice[2][1]=*linie8;
        cap->matrice[2][2]=*linie9;
        //Constructia si afisarea arborelui si eliberarea memoriei
        umple(cap,mutare[0],fp2,0,"-c1");
        eliberare(cap);
        free(mutare);
        free(linie1);
        free(linie2);
        free(linie3);
        free(linie4);
        free(linie5);
        free(linie6);
        free(linie7);
        free(linie8);
        free(linie9); 
   }
   if(strcmp("-c2",argv[1])==0)
   {
        //Citire
        fscanf(fp1,"%s",mutare);
        fscanf(fp1,"%s %s %s",linie1,linie2,linie3);
        fscanf(fp1,"%s %s %s",linie4,linie5,linie6);
        fscanf(fp1,"%s %s %s",linie7,linie8,linie9);
        //Completare matrice radacina
        cap->matrice[0][0]=*linie1;
        cap->matrice[0][1]=*linie2;
        cap->matrice[0][2]=*linie3;
        cap->matrice[1][0]=*linie4;
        cap->matrice[1][1]=*linie5;
        cap->matrice[1][2]=*linie6;
        cap->matrice[2][0]=*linie7;
        cap->matrice[2][1]=*linie8;
        cap->matrice[2][2]=*linie9;
        //Apeluri functii si eliberare
        umple(cap,mutare[0],fp2,0,"-c2");
        //task2(cap,fp2,0);
        eliberare(cap);
        free(mutare);
        free(linie1);
        free(linie2);
        free(linie3);
        free(linie4);
        free(linie5);
        free(linie6);
        free(linie7);
        free(linie8);
        free(linie9);    
   }
   fclose(fp1);
   fclose(fp2);
   return 0;
}
