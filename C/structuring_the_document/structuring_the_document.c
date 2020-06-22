#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
struct document get_document(char* text) {
    struct document doc;
    struct paragraph* par;
    struct sentence* sen;
    struct word* w;
    char* letters;
    doc.paragraph_count = 1;
    int i,j,k;
    int begin_paragraph = 0, begin_sentence = 0, begin_word = 0;
    int current_paragraph, current_sentence, current_word;
    int ch;

    for(int c = 0; text[c] != '\0'; c++){
        if(text[c] == '\n')
            doc.paragraph_count++;
    }

    doc.data = malloc(doc.paragraph_count * sizeof(struct paragraph));

    current_paragraph = 0;
    while(current_paragraph < doc.paragraph_count){
        par = malloc(sizeof(struct paragraph));
        par->sentence_count = 0;
        i = begin_paragraph;
        while(text[i] != '\n' && text[i] != '\0'){
            if(text[i] == '.')
                par->sentence_count++;
            i++;
        }
        par->data = malloc(par->sentence_count * sizeof(struct sentence));
        begin_sentence = begin_paragraph;
        current_sentence = 0;
        while(current_sentence < par->sentence_count){
            sen = malloc(sizeof(struct sentence));
            sen->word_count = 1;
            j = begin_sentence;
            while(text[j] != '.' && text[j] != '\0'){
                if(text[j] == ' ')
                    sen->word_count++;
                j++;
            }
            sen->data = malloc(sen->word_count * sizeof(struct word));
            current_word = 0;
            begin_word = begin_sentence;
            k = begin_word;
            while(current_word < sen->word_count){
                w = malloc(sizeof(struct word));
                while(text[k] != ' ' && text[k] != '.')
                    k++;
                k++;
                letters = malloc(k * sizeof(char));
                memcpy(letters, text + begin_word, k - begin_word - 1);
                letters[k - begin_word - 1] = '\0';
                w->data = letters;
                *(sen->data + current_word) = *w;
                current_word++;
                begin_word = k;
            }
            *(par->data + current_sentence) = *sen;
            current_sentence++;
            begin_sentence = j+1;
        }
        *(doc.data + current_paragraph) = *par;
        current_paragraph++;
        begin_paragraph = i+1;
    }
    return doc;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return *(Doc.data + k - 1);
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return *(kth_paragraph(Doc,m).data + k - 1);
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return *(kth_sentence_in_mth_paragraph(Doc,m,n).data + k - 1);
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}