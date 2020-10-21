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

// Reserved words declaration
char *reserved[] = { "const", "var", "procedure", "call", "begin", "end", "if", 
					 "then", "else", "while", "do", "read", "write", "odd" };

// Special symbols hash table declaration
token_type ssym[256];

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

int main(int argc, char *argv[])
{
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

	// Declarations
	char c;
	int lexcount = 0;
	FILE *fp

	return 0;
}