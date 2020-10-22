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
char *reserved[] = { "odd", "begin", "end", "if", "then", "while", "do", "call", 
					 "const", "var", "procedure", "write", "read", "else" };

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

// Should these take lexeme structs instead?
token_type getAlphaTokenType(char *s)
{
	for(int i = 0; i < 14; i++)
	{
		if(!strcmp(s, reserved[i]))
			if(i == 0)
				return oddsym;
			return i + 20;
	}

	return identsym;
	
	/*
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
	*/
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
	// Initialize variables
	lexeme lexeme_table[MAX_TABLE_SIZE];
	char ch;
	char buffer[32];
	int i, j = 0;
	FILE *fp;

	// Special symbols hash table declaration
	token_type ssym[256];
	
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

	while((ch = fgetc(fp)) != EOF)
	{
		printf("%c", ch);
		// Ignore whitespace
		if(isspace(ch) || iscntrl(ch))
		{
			continue;
		}
		// Reserved word or identifier
		else if(isalpha(ch))
		{
			buffer[0] = ch;
			i = 1;
			// Continue adding to buffer
			while((ch = fgetc(fp)) != EOF && (isalpha(ch) || isdigit(ch)))
			{
				buffer[i] =  ch;
				i++;
				printf("%c", ch);
			}
			printf("%c", ch);
			
			// Add lexeme to table
			buffer[i] = '\0';
			char name[i + 1];
			strcpy(name, buffer);
			lexeme_table[j].name = name;
			lexeme_table[j].token = getAlphaTokenType(name);
			if(i > 12 && lexeme_table[j].token == identsym)
				lexeme_table[j].error = idtoolong;

			j++;
		}
		// Number
		else if(isdigit(ch))
		{
			buffer[0] = ch;
			i = 1;
			// Continue adding to buffer
			while((ch = fgetc(fp)) != EOF && (isalpha(ch) || isdigit(ch)))
			{
				buffer[i] = ch;
				i++;
				printf("%c", ch);

				if()	
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
		/*
		else if(issymbol(ch))
		{

		}
		else
		{
			error = invalidsym;
		}

		printf("%s | %d\n", lexeme_table[j].name, lexeme_table[j].token);
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
	*/
	}
	/*
	// Why is this broken?
	printf("\n\nLEXEME LIST\n");
	for(i = 0; i < j; i++)
	{
		printf("%s | %d\n", lexeme_table[i].name, lexeme_table[i].token);
	}
	// Print file contents.

	// Print part 2.

	// Print part 3.

	*/
	return 0;
}
