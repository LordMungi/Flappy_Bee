#include "Templates.h"

namespace templates
{
	btn::Button button;

	void init()
	{
		button.size = { 0.275f, 0.075f };
		button.textData.fontSize = 0.075f;
		button.useSprite = false;
		button.activeColor = SEMITRANSPARENT_B;
		button.mainColor = SEMITRANSPARENT_B;
		button.hoveredColor = SEMITRANSPARENT_B;
	}
}