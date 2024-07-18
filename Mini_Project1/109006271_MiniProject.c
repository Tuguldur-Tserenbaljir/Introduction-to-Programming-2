#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//go to lex.h
///////////////////////////////////////////////////////////////////////

#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE, 
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, INCDEC,
    LPAREN, RPAREN,
    XOR, OR , AND,

} TokenSet;

// Test if a token matches the current token 
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);




//go to parser.h
///////////////////////////////////////////////////////////////////////

#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    printf("EXIT 1\n"); \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left; 
    struct _Node *right;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Find the memory address of a register 
extern int find_memory_address(char* string, int is_assign);

// Free the syntax tree
extern void freeTree(BTNode *root);
//neg negeer unshin
extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *expr_tail(BTNode *left);
extern void statement(void); //buheleer avaad
//statement expression oor ni buheleer ni duudagdan
//expr ehleed unshij dussaad
//term->tail, tail->factor, factor-> +, - iig duudna

extern BTNode *assign_expr(void);
extern BTNode *or_expr(void);
extern BTNode *or_expr_tail(BTNode *left);
extern BTNode *xor_expr(void);
extern BTNode *xor_expr_tail(BTNode *left);
extern BTNode *and_expr(void);
extern BTNode *and_expr_tail(BTNode *left);
extern BTNode *addsub_expr(void);
extern BTNode *addsub_expr_tail(BTNode *left);
extern BTNode *muldiv_expr(void);
extern BTNode *muldiv_expr_tail(BTNode *left);
extern BTNode *unary_expr (void);
/*
statement        := END | assign_expr END                                           +
assign_expr      := ID ASSIGN assign_expr | or_expr
or_expr          := xor_expr or_expr_tail
or_expr_tail     := OR xor_expr or_expr_tail | NiL
xor_expr         := and_expr xor_expr_tail
xor_expr_tail    := XOR and_expr xor_expr_tail | NiL
and_expr         := addsub_expr and_expr_tail
and_expr_tail    := AND addsub_expr and_expr_tail | NiL
addsub_expr      := muldiv_expr addsub_expr_tail
addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
muldiv_expr      := unary_expr muldiv_expr_tail
muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
unary_expr       := ADDSUB unary_expr | factor
factor           := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
*/

// Print error message and exit the program
extern void err(ErrorType errorNum);

//go to code.h
///////////////////////////////////////////////////////////////////////

// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);
extern int register_idx_tree(BTNode * root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
extern void printPostfix(BTNode *root);
extern void printInfix(BTNode *root);

extern int register_index;
extern int is_id;

//go to lex.c
///////////////////////////////////////////////////////////////////////
static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');
    //INCDEC,XOR, OR , AND,
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c)  && i < MAXLEN) {
            if(c =='_') error(SYNTAXERR);
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';

        char sym= fgetc(stdin);
            if(sym == '+'){
                //Checking if INCDEC ++
                lexeme[1] = '+'; //marking ++ incdec as $
                lexeme[2] = '\0';
                return INCDEC;
            }
            else if(sym == '-'){
                lexeme[1] = '-'; //marking -- incdec as @
                lexeme[2] = '\0';
                return INCDEC;
            }
            else ungetc(sym,stdin);
                return ADDSUB;
    }else if (c == '&' ) {
        //AND
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '^' ) {
        //XOR
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == '|' ) {
        //OR
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    }else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while((isalpha(c) || c == '_' || isdigit(c)) && i<MAXLEN){
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}




//go to parser.c
///////////////////////////////////////////////////////////////////////
int sbcount = 0;
Symbol table[TBLSIZE];

