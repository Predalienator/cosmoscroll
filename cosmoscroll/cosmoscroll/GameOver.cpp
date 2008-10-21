#include "GameOver.hpp"
#include "MediaManager.hpp"


GameOver::GameOver(sf::RenderWindow& app) :
	Screen(app)
{
}



Screen::Choice GameOver::Run()
{
    const char* message = "Perdu !\nR : Rejour\nQ : Quitter";
    bool running = true;
    Screen::Choice choice = Screen::EXIT_APP;
    
    sf::Event event;
    sf::String string(message);
    string.SetColor(sf::Color::White);
    string.SetPosition(42, 42);
    string.SetFont(GET_FONT());
    
    while (running)
    {
        while (app_.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.Type == sf::Event::KeyPressed)
            {
                switch (event.Key.Code)
                {
                    case sf::Key::Escape:
                    case 'q':
                        running = false;
                        break;
                    case 'r':
                        running = false;
                        choice = Screen::GAME;
                        break;
                    default:
                        break;
                }
            }
        }
        app_.Draw(string);
        app_.Display();
    }
    return choice;
}

