#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace sf;

#define NUM_BRANCHES 6
enum class Side { LEFT, RIGHT, NONE };
Sprite spriteBranches[NUM_BRANCHES];
Side   branchPosition[NUM_BRANCHES];

void updateBranch(int);
int  main() {
#pragma region VM
    VideoMode    vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Fullscreen);
    View         view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);
#pragma endregion
#pragma region Variables
    const float maxElapsedTime    = 3.0f;
    float       barWidth          = 400.0f;
    float       barHeight         = 50.0f;
    float       elapsedTime       = maxElapsedTime;
    float       barWidthPerSecond = barWidth / elapsedTime;
    int         beeSpeed          = 1000;
    bool        beeActive         = false;
    int         cloud1Speed       = 1000;
    int         cloud2Speed       = 1000;
    int         cloud3Speed       = 1000;
    bool        cloud1Active      = false;
    int         cloud2Active      = false;
    int         cloud3Active      = false;
    bool        gamePaused        = true;
    bool        gameOver          = true;
    const int   Player_L          = 580;
    const int   Player_R          = 1200;
    const int   Axe_L             = 690;
    const int   Axe_R             = 1075;
    int         score             = 0;
    Side        playerSide        = Side::LEFT;
#pragma endregion

#pragma region Loading_Assets
    // For Background
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(0, 0);

    // For Tree
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810, 0);

    // For Bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);
    spriteBee.setPosition(0, 800);

    // For Clouds
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 150);
    spriteCloud3.setPosition(0, 300);

    String messageString = "Enter \'Space Bar\' to Start";
    Font   font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    Text messageText;
    messageText.setFont(font);
    messageText.setFillColor(Color::Cyan);
    messageText.setCharacterSize(70);
    messageText.setString(messageString);
    messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2);
    messageText.setPosition(1920 / 2, 1080 / 2);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setFillColor(Color::Red);
    scoreText.setCharacterSize(100);
    scoreText.setString("Score : 0");
    scoreText.setPosition(20, 20);

    Text pauseText;
    pauseText.setFont(font);
    pauseText.setFillColor(Color::Green);
    pauseText.setCharacterSize(80);
    pauseText.setString("Press 'P' to Pause/Unpause");
    pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
    pauseText.setPosition(1920 / 2, 1080 / 2);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setFillColor(Color::Green);
    gameOverText.setCharacterSize(80);
    gameOverText.setString("Game Over");
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
    gameOverText.setPosition(2000, 2000);

    RectangleShape timebar(Vector2f(barWidth, barHeight));
    timebar.setFillColor(Color::Red);
    timebar.setPosition(view.getSize().x / 2 - barWidth / 2, view.getSize().y - 75);

    // For Player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(Player_L, 720);

    // For Axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(3000, 830);

    // For Brach
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for (int i = 0; i < NUM_BRANCHES; i++) {
        spriteBranches[i].setTexture(textureBranch);
        spriteBranches[i].setOrigin(spriteBranches[i].getLocalBounds().width / 2, spriteBranches[i].getLocalBounds().height / 2);
    }
