#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Platform.h"
#include "Button.h"
#include "TextBoard.h"
#include <string>
#include "Coins.h"

static float screenHSize = 1000.0f;
static float screenVSize = 600.0f;

//redundant code;    was working on ability to resize game window, it had a lot of problems so had to drop it in order to finish work in this month
void ResizePOV(const sf::RenderWindow& gameWindow, sf::View& pov) {
	float aspectratio = float(gameWindow.getSize().x) / float(gameWindow.getSize().y);
	pov.setSize(screenHSize * aspectratio, screenVSize);
}

int main() {
	//game variables
	sf::RenderWindow gameWindow(sf::VideoMode(screenHSize, screenVSize), "Platformer", sf::Style::Close);
	sf::Event gameEvents;
	sf::Vector2i mousePosition;
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::View pov(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screenHSize, screenVSize));
	float gameMode = 0.0f;
	
	//Background related objects
	sf::RectangleShape Background;
	sf::Texture backgroundTextureMainMenu;
	backgroundTextureMainMenu.loadFromFile("Assets/Background/mainMenu.png");

	sf::Texture backgroundTextureGame;
	backgroundTextureGame.loadFromFile("Assets/Background/game.png");


	sf::RectangleShape HowToDescription;
	HowToDescription.setSize(sf::Vector2f(screenHSize - 100.0f, screenVSize - 200.0f));
	HowToDescription.setPosition(sf::Vector2f(50.0f, 50.0f));

	sf::Texture textureHowToDescription;
	textureHowToDescription.loadFromFile("Assets/Textboards/metal.png");
	HowToDescription.setTexture(&textureHowToDescription);

	//background music
	//main menu
	/*sf::SoundBuffer backgroundMusic;
	backgroundMusic.loadFromFile("Assets/Music/FloatinurboatxChrisLinton_HoldingOn.ogg");
	sf::Sound sound;
	sound.setBuffer(backgroundMusic);*/
	

	//initializing player
	Player player(10.0f, "Assets/Player/SpriteSheetPlayer.png", sf::Vector2u(5, 6), 0.2f, 150.0f, 200.0f);


	//initializing platforms
	Platform platforms[10];

	sf::Texture platformTexture;
	platformTexture.loadFromFile("Assets/Platforms/blue.png");
	sf::Texture finishTexture;
	finishTexture.loadFromFile("Assets/Platforms/finish.png");

	platforms[0] = Platform(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 210.0f));
	platforms[1] = Platform(&platformTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 550.0f));
	platforms[2] = Platform(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(1500.0f, 400.0f));	
	platforms[3] = Platform(&platformTexture, sf::Vector2f(100.0f, 350.0f), sf::Vector2f(2150.0f, 550.0f));
	platforms[4] = Platform(&platformTexture, sf::Vector2f(50.0f, 200.0f), sf::Vector2f(1850.0f, 550.0f));
	platforms[5] = Platform(&platformTexture, sf::Vector2f(50.0f, 200.0f), sf::Vector2f(2200.0f, 200.0f));
	platforms[6] = Platform(&platformTexture, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(1700.0f, 850.0f));
	platforms[7] = Platform(&platformTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(2700.0f, 650.0f));
	platforms[8] = Platform(&platformTexture, sf::Vector2f(300.0f, 200.0f), sf::Vector2f(3000.0f, 650.0f));
	platforms[9] = Platform(&platformTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(3500.0f, 600.0f));

	Platform finish(&finishTexture, sf::Vector2f(30.0f, 400.0f), sf::Vector2f(3500.0f, 200.0f));

	//initializing coins
	sf::Font font;
	font.loadFromFile("Assets/Font/pixel.ttf");
	sf::Image coinImage;
	coinImage.loadFromFile("Assets/Coins/SpriteSheetCoin.png");
	coinImage.createMaskFromColor(sf::Color(255, 174, 201));
	sf::Texture coinTexture;
	coinTexture.loadFromImage(coinImage);
	Coins coins[20];

	coins[0] = Coins(10.0f, 22, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[1] = Coins(500.0f, 20, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(-35.0f, 550.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[2] = Coins(1000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(-35.0f, 650.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[3] = Coins(50.0f, 22, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(400.0f, 40.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[4] = Coins(50.0f, 22, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(490.0f, 40.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[5] = Coins(50.0f, 22, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(615.0f, 40.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[6] = Coins(500.0f, 20, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1020.0f, 600.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[7] = Coins(500.0f, 20, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1275.0f, 450.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[8] = Coins(50.0f, 20, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(1375.0f, 230.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[9] = Coins(50.0f, 20, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(1505.0f, 230.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[10] = Coins(100.0f, 20, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1635.0f, 230.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[11] = Coins(500.0f, 20, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1695.0f, 680.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[12] = Coins(1000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1630.0f, 815.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[13] = Coins(1000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1770.0f, 815.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[14] = Coins(2000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1630.0f, 890.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[15] = Coins(2000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1770.0f, 890.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[16] = Coins(50.0f, 22, sf::Vector2f(12.0f, 15.0f), &font, sf::Vector2f(1855.0f, 380.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[17] = Coins(2000.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(1895.0f, 650.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[18] = Coins(2500.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(2198.0f, 30.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);
	coins[19] = Coins(2500.0f, 15, sf::Vector2f(15.0f, 15.0f), &font, sf::Vector2f(2560.0f, 200.0f), sf::Vector2f(50.0f, 50.0f), &coinTexture, sf::Vector2u(6, 1), 0.1f);


	//initializing buttons	
	//main menu
	Button buttonStart = Button ("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "Start", 20, sf::Vector2f(30.0f, 12.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(screenHSize / 2.0f, 350.0f), sf::Vector2u(10, 2), 0.1f);
	Button buttonHowTo = Button("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "HowToPlay", 20, sf::Vector2f(52.0f, 12.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(screenHSize / 2.0f, 450.0f), sf::Vector2u(10, 2), 0.1f);
	Button buttonExit = Button("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "Exit", 20, sf::Vector2f(25.0f, 12.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(screenHSize / 2.0f, 550.0f), sf::Vector2u(10, 2), 0.1f);
	
	//howto menu
	Button buttonReturn = Button("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "Return to menu", 18, sf::Vector2f(68.0f, 12.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(100.0f, 500.0f), sf::Vector2u(10, 2), 0.1f);

	//performance menu
	Button buttonReplay = Button("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "Replay", 20, sf::Vector2f(30.0f , 15.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(screenHSize / 4.0f, 500.0f), sf::Vector2u(10, 2), 0.1f);
	Button buttonReturnToMainMenu = Button("Assets/Button/SpriteSheetButton.png", "Assets/Font/pixel.ttf", "Return to menu", 18, sf::Vector2f(68.0f, 12.0f), sf::Vector2f(153.0f, 67.0f), sf::Vector2f(screenHSize / 4.0f  * 3.0f, 500.0f), sf::Vector2u(10, 2), 0.1f);

	
	//initializing textboards
	sf::Image textBoardInvisImage;
	textBoardInvisImage.loadFromFile("Assets/Textboards/transparent.png");
	textBoardInvisImage.createMaskFromColor(sf::Color(255, 174, 201));
	sf::Texture textBoardInvisTexture;
	textBoardInvisTexture.loadFromImage(textBoardInvisImage);

	std::string HowToText[5];
	HowToText[0] = "Use keys 'a' and 'd' to move left and right respectively.";
	HowToText[1] = "Use key 'space' to jump";
	HowToText[2] = "You can grab onto ledge and make jump even";
	HowToText[3] = "if there is no ground below you.";
	HowToText[4] = "Get to finish in order to win, good luck!";

	TextBoard textBoardHowTos[5];
	textBoardHowTos[0] = TextBoard(HowToText[0], 30, &font, &textBoardInvisTexture, sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 70.0f), sf::Vector2f(0.0f, 0.0f));
	textBoardHowTos[1] = TextBoard(HowToText[1], 30, &font, &textBoardInvisTexture, sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), sf::Vector2f(0.0f, 0.0f));
	textBoardHowTos[2] = TextBoard(HowToText[2], 30, &font, &textBoardInvisTexture, sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 130.0f), sf::Vector2f(0.0f, 0.0f));
	textBoardHowTos[3] = TextBoard(HowToText[3], 30, &font, &textBoardInvisTexture, sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 160.0f), sf::Vector2f(0.0f, 0.0f));
	textBoardHowTos[4] = TextBoard(HowToText[4], 30, &font, &textBoardInvisTexture, sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 190.0f), sf::Vector2f(0.0f, 0.0f));

	TextBoard textboardInformationGame("Lifes left : ", 40, "Assets/Font/pixel.ttf", "Assets/Textboards/transparent.png", sf::Color(255, 0, 0), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 20.0f), sf::Vector2f(0.0f, 0.0f));

	TextBoard textboardPerformance = TextBoard("You win!", 30, "Assets/Font/pixel.ttf", "Assets/Textboards/metal.png", sf::Color(255, 0, 0), sf::Vector2f(45.0f, 30.0f), sf::Vector2f((screenHSize - 200.0f) / 2.0f, 200.0f), sf::Vector2f(200.0f, 100.0f));

	while (gameWindow.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		
		//if framerate is less than 10fps
		if (deltaTime > 1.0f / 10.0f) {
			deltaTime = 1.0f / 10.0f;
		}

		//clearing all from old buffer
		gameWindow.clear();

		//variables that need to be constantly updated
		mousePosition = sf::Mouse::getPosition(gameWindow);

		while (gameWindow.pollEvent(gameEvents)) {
			switch (gameEvents.type) {
			case sf::Event::Closed:
				gameWindow.close();
				break;
			}			
		}

		//main menu
		if (gameMode == 0.0f) {
			//setting background and drawing it
			Background.setSize(sf::Vector2f(screenHSize, screenVSize));
			Background.setTexture(&backgroundTextureMainMenu);
			Background.setPosition(sf::Vector2f(0.0f, 0.0f));
			gameWindow.draw(Background);

			buttonStart.Update(deltaTime, mousePosition, gameMode, 2.0f);
			buttonHowTo.Update(deltaTime, mousePosition, gameMode, 1.0f);
			buttonExit.Update(deltaTime, mousePosition, gameMode, 4.0f);

			buttonStart.Draw(gameWindow);
			buttonHowTo.Draw(gameWindow);
			buttonExit.Draw(gameWindow);
		}


		//HowTo menu
		else if (gameMode == 1.0f) {
			buttonReturn.Update(deltaTime, mousePosition, gameMode, 0.0f);

			gameWindow.draw(Background);
			gameWindow.draw(HowToDescription);

			for (int i = 0; i < 5; i++) {
				textBoardHowTos[i].Draw(gameWindow);
			}
			buttonReturn.Draw(gameWindow);
			
		}


		//Game menu
		else if(gameMode == 2.0f){
			//setting background and drawing it
			Background.setSize(sf::Vector2f(4016.0f, 1156.0f));
			Background.setTexture(&backgroundTextureGame);
			Background.setPosition(sf::Vector2f(-500.0f, -200.0f));
			gameWindow.draw(Background);

			pov.setCenter(player.GetPosition());
			gameWindow.setView(pov);

			player.Update(deltaTime);

			//handling platform and physics related to them
			sf::Vector2f direction;
			player.AllowJump(false);
			for (int i = 0; i < 10; i++) {
				if (platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f)) {
					player.AllowJump(true);
					player.OnColliosion(direction);
				}
				platforms[i].Draw(gameWindow);
			}	

			//coin handling
			for (int i = 0; i < 20; i++) {
				if (coins[i].GetCollision().CheckCollision(player.GetCollision(), direction, 0.0f)) {
					player.SetScore(player.GetScore() + coins[i].GetScore());
					coins[i].Collected(true);
				}
				coins[i].Update(deltaTime);
				coins[i].Draw(gameWindow);
			}

			//handling if player fell too far down
			if (player.GetPosition().y > 1500.0f) {
				player.TakesDamage(7.0f);
				for (int i = 0; i < 20; i++) {
					coins[i].Collected(false);
				}
				player.SetScore(0.0f);
			}

			//handling finish line
			if (finish.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f)) {
				pov.setCenter(screenHSize / 2.0f, screenVSize / 2.0f);
				gameWindow.setView(pov);
				gameMode = 3.0f;
				textboardPerformance.SetText("You win!");
				player.SetScore(player.GetScore() + 1000.0f);
			}
			finish.Draw(gameWindow);

			player.Draw(gameWindow);

			//handling information board
			textboardInformationGame.SetText("Lifes Left : " + std::to_string(player.GetLife()) + "            Score: " + std::to_string((int)player.GetScore()));
			textboardInformationGame.SetPosition(-sf::Vector2f(player.GetPosition().x - 450.0f, player.GetPosition().y - 320.0f));
			textboardInformationGame.Draw(gameWindow);

			//if player dies
			if (player.GetLife() <= 0) {
				pov.setCenter(screenHSize / 2.0f, screenVSize / 2.0f);
				gameWindow.setView(pov);
				gameMode = 3.0f;
				textboardPerformance.SetText("You lost!");
			}
		}
		//performance screen
		else if (gameMode == 3.0f) {
			//handling stage after finishing it
			player.SetLife(4);
			player.SetPosition(sf::Vector2f(200.0f, 200.0f));
			player.SetScore(0.0f);
			for (int i = 0; i < 20; i++) {
				coins[i].Collected(false);
			}

			//setting background and drawing it
			Background.setSize(sf::Vector2f(screenHSize, screenVSize));
			Background.setTexture(&backgroundTextureMainMenu);
			Background.setPosition(sf::Vector2f(0.0f, 0.0f));
			gameWindow.draw(Background);

			buttonReplay.Update(deltaTime, mousePosition, gameMode, 2.0f);
			buttonReturnToMainMenu.Update(deltaTime, mousePosition, gameMode, 0.0f);

			textboardPerformance.Draw(gameWindow);
			buttonReplay.Draw(gameWindow);
			buttonReturnToMainMenu.Draw(gameWindow);
		}
		//exit
		else {
			gameWindow.close();
			break;
		}

		
		gameWindow.display();
	}
	return  0;
}
