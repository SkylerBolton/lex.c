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
	invalidid = 1, numtoolong, idtoolong, invalidsym
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
			else
				return i + 20;
	}

	return identsym;
}

void printLexeme(char *s)
{

}

// TODO		break each condition inside the while loop into its own method to
//			avoid tokenizing unnecessary characters
int main(int argc, char *argv[])
{
	// Initialize variables
	lexeme lexeme_table[MAX_TABLE_SIZE];
	char ch;
	char buffer[32];
	int i, j = 0, k = 0;
	error_type error;
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

	ch = fgetc(fp);
	printf("%c", ch);
	while(ch != EOF)
	{
		buffer[0] = ch;
		i = 1;
		error = 0;

		printf("\nWhile loop iteration #%d. ch = '%c'.", k, ch);

		//printf("%c", ch);
		// Ignore whitespace
		if(isspace(ch) || iscntrl(ch))
		{

			printf("\nWhitespace found.\n");
			// NEWLY ADDED
			ch = fgetc(fp);
			printf("%c", ch);

			continue;
		}
		// Reserved word or identifier
		else if(isalpha(ch))
		{
			printf("\nisalpha() true.\n");
			buffer[0] = ch;
			i = 1;
			error = 0;
			// Continue adding to buffer
			while((ch = fgetc(fp)) != EOF && isalnum(ch))
			{
				buffer[i] =  ch;
				i++;
				printf("%c", ch);
			}
			printf("%c", ch);

			// Add lexeme to table
			buffer[i] = '\0';
			lexeme_table[j].name = malloc(sizeof(char) * (i+1));
			strcpy(lexeme_table[j].name, buffer);
			lexeme_table[j].token = getAlphaTokenType(buffer);
			if(i > 12 && lexeme_table[j].token == identsym)
				error = idtoolong;
			lexeme_table[j].error = error;

			// NEWLY ADDED
			ch = fgetc(fp);
			printf("%c", ch);

			j++;
		}
		// Number or invalid identifier
		else if(isdigit(ch))
		{
			printf("isdigit() true.\n");
			buffer[0] = ch;
			i = 1;
			error = 0;
			// Continue adding to buffer
			while((ch = fgetc(fp)) != EOF && isalnum(ch))
			{
				buffer[i] = ch;
				i++;
				printf("%c", ch);

				if(isalpha(ch))
					error = invalidid;
			}
			printf("%c", ch);

			// Add lexeme to table
			buffer[i] = '\0';
			if(error) // If it's an invalid identifier
			{
				lexeme_table[j].name = malloc(sizeof(char) * (i+1));
				strcpy(lexeme_table[j].name, buffer);
				lexeme_table[j].token = identsym;
				lexeme_table[j].error = error;
			}
			else // If it's an integer
			{
				lexeme_table[j].value = atoi(buffer);
				lexeme_table[j].token = numbersym;
				if(i > 6)
					error = numtoolong;
				lexeme_table[j].error = error;
			}

			// NEWLY ADDED
			ch = fgetc(fp);
			printf("%c", ch);

			j++;
		}

		else
		{
			printf("\nThis is a symbol.\n");

			if(ch == '+' || ch == '-' || ch == '*' || ch == '=' || ch == '(' ||
				ch == ')' || ch == ',' || ch == ';' || ch == '.')
			{
				buffer[i] = '\0';

				// Add lexeme to table
				lexeme_table[j].name = malloc(sizeof(char) * (i+1));
				strcpy(lexeme_table[j].name, buffer);
				lexeme_table[j].token = ssym[ch];
				lexeme_table[j].error = error;

				j++;
			}
			else if(ch == '<')
			{
				ch = fgetc(fp);
				if(ch == '>' || ch == '=') // "<>" | "<=" tokens
				{
					buffer[i] = ch;
					i++;
					printf("%c", ch);

					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = ssym[buffer[0] * 2 + buffer[1]];
					lexeme_table[j].error = error;

					j++;
				}
				else // "<" token
				{
					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = ssym[ch];
					lexeme_table[j].error = error;

					j++;
				}
			}
			else if(ch == '>')
			{
				ch = fgetc(fp);
				if(ch == '=') // ">=" token
				{
					buffer[i] = ch;
					i++;
					printf("%c", ch);

					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = ssym[buffer[0] * 2 + buffer[1]];
					lexeme_table[j].error = error;

					j++;
				}
				else // ">" token
				{
					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = ssym[ch];
					lexeme_table[j].error = error;

					j++;
				}
			}
			else if(ch == ':')
			{
				ch = fgetc(fp);
				if(ch == '=') // ":=" token
				{
					buffer[i] = ch;
					i++;
					printf("%c", ch);

					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = ssym[buffer[0] * 2 + buffer[1]];
					lexeme_table[j].error = error;

					j++;
				}
				else // Invalid symbol
				{
					buffer[i] = '\0';

					// Add lexeme to table
					lexeme_table[j].name = malloc(sizeof(char) * (i+1));
					strcpy(lexeme_table[j].name, buffer);
					lexeme_table[j].token = nulsym;
					lexeme_table[j].error = invalidsym;

					j++;
				}
			}
			else
			{
				buffer[i] = '\0';

				// Add lexeme to table
				lexeme_table[j].name = malloc(sizeof(char) * (i+1));
				strcpy(lexeme_table[j].name, buffer);
				lexeme_table[j].token = nulsym;
				lexeme_table[j].error = invalidsym;

				j++;

			}

			// NEWLY ADDED
			ch = fgetc(fp);
			printf("%c", ch);
		}
		k++;
	}

	printf("\n\n");
	for(i = 0; i < j; i++)
	{
		lexeme l = lexeme_table[i];
		printf("Lexeme %d: name %s value %d token %d error %d\n",
				i, l.name, l.value, l.token, l.error);
	}

	printf("\n\nLexeme Table:\nlexeme | token type\n");
	for(i = 0; i < j; i++)
	{
		lexeme l = lexeme_table[i];
		if (l.value > 0)
		{
			printf("%d | %d\n", l.value, l.token);
		}
		else
		{
			printf("%s | %d\n", l.name, l.token);
		}
	}


	return 0;
}
