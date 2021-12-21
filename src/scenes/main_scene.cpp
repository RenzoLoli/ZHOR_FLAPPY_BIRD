#include "scenes/main_scene.hpp"

#include "ZHOR_ENGINE/game_context.hpp"

sf::View cam;
float _zoom = 1;

MainScene::MainScene() : Scene("root")
{
}

MainScene::~MainScene()
{
    delete bird;
    delete pipes;
}

void MainScene::create(GameContext *context){
    bird = new BirdScene({100,50});
    this->addChild(bird);

    pipes = new PipesScene();
    this->addChild(pipes);

    sf::Vector2f center = {
        context->window->getSize().x *0.5,
        context->window->getSize().y *0.5
    };
    cam.setCenter(center);
    cam.setSize((sf::Vector2f)context->window->getSize());
    cam.zoom(_zoom);

    if(!font.loadFromFile("./font/Consolas.ttf")){
        std::cout << "error al abrir el archivo fuente" << "\n";
    }

    pointsText.setFont(font);
    pointsText.setStyle(sf::Text::Style::Bold);
    pointsText.setPosition({20,10});
    pointsText.setString(std::to_string(this->bird->getPoints()));
    pointsText.setCharacterSize(32);
}

void MainScene::init(GameContext *context)
{
}

void MainScene::update(GameContext *context, double &dt)
{
    pointsText.setString(std::to_string(this->bird->getPoints()));
}
void MainScene::event(GameContext *context, double &dt)
{
    sf::Event *e = context->event;
    if (e->type == sf::Event::Closed)
    {
        context->window->close();
    }

    if(e->type == sf::Event::KeyPressed){
        if(e->key.code == sf::Keyboard::R){
            reloadScene(context);
        }
    }
}
void MainScene::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(cam);
    target.clear();
    target.draw(*pipes);
    target.draw(*bird);

    target.draw(pointsText);
}

void MainScene::free()
{
}