#include "Error.h"

#include "ResourceList.h"

#include <Dialogs.h>
#include <Processes.h>
#include <TextUtils.h>

#include <stdarg.h>
#include <string.h>

// Append strings onto one string. Final string must be NULL.
static void StrAppend(unsigned char *outp, ...) {
	unsigned n = outp[0], m;
	const unsigned char *arg;
	va_list ap;

	va_start(ap, outp);
	for (;;) {
		arg = va_arg(ap, const unsigned char *);
		if (arg == NULL) {
			break;
		}
		m = arg[0];
		if (m > 255 - n) {
			m = 255 - n;
		}
		memcpy(outp + n + 1, arg + 1, m);
		n += m;
	}
	va_end(ap);
	outp[0] = n;
}

static void ExitErrorOSMaybe(error_code err, short oserr, bool has_oserr) {
	Str255 message;

	GetIndString(message, rSTRS_Errors, err + 1);
	if (message[0] == 0) {
		GetIndString(message, rSTRS_Errors, 1);
	}
	if (has_oserr) {
		unsigned char num[16];
		NumToString(oserr, num);
		StrAppend(message, "\p (err = ", num, "\p)", NULL);
	}
	ParamText(message, NULL, NULL, NULL);
	Alert(rALRT_Error, NULL);
	ExitToShell();
}

void ExitError(error_code err) {
	ExitErrorOSMaybe(err, 0, false);
}

void ExitErrorOS(error_code err, short oserr) {
	ExitErrorOSMaybe(err, oserr, true);
}
