#include<stdio.h>
#include<string.h>
#include<ctype.h>
char matrix[16][16];

void matrixFormation(const char* key){
    int row = 0, col = 0;
    int used[256] = {0};
    char ch;
    for (int i = 0; key[i]!='\0';i++){
        ch = key[i];

        if(!used[ch]){
            matrix[row][col] = ch;
            used[ch] = 1;
            col++;

            if(col == 16){
                col = 0;
                row = row + 1;
            }
        }
    }
    for (int i = 0; i < 256; i++){
        if(!used[i]){
            matrix[row][col] = (char)i;
            used[ch] = 1;
            col++;

            if(col == 16){
                col = 0;
                row = row + 1;
            }
        }
    }
}

void findPosition(unsigned char ch, int *row, int *col) {
    for (int r = 0; r < 16; r++) {
        for (int c = 0; c < 16; c++) {
            if (matrix[r][c] == ch) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

void encrypt(char *text){
    int len = strlen(text);

    for (int i = 0; text[i]!='\0'; i+=2){
        int r1,c1,r2,c2;

        findPosition(text[i], &r1, &c1);
        findPosition(text[i+1], &r2, &c2);

        if(r1 == r2){
            text[i] = matrix[r1][(c1+1)%16];
            text[i+1] = matrix[r2][(c2+1)%16];
        }
        else if(c1 == c2){
            text[i] = matrix[(r1+1)%16][c1];
            text[i+1] = matrix[(r2+1)%16][c2];
        }
        else{
            text[i] = matrix[r1][c2];
            text[i+1] = matrix[r2][c1];
        }
    }
}
void formatText(char *text,char *formatted){
    int len = strlen(text);
    for (int i = 0; text[i]!='\0';i++){
        formatted[i]=text[i];
    }

    formatted[len]='\0';

    for (int i = 0; text[i]!='\0';i+=2){
        if((i+1)<len && formatted[i] == formatted[i+1]){
            for(int j=len; j > i; j--){
                formatted[j] = formatted[j-1];
            }
            formatted[i+1] = 'X';
            len++;
            formatted[len] = '\0';

        }
    }
}

int main(){
    char text[8192] = {0};
    char formatted[9000] = {0};
    char key[256];

    printf("Enter a key: ");
    fgets(key,sizeof(key),stdin);
    key[strcspn(key,"\n")] = 0;

    matrixFormation(key);

    FILE* inFile = fopen("input.txt","r");
    fread(text,sizeof(char),sizeof(text),inFile);
    fclose(inFile);

    formatText(text,formatted);
    printf("Text after formatting:\n%s\n",formatted);

    encrypt(formatted);
    FILE* outFile = fopen("encrypt.txt","w");
    fprintf(outFile,"%s",formatted);
    fclose(outFile);
}
