#ifndef ERROR_H
#define ERROR_H

// Codes for errors that can occur in-game.
typedef enum {
	kErrNone,
	kErrNoColorQD,
	kErrNo8Bit,
} error_code;

// Display an error message and exit the game.
void ExitError(error_code err);

// Display an error message with an OSErr value from the Macintosh toolbox.
void ExitErrorOS(error_code err, short oserr);

#endif
