#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "Boid-Simulation");
    window.setFramerateLimit(144);
    sf::CircleShape boid(80.f, 3);
    boid.setFillColor(sf::Color(100, 250, 50));
    boid.setScale(0.5f, 0.5f);
    boid.setPosition(200.f, 200.f);

    sf::Clock clock;
    sf::Time lastDirChange{ sf::Time::Zero };
    const float UPDATE_INTERVAL = 0.50;

    int vx { 1 };
    int vy { 1 };

    while (window.isOpen())
    {
        sf::Time timeElapsed = clock.getElapsedTime();
        // std::cout << timeElapsed.asSeconds() << std::endl;

        if (timeElapsed.asSeconds() - lastDirChange.asSeconds() > 2.0) {
            // obtain a random number from hardware
            std::random_device rd; 
            // seed the generator
            std::mt19937 gen(rd()); 
            // define the range inclusivle
            std::uniform_int_distribution<> distr(-1, 1); 

            // random value between -1 and 1 as movement offset
            vx = distr(gen);
            vy = distr(gen);

            std::cout << vx << std::endl;
            std::cout << vy << std::endl;

            lastDirChange = timeElapsed;
        }

        boid.move(vx *  UPDATE_INTERVAL, vy *  UPDATE_INTERVAL);
        sf::Vector2f position = boid.getPosition();
        // std::cout << position.x << std::endl;
        // std::cout << position.y << std::endl;


        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(boid);
        window.display();
    }
}
