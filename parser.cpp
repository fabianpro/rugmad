// El parser analizará los tokens generados por el lexer y construirá un Árbol de Sintaxis Abstracta (AST).

ASTNode *newNode(TokenType type, const char *value)
{
    printf("NewNode:" + type);
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    node->condition = NULL;
    node->elseNode = NULL;
    return node;
}

void advanceToken()
{
    currentToken = nextToken();
}

//ASTNode *parseProgram();
ASTNode *parseBody();
ASTNode *parseInstruction();
ASTNode *parseRepeat();
ASTNode *parseConditional();

/*ASTNode *parseProgram()
{
    advanceToken();
    if (currentToken.type != TOKEN_INICIAR)
    {
        printf("Error: Se esperaba 'iniciar'\n");
        exit(1);
    }

    ASTNode *node = newNode(TOKEN_INICIAR, "iniciar");
    node->left = parseBody();

    if (currentToken.type != TOKEN_FINALIZAR)
    {
        printf("Error: Se esperaba 'finalizar'\n");
        exit(1);
    }

    ASTNode *endNode = newNode(TOKEN_FINALIZAR, "finalizar");
    endNode->left = node;
    return endNode;
}*/

ASTNode *parseBody()
{
    ASTNode *node = parseInstruction();
    if (currentToken.type != TOKEN_FINALIZAR && currentToken.type != TOKEN_SINO)
    {
        node->right = parseBody();
    }
    return node;
}

ASTNode* parseFactor() {
    ASTNode* node = nullptr;

    if (currentToken.type == TOKEN_NUMERO) {
        node = newNode(TOKEN_NUMERO, currentToken.value);
        advanceToken();
    } else if (currentToken.type == TOKEN_VARIABLE) {
        node = newNode(TOKEN_VARIABLE, currentToken.value);
        advanceToken();
    } else {
        printf("Error: Se esperaba un número o una variable\n");
        exit(1);
    }

    return node;
}

/*ASTNode* parseTerm() {
    ASTNode* node = parseFactor();

    while (currentToken.type == TOKEN_OPERADOR &&
           (strcmp(currentToken.value, "*") == 0 || strcmp(currentToken.value, "/") == 0)) {
        TokenType operatorType = currentToken.type;
        const char* operatorValue = currentToken.value;
        advanceToken();
        ASTNode* rightNode = parseFactor();
        ASTNode* newNode = new ASTNode;
        newNode->type = operatorType;
        newNode->value = operatorValue;
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }

    return node;
}

ASTNode* parseExpression() {
    ASTNode* node = parseTerm();

    while (currentToken.type == TOKEN_OPERADOR &&
           (strcmp(currentToken.value, "+") == 0 || strcmp(currentToken.value, "-") == 0)) {
        TokenType operatorType = currentToken.type;
        const char* operatorValue = currentToken.value;
        advanceToken();
        ASTNode* rightNode = parseTerm();
        ASTNode* newNode = new ASTNode;
        newNode->type = operatorType;
        newNode->value = operatorValue;
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }

    return node;
}*/

ASTNode *parseInstruction() {
    ASTNode *node = NULL;

    switch (currentToken.type) {
        case TOKEN_INICIAR:
            // Crear el nodo para 'iniciar'
            node = newNode(TOKEN_INICIAR, currentToken.value);
            advanceToken();
            node->left = parseBody();
            break;
        case TOKEN_MOSTRAR:
            // Crear el nodo para 'mostrar'
            node = newNode(TOKEN_MOSTRAR, currentToken.value);
            advanceToken();
            // Verificar que el siguiente token sea de tipo TEXTO
            if (currentToken.type != TOKEN_TEXTO) {
                printf("Error: Se esperaba texto después de 'mostrar'\n");
                exit(1);
            }
            // Crear un nodo hijo para el texto
            node->left = newNode(TOKEN_TEXTO, currentToken.value);
            printf("NewNode:" + type);
            advanceToken();
            break;

        case TOKEN_SI:
            // Parsear una estructura condicional
            node = parseConditional();
            break;

        case TOKEN_REPETIR:
            // Parsear una estructura de repetición
            node = parseRepeat();
            break;

        /*case TOKEN_VARIABLE:
            // Suponiendo que puede haber asignaciones de variables
            node = newNode(TOKEN_VARIABLE, currentToken.value);
            advanceToken();
            if (currentToken.type != TOKEN_OPERADOR || strcmp(currentToken.value, "=") != 0) {
                printf("Error: Se esperaba '=' después de la variable\n");
                exit(1);
            }
            advanceToken();
            node->left = parseExpression();  // Suponiendo una función parseExpression para manejar expresiones
            break;*/

        default:
            if (currentToken.type != TOKEN_FINALIZAR) {
                printf("Error: Instrucción no reconocida: %s\n", currentToken.value);
                exit(1);
            }   
            return NULL;       
    }

    return node;
}

