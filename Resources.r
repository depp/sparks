#include "ResourceList.h"

#include "Dialogs.r"
#include "MacTypes.r"

Include "Resources.rsrc";

resource 'ALRT' (rALRT_Error, purgeable) {
	{ 40, 40, 137, 360 },
	128, /* DITL ID */
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	},
	centerMainScreen
};


resource 'ALRT' (rALRT_ChangeDepth, purgeable) {
	{ 58, 42, 165, 443 },
	129, /* DITL ID */
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	},
	noAutoCenter
};

resource 'DITL' (128, purgeable) {{
	/* Quit button */
	{ 67, 242, 87, 312 },
	Button { enabled, "Quit" },
	/* Error text */
	{ 7, 73, 54, 312 },
	StaticText { enabled, "^0" },
	/* Icon */
	{ 10, 20, 42, 52 },
	Icon { enabled, 0 }
}};

resource 'DITL' (129, purgeable) {{
	{74, 303, 94, 378},
	Button {
		enabled,
		"Change"
	},
	{74, 205, 94, 280},
	Button {
		enabled,
		"Quit"
	},
	{13, 78, 61, 378},
	StaticText {
		disabled,
		"This application can only run under 256 "
		"colors. Would you like them set to 256 "
		"now?  They will be set back when the app"
		"lication quits.  "
	},
	{13, 23, 45, 55},
	Icon {
		disabled,
		2
	}
}};

resource 'STR#' (rSTRS_Errors, purgeable) {{
	"An unknown error occurred.",
	"This game requires color QuickDraw.",
	"This game requires a monitor that supports 256 colors.",
	"Could not change monitor depth.",
}};
