#include<stdio.h>
#include<string.h>
void encrypt(char *text,const char *key){
    for(int i=0; text[i]!='\0';i++){
        if(text[i] >= 32 && text[i] <= 126)
            text[i] = key[text[i]-32];
    }
}

void decrypt(char *text, const char *key){
    for(int i=0; text[i]!='\0';i++){
        for (int j = 0; j < 95; j++) {
            if (key[j] == text[i]) {

                text[i] = j + 32;
                break;
            }
        }
    }
}


int main(){
    char text[8192] = {0};
    const char key[96] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?`~ ";
    FILE* inFile = fopen("input.txt","r");
    if (!inFile) {
        perror("Failed to open file");
        return 1;
    }

    // Capture the number of bytes actually read
    size_t bytesRead = fread(text, sizeof(char), sizeof(text)-1, inFile);
    fclose(inFile);

    // Explicitly set the null terminator
    text[bytesRead] = '\0';

    printf("Original text:\n%s\n", text);

    encrypt(text, key);
    FILE* outfile = fopen("encrypted.txt","w");
    fprintf(outfile, "%s", text);
    fclose(outfile);
    decrypt(text,key);
    printf("Decrypted text:\n%s\n",text);
    return 0;
}