ASTNode *parseRepeat()
{
    ASTNode *node = newNode(TOKEN_REPETIR, currentToken.value);
    advanceToken();
    if (currentToken.type != TOKEN_NUMERO)
    {
        printf("Error: Se esperaba un número después de 'repetir'\n");
        exit(1);
    }
    node->left = newNode(TOKEN_NUMERO, currentToken.value);
    advanceToken();
    if (currentToken.type != TOKEN_VECES)
    {
        printf("Error: Se esperaba 'veces' después del número en 'repetir'\n");
        exit(1);
    }
    advanceToken();
    if (currentToken.type != TOKEN_INICIAR)
    {
        printf("Error: Se esperaba 'iniciar' después de 'repetir [num] veces'\n");
        exit(1);
    }
    node->right = parseBody();
    if (currentToken.type != TOKEN_FINALIZAR)
    {
        printf("Error: Se esperaba 'finalizar' después del cuerpo de 'repetir [num] veces'\n");
        exit(1);
    }
    advanceToken();
    return node;
}

ASTNode *parseConditional()
{
    ASTNode *node = newNode(TOKEN_SI, currentToken.value);
    advanceToken();
    if (currentToken.type != TOKEN_NUMERO)
    {
        printf("Error: Se esperaba numero despues de 'si'\n");
        exit(1);
    }
    node->condition = newNode(TOKEN_NUMERO, currentToken.value);
    advanceToken();

    if (currentToken.type != TOKEN_OPERADOR)
    {
        printf("Error: Se esperaba condicion despues del numero\n");
        exit(1);
    }
    node->condition = newNode(TOKEN_OPERADOR, currentToken.value);
    advanceToken();

    if (currentToken.type != TOKEN_NUMERO)
    {
        printf("Error: Se esperaba numero despues del comparador o condicion\n");
        exit(1);
    }
    node->condition = newNode(TOKEN_NUMERO, currentToken.value);
    advanceToken();

    if (currentToken.type != TOKEN_ENTONCES)
    {
        printf("Error: Se esperaba 'entonces' despues de la condicion en 'si'\n");
        exit(1);
    }
    advanceToken();

    if (currentToken.type != TOKEN_INICIAR)
    {
        printf("Error: Se esperaba 'iniciar' despues 'si [condición] entonces'\n");
        exit(1);
    }
    node->left = parseBody();

    if (currentToken.type != TOKEN_FINALIZAR)
    {
        printf("Error: Se esperaba 'finalizar' despues del cuerpo del 'si'\n");
        exit(1);
    }
    advanceToken();

    if (currentToken.type == TOKEN_SINO)
    {
        advanceToken();
        if (currentToken.type != TOKEN_INICIAR)
        {
            printf("Error: Se esperaba 'iniciar' despues de 'sino'\n");
            exit(1);
        }
        node->elseNode = parseBody();
        if (currentToken.type != TOKEN_FINALIZAR)
        {
            printf("Error: Se esperaba 'finalizar' despues del cuerpo de 'sino'\n");
            exit(1);
        }
        advanceToken();
    }
    return node;
}
