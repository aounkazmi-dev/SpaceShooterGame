
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

struct Bullet {
    RectangleShape bulletShape;
    bool active=false;

    void initialize(float x, float y) {
        bulletShape.setSize(Vector2f(5.1f, 10.1f));
        bulletShape.setFillColor(Color::Green);
        bulletShape.setPosition(x, y);
        active = true;
    }

    void move(float deltaTime) {
        if (active) {
            bulletShape.move(0.f, -500.f * deltaTime);
            if (bulletShape.getPosition().y < 0) {
                active = false;
            }
        }
    }
};


struct recEnemy {
    
    Sprite enemySprite;
    bool active=false;

    void initialize(float x, float y, Texture& texture) {
        enemySprite.setTexture(texture);
        enemySprite.setScale(0.3f, 0.3f);  
        enemySprite.setPosition(x, y);
        active = true;
    }

    void move(float deltaTime, float speed) {
        if (active) {
            enemySprite.move(0.f, speed * deltaTime);
            if (enemySprite.getPosition().y > 800.f) {
                active = false;
            }
        }
    }

    bool checkCollision(const Bullet& bullet) {
        return enemySprite.getGlobalBounds().intersects(bullet.bulletShape.getGlobalBounds());
    }
};

struct EnemyBullet {
    RectangleShape bulletShape;
    bool active=false;
    float speed=200.f;

    void initialize(float x, float y, float enemyBulletSpeed){
        bulletShape.setSize(Vector2f(5.1f, 10.1f));
        bulletShape.setFillColor(Color::Red);
        bulletShape.setPosition(x, y);
        active = true;
        speed = enemyBulletSpeed;
    }

    void move(float deltaTime) {
        if (active) {
            
             
            bulletShape.move(0.f, speed * deltaTime);  

           
            if (bulletShape.getPosition().y < 0 || bulletShape.getPosition().y > 800 || bulletShape.getPosition().x < 0 || bulletShape.getPosition().x > 1000) {
                active = false;
            }
        }
    }
};



struct CircleEnemy {

    Sprite enemySprite;
    bool active=false;

    void initialize(float x, float y, Texture& texture) {
        enemySprite.setTexture(texture);
        enemySprite.setScale(0.15f, 0.15f); 
        enemySprite.setPosition(x, y);
        active = true;
    }

    void move(float deltaTime, float speed) {
        if (active) {
            enemySprite.move(0.f, speed * deltaTime);
            if (enemySprite.getPosition().y > 800.f) {
                active = false;
            }
        }
    }

    bool checkCollision(const Bullet& bullet) {
        return enemySprite.getGlobalBounds().intersects(bullet.bulletShape.getGlobalBounds());
    }
};

