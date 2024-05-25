<programa> ::= <iniciar> <cuerpo> <finalizar>
<iniciar> ::= "iniciar"
<finalizar> ::= "finalizar"
<cuerpo> ::= <instruccion> | <instruccion> <cuerpo>
<instruccion> ::= <mostrar> | <repetir> | <condicional>
<mostrar> ::= "mostrar" <texto>
<repetir> ::= "repetir" <numero> "veces" <iniciar> <cuerpo> <finalizar>
<condicional> ::= "si" <condicion> "entonces" <iniciar> <cuerpo> <finalizar> [ "sino" <iniciar> <cuerpo> <finalizar> ]
<condicion> ::= <expresion>
<expresion> ::= <variable> <operador> <valor>
<texto> ::= "\"" [a-zA-Z ]* "\""
<numero> ::= [0-9]+
<variable> ::= [a-zA-Z]+
<valor> ::= [a-zA-Z0-9]+
<operador> ::= "==" | "!=" | "<" | ">" | "<=" | ">="