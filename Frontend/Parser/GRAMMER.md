# 语法
该文档展示的是当前Sakora支持的语法，将分为Expression和Statement展示

**Expression**
```
primExpr -> value | '(' wholeExpr ')'
mulExpr -> primExpr ('*'|'/' primExpr)*
addExpr -> mulExpr ('+'|'-' mulExpr)*
boolExpr -> addExpr ('and'|'or' addExpr)*
wholeExpr -> addExpr 
```