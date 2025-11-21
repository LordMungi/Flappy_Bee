#include "Game.h"

#include "Ball.h"
#include "ObstacleManager.h"
#include "Obstacle.h"

#include "Templates.h"
#include "Config.h"

namespace game
{
	GameState nextState;

	btn::Button pauseButton;
	drw::TextData scoreTextData;
	drw::TextData labelData;

	btn::Button retryButton;
	btn::Button returnButton;
	btn::Button exitPauseButton;

	drw::SpriteData backgroundFar;
	drw::SpriteData backgroundMid;
	drw::SpriteData backgroundNear;
	vec::Vector2 farOffset2;
	vec::Vector2 midOffset2;
	vec::Vector2 nearOffset2;
	const float farSpeed = 0.2f;
	const float midSpeed = 0.4f;
	const float nearSpeed = 0.6f;
	
	const int maxPlayers = 2;
	bll::Ball players[maxPlayers] = {};

	obstcl::FullObstacle obstacles[obstcl::maxObstacles];

	bool isPaused = false;
	bool isActive = true;
	bool isStarted = false;

	snd::AudioData bgm;
	snd::AudioData hitWall;
	snd::AudioData point;

	ctrl::Key pauseKey = ctrl::Key::ESCAPE;
	ctrl::Key startKey = ctrl::Key::SPACE;

	void init()
	{
		bgm.file = "res/audio/bgm1.mp3";
		bgm.id = snd::InitAudioData(bgm);

		hitWall.file = "res/audio/hitwall.wav";
		hitWall.id = snd::InitAudioData(hitWall);

		point.file = "res/audio/point.wav";
		point.id = snd::InitAudioData(point);

		vec::Vector2 backgroundSize = { 3.5f, 1 };

		backgroundFar.file = "res/sprites/parallax/back.png";
		backgroundFar.size = { 1.5f,1.0f };
		backgroundFar.offset = { 0.0f,0.0f };
		farOffset2 = { backgroundFar.size.x, 0.0f };

		backgroundFar.id = drw::InitSpriteData(backgroundFar);

		backgroundMid.file = "res/sprites/parallax/mid.png";
		backgroundMid.size = { 1.5f,1.0f };
		backgroundMid.offset = { 0.0f,0.0f };
		midOffset2 = { backgroundMid.size.x, 0.0f };

		backgroundMid.id = drw::InitSpriteData(backgroundMid);

		backgroundNear.file = "res/sprites/parallax/front.png";
		backgroundNear.size = { 1.5f,1.0f };
		backgroundNear.offset = { 0.0f,0.0f };
		nearOffset2 = { backgroundNear.size.x, 0.0f };

		backgroundNear.id = drw::InitSpriteData(backgroundNear);

		for (int i = 0; i < maxPlayers; i++)
			bll::Init(players[i], i + 1);

		obstcl::Init(obstacles);

		scoreTextData.fontSize = 0.1f;

		pauseButton = templates::button;
		pauseButton.pos = { 0.5f, 0.9f };
		pauseButton.textData.text = "Pause";
		btn::Init(pauseButton);

		retryButton = templates::button;
		retryButton.pos = { 0.5f, 0.7f };
		retryButton.textData.text = "Retry";
		btn::Init(retryButton);

		returnButton = templates::button;
		returnButton.pos = { 0.5f, 0.6f };
		returnButton.textData.text = "Return";
		btn::Init(returnButton);

		exitPauseButton = templates::button;
		exitPauseButton.pos = { 0.5f, 0.5f };
		exitPauseButton.textData.text = "Exit";
		btn::Init(exitPauseButton);

		nextState = GameState::GAMEPLAY;

		isPaused = false;
		isStarted = false;

		snd::Play(bgm.id);
	}

	GameState update()
	{
		if (isPaused) {

			btn::UpdateInput(retryButton);
			btn::UpdateInput(returnButton);
			btn::UpdateInput(exitPauseButton);

			if (retryButton.signal) {
				isPaused = false;
				for (int i = 0; i < config::playersInGame; i++)
					bll::Reset(players[i]);

				obstcl::Reset(obstacles);
			}

			if (returnButton.signal || ctrl::IsKeyPressed(pauseKey)) {
				isPaused = false;
			}

			if (exitPauseButton.signal) {
				nextState = GameState::MAIN_MENU;
			}
		}
		else if (isActive && isStarted)
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

			for (int i = 0; i < config::playersInGame; i++)
			{
				bll::UpdateInput(players[i]);
				bll::Update(players[i]);
				if (!players[i].isAlive)
					players[i].pos += obstacles[0].vel * rend::deltaTime;
			}

			obstcl::Update(obstacles);

			for (int i = 0; i < config::playersInGame; i++)
			{
				if (!players[i].hasScored && obstacles[0].pos.x <= players[i].pos.x)
				{
					players[i].hasScored = true;
					players[i].score++;
					snd::Play(point.id);
				}
				else if (obstacles[0].pos.x > players[i].pos.x)
				{
					players[i].hasScored = false;
				}
			}
		}
		else
		{
			if (ctrl::IsKeyPressed(startKey))
			{
				isStarted = true;
				for (int i = 0; i < config::playersInGame; i++)
					bll::Reset(players[i]);
				obstcl::Reset(obstacles);
			}
		}

