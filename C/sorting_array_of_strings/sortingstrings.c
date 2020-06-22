#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_CHARS 'z' - 'a' + 1

int lexicographic_sort(const char* a, const char* b) {
    int alen = strlen(a), blen = strlen(b);
    int shorter = alen >= blen ? blen : alen;
    for(int i = 0; i < shorter; i++){
        if(a[i] == b[i]) continue;
        else if(a[i] > b[i]) return 1;
        else return -1;
    }
    if(alen == blen)
        return 0;
    else if(alen > blen)
        return 1;
    return -1;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return lexicographic_sort(b, a);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    char arr1[N_CHARS], arr2[N_CHARS];
    int na = 0, nb = 0, alen = strlen(a), blen = strlen(b);
    for(int i = 0; i < N_CHARS; i++){
        arr1[i] = 0;
        arr2[i] = 0;
    }
    for(int i = 0; i < alen; i++){
        if(arr1[a[i] - 'a'] == 0){
            na++;
            arr1[a[i] - 'a'] = 1;
        }
    }
    for(int i = 0; i < blen; i++){
        if(arr2[b[i] - 'a'] == 0){
            nb++;
            arr2[b[i] - 'a'] = 1;
        }
    }
    if(na > nb)
        return 1;
    else if (na < nb)
        return -1;
    return lexicographic_sort(a,b);
}

int sort_by_length(const char* a, const char* b) {
    int alen = strlen(a), blen = strlen(b);
    if(alen > blen)
        return 1;
    if(alen < blen)
        return -1;
    return lexicographic_sort(a,b);
}

void swap(char* a, char* b){
    char* temp = a;
    *a = *b;
    *b = *temp;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    char* temp;
    for(int i = 1; i < len; i++){
        for(int j = 0; j < i; j++){
            if(cmp_func(arr[j],arr[i]) > 0){
                temp = arr[i];
                for(int k = i-1; k >= j; k--)
                    arr[k+1] = arr[k];
                arr[j] = temp;
                break;
            }
        }
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}