#pragma endregion

    Clock clock;
    Time  dt;
    while (window.isOpen()) {
        dt = clock.restart();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::Space && gameOver) {
                    // restarting our game
                    score       = 0;
                    elapsedTime = maxElapsedTime;
                    gameOver    = false;
                    gamePaused  = false;
                    gameOverText.setPosition(2000, 2000);
                    clock.restart();
                    for(int i=0;i<NUM_BRANCHES-1;i++){
                        updateBranch(time(0) + i);
                    }
                    branchPosition[5]=Side::NONE;
                }
                if (event.key.code == Keyboard::P && !gameOver) {
                    // pause or play our game
                    gamePaused = !gamePaused;
                    clock.restart();
                }
                if (event.key.code == Keyboard::Left && !gamePaused) {
                    score++;
                    playerSide = Side::LEFT;
                    elapsedTime += (2.0 / score) + 0.15f;
                    elapsedTime = (elapsedTime > maxElapsedTime) ? maxElapsedTime : elapsedTime;
                    spritePlayer.setPosition(Player_L, spritePlayer.getPosition().y);
                    spriteAxe.setPosition(Axe_L, spriteAxe.getPosition().y);
                    updateBranch(score);
                }
                if (event.key.code == Keyboard::Right && !gamePaused) {
                    score++;
                    playerSide = Side::RIGHT;
                    elapsedTime += (2.0 / score) + 0.15f;
                    elapsedTime = (elapsedTime > maxElapsedTime) ? maxElapsedTime : elapsedTime;
                    spritePlayer.setPosition(Player_R, spritePlayer.getPosition().y);
                    spriteAxe.setPosition(Axe_R, spriteAxe.getPosition().y);
                    updateBranch(score);
                }
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left) {
                    spriteAxe.setPosition(3000, spriteAxe.getPosition().y);
                }
            }
        }

        if (!gamePaused) {
            elapsedTime -= dt.asSeconds();
            timebar.setSize(Vector2f(elapsedTime * barWidthPerSecond, barHeight));

            if (elapsedTime < 0) {
                gameOver   = true;
                gamePaused = true;
                gameOverText.setString("Game Over");
                gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
                gameOverText.setPosition(1920 / 2, 1080 / 2 - 100);
            }
            scoreText.setString("Score = " + std::to_string(score));
#pragma region animation_bee_cloud
            if (!beeActive) { // For Bee movement
                srand(time(0));
                int height = rand() % 300 + 650;
                spriteBee.setPosition(2000, height);
                beeSpeed  = rand() % 450 + 150;
                beeActive = true;
            } else {
                spriteBee.setPosition(spriteBee.getPosition().x - beeSpeed * dt.asSeconds(), spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            if (!cloud1Active) { // For Cloud1 movement
                srand(time(0));
                int height = rand() % 150;
                spriteCloud1.setPosition(-100, height);
                cloud1Speed  = rand() % 200 + 50;
                cloud1Active = true;
                float scale  = (float)(rand() % 40 + 60) / 100;
                spriteCloud1.setScale(scale, scale);
            } else {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed * dt.asSeconds(), spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x > 2000)
                    cloud1Active = false;
            }
            if (!cloud2Active) { // For Cloud2 movement
                srand(time(0) + 30);
                int height = rand() % 150 + 150;
                spriteCloud2.setPosition(-100, height);
                cloud2Speed  = rand() % 200 + 50;
                cloud2Active = true;
                float scale  = (float)(rand() % 40 + 60) / 100;
                spriteCloud2.setScale(scale, scale);
            } else {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + cloud2Speed * dt.asSeconds(), spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x > 2000)
                    cloud2Active = false;
            }
            if (!cloud3Active) { // For Cloud3 movement
                srand(time(0) + 50);
                int height = rand() % 150 + 300;
                spriteCloud3.setPosition(-100, height);
                cloud3Speed  = rand() % 200 + 50;
                cloud3Active = true;
                float scale  = (float)(rand() % 40 + 60) / 100;
                spriteCloud3.setScale(scale, scale);
            } else {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed * dt.asSeconds(), spriteCloud3.getPosition().y);
                if (spriteCloud3.getPosition().x > 2000)
                    cloud3Active = false;
            }
#pragma endregion
            for (int i = 0; i < NUM_BRANCHES; i++) {
                int height = i * 150;
                if (branchPosition[i] == Side::LEFT) {
                    spriteBranches[i].setPosition(600, height);
                    spriteBranches[i].setRotation(180);
                } else if (branchPosition[i] == Side::RIGHT) {
                    spriteBranches[i].setPosition(1320, height);
                    spriteBranches[i].setRotation(0);
                } else {
                    spriteBranches[i].setPosition(3000, height);
                }
            }
            if(playerSide == branchPosition[5]){
                gameOver = true;
                gamePaused = true;
                gameOverText.setString("Squished");
                gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
                gameOverText.setPosition(1920 / 2, 1080 / 2 - 100);
            }
        }

        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(spriteBranches[i]);
        }
        window.draw(spriteBee);
        window.draw(timebar);
        if (gamePaused && !gameOver)
            window.draw(pauseText);
        if (gameOver)
            window.draw(messageText);
        window.draw(scoreText);
        window.draw(gameOverText);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.display();
    }

    return 0;
}

void updateBranch(int seed) {
    srand(seed);
    int r = rand() % 3;
    for (int i = NUM_BRANCHES - 1; i > 0; i--) {
        branchPosition[i] = branchPosition[i - 1];
    }
    branchPosition[0] = (Side)r;
}