		for (int o = 0; o < obstcl::maxObstacles; o++)
		{
			for (int i = 0; i < config::playersInGame; i++)
			{
				if (obstcl::mngr::Collide(obstacles[o].obstacles, players[i]))
				{
					bll::Die(players[i]);
					snd::Play(hitWall.id);
				}
			}
		}

		btn::UpdateInput(pauseButton);
		if (pauseButton.signal || ctrl::IsKeyPressed(pauseKey)) {
			isPaused = true;
		}

		isActive = false;
		for (int i = 0; i < config::playersInGame; i++)
		{
			if (players[i].isAlive)
				isActive = true;
		}
		btn::Sound(retryButton);
		btn::Sound(returnButton);
		btn::Sound(exitPauseButton);
		btn::Sound(pauseButton);


		if (nextState != GameState::GAMEPLAY)
			snd::Stop(bgm.id);

		return nextState;
	}

	void draw()
	{
		drw::Sprite(drw::spriteDataList[backgroundFar.id], { 0.5f,0.5f }, backgroundFar.size, backgroundFar.offset);
		drw::Sprite(drw::spriteDataList[backgroundFar.id], { 0.5f,0.5f }, backgroundFar.size, farOffset2);
		drw::Sprite(drw::spriteDataList[backgroundMid.id], { 0.5f,0.5f }, backgroundMid.size, backgroundMid.offset);
		drw::Sprite(drw::spriteDataList[backgroundMid.id], { 0.5f,0.5f }, backgroundMid.size, midOffset2);
		drw::Sprite(drw::spriteDataList[backgroundNear.id], { 0.5f,0.5f }, backgroundNear.size, backgroundNear.offset);
		drw::Sprite(drw::spriteDataList[backgroundNear.id], { 0.5f,0.5f }, backgroundNear.size, nearOffset2);

		obstcl::Draw(obstacles);

		for (int i = 0; i < config::playersInGame; i++)
			bll::Draw(players[i]);

		btn::Draw(pauseButton);

		if (!isActive)
		{
			labelData.text = "SPACE to RESTART";
			drw::Text(labelData.text.c_str(), { 0.5f, 0.5f }, { 0.1f }, { 0,0 }, BLACK_B);
		}
		if (!isStarted)
		{
			labelData.text = "SPACE to START";
			drw::Text(labelData.text.c_str(), { 0.5f, 0.15f }, { 0.1f }, { 0,0 }, BLACK_B);
			labelData.text = "Jump to avoid the obstacles!";
			drw::Text(labelData.text.c_str(), { 0.5f, 0.08f }, { 0.05f }, { 0,0 }, BLACK_B);

			labelData.text = "P1";
			drw::Text(labelData.text.c_str(), { 0.1f, 0.6f }, { 0.05f }, { 0,0 }, BLACK_B);
			labelData.text = "W";
			drw::Text(labelData.text.c_str(), { 0.1f, 0.4f }, { 0.05f }, { 0,0 }, BLACK_B);
			labelData.text = "LMB";
			drw::Text(labelData.text.c_str(), { 0.1f, 0.35f }, { 0.05f }, { 0,0 }, BLACK_B);

			if (config::playersInGame > 1)
			{
				labelData.text = "P2";
				drw::Text(labelData.text.c_str(), { 0.2f, 0.6f }, { 0.05f }, { 0,0 }, BLACK_B);
				labelData.text = "UP";
				drw::Text(labelData.text.c_str(), { 0.2f, 0.4f }, { 0.05f }, { 0,0 }, BLACK_B);
				labelData.text = "RMB";
				drw::Text(labelData.text.c_str(), { 0.2f, 0.35f }, { 0.05f }, { 0,0 }, BLACK_B);
			}

		}

		labelData.text = std::to_string(players[0].score);
		drw::Text(labelData.text.c_str(), { 0.1f, 0.9f }, { 0.1f }, { 0,0 }, BLACK_B);
		if (config::playersInGame > 1)
		{
			labelData.text = std::to_string(players[1].score);
			drw::Text(labelData.text.c_str(), { 0.9f, 0.9f }, { 0.1f }, { 0,0 }, BLACK_B);
		}


		if (isPaused) {
			drw::Rectangle(vec::Vector4(0.0f, 0.0f, 1.0f, 1.0f), SEMITRANSPARENT_B);
			btn::Draw(retryButton);
			btn::Draw(returnButton);
			btn::Draw(exitPauseButton);
		}
	}
}