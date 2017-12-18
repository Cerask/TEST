#include<stdio.h>
#include<stdlib.h>
#include<string.h>


    void function_v(FILE** F_x)
    {
    	char c;

    	if ( (*F_x = fopen("predaj.txt","r")) == NULL)
    	   printf("Neotvoreny subor\n");
    	else {
			printf("Vypis zaznamov:\n");
    		printf("---------------\n");
    		
        	while(1) {				
    			printf("meno priezvisko: ");
    			do putchar(c=getc(*F_x)); while (c!= '\n');
    			printf("SPZ: ");
    			do putchar(c=getc(*F_x)); while (c!= '\n');
    			printf("typ auta: "); 	
    			do putchar(c=getc(*F_x)); while (c!= '\n');
    			printf("cena: ");
    			do putchar(c=getc(*F_x)); while (c!= '\n');
    			printf("datum: ");
    			do putchar(c=getc(*F_x)); while (c!= '\n');
    		
    			if ( (c=getc(*F_x)) == EOF) break;
    			else putchar(c);
    		}
    		putchar('\n');
    	}
    	rewind(*F_x);
	}
	
	
	void function_o(FILE* F_x)
	{
		char   c, stav, meno[51], spz[7];
		long   x, datum;
		double cena;
		
		scanf("%ld",&x);
		
		printf("Odmeny pre zamestnancov:\n");
    	printf("------------------------\n");
		
		while(1) {
			
			fgets(meno, 52, F_x);              
			meno[strlen(meno)-1]=0;
			
			fscanf(F_x, "%s\n", spz); 		
			
		    stav=getc(F_x); 				
			getc(F_x);
		    
		    cena=0;                            
		    while ( (c=getc(F_x)) != '.')
		    {
		    	cena = cena * 10 + (c - '0');
		    }
		    c=getc(F_x);
			 cena=cena+(c - '0')/10.00;
		    c=getc(F_x); 
			cena=cena+(c - '0')/100.00;   
		    getc(F_x);
		    
		    datum=0;						   
		    while ( (c=getc(F_x)) != '\n')
		    	datum = datum * 10 + (c - '0');
		    	
		    if (stav=='1')
			{
				cena = cena * 0.015;
			}
		    else 
		    {
				cena = cena * 0.022;
		    }	
		    if (x-datum>=10000) 
			{
				printf("%s %s %.2lf\n", meno, spz, cena);
		    }
		    
		    c=getc(F_x);
    		if (c==EOF)
			{
				break;
			}
		}
		rewind(F_x);
	}
	
	
	int function_n(FILE* F_x, char **arr, int *aloc)
	{
		char c, str[51];
		int i, count=1;
		
		if (F_x==0) {
			printf("Subor nie je otvoreny\n");
			return 0;
		}
		
		while ((c=getc(F_x)) != EOF) if (c=='\n') count++;
		count/=6;
		rewind(F_x);
		
		if (*aloc) free(*arr);	
		*arr = (char*) calloc(count * 7, sizeof(char));
		*aloc = 1;
				
		count=0;
		while(1) {
			fgets(str, 52, F_x);
			
			for (i=0; i<7; i++)	(*arr)[i+7*count]=getc(F_x);                     
			getc(F_x);
			for (i=0; i<3; i++) fscanf(F_x, "%s\n",str);
			
			count++;
    		if (feof(F_x)) break;
		}
		rewind(F_x);
		printf("Pole sa alokovalo\n");
		return count;
	}


	void function_s(int p, char *arr, int aloc)
	{
		int i,j, count=7;
		
		if (aloc==2) count=9;
		
		if (aloc) {
			printf("SPZ polozky:\n");
			printf("------------\n");
			for (i=0; i<p; i++) {
				for (j=0; j<7; j++) {
					if (j==2 || j==5) putchar(' ');
					putchar(arr[i*count+j]);
    			}
				putchar('\n');
				
    			if (aloc==2) printf("%c%c\n",arr[i*9+7],arr[i*9+8]);
			}
		}
		else printf("Pole nie je vytvorene\n");
	}
	
	
	void function_p(int p, char *arr, int aloc)
	{
		int i;
		if (aloc) {
			printf("Palindromy:\n");
			printf("-----------\n");
			for (i=0; i<p; i++)
				if ( arr[i*7] == arr[i*7+6] && arr[i*7+1] == arr[i*7+5] && arr[i*7+2] == arr[i*7+4] ) 
					printf("%c%c\n", arr[i*7], arr[i*7+1]);
		}
        else printf("Pole nie je vytvorene\n");
	}
	
	
	void function_z(int p, char *arr, int aloc)
	{
		int i, j, town, memory=1, *AR1, *AR2, search;
			
		if (aloc && p>0) {
			
			printf("Z ktoreho okresu sa predalo najviac aut:\n");
			printf("----------------------------------------\n");
			
			AR1 = (int*) calloc(1, sizeof(int) );
			AR2 = (int*) calloc(1, sizeof(int) );
			AR1[0] = arr[0]*100 + arr[1];
			AR2[0] = 1;
		    
		   for (i=1; i<p; i++) {
				town = arr[i*7]*100 + arr[i*7+1];
				search = 0;
				for (j=0; j < memory; j++)
					if (AR1[j]==town) { 
					   AR2[j]++;
					   search=1;    
					}
				if (search==0) {
				   memory++;	
				   AR1 = (int*) realloc(AR1, memory * sizeof(int) );
		           AR2 = (int*) realloc(AR2, memory * sizeof(int) );
		           AR1[memory-1] = town;
				   AR2[memory-1] = 1;
				}
			}
		   int max=0;
 		   for (i=0; i < memory; i++) if (max < AR2[i]) 
				max = AR2[i];
    	   for (i=0; i < memory; i++) if (max == AR2[i])
				printf("%c%c %d\n", AR1[i] /100, AR1[i] %100, AR2[i]);
           free(AR1);
	       free(AR2);  
		} 
		else printf("Pole nie je vytvorene\n");
	}
	
	
	void function_a(int p, char **arr, int *aloc)
	{
		int i, j, input, c_spz=7;
		char c, *newarr;
		
		if (aloc>0 && p>0) {
			scanf("%d",&input);
			
			if (*aloc==2)
			{
				c_spz=9;
			}
			
			newarr = (char*) calloc(p * 9, sizeof(char));
			for (i=0;i<p;i++) 
			{
				for (j=0;j<7;j++) 
				{
					newarr[i*9+j] = (*arr)[i*c_spz+j];
				}
				while (input>25) 
				{ 
					input=input-26;
				}
				c = (*arr)[i*c_spz+0];
				c = c + input;
				if (c > 'Z') c=c-26;
				newarr[i*9+7] = c;
				
				c = (*arr)[i*c_spz+1];
				c = c + input;
				if (c > 'Z') c=c-26;
				newarr[i*9+8] = c;
			}
				
			free(*arr);
			*arr=newarr;
			*aloc=2;
			printf("Funkcia sa vykonala. (kontrola - s)\n");
		}
		else 
		{
			printf("Pole nie je vytvorene\n");
		}
	}


	void function_b(int p, char *arr, int aloc)
	{
		int i, j, c_spz=7, counter[10];
		char c;
		
		if (aloc>0) {
			printf("Histogram:\n");
			printf("----------\n");
			
			for (i=0; i<10; i++) 
			{
				counter[i]=0;
			}
			if (aloc==2) c_spz=c_spz+2;
		
			for (i=0; i<(p*c_spz); i++) 
			{
				c = arr[i];
				if (c>='0' && c<='9') 
				{
					counter[c-'0']=counter[c-'0']+1;
				}
			}	
			for (i=0; i<10; i++) 
			{
				if (counter[i])
				{
				printf("%d:%d\n",i,counter[i]);
				}
			}
		}
		else 
		{
			printf("Pole nie je vytvorene\n");
		}
	}
	

	void main()
	{
		FILE *File_x=0; 
		char command, *array;
		int count, al=0;
		
		printf("Project 1 - Work with array\n");
		printf("---------------------------\n");
		printf("Commands: v, o [rrrrmmdd], n, s, p, z, a [n], b, k\n");
		
		while (1) {
			scanf("%c",&command);
			switch(command)
			{
				case 'v':  function_v(&File_x); 				break;
				case 'o':  if (File_x) function_o(File_x);  	break;
				case 'n':  count=function_n(File_x,&array,&al); break;
				case 's':  function_s(count, array, al); 		break;
				case 'p':  function_p(count, array, al); 		break;
				case 'z':  function_z(count, array, al);		break;
				case 'a':  function_a(count, &array, &al);		break;
				case 'b':  function_b(count, array, al);		break;
				case 'k':  fclose(File_x); exit(0); 			break;
        	}
        }
	}
	
