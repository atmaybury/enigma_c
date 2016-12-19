/* TODO:
 * factor out reformat
 * factor out encyphering
 * factor out rotating
 * need findchar?
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototypes
int findchar(char* a, char b);
int mod26(int n);

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

    // rotor offsets
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;

    // encipher chars
    for (int x = 0; x < j; x++){

        // rotate
        int len = strlen(rotor1);
        char tmp = rotor1[0];
        for (int i = 0; i < (len - 1); i++){
            rotor1[i] = rotor1[i + 1]; 
        }
        rotor1[len - 1] = tmp;

        r1++;

        // check rotors 2 & 3
        if (r1 == 26){
            r2++;
            r1 = 0;
        }
        if (r2 == 26){
            r3++;
            r2 == 0;
        }
        r3 = (r3 % 26);

        // pass through rotors
        int i = input2[x] - 'A';
        char a = rotor1[i];

        int j = a - 'A';
        char b = rotor2[j];

        int k = b - 'A';
        char c = rotor3[k];

        int l = c - 'A';
        char d = reflec[l];

        int m = findchar(rotor3, d);
        char e = palpha[m];

        int n = findchar(rotor2, e);
        char f = palpha[n];
        
        int o = findchar(rotor1, f);
        input2[x] = palpha[o];
   }

    // print output string
    printf("%s\n", input2);
}

int findchar(char* a, char b){
    char *e = strchr(a, b);
    int index = (int)(e - a);
    return index;
}

int mod26(int n){
    return (n+26)%26;
}
