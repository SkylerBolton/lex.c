// Skyler Bolton
// Alejandro Herrada

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDENTIFIER_LENGTH 11
#define MAX_NUMBER_LENGTH 5
#define MAX_TABLE_SIZE 500

// Token declaration
typedef enum
{
	nulsym = 1, identsym, numbersym, plussym, minussym,	multsym, slashsym,
	oddsym, eqsym, neqsym, lessym, leqsym, gtrsym, geqsym, lparentsym,
	rparentsym, commasym, semicolonsym,	periodsym, becomessym, beginsym, endsym,
	ifsym, thensym,	whilesym, dosym, callsym, constsym, varsym, procsym,
	writesym, readsym, elsesym, commentsym, endcommentsym
} token_type;

// Reserved words declaration
char *reserved[] = { "const", "var", "procedure", "call", "begin", "end", "if",
					 "then", "else", "while", "do", "read", "write", "odd" };

// Special symbols hash table declaration
token_type ssym[256];

// Error type declaration
typedef enum
{
	invalidid = 1, numtoolong, idtoolong, invalidsym, none
} error_type;

// Lexeme struct
typedef struct lexeme
{
	char* name;
	int value;
	token_type token;
	error_type error;
} lexeme;

// Lexeme table declaration
lexeme lexeme_table[MAX_TABLE_SIZE];

// TODO: declare / initialize variables in main
// TODO: initialize file IO
// TODO: setup readings according to state diagram (use switch?)
// TODO: isReserved() method: check if lexeme is reserved word
//		 should be simple check: loop, if(!strcmp) return true else return false
//		 we may need the token type instead in which case make sure reseved list
//		 aligns with token_type enum and return offset of i when reserved word
//		 is found
// TODO: printLexeme() method: check lexeme token type, if it's an error, and
// 		 print accordingly

// Should these take lexeme structs instead?
token_type getAlphaTokenType(char *s)
{
	if (strcmp(s, "const") == 0)
		return constsym;

	else if (strcmp(s, "var") == 0)
		return varsym;

	else if (strcmp(s, "procedure") == 0)
		return procsym;

	else if (strcmp(s, "call") == 0)
		return callsym;

	else if (strcmp(s, "begin") == 0)
		return beginsym;

	else if (strcmp(s, "end") == 0)
		return endsym;

	else if (strcmp(s, "if") == 0)
		return ifsym;

	else if (strcmp(s, "then") == 0)
		return thensym;

	else if (strcmp(s, "else") == 0)
		return elsesym;

	else if (strcmp(s, "while") == 0)
		return whilesym;

	else if (strcmp(s, "do") == 0)
		return dosym;

	else if (strcmp(s, "while") == 0)
		return varsym;

	else if (strcmp(s, "read") == 0)
		return readsym;

	else if (strcmp(s, "write") == 0)
		return writesym;

	else if (strcmp(s, "odd") == 0)
		return oddsym;

	else
		return identsym;
}


int issymbol(char c)
{
	return 1;
}

void printLexeme(char *s)
{

}

int main(int argc, char *argv[])
{
	// Initialize variables.
	char ch;
	char buffer[32];
	error_type error = none;
	int i, j = 0,  val = 0;
	FILE *fp;
	token_type current;

	// Initialize symbol hash table
	ssym['+'] = plussym;
	ssym['-'] = minussym;
	ssym['*'] = multsym;
	ssym['/'] = slashsym;
	ssym['('] = lparentsym;
	ssym[')'] = rparentsym;
	ssym['='] = eqsym;
	ssym[','] = commasym;
	ssym['.'] = periodsym;
	ssym['<'] = lessym;
	ssym['>'] = gtrsym;
	ssym[';'] = semicolonsym;
	ssym['<' * 2 + '>'] = neqsym;
	ssym['<' * 2 + '='] = leqsym;
	ssym['>' * 2 + '='] = geqsym;
	ssym['/' * 2 + '*'] = commentsym;
	ssym['*' * 2 + '/'] = endcommentsym;

	// Read file into lexeme_table(?)
	if((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Unable to open file :(\n");
		return 1;
	}

	i = 1;
	ch = fgetc(fp);
	buffer[0] = ch;
	while(ch != EOF)
	{
		// Ignore.
		if(isspace(ch))
		{
			ch = fgetc(fp);
			buffer[0] = ch;
			i = 1;
			continue;
		}

		// Either a reserved word or idenifier.
		else if(isalpha(ch))
		{
			ch = fgetc(fp);
			// Continue adding to buffer
			while(ch != EOF && (isalpha(ch) || isdigit(ch)))
			{
				buffer[i] = ch;
				ch = fgetc(fp);
				i++;
			}

			if(i > 12)
			{
				error = idtoolong;
			}

			lexeme_table[j].name = buffer;
			lexeme_table[j].value = 0;
			lexeme_table[j].token = getAlphaTokenType(buffer);
			lexeme_table[j].error = error;
		}

		// Either a number or idenifier.
		else if(isdigit(ch))
		{
			ch = fgetc(fp);
			// Continue adding to buffer
			while(ch != EOF && (isalpha(ch) || isdigit(ch)))
			{
				if(isalpha(ch))
				{
					error = invalidid;
				}

				buffer[i] = ch;
				ch = fgetc(fp);
				i++;
			}

			if(i > 5)
			{
				error = idtoolong;
			}

			lexeme_table[j].name = buffer;
			if(error == invalidid)
			{
				lexeme_table[j].value = 0;
				lexeme_table[j].token = identsym;
			}
			else
			{
				lexeme_table[j].value = atoi(buffer);
				lexeme_table[j].token = numbersym;
			}
			lexeme_table[j].error = error;
		}

		else if(issymbol(ch))
		{
			
		}
		else
		{
			// Error.
		}

		// Add this to lexeme_table
		printf("%s\n",lexeme_table[j].name);
		j++;

		// clean buffer and get ready for next iteration
		for(i = 0; i < 32; i++)
		{
			buffer[i] = '\0';
		}
		ch = fgetc(fp);
		buffer[0] = ch;
		i = 1;
	}

	// Print file contents.

	// Print part 2.

	// Print part 3.


	return 0;
}
