#include "ResourceList.h"

#include "Dialogs.r"

Include "Resources.rsrc";

resource 'ALRT' (rALRT_ChangeDepth, purgeable) {
	{58, 42, 165, 443},
	400, /* DITL ID */
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	},
	noAutoCenter
};

resource 'DITL' (400, purgeable) {{
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
