#include"GraphicsSystem.h"

const std::unordered_map<std::string, std::shared_ptr<SpaceTag::Scene>> SpaceTag::GraphicsSystem::scenes
{
    {"Game Scene", std::make_shared<SpaceTag::GameScene>()},
    {"Start Scene", std::make_shared<SpaceTag::StartScene>()}
};

std::shared_ptr<SpaceTag::Scene> SpaceTag::GraphicsSystem::scene(scenes.at("Start Scene"));

sf::Event SpaceTag::GraphicsSystem::event;
sf::RenderWindow SpaceTag::GraphicsSystem::renderWindow;

void SpaceTag::GraphicsSystem::DrawScene()
{
    if(scene)
    {
        renderWindow.draw(*scene);
    }
}

void SpaceTag::GraphicsSystem::ProcessEvent(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::Closed:
        {
            renderWindow.close();

            break;
        }

        default:
        {
            UpdateSceneOnEvent(event);

            break;
        }
    }
}

void SpaceTag::GraphicsSystem::ResetScene()
{
    if(scene)
    {
        scene->Reset();
    }
}

void SpaceTag::GraphicsSystem::SetRenderWindow()
{
    renderWindow.create(sf::VideoMode::getDesktopMode(), "Space Tag");
    renderWindow.setVerticalSyncEnabled(true);
}

void SpaceTag::GraphicsSystem::ShowRenderWindow()
{
    while(renderWindow.isOpen())
    {
        while(renderWindow.pollEvent(event))
        {
            ProcessEvent(event);
        }

        try
        {
            UpdateSceneOnFrame();
        }

        catch(const std::out_of_range&)
        {
            throw;
        }

        renderWindow.clear();
        DrawScene();
        renderWindow.display();
    }
}

void SpaceTag::GraphicsSystem::UpdateSceneOnEvent(const sf::Event& event)
{
    if(scene)
    {
        scene->UpdateOnEvent(event);
    }
}

void SpaceTag::GraphicsSystem::UpdateSceneOnFrame()
{
    if(scene)
    {
        try
        {
            scene->UpdateOnFrame();
        }

        catch(const std::out_of_range&)
        {
            throw;
        }
    }
}

sf::Vector2f SpaceTag::GraphicsSystem::MapCoordinates(const int xAxisPosition, const int yAxisPosition)
{
    sf::Vector2i vector2i(xAxisPosition, yAxisPosition);
    return renderWindow.mapPixelToCoords(vector2i);
}

sf::Vector2f SpaceTag::GraphicsSystem::MapCoordinates(const sf::Vector2i& vector2i)
{
    return renderWindow.mapPixelToCoords(vector2i);
}

void SpaceTag::GraphicsSystem::LoadScene(const std::string& sceneName)
{
    ResetScene();

    try
    {
        scene=scenes.at(sceneName);
    }

    catch(const std::out_of_range&)
    {
        throw;
    }
}

void SpaceTag::GraphicsSystem::Start()
{
    SetRenderWindow();
    ShowRenderWindow();
}

void SpaceTag::GraphicsSystem::Stop()
{
    renderWindow.close();
}
