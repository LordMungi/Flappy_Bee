#include "Credits.h"

#include "Templates.h"

namespace credits
{
	GameState nextState;

	btn::Button backButton;
	drw::TextData creditsTitleTextData;
	drw::TextData creditsTextData;
	drw::TextData credits2TextData;
	drw::TextData creditsTitle2TextData;
	drw::TextData credits3TextData;

	void init()
	{
		backButton = templates::button;
		backButton.pos = { 0.5f, 0.1f };
		backButton.textData.text = "Back";
		btn::Init(backButton);

		creditsTitleTextData.fontSize = 0.07f;
		creditsTitleTextData.text = "Programming";

		creditsTextData.fontSize = 0.05f;
		creditsTextData.text = "Borja Lia";

		credits2TextData.fontSize = 0.05f;
		credits2TextData.text = "Santino Verrua";

		creditsTitle2TextData.fontSize = 0.07f;
		creditsTitle2TextData.text = "Art";

		credits3TextData.fontSize = 0.05f;
		credits3TextData.text = "Vittorio Dolce";

		nextState = GameState::CREDITS;
	}

	GameState update()
	{
		btn::UpdateInput(backButton);
		if (backButton.signal) {
			nextState = GameState::MAIN_MENU;
		}
		btn::Sound(backButton);
		return nextState;
	}

	void draw()
	{
		btn::Draw(backButton);
		drw::Text(creditsTitleTextData.text.c_str(), creditsTitleTextData, { 0.5f, 0.90f }, creditsTitleTextData.fontSize, { 0,0 }, BLACK_B);
		drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.8f }, creditsTextData.fontSize, { 0,0 }, BLACK_B);
		drw::Text(credits2TextData.text.c_str(), credits2TextData, { 0.5f, 0.75f }, credits2TextData.fontSize, { 0,0 }, BLACK_B);
		drw::Text(creditsTitle2TextData.text.c_str(), creditsTitle2TextData, { 0.5f, 0.65f }, creditsTitle2TextData.fontSize, { 0,0 }, BLACK_B);
		credits3TextData.text = "Game Sprites - Vittorio Dolce";
		drw::Text(credits3TextData.text.c_str(), credits3TextData, { 0.5f, 0.55f }, credits3TextData.fontSize, { 0,0 }, BLACK_B);
		credits3TextData.text = "UI SFX - Cyrex Studios - https://cyrex-studios.itch.io/universal-ui-soundpack";
		drw::Text(credits3TextData.text.c_str(), credits3TextData, { 0.5f, 0.50f }, credits3TextData.fontSize, { 0,0 }, BLACK_B);
		credits3TextData.text = "Game SFX - FilmCow - https://filmcow.itch.io/filmcow-sfx";
		drw::Text(credits3TextData.text.c_str(), credits3TextData, { 0.5f, 0.45f }, credits3TextData.fontSize, { 0,0 }, BLACK_B);
		credits3TextData.text = "BGM - Pizza Doggy - https://pizzadoggy.itch.io/cozy-tunes";
		drw::Text(credits3TextData.text.c_str(), credits3TextData, { 0.5f, 0.40f }, credits3TextData.fontSize, { 0,0 }, BLACK_B);
	}
}