/*
    extern BTNode *expr(void);
    extern BTNode *expr_tail(BTNode *left);
    extern BTNode *term(void);
    extern BTNode *term_tail(BTNode *left);
    statement        := END | assign_expr END                                           +
assign_expr      := ID ASSIGN assign_expr | or_expr
or_expr          := xor_expr or_expr_tail
or_expr_tail     := OR xor_expr or_expr_tail | NiL
xor_expr         := and_expr xor_expr_tail
xor_expr_tail    := XOR and_expr xor_expr_tail | NiL
and_expr         := addsub_expr and_expr_tail
and_expr_tail    := AND addsub_expr and_expr_tail | NiL
addsub_expr      := muldiv_expr addsub_expr_tail
addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
muldiv_expr      := unary_expr muldiv_expr_tail
muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
unary_expr       := ADDSUB unary_expr | factor
    factor           := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
*/

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}
//Getvak us to get value of an in
//And it can be used in codegen deoendding on how you code it
int getval(char *str) {
    int i = 0;
    for (i = 0; i < sbcount; i++){
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    }

    if (sbcount >= TBLSIZE){
        err(RUNOUT);
    }
    error(RUNOUT);
    return 0;
}
//   x= 100 + 10*y
//   table.name =======> \
// setting the value of x,y,z (table name) to the current result
int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}


int find_memory_address(char* string, int is_assign){
    for(int i=0; i<sbcount; i++){
        if(strcmp(string, table[i].name)==0){
            return i;
        }
    }

    if (sbcount >= TBLSIZE){
        //printf("error runout getval_register_idx\n"); // debug
        error(RUNOUT);
    }

    else if(is_assign == 1){
        strcpy(table[sbcount].name, string);
        table[sbcount].val = 0;
        sbcount++;
        return (sbcount-1); 
    }

    // if(is_assign == 1){
    //     strcpy(table[sbcount].name, string);
    //     table[sbcount].val = 0;
    //     sbcount++;
    //     return (sbcount-1); 
    // }

    // else if (sbcount >= TBLSIZE){
    //     //printf("error runout getval_register_idx\n"); // debug
    //     error(RUNOUT);
    // }
    return 0; 

}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//factor  := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  | 
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN

BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        retp->right = makeNode(INT, "1"); //bcs increment decrement will either +1 or -1
        advance();
        if (match(ID)) {
            retp->left = makeNode(ID, getLexeme());
            advance();
        }
        else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr(); //accrding grammar
        if (match(RPAREN))
            advance();
        else{ error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }

    return retp;
}


//  assign_expr     := ID ASSIGN assign_expr | or_expr
BTNode *assign_expr(void){
    BTNode *node = NULL;
    BTNode *left_child = or_expr();

    if(match(ASSIGN)){ // bcs if its assign u wanna check first
        if(left_child->data == ID){
            node = makeNode(ASSIGN, getLexeme());
            advance();
            node->left = left_child;
            node->right = assign_expr();
            return node;
        }else{
            error(NOTNUMID);
            return NULL;
        }
    }else{
        return left_child;
    }
}


//    or_expr         := xor_expr or_expr_tail
BTNode *or_expr(void){
    BTNode *node = xor_expr(); // they want xor_expr @ grammar
    return or_expr_tail(node);
}


