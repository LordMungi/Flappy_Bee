#include "StateManager.h"

void MainLoop()

{
	bool isPaused = false;
	bool isActive = true;

	ctrl::Key pauseKey = ctrl::Key::ESCAPE;
	ctrl::Key restartKey = ctrl::Key::SPACE;

	bool isRunning = true;
	bLib::Init("Flappy Bird");
	GameState currentState = GameState::MAIN_MENU;
	int playersInGame = 0;

	float gameTimer = 0.0f;
	//const int MOUSE_PARTICLE_COUNT = 5;

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
	btn::Button pauseButton;
	drw::TextData scoreTextData;
	//drw::AnimationData mouseAnim;
	//prtcl::ParticleActivator mouseParticleActivator;
	//prtcl::ParticleData mouseParticles[MOUSE_PARTICLE_COUNT]; // Array estático
	drw::TextData labelData;

	vec::Vector2 backgroundSize = { 3.5f, 1 };

	drw::SpriteData backgroundFar;
	backgroundFar.file = "res/sprites/parallax/back.png";
	backgroundFar.size = { 2.0f,1.0f };
	backgroundFar.offset = {0.0f,0.0f};
	float farSpeed = 0.2f;
	vec::Vector2 farOffset2 = { backgroundFar.size.x, 0.0f };

	backgroundFar.id = drw::InitSpriteData(backgroundFar);

	drw::SpriteData backgroundMid;
	backgroundMid.file = "res/sprites/parallax/mid.png";
	backgroundMid.size = { 2.0f,1.0f };
	backgroundMid.offset = {0.0f,0.0f};
	float midSpeed = 0.4f;
	vec::Vector2 midOffset2 = { backgroundMid.size.x, 0.0f };

	backgroundMid.id = drw::InitSpriteData(backgroundMid);

	drw::SpriteData backgroundNear;
	backgroundNear.file = "res/sprites/parallax/front.png";
	backgroundNear.size = { 2.0f,1.0f };
	backgroundNear.offset = {0.0f,0.0f};
	float nearSpeed = 0.6f;
	vec::Vector2 nearOffset2 = { backgroundNear.size.x, 0.0f };

	backgroundNear.id = drw::InitSpriteData(backgroundNear);

	const int maxPlayers = 2;

	bll::Ball players[maxPlayers] = {};
	for (int i = 0; i < maxPlayers; i++)
		bll::Init(players[i], i + 1);


	obstcl::FullObstacle obstacles[obstcl::maxObstacles];
	obstcl::Init(obstacles);

	// Pause
	btn::Button retryButton;
	btn::Button returnButton;
	btn::Button exitPauseButton;

	//Version Overlay
	drw::TextData versionTextData;

	//drw::SpriteData fireFrame1;
	//fireFrame1.file = "res/sprites/fire1.png";
	//fireFrame1.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame2;
	//fireFrame2.file = "res/sprites/fire2.png";
	//fireFrame2.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame3;
	//fireFrame3.file = "res/sprites/fire3.png";
	//fireFrame3.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame4;
	//fireFrame4.file = "res/sprites/fire4.png";
	//fireFrame4.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrames[] = { fireFrame1, fireFrame2, fireFrame3, fireFrame4 };

	//mouseAnim.duration = 0.25f;
	//drw::InitAnimData(mouseAnim, fireFrames, 4);

	// Inicializacion

	btn::Button templateButton;
	templateButton.size = { 0.275f, 0.075f };
	templateButton.textData.fontSize = 0.075f;
	templateButton.useSprite = false;
	templateButton.activeColor = SEMITRANSPARENT_B;
	templateButton.mainColor = SEMITRANSPARENT_B;
	templateButton.hoveredColor = SEMITRANSPARENT_B;


	//Menu
	playButton = templateButton;
	playButton.pos = { 0.5f, 0.6f };
	playButton.textData.text = "1P";
	btn::Init(playButton);

	play2Button = templateButton;
	play2Button.pos = { 0.5f, 0.5f };
	play2Button.textData.text = "2P";
	btn::Init(play2Button);

	creditsButton = templateButton;
	creditsButton.pos = { 0.5f, 0.4f };
	creditsButton.textData.text = "Credits";
	btn::Init(creditsButton);

	exitButton = templateButton;
	exitButton.pos = { 0.5f, 0.3f };
	exitButton.textData.text = "Exit";
	btn::Init(exitButton);

	//Credits
	backButton = templateButton;
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
	pauseButton = templateButton;
	pauseButton.pos = { 0.5f, 0.9f };
	pauseButton.textData.text = "Pause";
	btn::Init(pauseButton);

	scoreTextData.fontSize = 0.1f;

	//mouseParticleActivator.loop = true;
	//mouseParticleActivator.animated = true;
	//mouseParticleActivator.animation = mouseAnim;
	//mouseParticleActivator.amount = MOUSE_PARTICLE_COUNT;
	//mouseParticleActivator.lifetime = { 0.2f, 0.5f };
	//mouseParticleActivator.direction = { 0.0f, -1.0f };
	//mouseParticleActivator.spread = 180.0f;
	//mouseParticleActivator.minSize = { 0.005f, 0.005f };
	//mouseParticleActivator.maxSize = { 0.02f, 0.02f };
	//mouseParticleActivator.speed = { 0.1f, 0.3f };
	//prtcl::Init(mouseParticleActivator, mouseParticles);

	retryButton = templateButton;
	retryButton.pos = { 0.5f, 0.7f };
	retryButton.textData.text = "Retry";
	btn::Init(retryButton);

	returnButton = templateButton;
	returnButton.pos = { 0.5f, 0.6f };
	returnButton.textData.text = "Return";
	btn::Init(returnButton);

	exitPauseButton = templateButton;
	exitPauseButton.pos = { 0.5f, 0.5f };
	exitPauseButton.textData.text = "Exit to Menu";
	btn::Init(exitPauseButton);

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

			if (playButton.signal) {
				playersInGame = 1;
				currentState = GameState::GAMEPLAY;
				isPaused = false;
				gameTimer = 0.0f;
				bll::Reset(players[0]);
				obstcl::Reset(obstacles);
			}
			if (play2Button.signal) {
				playersInGame = 2;
				currentState = GameState::GAMEPLAY;
				isPaused = false;
				gameTimer = 0.0f;
				bll::Reset(players[0]);
				bll::Reset(players[1]);
				obstcl::Reset(obstacles);
			}
			if (creditsButton.signal) {
				currentState = GameState::CREDITS;
			}
			if (exitButton.signal) {
				isRunning = false;
			}
			break;

		case GameState::GAMEPLAY:

			if (isPaused) {

				btn::UpdateInput(retryButton);
				btn::UpdateInput(returnButton);
				btn::UpdateInput(exitPauseButton);

				if (retryButton.signal) {
					isPaused = false;
					gameTimer = 0.0f;
					for (int i = 0; i < playersInGame; i++)
						bll::Reset(players[i]);
					
					obstcl::Reset(obstacles);
				}

				if (returnButton.signal || ctrl::IsKeyPressed(pauseKey)) {
					isPaused = false;
				}

				if (exitPauseButton.signal) {
					currentState = GameState::MAIN_MENU;
				}
				break;
			}
			else if (isActive)
			{
				if (backgroundFar.offset.x <= -backgroundFar.size.x) {
					backgroundFar.offset.x = farOffset2.x + backgroundFar.size.x;
				}
				if (farOffset2.x <= -backgroundFar.size.x) {
					farOffset2.x = backgroundFar.offset.x + backgroundFar.size.x;
				}
				if (backgroundMid.offset.x <= -backgroundMid.size.x) {
					backgroundMid.offset.x = midOffset2.x + backgroundMid.size.x;
				}
				if (midOffset2.x <= -backgroundMid.size.x) {
					midOffset2.x = backgroundMid.offset.x + backgroundMid.size.x;
				}
				if (backgroundNear.offset.x <= -backgroundNear.size.x) {
					backgroundNear.offset.x = nearOffset2.x + backgroundNear.size.x;
				}
				if (nearOffset2.x <= -backgroundNear.size.x) {
					nearOffset2.x = backgroundNear.offset.x + backgroundNear.size.x;
				}

				backgroundFar.offset.x -= rend::deltaTime * farSpeed;
				farOffset2.x -= rend::deltaTime * farSpeed;
				backgroundMid.offset.x -= rend::deltaTime * midSpeed;
				midOffset2.x -= rend::deltaTime * midSpeed;
				backgroundNear.offset.x -= rend::deltaTime * nearSpeed;
				nearOffset2.x -= rend::deltaTime * nearSpeed;

				gameTimer += rend::deltaTime;


				for (int i = 0; i < playersInGame; i++)
				{
					bll::UpdateInput(players[i]);
					bll::Update(players[i]);
					if (!players[i].isAlive)
						players[i].pos += obstacles[0].vel * rend::deltaTime;
				}

				obstcl::Update(obstacles);


			}
			else
			{
				if (ctrl::IsKeyPressed(restartKey))
				{
					gameTimer = 0.0f;
					for (int i = 0; i < playersInGame; i++)
						bll::Reset(players[i]);
					obstcl::Reset(obstacles);
				}
			}

			for (int o = 0; o < obstcl::maxObstacles; o++)
			{
				for (int i = 0; i < playersInGame; i++)
				{
					if (obstcl::mngr::Collide(obstacles[o].obstacles, players[i])) 
						bll::Die(players[i]);
				}
			}

			btn::UpdateInput(pauseButton);
			if (pauseButton.signal || ctrl::IsKeyPressed(pauseKey)) {
				isPaused = true;
			}

			//mouseParticleActivator.pos = rend::mousePos;
			//prtcl::Update(mouseParticleActivator, mouseParticles);

			break;

		case GameState::CREDITS:

			btn::UpdateInput(backButton);
			if (backButton.signal) {
				currentState = GameState::MAIN_MENU;
			}
			break;
		}

		isActive = false;
		for (int i = 0; i < playersInGame; i++)
		{
			if (players[i].isAlive)
				isActive = true;
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

			drw::Sprite(drw::spriteDataList[backgroundFar.id], { 0.5f,0.5f }, { 2.0f,1.0f }, backgroundFar.offset);
			drw::Sprite(drw::spriteDataList[backgroundFar.id], { 0.5f,0.5f }, { 2.0f,1.0f }, farOffset2);
			drw::Sprite(drw::spriteDataList[backgroundMid.id], { 0.5f,0.5f }, { 2.0f,1.0f }, backgroundMid.offset);
			drw::Sprite(drw::spriteDataList[backgroundMid.id], { 0.5f,0.5f }, { 2.0f,1.0f }, midOffset2);
			drw::Sprite(drw::spriteDataList[backgroundNear.id], { 0.5f,0.5f }, { 2.0f,1.0f }, backgroundNear.offset);
			drw::Sprite(drw::spriteDataList[backgroundNear.id], { 0.5f,0.5f }, { 2.0f,1.0f }, nearOffset2);

			//prtcl::Draw(mouseParticles);

			obstcl::Draw(obstacles);

			for (int i = 0; i < playersInGame; i++)
				bll::Draw(players[i]);

			btn::Draw(pauseButton);

			//drw::Text(scoreTextData.text.c_str(),scoreTextData, { 0.5f, 0.5f }, scoreTextData.fontSize, { 0,0 }, WHITE_B);

			if (!isActive)
			{
				labelData.text = "SPACE to RESTART";
				drw::Text(labelData.text.c_str(), { 0.5f, 0.5f }, { 0.1f }, { 0,0 }, BLACK_B);
			}

			if (isPaused) {
				drw::Rectangle(vec::Vector4(0.0f, 0.0f, 1.0f, 1.0f), SEMITRANSPARENT_B);
				btn::Draw(retryButton);
				btn::Draw(returnButton);
				btn::Draw(exitPauseButton);

				scoreTextData.text = std::to_string(gameTimer);
			}
			else {
				scoreTextData.text = std::to_string(gameTimer);
			}

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
