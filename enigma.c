/* TODO:
 * factor out reformat
 * make initial rotor settings configurable
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
    fseek(infile,0,SEEK_END);
    int size = ftell(infile);
    fseek(infile,0,SEEK_SET);
    char input[size];
    fgets(input,size,infile);
    fclose(infile);

    // reformat text
    char input2[size];
    int j = 0;
    for (int i = 0; i < size; i++){
        if (input[i] >= 'A' && input[i] <= 'Z'){
            input2[j] = input[i];
            j++;
        }
        if (input[i] >= 'a' && input[i] <= 'z'){
            input2[j] = toupper(input[i]);
            j++;
        }
    }
    input2[j] = '\0';

    // rotor strings
    char palpha[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rotor1[] =  "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char rotor2[] =  "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char rotor3[] =  "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char reflec[] =  "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    int len = strlen(palpha);

    // rotor offsets
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;

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

    // encipher chars
    for (int i = 0; i < j; i++){

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
        char a = rotorPass(rotor1, input2[i]);
        char b = rotorPass(rotor2, a);
        char c = rotorPass(rotor3, b);
        char d = rotorPass(reflec, c);
        char e = palpha[findchar(rotor3, d)];
        char f = palpha[findchar(rotor2, e)];
        input2[i] = palpha[findchar(rotor1, f)];
   }

    // print output string
    printf("%s\n", input2);
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
