#include<stdio.h>
#include<string.h>

void encrypt(char *text, const char *key){
    int keylen = strlen(key);
    int keyindex = 0;

    for (int i=0; text[i]!='\0';i++){
        if(text[i] >= 32 && text[i] <= 126){
            int textval = text[i] - 32;
            int keyval = key[keyindex % keylen] - 32;

            text[i] = ((textval + keyval) % 95) + 32;

            keyindex++;
        }
    }
}

void decrypt(char *text, const char *key) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 32 && text[i] <= 126) {

            int text_val = text[i] - 32;
            int key_val = key[key_index % key_len] - 32;

            // Shift backward. Add +95 before the modulo to protect against negative results in C!
            text[i] = ((text_val - key_val + 95) % 95) + 32;

            key_index++;
        }
    }
}

int main(){
    char text[8192] = {0};
    char key[256];

    printf("Enter a key: ");
    fgets(key,sizeof(key), stdin);
    key[strcspn(key,"\n")]=0;

    FILE* inFile = fopen("input.txt","r");
    fread(text, sizeof(char), sizeof(text)-1, inFile);
    printf("Original text:\n%s\n",text);

    encrypt(text, key);
    FILE* outFile = fopen("encrypted.txt","w");
    fprintf(outFile, "%s", text);
    fclose(outFile);

    decrypt(text,key);
    printf("Decrypted text:\n%s\n",text);

    return 0;

}
