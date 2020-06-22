#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char*** kth_paragraph(char**** document, int k) {
    return *(document + k - 1);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    char*** par = kth_paragraph(document,m);
    return *(par + k - 1);
}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    char** sen = kth_sentence_in_mth_paragraph(document,m,n);
    return *(sen + k - 1);
}

char**** get_document(char* text) {
    int n_paragraphs = 1, n_sentences, n_words;
    int cur_paragraph = 0, cur_sentence = 0, cur_word = 0;
    int begin_paragraph = 0;
    int begin_sentence = 0;
    int begin_word = 0;
    int i,j,k;
    char**** document;
    char*** paragraph;
    char** sentence;
    char* word;
    for(int i = 0; text[i] != '\0'; i++){
        if(text[i] == '\n')
            n_paragraphs++;
    }
    document = malloc(n_paragraphs * sizeof(char***));
    while(cur_paragraph != n_paragraphs){
        n_sentences = 0;
        i = begin_paragraph;
        while(text[i] != '\n' && text[i] != '\0'){
            if(text[i] == '.')
                n_sentences++;
            i++;
        }
        paragraph = malloc(n_sentences * sizeof(char**));
        cur_sentence = 0;
        begin_sentence = begin_paragraph;
        while(cur_sentence < n_sentences){
            j = begin_sentence;
            n_words = 1;
            while(text[j] != '.' && text[j] != '\0'){
                if(text[j] == ' ')
                    n_words++;
                j++;
            }
            sentence = malloc(n_words * sizeof(char*));
            cur_word = 0;
            begin_word = begin_sentence;
            k = begin_word;
            while(cur_word < n_words){
                while(text[k] != ' ' && text[k] != '.' && text[k] != '\0')
                    k++;
                k++;
                word = malloc( (k - begin_word) * sizeof(char));
                memcpy(word,text + begin_word,k - begin_word - 1);
                word[k - begin_word - 1] = '\0';
                *(sentence + cur_word) = word;
                cur_word++;
                begin_word = k;  
            }
            *(paragraph + cur_sentence) = sentence;
            cur_sentence++;
            begin_sentence = j+1;
        }
        *(document + cur_paragraph) = paragraph;
        cur_paragraph++;
        begin_paragraph = i+1;
    }
    return document;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}