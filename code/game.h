#pragma once
#include "alien.h"
#include "mysteryship.h"
#include "obstacle.h"
#include "spaceship.h"

class Game
{
public:

    Game();
    void Draw() const;
    void Update(double deltaTime);
    void HandleInput(double deltaTime);
    void UnloadTextures() const;
    bool isRunning{};
    int lives{};
    int score{};
    int highScore{};
    Music music{};

private:

    void DeleteInactiveLasers();
    static std::vector<Obstacle> CreateObstacles();
    static std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollisions();
    void GameOver();
    void Reset();
    void InitGame();
    void CheckForHighscore();
    static void SaveHighscoreToFile(int highscore);
    static int LoadHighscoreFromFile();

    Spaceship spaceship{};
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection{};
    std::vector<Laser> alienLasers;
    float alienLaserShootInterval = 0.35f;
    double timeLastAlienFired{};
    MysteryShip mystery_ship{};
    float mysteryShipSpawnInterval{};
    double timeLastSpawnMysteryShip{};
    Sound explosionSound{};
};
