#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"
#include <stdio.h>
#include <vector>
using namespace std;
 
int yyparse(SExpression **expression, yyscan_t scanner);
 
SExpression *getAST(const char *expr)
{
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;
 
    if (yylex_init(&scanner))
    {
        // couldn't initialize
        return NULL;
    }
 
    state = yy_scan_string(expr, scanner);
 
    if (yyparse(&expression, scanner))
    {
        // error parsing
        return NULL;
    }
 
    yy_delete_buffer(state, scanner);
 
    yylex_destroy(scanner);
 
    return expression;
}
 
int evaluate(SExpression *e)
{
    switch (e->type)
    {
        case eVALUE:
            return e->value;
        case eMULTIPLY:
            return evaluate(e->left) * evaluate(e->right);
        case ePLUS:
            return evaluate(e->left) + evaluate(e->right);
        default:
            // shouldn't be here
            return 0;
    }
}
 
int main(int argc, char **argv)
{
	vector<char> buffer;
	FILE *fptr = fopen(argv[1], "rb");
	fseek(fptr, 0, SEEK_END);
	int length = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	
	buffer.resize(length+1);
	fread(&buffer[0], 1, length, fptr);
	buffer[length] = 0;
	fclose(fptr);
	
	printf("%s", &buffer[0]);
    
	SExpression *e = getAST(&buffer[0]);
	
    // result = evaluate(e);
 
    // printf("Result of '%s' is %d\n", test, result);
 
    // deleteExpression(e);
 
    return 0;
}
