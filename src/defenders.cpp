#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "globals.hpp"
#include "menu.hpp"
#include <iostream>

int main()
{
	InitWindow(Window::width, Window::height, "Galactic Defenders");
	InitAudioDevice(); // Initialize audio device
	SetTargetFPS(60);
	SetExitKey(0); // so esc key doesn't close the window but returns to menu
	// Color yellow = {243, 216, 63, 255};
	Font font = LoadFontEx("fonts/gamefont.ttf", 64, 0, 0);

	Menu menu(LoadTexture("../assets/background/background1.png"));
	Texture2D gameBackground = LoadTexture("../assets/background/background2.png");

	Music music = LoadMusicStream("../assets/sounds/background.ogg");
	PlayMusicStream(music); // Start playing the music

	Texture2D level1Image = LoadTexture("../assets/buttons/level1.png");
	Texture2D level2Image = LoadTexture("../assets/buttons/level2.png");
	Texture2D level3Image = LoadTexture("../assets/buttons/level3.png");
	Texture2D gameOverImage = LoadTexture("../assets/buttons/you_lose.png");

	Texture2D livesImage = LoadTexture("../assets/buttons/hp.png");

	Game *game = nullptr; // Declare a pointer to the Game object - shrine

	while (!WindowShouldClose())
	{
		BeginDrawing();

		switch (Window::current)
		{
		// menu active on start
		case Window::MENU:
			menu.Update();
			menu.Draw();
			UpdateMusicStream(music);

			// If we are switching from GAME to MENU, delete the game object
			if (game != nullptr)
			{
				delete game;
				game = nullptr;
				std::cout << "Game object deleted" << std::endl;
			}
			break;

		case Window::GAME:
			// If we are switching to GAME from MENU, create the game object
			if (game == nullptr)
			{
				game = new Game();
			}

			game->HandleInput();
			game->Update();

			ClearBackground(RAYWHITE);
			DrawTexture(gameBackground, 0, 0, WHITE);
			if (game->run)
			{
				DrawTexture(level1Image, 50 + 50, 50, WHITE);
			}
			else
			{
				DrawTexture(gameOverImage, 400, 50, WHITE);
			}
			for (int i = 0; i <= game->lives - 1; i++)
			{
				DrawTexture(livesImage, (i + 1) * 70 + 400, 50, WHITE);
			}

			game->Draw();

			// Check for return to MENU input
			if (IsKeyPressed(KEY_ESCAPE))
			{
				Window::current = Window::MENU; // Transition back to MENU state
				PlayMusicStream(music);			// Restart music when returning to menu
			}
			break;
		}

		EndDrawing();
	}

	// Cleanup
	UnloadMusicStream(music); // Unload music stream
	CloseAudioDevice();		  // Close audio device
	CloseWindow();			  // Close window

	// If the game object still exists, delete it
	if (game != nullptr)
	{
		delete game;
	}

	return 0;
}
