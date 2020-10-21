// Skyler Bolton
// Alejandro Herrada

#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

// These next 3 functions the token_type of the string.
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

// Might be better to put this in main for error detection.
token_type getDigitTokenType(char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; i++)
	{
		// Bad idenifier name.
		if (isalpha(s[i]))
		{
			return identsym;
		}
	}
	return numbersym;
}


token_type getSymbolTokenType(char *s)
{
	if(s[0] == '+')
		return plussym;

	else if(s[0] == '-')
		return minussym;

	else if(s[0] == '*')
		if(s[1] == '/')
			return endcommentsym;
		else
			return multsym;

	else if(s[0] == '/')
		if(s[1] == '*')
			return commentsym;
		else
			return slashsym;

	else if(s[0] == '(')
		return lparentsym;

	else if(s[0] == ')')
		return rparentsym;

	else if(s[0] == '=')
		return eqsym;

	else if(s[0] == ',')
		return commasym;

 	else if(s[0] == '.')
		return commasym;

	else if(s[0] == '<')
		if(s[1] == '=')
			return leqsym;
		else
			return lessym;

	else if(s[0] == '>')
		if(s[1] == '=')
			return geqsym;
		else
			return gtrsym;

	else if(s[0] == ';')
		return semicolonsym;

	// :=
	else
		return becomessym;
}

int main(int argc, char *argv[])
{
	// Make declarations
	int i, j;
	int numLexemes;
	int commentFlag = 0;
	token_type current;
	FILE *fp;

	// HARDCODED ARRAY.
	// TODO: create this from a file.
	char array[18][12] = {{"var"},
						 {"x"},
						 {","},
						 {"y"},
					   	 {";"},
						 {"begin"},
						 {"y"},
						 {":="},
						 {"3"},
						 {";"},
						 {"x"},
						 {":="},
						 {"y"},
						 {"+"},
						 {"56"},
						 {";"},
						 {"end"},
						 {"."}};

	// Hardcoded length
	numLexemes = 18;

	// Open input file
	if((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Unable to open file :(\n");
		return 1;
	}

	/* Print contents of array.
	printf("Array contents:");
	for(i = 0; i < numLexemes; i++)
	{
		printf("\n");
		for(j = 0; array[i][j] != '\0'; j++)
		{
			printf("%c", array[i][j]);
		}
	}
	printf("\n\n");
	*/

	printf("\nLexeme Table:\n");
	printf("lexeme     token type\n");
	for(i = 0; i < numLexemes; i++)
	{
		// Ignores everything until we see "*/".
		// This could be done while reading the file instead to make this part faster.
		if (commentFlag)
		{
			printf("INSIDE COMMENT\n");
			if(isalpha(array[i][0]))
			{
				continue;
			}

			else if(isdigit(array[i][0]))
			{
				continue;
			}

			else
			{
				current = getSymbolTokenType(array[i]);
				if(current == endcommentsym)
				{
					commentFlag = 0;
				}
			}
		}

		// This is when we aren't in a comment block.
		else
		{
			// array[i] is either a reserved word or identifer.
			if(isalpha(array[i][0]))
			{
				current = getAlphaTokenType(array[i]);
				printf("%s | %d\n", array[i], current);
				// Prepare for part 3
			}

			// array[i] is either a number or a badly named identifier.
			else if(isdigit(array[i][0]))
			{
				current = getDigitTokenType(array[i]);
				// TODO: check for int length.
				printf("%s | %d\n", array[i], current);
			}

			// array[i] is a symbol.
			else
			{
				current = getSymbolTokenType(array[i]);
				if(current == commentsym)
				{
					commentFlag = 1;
				}
				else
				{
					printf("%s | %d\n", array[i], current);
				}
			}
		}
	}

	// This is where we would print part 3 using info stored during the previous parts.

	return 0;
}