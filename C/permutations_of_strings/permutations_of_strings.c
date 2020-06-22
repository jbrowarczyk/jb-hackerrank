#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **s, int i1, int i2){
    char *temp = s[i1];
    s[i1] = s[i2];
    s[i2] = temp;
}

void rev(char **s, int start, int end){
    char* temp;
    while(start < end){
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    int k,l;
    k = -1;
    for(int i = 0; i < n-1; i++){
        if(strcmp(s[i],s[i+1]) < 0)
            k = i;
    }
    if(k < 0)
        return 0;
    l = -1;
    for(int i = k+1; i < n; i++){
        if(strcmp(s[k],s[i]) < 0)
            l = i;
    }
    if(l < 0){
        printf("boom!\n");
        fflush(stdout);
        return 0;
    }

    swap(s,k,l);
    rev(s,k+1,n-1);
    
    return 1;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}