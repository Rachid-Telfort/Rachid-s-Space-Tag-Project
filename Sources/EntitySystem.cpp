#include"EntitySystem.h"

bool SpaceTag::EntitySystem::tagged(false);

std::default_random_engine SpaceTag::EntitySystem::defaultRandomEngine(randomDevice());
std::random_device SpaceTag::EntitySystem::randomDevice;
std::uniform_int_distribution<unsigned char> SpaceTag::EntitySystem::uniformIntDistribution(0u, 5u);
std::vector<sf::CircleShape> SpaceTag::EntitySystem::circleShapes(1u);

std::chrono::duration<float, std::milli> SpaceTag::EntitySystem::duration;
std::chrono::time_point<std::chrono::steady_clock> SpaceTag::EntitySystem::endPoint;
std::chrono::time_point<std::chrono::steady_clock> SpaceTag::EntitySystem::startPoint;

sf::ConvexShape SpaceTag::EntitySystem::convexShape(8u);

void SpaceTag::EntitySystem::SetCircleShape(sf::CircleShape& circleShape)
{
    circleShape.setFillColor(sf::Color::Red);
    circleShape.setRadius(5.0f);

    sf::FloatRect floatRect(circleShape.getLocalBounds());
    circleShape.setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);

    SetCircleShapePosition(circleShape, uniformIntDistribution(defaultRandomEngine));
}

void SpaceTag::EntitySystem::SetCircleShapePosition(sf::CircleShape& circleShape, const unsigned char index)
{
    switch(index)
    {
        case 0u:
        {
            circleShape.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/4u);

            break;
        }

        case 1u:
        {
            circleShape.setPosition(sf::VideoMode::getDesktopMode().width/8u, sf::VideoMode::getDesktopMode().height/2u);

            break;
        }

        case 2u:
        {
            circleShape.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/4u);

            break;
        }

        case 3u:
        {
            circleShape.setPosition(sf::VideoMode::getDesktopMode().width*7u/8u, sf::VideoMode::getDesktopMode().height/2u);

            break;
        }

        default:
        {
            circleShape.setPosition(sf::VideoMode::getDesktopMode().width/8u, sf::VideoMode::getDesktopMode().height/8u);

            break;
        }
    }
}

void SpaceTag::EntitySystem::SetConvexShape()
{
    sf::Vector2f vector2f;
    convexShape.setPoint(0u, vector2f);

    vector2f.x=-25.0f;
    vector2f.y=25.0f;
    convexShape.setPoint(1u, vector2f);

    vector2f.x=-6.25f;
    vector2f.y=12.5f;
    convexShape.setPoint(2u, vector2f);

    vector2f.x=-18.75f;
    vector2f.y=37.5f;
    convexShape.setPoint(3u, vector2f);

    vector2f.x=0.0f;
    vector2f.y=50.0f;
    convexShape.setPoint(4u, vector2f);

    vector2f.x=18.75f;
    vector2f.y=37.5f;
    convexShape.setPoint(5u, vector2f);

    vector2f.x=6.25f;
    vector2f.y=12.5f;
    convexShape.setPoint(6u, vector2f);

    vector2f.x=25.0f;
    vector2f.y=25.0f;
    convexShape.setPoint(7u, vector2f);

    convexShape.setFillColor(sf::Color::Blue);

    sf::FloatRect floatRect(convexShape.getLocalBounds());
    convexShape.setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
    convexShape.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/2u);
}

void SpaceTag::EntitySystem::UpdateCircleShapesOnFrame()
{
    for(sf::CircleShape& circleShape:circleShapes)
    {
        if(circleShape.getPosition().x<convexShape.getPosition().x)
        {
            circleShape.move(10.0f, 0.0f);
        }

        else if(circleShape.getPosition().x>convexShape.getPosition().x)
        {
            circleShape.move(-10.0f, 0.0f);
        }

        if(circleShape.getPosition().y<convexShape.getPosition().y)
        {
            circleShape.move(0.0f, 10.0f);
        }

        else if(circleShape.getPosition().y>convexShape.getPosition().y)
        {
            circleShape.move(0.0f, -10.0f);
        }

        UpdateCircleShapeWithinBounds(circleShape);
    }

    endPoint=std::chrono::steady_clock::now();
    duration=endPoint-startPoint;

    if(duration.count()>3000.0f&&circleShapes.size()<100u)
    {
        circleShapes.emplace_back(5.0f);
        SetCircleShape(circleShapes.back());
        startPoint=std::chrono::steady_clock::now();
    }
}

