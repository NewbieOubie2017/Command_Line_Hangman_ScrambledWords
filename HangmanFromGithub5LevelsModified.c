#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
look up functions rand_index    rand_index = rand() % length;
and malloc
*/

// This function takes a character to print, an integer n for the amount of times to print,
// and an integer space indicating if the user would like spaces between their characters.
// (0 for no, 1 for yes)
/*
level one gives you all the letters scrambled and you guess the letter and position.
level 2 harder word
level 3 & 4 harder word
level 5 very hard word

this game only has 5 words in the vocabulary

*/
char print_char(char ch, int n, int space)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (space)
		{
			printf("%c ", ch);
		}
		else
		{
			printf("%c", ch);
		}
	}
	printf("\n");
}

// Function that takes an integer array, the length of the array, and an integer, and checks
// whether the integer appears within the array, returning 1 if found, returning 0 otherwise.
int value_is_in_array(int *index_arr, int length, int val)
{
	int i;

	for (i = 0; i < length; i++)
	{
		if (index_arr[i] == val)
		{
			return 1;
		}
	}
	return 0;
}

// Function that takes a string as its only parameter and mixes its characters, resulting
// in a scrambled string.
void scramble_string(char *str)
{
	int i, j = 0, length = strlen(str), rand_index;
	char *dest = malloc(sizeof(char) * (length + 1));
	int *index_exceptions = malloc(sizeof(int) * length);

	// loop that sets all indices to not consider when scrambling the string to -1
	for (i = 0; i < length; i++)
	{
		index_exceptions[i] = -1;
	}

	// loop that randomly generates an index each iteration to place each character in the string
	while (j < length)
	{
		rand_index = rand() % length;

		if (!value_is_in_array(index_exceptions, length, rand_index))
		{
			dest[rand_index] = str[j];
			index_exceptions[j] = rand_index;
			j++;
		}
	}

	strcpy(str, dest);
	free(dest);
	free(index_exceptions);
}

// Function that takes an integer that represents the difficulty level (1-5) and starts the hangman
// game. The player can only make up to 5 incorrect guesses before he loses.
void hangman(int difficulty)
{
	int i, j;
	int field_width = 50;
	int num_guesses = 5;
	int guess_right = 0;
	int position = -1;
	int word_length;

	char guess;
	char source[100] = "";
	char dest[100] = "";
	char scrambled_str[100] = "";
	int wordRand_index = rand() % 5;
	if (difficulty == 1) {
        char word_list1[5][100] = {"juicy", "curry", "board", "black", "green"};
        strcpy(source, word_list1[wordRand_index -1]);
	}
	else if (difficulty == 2) {
        char word_list2[5][100] = {"puzzle", "street", "snoopy", "mantra", "lovely"};
        strcpy(source, word_list2[wordRand_index -1]);
	}
	else if (difficulty == 3) {
        char word_list3[5][100] = {"abandon", "zephyr", "blatant", "concrete", "hatchet"};
        strcpy(source, word_list3[wordRand_index -1]);
	}
	else if (difficulty == 4) {
        char word_list4[5][100] = {"pleasant", "aesthetic", "similar", "abstract", "practical"};
        strcpy(source, word_list4[wordRand_index -1]);
	}
	else if (difficulty == 5) {
        char word_list5[5][100] = {"slightly", "beautiful", "prodigious", "flapjack", "quizzical"};
        strcpy(source, word_list5[wordRand_index -1]);
	}


	//strcpy(source, word_list[difficulty - 1]);  //strcpy copies second string to first pointer
	//printf("source is %s", source);
	word_length = strlen(source);

	strcpy(scrambled_str, source);
	scramble_string(scrambled_str);

	// Initializes dest with all asterisks up to the length of the source string.
	for (i = 0; i < word_length; i++)
	{
		dest[i] = '*';
		//field_width++;
	}

	// TODO: fix field width for hangman line
	printf("\n\n%*s", field_width, "** Hangman **\n\n");
	printf("%36s", "");
	print_char('*', word_length * 2 - 1, 0);
	printf("%36s", "");
	print_char('.', word_length, 1);
	printf("\n");
	printf("%36s", "");
	print_char('_', word_length, 1);
	printf("%36s", "");
	print_char('.', word_length, 1);
	printf("%36s", "");
	print_char('*', word_length * 2 - 1, 0);
	//printf("%50s", "*************\n");
	//printf("%51s", ". . . . . . .\n\n");
	//printf("%36s", "");
	//printf("%50s", ". . . . . . .\n");
	//printf("%51s", "*************\n\n");

	while (strcmp(source, dest) != 0)
	{
		// implement availale characters displayed to screen, dissapear as user gets right.
		printf("scrambled word: %s\n\n", scrambled_str);
		printf("Enter a character. (Or enter 0 to quit)\n");
		scanf("%c", &guess);

		if (guess == '0' || position == 0)
		{
		  break;
		}

		//while (getchar() != '\n');

		printf("Enter a position to place the character. (1 - %d) (Or enter 0 to quit)\n", word_length);
		scanf("%d", &position);

		if (guess == '0' || position == 0)
		{
			break;
		}

		while (getchar() != '\n');

		while (position < 0 || position > word_length)
		{
			printf("Enter a  valid position to place the character. (1 - %d) (Or enter 0 to quit)\n", word_length);
			scanf("%d", &position);
			while (getchar() != '\n');
		}

		//while (getchar() != '\n');

		if (guess == '0' || position == 0)
		{
			break;
		}

		// if statement that checks whether the character guessed and the position it's located matches
		// with the source string.
		if (guess == source[position - 1])
		{
			dest[position - 1] = source[position - 1];
			guess_right = 1;
		}

		// if-else block that tells the user if he/she guessed correctly or incorrectly.
		if (guess_right == 0)
		{
		  num_guesses--;
		  if (num_guesses == 0)
		  {
			 printf("You are out of guesses!\nGAME OVER\n");
			 break;
		  }
		  printf("You guessed wrong! You have %d guesses left!\n", num_guesses);
		}
		else
		{
		  printf("You guessed a character correctly!\n");
		  printf("\n\n%50s", "** Hangman **\n");
		  printf("%36s", "");
		  print_char('*', word_length * 2 - 1, 0);
		  printf("%36s", "");
		  print_char('.', word_length, 1);
		  printf("\n%36s", "");

		  for (j = 0; j < word_length; j++)
		  {
			 printf("%c ", dest[j]);
		  }

		  printf("\n%36s", "");
		  print_char('_', word_length, 1);
		  printf("%36s", "");
		  print_char('.', word_length, 1);
		  printf("%36s", "");
		  print_char('*', word_length * 2 - 1, 0);

		  if (strcmp(source, dest) == 0)
		  {
			 printf("Congratulations! You Won!!!!!\n");
			 hangman(difficulty);






		  }
		  guess_right = 0;
		}
	}
	return;
}

int main(void)
{
	int difficulty;
	char temp;
	srand(time(NULL));

	printf("Please enter a difficulty level 1-5.\n");
	scanf("%d", &difficulty);

	// loop that accounts for invalid difficulty level
	while (difficulty < 1 || difficulty > 5)
	{
		printf("Please enter a valid difficulty level (1-5).\n");
		scanf("%d", &difficulty);
	}

	// TODO: create clear_buffer() function
	// consumes new-line character from the current buffer
	scanf("%c", &temp);
	//while (getchar() != '\n');

	hangman(difficulty);
	return 0;
}