//double check with someone cause tuudo wrote this
//    or_expr_tail     := OR xor_expr or_expr_tail | NiL
BTNode *or_expr_tail(BTNode *left){
    BTNode *node = NULL;
    if(match(OR)){
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else{
        return left;
    }
}


//xor_expr         := and_expr xor_expr_tail
BTNode *xor_expr(void){
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}


//xor_expr_tail    := XOR and_expr xor_expr_tail | NiL
BTNode *xor_expr_tail(BTNode *left){
    BTNode *node = NULL;
    if(match(XOR)){
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}


//and_expr         := addsub_expr and_expr_tail
BTNode *and_expr(void){
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}


//and_expr_tail    := AND addsub_expr and_expr_tail | NiL
BTNode *and_expr_tail(BTNode *left){
    BTNode *node = NULL;
    if (match(AND)){
        node = makeNode(AND,getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else{
        return left;
    }
}


//addsub_expr      := muldiv_expr addsub_expr_tail
BTNode *addsub_expr(void){
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}



//addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left){
    BTNode *node = NULL;
    if(match(ADDSUB)){
        node = makeNode(ADDSUB,getLexeme());
        advance();
        node->left = left ;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    }else{
        return left;
    }
}


//muldiv_expr      := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(void){
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}


//muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode *left){
    BTNode *node = NULL;
    if(match(MULDIV)){
        node = makeNode(MULDIV,getLexeme());
        advance();
        node->left=left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else{
        return left;
    }
}


//unary_expr       := ADDSUB unary_expr | factor
BTNode *unary_expr (void){
    BTNode *node=NULL;
    if (match(ADDSUB)){
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = makeNode(INT, "0");
        node->right = unary_expr();
        return node;
    } else{
        return factor();
    }
}


//statement        := END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        for(int i=0;i<3;i++){//printing the output before endfile
            printf("MOV r%d [%d]\n",i , i*4);
        }
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
       // printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            register_index = 0;
            int x= evaluateTree(retp);
            int print = register_idx_tree(retp);
            
            // printf("Prefix traversal: ");
            // printPrefix(retp);
            // printf("\n");
            // printf("Infix traversal: ");
            // printInfix(retp);
            // printf("\n");
            // printf("Postfix traversal: ");
            // printPostfix(retp);
            // printf("\n");
            // // printf("memory values : ");
                // for(int i=0;i<10;i++){ //printing the output
                //     printf("%d\n",table[i].val);
                // }

            // for(int i=0;i<3;i++){//printing the output before endfile
            //     printf("MOV [%d] %d\n",i,table[i].val);
            // }
            freeTree(retp);
            advance();
        } else {
            err(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}



//go to code.c
///////////////////////////////////////////////////////////////////////
int register_index;
int is_id;
int ada_id;

int register_idx_tree(BTNode * root){
    int retval = 0, lv = 0, rv = 0;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = register_index;
                register_index++;
                printf("MOV r%d [%d]\n", retval, find_memory_address(root->lexeme, 0)*4);
                ada_id = 1;
                break;
            case INT:
                retval = register_index;
                register_index++;
                int number = atoi(root->lexeme);
                printf("MOV r%d %d\n", retval, number);
                break;
            case ASSIGN:
                rv = register_idx_tree(root->right);
                printf("MOV [%d] r%d\n", find_memory_address(root->left->lexeme,1)*4, rv);
                retval = rv;
                break;
            case ADDSUB:
                lv = register_idx_tree(root->left);
                rv = register_idx_tree(root->right);
                    if (strcmp(root->lexeme, "+") == 0) {
                        retval = lv;
                        printf("ADD r%d r%d\n",lv, rv);// ADD, register no_, register no_
                    } else if (strcmp(root->lexeme, "-") == 0) {
                        retval = lv;
                        printf("SUB r%d r%d\n", lv, rv);
                    } 
                register_index--;
                break;
            case MULDIV://they want u to print out the assembly code
                lv = register_idx_tree(root->left);
                if (strcmp(root->lexeme, "*") == 0) {
                    rv = register_idx_tree(root->right);
                    retval = lv;
                    printf("MUL r%d r%d\n", lv, rv);
                } else if (strcmp(root->lexeme, "/") == 0) {
                    ada_id = 0;
                    rv = register_idx_tree(root->right);
                    int temp = evaluateTree(root->right);
                   
                    if (ada_id == 0 && temp == 0){
                        error(DIVZERO);
                    }
                   
                    if(ada_id == 1 && temp == 0){
                        retval = 0;
                    }
                    else retval = lv;
                    printf("DIV r%d r%d\n", lv, rv);
                }
                register_index--;
                break;
            case INCDEC:
                lv = register_idx_tree(root->left); //this it the ID
                rv = register_idx_tree(root->right);
                if (strcmp(root->lexeme, "++") == 0) {//for inc dec, u directly change value of the variable
                    retval = lv;
                    printf("ADD r%d r%d\n", lv, rv);// ADD, register no_, register no_
                } else if (strcmp(root->lexeme, "--") == 0) {
                    retval = lv;
                    printf("SUB r%d r%d\n", lv, rv);
                }
                printf("MOV [%d] r%d\n", find_memory_address(root->left->lexeme,0)*4, lv);
                register_index--;
                break;
            case XOR:
                lv = register_idx_tree(root->left);
                rv = register_idx_tree(root->right);
                if(strcmp(root->lexeme, "^")==0){
                    retval = lv;
                    printf("XOR r%d r%d\n", lv, rv);
                }
                register_index--;
                break;
            case OR:
                lv = register_idx_tree(root->left);
                rv = register_idx_tree(root->right);
                if(strcmp(root->lexeme, "|")==0){
                    retval = lv;
                    printf("OR r%d r%d\n", lv, rv);
                }
                register_index--;
                break;
            case AND:
                lv = register_idx_tree(root->left);
                rv = register_idx_tree(root->right);
                if(strcmp(root->lexeme, "&")==0){
                    retval = lv;
                    printf("AND r%d r%d\n", lv, rv);
                }
                register_index--;
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme); // if ID found, u get the value
                is_id = 1;
                ada_id = 1;
                break;
            case INT:
                retval = atoi(root->lexeme); //atoi reads string and make into int
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);//if u find '=', u set value into a variable
                break;
            case ADDSUB:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                    if (strcmp(root->lexeme, "+") == 0) {
                        retval = lv + rv;
                    } else if (strcmp(root->lexeme, "-") == 0) {
                        retval = lv - rv;
                    } 
                break;
            case MULDIV://they want u to print out the assembly code
                lv = evaluateTree(root->left);
                if (strcmp(root->lexeme, "*") == 0) {
                    rv = evaluateTree(root->right);
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    is_id = 0;
                    rv = evaluateTree(root->right);
                   
                    if (is_id == 0 && rv == 0){
                        error(DIVZERO);
                    }
                    if(is_id == 1 && rv == 0){
                        retval = 0;
                    }
                    else retval = lv / rv;
                }
                break;
            case INCDEC:
                lv = evaluateTree(root->left); //this it the ID
                if (strcmp(root->lexeme, "++") == 0) {//for inc dec, u directly change value of the variable
                    retval = setval(root->left->lexeme, lv+1); // increment
                } else if (strcmp(root->lexeme, "--") == 0) {
                    retval = setval(root->left->lexeme, lv-1);//decrement
                }
                break;
            case XOR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if(strcmp(root->lexeme, "^")==0){
                    retval = lv ^ rv;
                }
                break;
            case OR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if(strcmp(root->lexeme, "|")==0){
                    retval = lv | rv;
                }
                break;
            case AND:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if(strcmp(root->lexeme, "&")==0){
                    retval = lv & rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


void printPostfix(BTNode *root) {
    if (root != NULL) {
        printPostfix(root->left);
        printPostfix(root->right);
        printf("%s ", root->lexeme);
    }else{
        //printf("End ");
    }
}

void printInfix(BTNode *root) {
    if (root != NULL) {
        printInfix(root->left);
        printf("%s ",root->lexeme);
        printInfix(root->right);
    }else{
        //printf("End ");
    }
}


//MAIN.c
//////////////////////////////////////////////////////////////////

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  | 
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}

/*
x = 5*y
MOV r0 5
MOV r1 [4]
MUL r0 r1
MOV [0] r0

x = 5/y
MOV r0 5
MOV r1 [4]
DIV r0 r1
MOV [0] r0

x = (y + (z = 2))
MOV r0 [4]
MOV r1 2
MOV [8] r1
ADD r0 r1
MOV [0] r0

x = (y = (z = (1+2)))
MOV r0 1
MOV r1 2
ADD r0 r1
MOV [8] r0
MOV [4] r0
MOV [0] r0

*/