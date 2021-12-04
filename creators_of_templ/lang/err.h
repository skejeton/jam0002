// Error printing
#ifndef ERR_H
#define ERR_H

typedef struct Location {
	int charno;
	int lineno;
} Location;

typedef struct Err {
    char buffer[4096];
    Location location;
} Err; 

// Creates a formatted error
Err err_f(Location at, char *fmt, ...);

// Prints formatted error into standard output
void err_explain(Err *err, char *source_file);

#endif // ERR_H