RectangleShape safetyBarrier1;
RectangleShape safetyBarrier2;
int main() {
 

    bool flag = false;
    bool gameOverFlag = false;
    bool winFlag = false;
    int score = 0;
    int lives = 3;
    int level = 1;
    srand(time(0));
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("imagebackground.PNG")) {
        cout << "ERROR !!! Unable to load background image" << endl;
        return 1;
    }
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    Texture spaceshipTexture;
    if (!spaceshipTexture.loadFromFile("spaceship.PNG")) {
        cout << "ERROR: Unable to load spaceship image!" << endl;
        return 1;
    }
    Sprite userSpaceship;
    userSpaceship.setTexture(spaceshipTexture);
    userSpaceship.setScale(0.15f, 0.15f);
   

    Texture gameovertexture;
    if (!gameovertexture.loadFromFile("gameover.JPG")) {
        cout << "ERROR !!! Unable to load Game over  image" << endl;
        return 1;
    }
    Sprite gameoverSprite;
    gameoverSprite.setTexture(gameovertexture);

    Texture winTexture;
    if (!winTexture.loadFromFile("Winimage.JPG")) {
        cout << "ERROR !!! Unable to load winning image" << endl;
        return 1;
    }
    Sprite winSprite;
    winSprite.setTexture(winTexture);

    Texture enemyTexture, bossEnemyTexture;
    if (!enemyTexture.loadFromFile("Enemy.PNG")) {
        cout << "ERROR !!! Unable to load Enemy texture" << endl;
        return 1;
    }
    if (!bossEnemyTexture.loadFromFile("enemyboss.PNG")) {
        cout << "ERROR !!! Unable to load BossEnemy texture" << endl;
        return 1;
    }


    Font font1, font2;
    if (!font1.loadFromFile("astrospace.otf") || !font2.loadFromFile("arial.ttf")) {
        cout << "ERROR !!! Please download the required fonts" << endl;
        return 1;
    }

    Text mainTitle, instruction, instruct, scoreText, livesText, gameOverText, levelText, winText;

    mainTitle.setFont(font1);
    mainTitle.setString("Space Shooting Game");
    mainTitle.setCharacterSize(50);
    mainTitle.setFillColor(Color::White);
    mainTitle.setPosition(200.f, 300.f);

    instruction.setFont(font2);
    instruction.setString("Press ENTER to Start");
    instruction.setCharacterSize(30);
    instruction.setFillColor(Color::Yellow);
    instruction.setPosition(350.f, 400.f);

    instruct.setFont(font2);
    instruct.setString("Press Esc to exit the game");
    instruct.setCharacterSize(20);
    instruct.setFillColor(Color::Red);
    instruct.setPosition(2.f, 2.f);

    scoreText.setFont(font2);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: 0");
    scoreText.setPosition(3.f, 3.f);

    livesText.setFont(font2);
    livesText.setFillColor(Color::White);
    livesText.setString("Lives: 3");
    livesText.setPosition(880.f, 3.f);

    gameOverText.setFont(font2);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Game Over!  You Lost ");
    gameOverText.setCharacterSize(30);
    gameOverText.setPosition(350.f, 400.f);

    levelText.setFont(font2);
    levelText.setFillColor(Color::White);
    levelText.setCharacterSize(30);
    levelText.setPosition(450.f, 3.f);

    winText.setFont(font2);
    winText.setFillColor(Color::Green);
    winText.setString("Congratulations! You Won!");
    winText.setCharacterSize(40);
    winText.setPosition(300.f, 400.f);

    RenderWindow window(VideoMode(1000, 800), "Space Shooting Game");
  
        FloatRect backgroundRect = backgroundSprite.getLocalBounds();
    backgroundSprite.setScale(window.getSize().x / backgroundRect.width, window.getSize().y / backgroundRect.height);
    
    FloatRect gameoverRect = gameoverSprite.getLocalBounds();
    gameoverSprite.setScale(window.getSize().x / gameoverRect.width, window.getSize().y / gameoverRect.height);

    FloatRect gamewinRect = winSprite.getLocalBounds();
    winSprite.setScale(window.getSize().x / gamewinRect.width, window.getSize().y / gamewinRect.height);


    safetyBarrier1.setSize(Vector2f(150.f, 30.f));  
    safetyBarrier1.setFillColor(Color(0, 255, 255, 150)); 
    safetyBarrier1.setPosition(150.f, 670.f);  

    safetyBarrier2.setSize(Vector2f(150.f, 30.f));  
    safetyBarrier2.setFillColor(Color(0, 255, 255, 150));  
    safetyBarrier2.setPosition(700.f, 670.f);  


    Bullet bullets[10];
    Clock shooting_time;
    float cooldown = 0.532f;

    recEnemy Recenemies[12];
    CircleEnemy circleEnemies[6];
    Clock enemy_spawn_timer_rec, enemy_spawn_timer_circle;
    Clock cl_deltaTime;
    int frameCount = 0;
   
    EnemyBullet enemyBullets[20]; 
    Clock enemyShootingTime[18];  
    float enemyCooldown = 1.5f;    

        while (window.isOpen()) {

            float deltaTime = cl_deltaTime.restart().asSeconds();

            Event ev;

            while (window.pollEvent(ev)) {
                if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }

                if (!flag && ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter) {
                    flag = true;
                    score = 0;
                    lives = 3;
                    level = 1;
                    userSpaceship.setPosition(475.f, 720.f);

                    gameOverFlag = false;
                    winFlag = false;
                }

                if (flag && ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) {
                    window.close();
                }
            }

            window.clear();
            window.draw(backgroundSprite);


            if (!flag) {
                window.draw(mainTitle);
                window.draw(instruction);
                window.draw(instruct);
            }

            if (flag && !gameOverFlag && !winFlag) {
                float recEnemySpeed = 100.f + 20.f * (1.5*level - 1);
                float circleEnemySpeed = 80.f + 20.f * (1.5f*level - 1);

                if (Keyboard::isKeyPressed(Keyboard::Left) && userSpaceship.getPosition().x > 2.f) {
                    userSpaceship.move(-300.f * deltaTime, 0.f);
                }
                if (Keyboard::isKeyPressed(Keyboard::Right) && userSpaceship.getPosition().x < 940.f) {
                    userSpaceship.move(300.f * deltaTime, 0.f);
                }
                if (Keyboard::isKeyPressed(Keyboard::Up) && userSpaceship.getPosition().y > 10.f) {
                    userSpaceship.move(0.f, -300.f * deltaTime);
                }
                if (Keyboard::isKeyPressed(Keyboard::Down) && userSpaceship.getPosition().y < 720.f) {
                    userSpaceship.move(0.f, 300.f * deltaTime);
                }
                if (Keyboard::isKeyPressed(Keyboard::Space) && shooting_time.getElapsedTime().asSeconds() > cooldown) {
                    for (int i = 0; i < 10; i++) {
                        if (!bullets[i].active) {
               
                            bullets[i].initialize(
                                userSpaceship.getPosition().x + userSpaceship.getGlobalBounds().width / 2 - 2.5f,
                                userSpaceship.getPosition().y
                            );
                            shooting_time.restart();
                            break;
                        }
                    }
                }


                if (level == 1){
                    if (enemy_spawn_timer_rec.getElapsedTime().asSeconds() > 3.f ) {
                        for (int i = 0; i < 12; i++) {
                            if (!Recenemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f; 
                                Recenemies[i].initialize(randomX, 0.f, enemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_rec.restart();
                    }

                    if (enemy_spawn_timer_circle.getElapsedTime().asSeconds() > 4.f) {
                        for (int i = 0; i < 6; i++) {
                            if (!circleEnemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                circleEnemies[i].initialize(randomX, 0.f, bossEnemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_circle.restart();
                    }
                   
                }
                else if (level == 2) {
                    
                    if (enemy_spawn_timer_rec.getElapsedTime().asSeconds() > 2.5f) {
                        for (int i = 0; i < 12; i++) {
                            if (!Recenemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                Recenemies[i].initialize(randomX, 0.f, enemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_rec.restart();
                    }

                    if (enemy_spawn_timer_circle.getElapsedTime().asSeconds() > 3.f) {
                        for (int i = 0; i < 6; i++) {
                            if (!circleEnemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                circleEnemies[i].initialize(randomX, 0.f, bossEnemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_circle.restart();
                    }
                }
                else if (level == 3) {
                    if (enemy_spawn_timer_rec.getElapsedTime().asSeconds() > 2.1f) {
                        for (int i = 0; i < 12; i++) {
                            if (!Recenemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                Recenemies[i].initialize(randomX, 0.f, enemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_rec.restart();
                    }

                    if (enemy_spawn_timer_circle.getElapsedTime().asSeconds() > 1.8f) {
                        for (int i = 0; i < 6; i++) {
                            if (!circleEnemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                circleEnemies[i].initialize(randomX, 0.f, bossEnemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_circle.restart();
                    }
                }
                else if (level == 4) {
                    if (enemy_spawn_timer_rec.getElapsedTime().asSeconds() > 1.f) {
                        for (int i = 0; i < 12; i++) {
                            if (!Recenemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                Recenemies[i].initialize(randomX, 0.f, enemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_rec.restart();
                    }

                    if (enemy_spawn_timer_circle.getElapsedTime().asSeconds() > 1.3f) {
                        for (int i = 0; i < 6; i++) {
                            if (!circleEnemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                circleEnemies[i].initialize(randomX, 0.f, bossEnemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_circle.restart();
                    }

                }

                else if (level >= 5) {
                    if (enemy_spawn_timer_rec.getElapsedTime().asSeconds() > 0.5f) {
                        for (int i = 0; i < 12; i++) {
                            if (!Recenemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f; 
                                Recenemies[i].initialize(randomX, 0.f, enemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_rec.restart();
                    }

                    if (enemy_spawn_timer_circle.getElapsedTime().asSeconds() > 0.7f) {
                        for (int i = 0; i < 6; i++) {
                            if (!circleEnemies[i].active) {
                                float randomX;
                                randomX = (rand() % 900) / 1.0f;
                                circleEnemies[i].initialize(randomX, 0.f, bossEnemyTexture);
                                break;
                            }
                        }
                        enemy_spawn_timer_circle.restart();
                    }

                }

                for (int i = 0; i < 10; i++) {
                    if (bullets[i].active) {
                        bullets[i].move(deltaTime);

                        for (int j = 0; j < 12; j++) {
                            if (Recenemies[j].active && Recenemies[j].checkCollision(bullets[i])) {
                                Recenemies[j].active = false;
                                bullets[i].active = false;
                                score =score+ 10;
                            }
                        }

                        for (int j = 0; j < 6; j++) {
                            if (circleEnemies[j].active && circleEnemies[j].checkCollision(bullets[i])) {
                                circleEnemies[j].active = false;
                                bullets[i].active = false;
                                score =score+ 20;
                             
                            }
                        }

                        if (bullets[i].bulletShape.getGlobalBounds().intersects(safetyBarrier1.getGlobalBounds()) ||
                            bullets[i].bulletShape.getGlobalBounds().intersects(safetyBarrier2.getGlobalBounds())) {
                            bullets[i].active = false; 
                        }

                    }
                }


                for (int i = 0; i < 12; i++) {
                    if (Recenemies[i].active) {
                        Recenemies[i].move(deltaTime, recEnemySpeed);


                        if (Recenemies[i].enemySprite.getGlobalBounds().intersects(userSpaceship.getGlobalBounds())) {
                            Recenemies[i].active = false;
                            lives--;
                            userSpaceship.setPosition(475.f, 720.f);
                        }
                        if (Recenemies[i].enemySprite.getGlobalBounds().intersects(safetyBarrier1.getGlobalBounds()) ||
                            Recenemies[i].enemySprite.getGlobalBounds().intersects(safetyBarrier2.getGlobalBounds())) {
                            Recenemies[i].active = false;  
                        }


                    }
                }

                for (int i = 0; i < 12; i++) {
                    if (Recenemies[i].active && enemyShootingTime[i].getElapsedTime().asSeconds() > enemyCooldown) {
                        for (int j = 0; j < 20; j++) {
                            if (!enemyBullets[j].active) {
                               
                                float enemyBulletSpeed = 200.f + 20.f * (1.5*level - 1); 
                                enemyBullets[j].initialize(
                                    Recenemies[i].enemySprite.getPosition().x + Recenemies[i].enemySprite.getGlobalBounds().width / 2 - 2.5f,
                                    Recenemies[i].enemySprite.getPosition().y + Recenemies[i].enemySprite.getGlobalBounds().height,
                                    enemyBulletSpeed
                                );
                                enemyShootingTime[i].restart();
                                break;
                            }
                        }
                    }
                }


                for (int i = 0; i < 6; i++) {
                    if (circleEnemies[i].active && enemyShootingTime[i + 12].getElapsedTime().asSeconds() > enemyCooldown) {

                        for (int j = 0; j < 20; j++) {
                            if (!enemyBullets[j].active) {
                                
                                float enemyBulletSpeed = 200.f + 20.f * (level - 1); 
                                enemyBullets[j].initialize(
                                    circleEnemies[i].enemySprite.getPosition().x + circleEnemies[i].enemySprite.getGlobalBounds().width / 2 - 2.5f,
                                    circleEnemies[i].enemySprite.getPosition().y + circleEnemies[i].enemySprite.getGlobalBounds().height,
                                    enemyBulletSpeed
                                );
                                enemyShootingTime[i + 12].restart();
                                break;
                            }
                        }
                    }
                }
                int i = 0;

                while(i<20) {
                    if (enemyBullets[i].active) {
                        enemyBullets[i].move(deltaTime);  

                        if (enemyBullets[i].bulletShape.getGlobalBounds().intersects(userSpaceship.getGlobalBounds())) {
                            lives--;  
                            enemyBullets[i].active = false;
                        }

                        if (enemyBullets[i].bulletShape.getGlobalBounds().intersects(safetyBarrier1.getGlobalBounds()) ||
                            enemyBullets[i].bulletShape.getGlobalBounds().intersects(safetyBarrier2.getGlobalBounds())) {
                            enemyBullets[i].active = false; 
                        }
                    }
                    i++;
                }
                 i = 0;
                while(i<6) {
                    if (circleEnemies[i].active) {
                        circleEnemies[i].move(deltaTime, circleEnemySpeed);

                        if (circleEnemies[i].enemySprite.getGlobalBounds().intersects(userSpaceship.getGlobalBounds())) {
                            circleEnemies[i].active = false;
                            lives--;
                            userSpaceship.setPosition(475.f, 720.f);
                        }
                        if (circleEnemies[i].enemySprite.getGlobalBounds().intersects(safetyBarrier1.getGlobalBounds()) ||
                            circleEnemies[i].enemySprite.getGlobalBounds().intersects(safetyBarrier2.getGlobalBounds())) {
                            circleEnemies[i].active = false;  
                        }

                    }
                    i++;
                }

                if (score >= level * 100) {
                    level++;
                    score = 0;
                    lives = 3;
                    userSpaceship.setPosition(475.f, 720.f);

                    for (int i = 0; i < 12; i++) {
                        Recenemies[i].active = false;
                    }

                    for (int i = 0; i < 6; i++) {
                        circleEnemies[i].active = false;
                    }

                    for (int i = 0; i < 10; i++) {
                        bullets[i].active = false;
                    }

                    for (int i = 0; i < 20; i++) {  
                        enemyBullets[i].active = false;  
                    }

                    if (level > 5) {
                        winFlag = true;
                    }
                }

                if (lives <= 0) {
                    gameOverFlag = true;
                }

                window.draw(userSpaceship);
                window.draw(safetyBarrier1);  
                window.draw(safetyBarrier2);  

                for (int i = 0; i < 10; i++) {
                    if (bullets[i].active) {
                        window.draw(bullets[i].bulletShape);
                    }
                }
                for (int i = 0; i < 20; i++) {
                    if (enemyBullets[i].active) {
                        window.draw(enemyBullets[i].bulletShape); 
                    }
                }


                for (int i = 0; i < 12; i++) {
                    if (Recenemies[i].active) {
                        window.draw(Recenemies[i].enemySprite);
                    }
                }

                for (int i = 0; i < 6; i++) {
                    if (circleEnemies[i].active) {
                        window.draw(circleEnemies[i].enemySprite);
                    }
                }


                scoreText.setString("Score: " + to_string(score));
                livesText.setString("Lives: " + to_string(lives));
                levelText.setString("Level: " + to_string(level));

                window.draw(scoreText);
                window.draw(livesText);
                window.draw(levelText);
            }
            else if (gameOverFlag) {
                window.clear();
                window.draw(gameoverSprite);
               

                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
                
            }
            else if (winFlag) {
                window.clear();
                window.draw(winSprite);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    flag = true;
                    score = 0;
                    lives = 3;
                    level = 1;
                    userSpaceship.setPosition(475.f, 720.f);  

                    gameOverFlag = false;  
                    winFlag = false;       
          
                    for (int i = 0; i < 12; i++) {
                        Recenemies[i].active = false; 
                    }
                    for (int i = 0; i < 6; i++) {
                        circleEnemies[i].active = false;  
                    }
                    for (int i = 0; i < 10; i++) {
                        bullets[i].active = false;  
                    }

                    enemy_spawn_timer_rec.restart();
                    enemy_spawn_timer_circle.restart();
                }
            }

            window.display();
            frameCount++;
        }
    
    return 0;
}


