//El lexer es responsable de convertir la entrada de texto en tokens:

// Función para avanzar al siguiente caracter en el código fuente
void advance() {
    pos++;
    currentChar = source[pos];
}

// Función para saltar los espacios en blanco
void skipWhitespace() {
    while (isspace(currentChar)) {
        advance();
    }
}

// Función para construir un token
Token makeToken(TokenType type, const char *value) {
    Token token;
    token.type = type;
    strcpy(token.value, value);
    return token;
}

// Función para obtener el siguiente token del código fuente
Token nextToken() {
    skipWhitespace();
    
    if (currentChar == '\0') return makeToken(TOKEN_EOF, "");

    if (isdigit(currentChar)) {
        char buffer[256];
        int i = 0;
        while (isdigit(currentChar)) {
            buffer[i++] = currentChar;
            advance();
        }
        buffer[i] = '\0';
        return makeToken(TOKEN_NUMERO, buffer);
    }

    if (isalpha(currentChar)) {
        char buffer[256];
        int i = 0;
        while (isalpha(currentChar)) {
            buffer[i++] = currentChar;
            advance();
        }
        buffer[i] = '\0';

        if (strcmp(buffer, "iniciar") == 0) return makeToken(TOKEN_INICIAR, buffer);
        if (strcmp(buffer, "finalizar") == 0) return makeToken(TOKEN_FINALIZAR, buffer);
        if (strcmp(buffer, "mostrar") == 0) return makeToken(TOKEN_MOSTRAR, buffer);
        if (strcmp(buffer, "repetir") == 0) return makeToken(TOKEN_REPETIR, buffer);
        if (strcmp(buffer, "veces") == 0) return makeToken(TOKEN_VECES, buffer);
        if (strcmp(buffer, "si") == 0) return makeToken(TOKEN_SI, buffer);
        if (strcmp(buffer, "entonces") == 0) return makeToken(TOKEN_ENTONCES, buffer);
        if (strcmp(buffer, "sino") == 0) return makeToken(TOKEN_SINO, buffer);
        
        return makeToken(TOKEN_VARIABLE, buffer);
    }

    if (currentChar == '\"') {
        advance();
        char buffer[256];
        int i = 0;
        while (currentChar != '\"') {
            buffer[i++] = currentChar;
            advance();
        }
        advance();  // Saltar cuota de cerrado
        buffer[i] = '\0';
        return makeToken(TOKEN_TEXTO, buffer);
    }

    if (currentChar == '=' || currentChar == '!' || currentChar == '<' || currentChar == '>') {
        char buffer[3] = { currentChar, '\0', '\0' };
        advance();
        if (currentChar == '=') {
            buffer[1] = '=';
            advance();
        }
        return makeToken(TOKEN_OPERADOR, buffer);
    }

    // Si llegamos aquí, nos encontramos con un caracter inesperado.
    char errorChar[2] = { currentChar, '\0' };
    advance();
    return makeToken(TOKEN_ERROR, errorChar);
}

// Función para establecer el código fuente a ser analizado por el lexer
void setSource(char *src) {
    source = src;
    pos = 0;
    currentChar = source[pos];
}
