#ifndef TEMPLE_H
#define TEMPLE_H

typedef enum {
	tok_lparen,
	tok_rparen,
	tok_lbrace,
	tok_rbrace,
	tok_dot,
	tok_colon,
	tok_semicolon,
	tok_comma,
	tok_at,
	tok_var,
	tok_keyword,
	tok_numlit,
	tok_strlit,
	tok_ident,
	tok_operator,
	tok_eof
} TokenType;

typedef struct {
	int charno;
	int lineno;
} Location;

typedef struct {
	Location loc;
	TokenType type;
	char *val;
	int len;
} Token;

typedef struct {
	char *buf; // null terminated
	Location loc;
	int cursor;
} Lexer;

Token next(Lexer *l);
void print_tok(Token tok);

#endif
