//main (is the core of program) maintest1 (is the lastest version)
//pointers were used for minimising analysing power
//main point here to create the login and password for simple users, that will gone after a while
//this txt file will be included into php code, which will put this variables into SQL database
#include <stdio.h>
#include <time.h> //used to generate random variables in gen_pass (exactly for rand and srand)
#include <string.h>
#include <stdlib.h>

void gen_pass(char nickname[ ], char teacher[ ], char pass[ ]) {
    srand(time(NULL)); //create starting point for random symbals, to avoid repetition

    int i,  j; //variables for counting in loop

    int x = strlen(nickname); //this is the 1st variable for generated pass (lenght of this)
    int y = strlen(teacher); //this is the second variable (lenght of this)

    char newpas[x + y + 1]; //combining this two variables will add them together before randomising
    strcpy(newpas, nickname); //copying the 1st into 2nd
    strcat(newpas, teacher); //string concatenation

    for (i = 0; i < x + y; i++) { //loop which uses rand to randomise cymbals in the password
        j = rand() % (x + y - i) + i; //rand generating random number 
        char h = newpas[j];

        newpas[j] = newpas[i]; //i and j using to combine string 
        newpas[i] = h; //replasing cymbals at the end of this loop
    }

    strncpy(pass, newpas, 26); //this will replace the variable which we were starting from to a new one
    pass[26] = '\0'; //indicating the end of this string
}

void saving_info(char nickname[ ], char pass[ ]) { //function that will save information into new txt file
    FILE *fptr = fopen("UserInfo.txt", "a"); //open the file if it exist or create a new one
    
    fprintf(fptr, "%s %s\n",  nickname, pass); //print nickname and pass into txt file

    fclose(fptr); //closing file
}

int main() { //main block
//all variables in this program
    char nickname[7];
    char teacher[21];
    char pass[27];
    char ans;
    int limit = 0;

    do { //loop for input users nickname

        // int limit = 0;
        
         if (limit == 5) { //break if user will type it more than 5 times in a row
            printf("Bro, I just said you, 2-6 cymbals!\n");
            return 1;
        }
        printf("Enter your nickname (2-6 characters): ");
        scanf("%s", nickname);
        limit++; // increment at the end of this loop

        // int limit = 0;
        // limit++;
        // if (limit = 5) {
        //     return 0;
        // }

    } while (strlen(nickname) < 2 || strlen(nickname) > 6);

    printf("Enter your favorite teacher's name: "); //input with teacher's name
    scanf("%s", teacher);

    gen_pass(nickname, teacher, pass); //generate password with function gen_pass
 
    printf("Your generated pass is: %s\n",  pass); //show the user password

    printf("Do you like this pass? (y/n): "); //asking user about new pass
    scanf(" %c", &ans);

    while (ans != 'y') { //loop for generating new pass if ans was anything exept y
        gen_pass(nickname, teacher, pass);
        printf("Your new generated pass is: %s\n", pass);
        printf("Do you like this pass? (y/n): ");
        scanf(" %c", &ans);
    }

    saving_info(nickname, pass); //after user choose right pass, it's savint into txt file

    return 0;
}