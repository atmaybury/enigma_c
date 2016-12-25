/* TODO
 * Implement plugboard
 * benchmark
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototypes
int findchar(char* a, char b);
int mod26(int n);
void arrayRotate(char* input, int len);
char rotorPass(char* rotor, char n);
char returnPass(char*rotor, char n);

int main(int argc, char* argv[]){

    // check for arguments
    if (argc != 2){
        printf("Syntax: engima input.txt\n");
        return 1;
    }
    // read infile to input[]
    FILE * infile = fopen(argv[1], "r");
    if (infile == NULL){
        printf("ERROR: No valid text file.\n");
        return 1;
    }

    FILE * outfile = fopen("ciphertext.txt", "w");
    if (outfile == NULL){
        printf("ERROR: Couldn't create output file.\n");
        return 1;
    }
    
    // rotor strings
    char palpha[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rotor1[] =  "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char rotor2[] =  "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char rotor3[] =  "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char reflec[] =  "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    int len = strlen(palpha);

    // rotor offsets
    printf("Rotor 1 position [enter int]:");
    int r1;
    scanf("%d", &r1);
    r1 = mod26(r1);

    printf("Rotor 2 position [enter int]:");
    int r2;
    scanf("%d", &r2);
    r2 = mod26(r2);

    printf("Rotor 3 position [enter int]:");
    int r3;
    scanf("%d", &r3);
    r3 = mod26(r3);

    // initial settings
    if (r1 != 0){
        for (int i = 0; i < r1; i++){
            arrayRotate(rotor1, len);
        }
    }
    if (r2 != 0){
        for (int i = 0; i < r2; i++){
            arrayRotate(rotor1, len);
        }
    }
    if (r3 != 0){
        for (int i = 0; i < r3; i++){
            arrayRotate(rotor3, len);
        }
    }

    int n;
    while ((n = fgetc(infile)) != EOF){
        if (isalpha(n)){
            if (islower(n)){
                n = toupper(n);
            }
            // rotate r1
            arrayRotate(rotor1, len);
            r1++;

            if (r1 == 26){
                arrayRotate(rotor2, len);
                r2++;
                r1 = 0;
            }
            if (r2 == 26){
                arrayRotate(rotor3, len);
                r3++;
                r2 = 0;
            }
            r3 = mod26(r3);

            // pass through rotors
            char a = rotorPass(rotor1, n);
            char b = rotorPass(rotor2, a);
            char c = rotorPass(rotor3, b);
            char d = rotorPass(reflec, c);
            char e = palpha[findchar(rotor3, d)];
            char f = palpha[findchar(rotor2, e)];
            char g = palpha[findchar(rotor1, f)];

            // print enciphered char
            fputc(g, outfile);
        }
    }
    fputc('\n', outfile);
    fclose(infile);
}

/*
 * FUNCTIONS
 */

int findchar(char* a, char b){
    char *e = strchr(a, b);
    int index = (int)(e - a);
    return index;
}

int mod26(int n){
    return (n+26)%26;
}

void arrayRotate(char* input, int len){
    char tmp = input[0];
    for (int i = 0; i < (len - 1); i++){
        input[i] = input[i + 1];
    }
    input[len - 1] = tmp;
}

char rotorPass(char* rotor, char n){
    int i = n - 'A';
    return rotor[i];
}

char returnPass(char* rotor, char n){
    int i = findchar(rotor, n);
    return rotor[i];
}
