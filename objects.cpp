typedef enum {
    TOKEN_INICIAR, 
    TOKEN_FINALIZAR, 
    TOKEN_MOSTRAR, 
    TOKEN_REPETIR, 
    TOKEN_VECES,
    TOKEN_SI, 
    TOKEN_ENTONCES, 
    TOKEN_SINO, 
    TOKEN_NUMERO, 
    TOKEN_TEXTO, 
    TOKEN_VARIABLE,
    TOKEN_OPERADOR, 
    TOKEN_EOF, 
    TOKEN_ERROR
} TokenType;


typedef struct {
    TokenType type;
    char value[256];
} Token;

typedef struct ASTNode
{
    TokenType type;
    char value[256];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *condition;
    struct ASTNode *elseNode;
} ASTNode;

char *source;
int pos = 0;
char currentChar;

Token currentToken;