#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "objects.cpp"
#include "lexer.cpp"
#include "parser.cpp"
#include "interpreter.cpp"
using namespace std;


std::string readFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {//int argc, char* argv[]
    // if (argc != 2) {
    //     std::cerr << "Uso: " << argv[0] << " <archivo>" << std::endl;
    //     return 1;
    // }

    //char* filename = argv[1]; // Change the type of filename from const char* to char*
    char* filename = "holamundo.mad"; 
    std::string code = readFile(filename);

    parseProgramAndStart(const_cast<char*>(code.c_str())); // Use const_cast to convert const char* to char*
    //setSource(const_cast<char*>(code.c_str())); // Use const_cast to convert const char* to char*
    //char sourceCode[] = "iniciar mostrar \"Hola Mundo\" finalizar"; 
    //setSource(sourceCode);
    //advanceToken();

    /*while (currentToken.type != TOKEN_FINALIZAR) { //TOKEN_EOF
        ASTNode* instruction = parseInstruction();
        interpreter(instruction);
    }*/

    return 0;
}
