# include <limits.h>
# include <string.h>
# include <stdio.h>

# define NO_OF_CHARS 256


int cbmtable(int i, int j , int m ,int j_jump,int k_jump, char *p){
    int IsMatch =1;
    int k,jump = k_jump;
    for(; jump < m ; jump++){

        IsMatch = 1;
        for( k = m-1; (k>j)&& (k>=jump); k-- ){
            if(p[k]!= p[k-jump]){
                IsMatch = 0;
                break;
            }
        }
        if(!IsMatch) continue;
        if((j>= jump)&&(p[j]==p[j-jump]))continue;
        IsMatch = 1;
        int l,delta = jump + j_jump;
        for(l = m-1; (l>i)&& (l>=delta);l--){
            if(p[l]!=p[l-delta]){
                IsMatch = 0;
                break;
            }
        }
         if(!IsMatch) continue;
        if((i>= delta)&&(p[i]==p[i-delta])) continue;
        return jump;
    }
    return jump;

}

int max (int a, int b) { return (a > b)? a: b; }

void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS])
{
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int) str[i]] = i;
}

void search( char *txt, char *pat)
{
	int m = strlen(pat);
	int n = strlen(txt);
   // int i,j,cbmt[m][m];
   int j_jump,k_jump;
	int badchar[NO_OF_CHARS];
    int count =0;

	badCharHeuristic(pat, m, badchar);

	int s = 0;
	while(s <= (n - m))
	{   count++;
		int j = m-1;
		while(j >= 0 && pat[j] == txt[s+j])
			j--;
            count++;
		if (j < 0)
		{
			printf("\npattern occurs at shift = %d\n", s);

			j_jump= (s+m < n)? m-badchar[txt[s+m]] : 1;
			s +=j_jump;
			//printf("\nj_jump:-%d",j_jump);

		}

		else{

			j_jump = max(1, j - badchar[txt[s+j]]);
                s+=j_jump;
               // printf("\nj_jump:-%d",j_jump);
		}
			if(s>n-m)
                break;

			int k= m-1;

		while(k>= 0 && pat[k] == txt[s+k])
			k--;
            count++;
		if (k < 0)
		{
			printf("\npattern occurs at shift = %d\n", s);
			k_jump= (s+m < n)? m-badchar[txt[s+m]] : 1;
                s+=k_jump;
              //  printf("\nk_jump:-%d",k_jump);
		}

		else{

			k_jump= max(1, k - badchar[txt[s+k]]);
			s+=k_jump;
			//printf("\nk_jump:-%d",k_jump);
		}
		int l= m-1;
		while(l >= 0 && pat[l] == txt[s+l])
			l--;
			if(l< 0){
                 //   printf("\npattern occurs at shift = %d\n", s);


			}


        if(s>n-m)
            break;
        if((s<= n-m)&&(k>=0 )&&(j>=0)){

                    int jump = cbmtable(j,k ,m,j_jump,k_jump,pat);
                    count++;
                    //printf("\ncbm:-%d\n",jump);
                    s+=jump;

            }



	}
	printf("The total no of comparison it made is : %d  ",count );
}



int main()
{



    int i, n, p;
	char word[26];

	time_t t;
	n = 5000;
	p = 10;
	char str[n];
	char pat[p];
	srand((unsigned) time(&t));

	for( i = 0 ; i < n ; i++ ) {
		str[i] = 97 + (rand() % 26);
	}
	for(i = 0 ; i < p ; i++){
		pat[i] = 97 + (rand() % 26);
	}


	int num = 1 + rand() % 100;

	int index,pt;
	for(i = 1 ; i <num ; i++){
        index = rand()%((i)*(n/num));
        for(pt=0;(pt<p)&&(index+pt<n);pt++){
            str[pt+index] = pat[pt];
        }
	}



	/*
    for( i = 0 ; i < n ; i++ ) {
		printf("%c",str[i]);
	}
	printf("\n\n");
	for(i = 0 ; i < p ; i++){
		printf("%c",pat[i]);
	}
    */


	search(str, pat);
	return 0;
}
