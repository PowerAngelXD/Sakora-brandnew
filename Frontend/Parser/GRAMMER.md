# 语法
该文档展示的是当前Sakora支持的语法，将分为Expression和Statement展示

**Expression**
```
identifier
keyword
callingExpr -> identifier ('(' (wholeExpr) (',' wholeExpr)* ')')
AtomIdentifier -> callingExpr ('[' (addExpr) ']')
IdentifierExpr -> AtomIdentifier ('.' AtomIdentifier)*
primExpr -> value | '(' wholeExpr ')' | arrayExpr | idenExpr
mulExpr -> primExpr ('*'|'/' primExpr)*
addExpr -> mulExpr ('+'|'-' mulExpr)*
logicExpr -> addExpr '!='|'=='|'>='|'<='|'>'|'<' addExpr
boolExpr -> logicExpr ('and'|'or' addExpr)*
arrayExpr -> '[' addExpr (',' addExpr)* ']'
primTypeExpr -> identifier | keyword
arrayTypeExpr -> primTypeExpr ('[' number ']')*
typeExpr -> arrayTypeExpr | primTypeExpr
wholeExpr -> addExpr | boolExpr
```

**Statement**
```
LetStatement -> 'let' identifier (':' typeExpr) '=' wholeExpr ';'
AssignStatement -> identifierExpr '=' wholeExpr ';'
```