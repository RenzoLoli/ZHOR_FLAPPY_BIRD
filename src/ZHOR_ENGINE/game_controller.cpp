#include "ZHOR_ENGINE/game_controller.hpp"

#include "ZHOR_ENGINE/game_context.hpp"
#include "ZHOR_ENGINE/scene_tree.hpp"

#include "scenes/main_scene.hpp"

GameController::GameController(WindowSettings settings)
{
    this->window = new sf::RenderWindow();
    this->event = new sf::Event();
    this->deltaClock = new sf::Clock();
    this->sceneTree = new SceneTree();
    this->mainScene = new MainScene();

    windowHasCreated = false;
}
GameController::~GameController()
{
    delete this->window;
    delete this->sceneTree;
    delete this->event;
    delete this->mainScene;
}

bool GameController::createWindow(WindowSettings settings)
{
    this->window->create(
        sf::VideoMode(
            settings.windowSize.x,
            settings.windowSize.y),
        settings.title,
        settings.style,
        settings.contextSettings
    );

    sf::VideoMode windowVideoMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPos = {
        (windowVideoMode.width - settings.windowSize.x) * settings.windowPos.x,
        (windowVideoMode.height - settings.windowSize.x) * settings.windowPos.y
    };
    this->window->setPosition(windowPos);
    this->window->setFramerateLimit(settings.fps);

#ifdef MAIN_SCENE_HPP
    this->sceneTree->setMainScene(this->mainScene);
    this->mainScene->create(this);
    windowHasCreated = true;
#else 
    windowHasCreated = false;
#endif

    return windowHasCreated;

}

void GameController::run()
{
    
    if(!this->windowHasCreated){
        throw StringError("no se creo bien la ventana");
    }

    double dt = 0;

    this->sceneTree->init(this);

    while (this->window->isOpen())
    {
        while (this->window->pollEvent(*this->event))
        {
            this->sceneTree->event(this, dt);
        }

        this->sceneTree->update(this, dt);

        this->window->draw(*this->sceneTree);

        this->window->display();

        dt = deltaClock->restart().asSeconds();
        this->fps = 1.f / (dt);
    }
}