#include "StateManager.h"
#include "GameState.h"

#include "Templates.h"
#include "Game.h"

namespace statemanager
{
	static void init();
	static void update(); 
	static void draw();

	void MainLoop()

	{
		bool isRunning = true;
		bLib::Init("Flappy Bird");
		GameState currentState = GameState::MAIN_MENU;

		//Menu
		btn::Button playButton;
		btn::Button play2Button;
		btn::Button creditsButton;
		btn::Button exitButton;

		// Credits
		btn::Button backButton;
		drw::TextData creditsTitleTextData;
		drw::TextData creditsTextData;
		drw::TextData credits2TextData;

		// Gameplay
	
		// Pause


		//Version Overlay
		drw::TextData versionTextData;


		// Inicializacion

		templates::init();

		//Menu
		playButton = templates::button;
		playButton.pos = { 0.5f, 0.6f };
		playButton.textData.text = "1P";
		btn::Init(playButton);

		play2Button = templates::button;
		play2Button.pos = { 0.5f, 0.5f };
		play2Button.textData.text = "2P";
		btn::Init(play2Button);

		creditsButton = templates::button;
		creditsButton.pos = { 0.5f, 0.4f };
		creditsButton.textData.text = "Credits";
		btn::Init(creditsButton);

		exitButton = templates::button;
		exitButton.pos = { 0.5f, 0.3f };
		exitButton.textData.text = "Exit";
		btn::Init(exitButton);

		//Credits
		backButton = templates::button;
		backButton.pos = { 0.5f, 0.3f };
		backButton.textData.text = "Back";
		btn::Init(backButton);

		creditsTitleTextData.fontSize = 0.07f;
		creditsTitleTextData.text = "Programming";

		creditsTextData.fontSize = 0.05f;
		creditsTextData.text = "Borja Lia";

		credits2TextData.fontSize = 0.05f;
		credits2TextData.text = "Santino Verrua";

		//Gameplay


		// Pause


		versionTextData.fontSize = 0.05f;
		versionTextData.text = "v0.4";
		versionTextData.color = SEMITRANSPARENT_B;

		while (isRunning) {

			isRunning = !rend::ShouldExit();

			//Update
			bLib::UpdateStart();

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				btn::UpdateInput(playButton);
				btn::UpdateInput(play2Button);
				btn::UpdateInput(creditsButton);
				btn::UpdateInput(exitButton);

				if (playButton.signal) 
				{
					currentState = GameState::GAMEPLAY;
					game::init(1);
				}
				if (play2Button.signal) 
				{
					currentState = GameState::GAMEPLAY;
					game::init(2);
				}
				if (creditsButton.signal) {
					currentState = GameState::CREDITS;
				}
				if (exitButton.signal) {
					isRunning = false;
				}
				break;

			case GameState::GAMEPLAY:
				currentState = game::update();
				break;

			case GameState::CREDITS:

				btn::UpdateInput(backButton);
				if (backButton.signal) {
					currentState = GameState::MAIN_MENU;
				}
				break;
			}


			bLib::UpdateEnd();

			//Draw
			drw::Begin();
			drw::Clear(DARKGREY_B);

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				btn::Draw(playButton);
				btn::Draw(play2Button);
				btn::Draw(creditsButton);
				btn::Draw(exitButton);
				drw::Text(versionTextData.text.c_str(), versionTextData, { 0.95f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);
				break;

			case GameState::GAMEPLAY:
				game::draw();
				break;

			case GameState::CREDITS:

				btn::Draw(backButton);
				drw::Text(creditsTitleTextData.text.c_str(), creditsTitleTextData, { 0.5f, 0.7f }, creditsTitleTextData.fontSize, { 0,0 }, BLACK_B);
				drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, BLACK_B);
				drw::Text(credits2TextData.text.c_str(), credits2TextData, { 0.5f, 0.53f }, credits2TextData.fontSize, { 0,0 }, BLACK_B);
				drw::Text(versionTextData.text.c_str(), versionTextData, { 0.95f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);
				break;
			}

			drw::End();
			//Sounds
		}
		rend::Close();
	}
}
