#include "templ.h"
#include <ctype.h>
#include <stdio.h>

static inline int is_skip_char(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static char peekc(Lexer *l) {
	return l->buf[l->cursor];
}

static char nextc(Lexer *l) {
	char c = l->buf[l->cursor++];
	l->loc.charno++;
	if (c == '\n') {
		l->loc.lineno++;
		l->loc.charno = 0;
	}
	return c;
}

Token next(Lexer *l) {
	for (char c=peekc(l); c && is_skip_char(c); c=peekc(l))
		nextc(l);

	int move = 1;
	Token tok = { .loc = l->loc, .val = l->buf + l->cursor, .len = 1 };
	switch (peekc(l)) {
	case 0:
		tok.type = tok_eof;
		move = 0;
		break;
	case '(':
		tok.type = tok_lparen;
		break;
	case ')':
		tok.type = tok_rparen;
		break;
	case '{':
		tok.type = tok_lbrace;
		break;
	case '}':
		tok.type = tok_rbrace;
		break;
	case '.':
		tok.type = tok_dot;
		break;
	case ':':
		tok.type = tok_colon;
		break;
	case ';':
		tok.type = tok_semicolon;
		break;
	case '@':
		tok.type = tok_at;
		break;
	case '$':
		tok.type = tok_var;
		break;
	case '"':
		tok.type = tok_strlit;
		++tok.val;
		nextc(l);
		for (char c=nextc(l); c && c != '"'; c=peekc(l)) {
			tok.len++;
			nextc(l);
		}
		break;
	case '+': case '-': case '*': case '/': case '=':
		tok.type = tok_operator;
		break;
	default:;
		char c = peekc(l);
		if (isdigit(c) || c == '-') {
			tok.type = tok_numlit;
			int numdot = 0;
			for (c = nextc(l); isdigit(c) || c == '.'; c = peekc(l)) {
				if (c == '.') numdot++;
				c = nextc(l);
				tok.len++;
			}
			//if (numdot > 1) { } TODO handle error
		} else {
			tok.type = tok_ident;
			for (c = nextc(l); (isalnum(c) || c == '_'); c = peekc(l)) {
				c = nextc(l);
				tok.len++;
			}
		}

		move = 0;
	}

	if (move) nextc(l);

	return tok;
}

void print_tok(Token tok) {
	static const char *type_lookup[] = {
		"lparen", "rparen", "lbrace", "rbrace", "dot", "colon", "semicolon",
		"comma", "at", "variable", "keyword", "number", "string", "identifier",
		"operator", "eof"
	};

	printf("tok (%d: %d) \'%.*s\' %s\n",
		tok.loc.lineno, tok.loc.charno, tok.len, tok.val, type_lookup[tok.type]);
}
