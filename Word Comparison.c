#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#define MAX_WORD_LENGHT 20
#define MAX_WORD_NUMBER 100
#define MAX_LINE_LENGTH 100

// structure declaration

typedef struct {
    char word[MAX_WORD_LENGHT];
    int occurrences;
}index_t;

// function prototypes
void read_words(char *,index_t[],int *);
void read_text(char *,index_t[],int);
void display_index(index_t[],int);
int compare(char*,char *);

int main(int argc,char*argv[]){
    index_t index[MAX_WORD_NUMBER];
    int n;
    read_words(argv[2],index,&n);
    read_text(argv[1],index,n);
    display_index(index,n);
    return EXIT_SUCCESS;
}

void read_words(char *name,index_t index[],int *num_ptr){
    FILE *fp= fopen("../output2.txt","r");
    int i=0;
    while (i<MAX_WORD_NUMBER && fscanf(fp,"%s",index[i].word)!=EOF){
        index[i].occurrences=0;
        i++;
    }
    *num_ptr=i; // update the total number of words
    fclose(fp);
}

void read_text(char *name,index_t index[],int n){
    char word[MAX_LINE_LENGTH+1];
    int i,j;
    FILE *fp= fopen("../input.txt","r");
    i=1;
    while (fscanf(fp,"%s",word)!=EOF){
        // look for the word in the index
        for(j=0;j<n;j++){
            if(compare(word, index[j].word)==1){
                // found an occurance for a word
                index[j].occurrences++;
            }
        }
        i++;
    }
    fclose(fp);
}

// case insensitive comparison

int compare(char *str1,char *str2){
    int i;
    if(strlen(str1)!= strlen(str2)){
        return 0;
    }
    for(i=0;i< strlen(str1);i++){
        if(tolower(str1[i])!= tolower(str2[i])){
            return 0;
        }
    }
    return 1;
}

void display_index(index_t index[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s - %d occurance(s)\n",index[i].word,index[i].occurrences);
    }
}