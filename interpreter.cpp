// Definimos el entorno de ejecución
typedef struct {
    int variables[256]; // Asumiendo que las variables son identificadores simples de un solo carácter
} Environment;

void executeAST(ASTNode *node, Environment *env);


void executeShow(ASTNode *node) {
    printf("%s\n", node->left->value);
}

void executeRepeat(ASTNode *node, Environment *env) {
    int times = atoi(node->left->value);
    for (int i = 0; i < times; i++) {
        executeAST(node->right, env);
    }
}

int evaluateCondition(ASTNode *node, Environment *env) {
    // Evaluar condición simple
    // El nodo tiene el formato `VARIABLE OPERADOR VALOR`

    if (node == NULL || node->left == NULL || node->right == NULL) {
        printf("Error: Condicion de nodo invalido\n");
        exit(1);
    }
    
    char varName = node->value[0]; // Suponemos que la variable es un solo carácter
    int leftValue = env->variables[varName - 'a']; // Convertimos el carácter a índice (a=0, b=1, ..., z=25)
    int rightValue = atoi(node->right->value); // Convertimos el valor del nodo derecho a entero
    char *op = node->value; // El operador se guarda en node->value

    if (strcmp(op, "==") == 0) {
        return leftValue == rightValue;
    } else if (strcmp(op, "!=") == 0) {
        return leftValue != rightValue;
    } else if (strcmp(op, "<") == 0) {
        return leftValue < rightValue;
    } else if (strcmp(op, ">") == 0) {
        return leftValue > rightValue;
    } else if (strcmp(op, "<=") == 0) {
        return leftValue <= rightValue;
    } else if (strcmp(op, ">=") == 0) {
        return leftValue >= rightValue;
    }

    // Si el operador no es reconocido, reportamos un error
    printf("Error: Operador desconocido '%s'\n", op);
    exit(1);
    return 0; // Para evitar una advertencia del compilador
}

void executeIf(ASTNode *node, Environment *env) {
    if (evaluateCondition(node->condition, env)) {
        executeAST(node->left, env);
    } else if (node->elseNode != NULL) {
        executeAST(node->elseNode, env);
    }
}

// Implementación simplificada de ejecutar el AST
void executeAST(ASTNode *node, Environment *env) {
    switch (node->type) {
        case TOKEN_MOSTRAR:
            executeShow(node);
            break;
        case TOKEN_REPETIR:
            executeRepeat(node, env);
            break;
        case TOKEN_SI:
            executeIf(node, env);
            break;
        case TOKEN_INICIAR:
            executeAST(node->left, env);
            break;
        case TOKEN_FINALIZAR:
            break;
        default:
            printf("Error: Desconocido AST (Árbol de Sintaxis Abstracta) del tipo de nodo\n");
    }

    if (node->right != NULL) {
        executeAST(node->right, env);
    }
}


// Implementación simplificada del intérprete
void interpreter(ASTNode *ast) {    
    Environment env = {0};
    executeAST(ast, &env);
}

// Función para procesar el código fuente
void parseProgramAndStart(char *sourceCode) {
    setSource(sourceCode); // Establecer el código fuente en la primera posicion del token
    advanceToken(); // Obtiene el token completo
    
    while (currentToken.type != TOKEN_FINALIZAR) { //TOKEN_EOF
        ASTNode* instruction = parseInstruction();
        //interpreter(instruction);
    }

    //ASTNode *ast = parseProgram();
    //interpreter(ast);
}