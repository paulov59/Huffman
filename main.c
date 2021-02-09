#include "main.h"

int main(){
    int opt;
    char namefile[1000];
    

    printf("Hello! Welcome to Prog.Huff™\n");
    printf("This is a file compression program that uses the Huffman's algorithm, please select one of the options below:\n%10d - Compact\n%10d - Descompact\n%10d - Exit\n", 1, 2, 3);
    scanf("%d", &opt);
    getchar();
    FILE *file;
    switch(opt){
        case 1:
            printf("Please enter the file name:\n");
            scanf("%[^\n]s",namefile);
            file = fopen(namefile,"rb");
            compact(file,namefile);
            break;
        case 2:
            printf("Please enter the file name:\n");
            scanf("%[^\n]s",namefile);
            file = fopen(namefile,"rb");
            descompact(file, namefile);
            break;
        case 3:
            printf("Bye!\n");
            return 0;
            break;
    }

    return 0;
}