void SpaceTag::EntitySystem::UpdateCircleShapeWithinBounds(sf::CircleShape& circleShape)
{
    sf::FloatRect floatRect(circleShape.getGlobalBounds());

    if(circleShape.getPosition().x<floatRect.width)
    {
        circleShape.setPosition(floatRect.width, circleShape.getPosition().y);
    }

    if(circleShape.getPosition().x>sf::VideoMode::getDesktopMode().width-floatRect.width)
    {
        circleShape.setPosition(sf::VideoMode::getDesktopMode().width-floatRect.width, circleShape.getPosition().y);
    }

    if(circleShape.getPosition().y<floatRect.height)
    {
        circleShape.setPosition(circleShape.getPosition().x, floatRect.height);
    }

    if(circleShape.getPosition().y>sf::VideoMode::getDesktopMode().height-floatRect.height)
    {
        circleShape.setPosition(circleShape.getPosition().x, sf::VideoMode::getDesktopMode().height-floatRect.height);
    }
}

void SpaceTag::EntitySystem::UpdateCollisionsOnFrame()
{
    for(sf::CircleShape& circleShape:circleShapes)
    {
        if(circleShape.getGlobalBounds().intersects(convexShape.getGlobalBounds()))
        {
            tagged=true;

            return;
        }
    }
}

void SpaceTag::EntitySystem::UpdateConvexShapeWithinBounds()
{
    sf::FloatRect floatRect(convexShape.getGlobalBounds());

    if(convexShape.getPosition().x<floatRect.width)
    {
        convexShape.setPosition(floatRect.width, convexShape.getPosition().y);
    }

    if(convexShape.getPosition().x>sf::VideoMode::getDesktopMode().width-floatRect.width)
    {
        convexShape.setPosition(sf::VideoMode::getDesktopMode().width-floatRect.width, convexShape.getPosition().y);
    }

    if(convexShape.getPosition().y<floatRect.height)
    {
        convexShape.setPosition(convexShape.getPosition().x, floatRect.height);
    }

    if(convexShape.getPosition().y>sf::VideoMode::getDesktopMode().height-floatRect.height)
    {
        convexShape.setPosition(convexShape.getPosition().x, sf::VideoMode::getDesktopMode().height-floatRect.height);
    }
}

void SpaceTag::EntitySystem::UpdateConvexShapeOnFrame()
{
    sf::Vector2i vector2i(sf::Mouse::getPosition());
    sf::Vector2f convexVector2f(convexShape.getPosition());
    sf::Vector2f mouseVector2f(SpaceTag::GraphicsSystem::MapCoordinates(vector2i));

    if(convexVector2f!=mouseVector2f)
    {
        sf::Vector2f difference(mouseVector2f-convexVector2f);
        float angle(std::atan2(difference.y, difference.x)*180.0f/3.14f);
        convexShape.setRotation(angle+90.0f);
        convexShape.setPosition(mouseVector2f);
        UpdateConvexShapeWithinBounds();
    }
}

void SpaceTag::EntitySystem::DrawEntities(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(convexShape);

    for(const sf::CircleShape& circleShape:circleShapes)
    {
        renderTarget.draw(circleShape);
    }
}

bool SpaceTag::EntitySystem::GameOver()
{
    return tagged;
}

void SpaceTag::EntitySystem::Reset()
{
    tagged=false;

    circleShapes.resize(1u);
    SetCircleShape(circleShapes.front());

    endPoint=std::chrono::steady_clock::now();
    startPoint=endPoint;

    convexShape.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/2u);
}

void SpaceTag::EntitySystem::Start()
{
    SetCircleShape(circleShapes.front());
    SetConvexShape();
}

void SpaceTag::EntitySystem::UpdateOnFrame()
{
    UpdateCircleShapesOnFrame();
    UpdateCollisionsOnFrame();
    UpdateConvexShapeOnFrame();
}
