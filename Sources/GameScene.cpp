#include"GameScene.h"

void SpaceTag::GameScene::DrawCircleShapes(sf::RenderTarget& renderTarget) const
{
    for(const sf::CircleShape& circleShape:circleShapes)
    {
        renderTarget.draw(circleShape);
    }
}

void SpaceTag::GameScene::DrawTexts(sf::RenderTarget& renderTarget) const
{
    for(std::size_t index(0u); index<texts.size(); ++index)
    {
        if(SpaceTag::EntitySystem::GameOver()&&index==1u)
        {
            continue;
        }

        renderTarget.draw(texts[index]);
    }
}

void SpaceTag::GameScene::SetCircleShapes()
{
    sf::FloatRect floatRect;

    for(sf::CircleShape& circleShape:circleShapes)
    {
        floatRect=circleShape.getLocalBounds();
        circleShape.setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
        circleShape.setPointCount(pointCountDistribution(defaultRandomEngine));
        circleShape.setPosition(xAxisPositionDistribution(defaultRandomEngine), yAxisPositionDistribution(defaultRandomEngine));
        circleShape.setRadius(radiusDistribution(defaultRandomEngine));
    }
}

void SpaceTag::GameScene::SetText(const std::size_t index)
{
    switch(index)
    {
        case 0u:
        {
            texts[index].setString("START MENU");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/8u);

            break;
        }

        case 1u:
        {
            texts[index].setString("RESUME GAME");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height*3u/8u);

            break;
        }

        case 2u:
        {
            texts[index].setString("RESTART GAME");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height*5u/8u);

            break;
        }

        case 3u:
        {
            texts[index].setString("QUIT GAME");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height*7u/8u);

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::GameScene::SetTexts()
{
    if(font.loadFromFile("Assets/Graphics/SpaceTagFont.ttf"))
    {
        for(std::size_t index(0u); index<texts.size(); ++index)
        {
            texts[index].setCharacterSize(sf::VideoMode::getDesktopMode().width/20u);
            texts[index].setFillColor(sf::Color(255u, 255u, 0u, 0u));
            texts[index].setFont(font);
            texts[index].setOutlineColor(sf::Color(255u, 0u, 0u, 0u));
            texts[index].setOutlineThickness(1.0f);
            SetText(index);
        }
    }
}

void SpaceTag::GameScene::UpdateCircleShapes()
{
    circleShapesEndPoint=std::chrono::steady_clock::now();
    circleShapesDuration=circleShapesEndPoint-circleShapesStartPoint;

    if(circleShapesDuration.count()>=100.0f)
    {
        SetCircleShapes();
        circleShapesStartPoint=std::chrono::steady_clock::now();
    }
}

void SpaceTag::GameScene::UpdatePressedIndex(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
    sf::Vector2f vector2f(SpaceTag::GraphicsSystem::MapCoordinates(mouseButtonEvent.x, mouseButtonEvent.y));

    for(std::size_t index(0u); index<texts.size(); ++index)
    {
        if(texts[index].getGlobalBounds().contains(vector2f))
        {
            if(SpaceTag::EntitySystem::GameOver()&&index==1u)
            {
                return;
            }

            pressedIndex=index;

            return;
        }
    }
}

void SpaceTag::GameScene::UpdateTextOnPressed(const unsigned char index)
{
    switch(index)
    {
        case 0u:
        {
            try
            {
                SpaceTag::GraphicsSystem::LoadScene("Start Scene");
            }

            catch(const std::out_of_range&)
            {
                throw;
            }

            break;
        }

        case 1u:
        {
            textsDisappearing=true;
            count=0u;
            pressedIndex=4u;

            break;
        }

        case 2u:
        {
            Reset();

            break;
        }

        case 3u:
        {
            SpaceTag::GraphicsSystem::Stop();

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::GameScene::UpdateTextsAppearOnFrame()
{
    textsEndPoint=std::chrono::steady_clock::now();
    textsDuration=textsEndPoint-textsStartPoint;

    if(textsDuration.count()>=2.0f)
    {
        alpha+=5u;

        for(sf::Text& text:texts)
        {
            text.setFillColor(sf::Color(255u, 255u, 0u, alpha));
            text.setOutlineColor(sf::Color(255u, 0u, 0u, alpha));
        }

        if(alpha==255u)
        {
            textsAppeared=true;
        }

        else
        {
            textsStartPoint=std::chrono::steady_clock::now();
        }
    }
}

void SpaceTag::GameScene::UpdateTextsDisappearOnFrame()
{
    textsEndPoint=std::chrono::steady_clock::now();
    textsDuration=textsEndPoint-textsStartPoint;

    if(textsDuration.count()>=2.0f)
    {
        alpha-=5u;

        for(sf::Text& text:texts)
        {
            text.setFillColor(sf::Color(255u, 255u, 0u, alpha));
            text.setOutlineColor(sf::Color(255u, 0u, 0u, alpha));
        }

        if(!alpha)
        {
            paused=false;
            textsAppeared=false;
            textsDisappearing=false;
            pressedIndex=4u;
        }

        else
        {
            textsStartPoint=std::chrono::steady_clock::now();
        }
    }
}

void SpaceTag::GameScene::UpdateTextsOnMouseButtonEvent(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
    switch(mouseButtonEvent.button)
    {
        case sf::Mouse::Left:
        {
            if(paused)
            {
                UpdatePressedIndex(mouseButtonEvent);
            }

            break;
        }

        case sf::Mouse::Right:
        {
            if(!paused)
            {
                paused=true;
            }

            else if(!textsDisappearing)
            {
                textsDisappearing=true;
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::GameScene::UpdateTextsOnPressed()
{
    textsEndPoint=std::chrono::steady_clock::now();
    textsDuration=textsEndPoint-textsStartPoint;

    if(textsDuration.count()>=20.0f)
    {
        texts[pressedIndex].setFillColor(sf::Color(colorDistribution(defaultRandomEngine), colorDistribution(defaultRandomEngine), colorDistribution(defaultRandomEngine)));
        texts[pressedIndex].setOutlineColor(sf::Color(colorDistribution(defaultRandomEngine), colorDistribution(defaultRandomEngine), colorDistribution(defaultRandomEngine)));

        if(count==20u)
        {
            texts[pressedIndex].setFillColor(sf::Color::Yellow);
            texts[pressedIndex].setOutlineColor(sf::Color::Red);

            try
            {
                UpdateTextOnPressed(pressedIndex);
            }

            catch(const std::out_of_range&)
            {
                throw;
            }
        }

        else
        {
            ++count;
            textsStartPoint=std::chrono::steady_clock::now();
        }
    }
}

SpaceTag::GameScene::GameScene():paused(false), textsAppeared(false), textsDisappearing(false), alpha('\0'), count('\0'), pressedIndex(4u), defaultRandomEngine(randomDevice()), colorDistribution(0u, 255u), pointCountDistribution(4u, 8u), radiusDistribution(1.0f, 10.0f), xAxisPositionDistribution(0.0f, sf::VideoMode::getDesktopMode().width), yAxisPositionDistribution(0.0f, sf::VideoMode::getDesktopMode().height)
{
    SetCircleShapes();
    SetTexts();
}

void SpaceTag::GameScene::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
    SpaceTag::EntitySystem::DrawEntities(renderTarget);
    DrawCircleShapes(renderTarget);

    if(paused)
    {
        DrawTexts(renderTarget);
    }
}

void SpaceTag::GameScene::Reset()
{
    paused=false;
    textsAppeared=false;
    textsDisappearing=false;
    alpha='\0';
    count='\0';
    pressedIndex=4u;

    circleShapesEndPoint=std::chrono::steady_clock::now();
    circleShapesStartPoint=circleShapesEndPoint;
    textsEndPoint=std::chrono::steady_clock::now();
    textsStartPoint=textsEndPoint;

    SpaceTag::EntitySystem::Reset();
}

void SpaceTag::GameScene::UpdateOnEvent(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::LostFocus:
        {
            paused=true;

            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            UpdateTextsOnMouseButtonEvent(event.mouseButton);

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::GameScene::UpdateOnFrame()
{
    if(!paused)
    {
        SpaceTag::EntitySystem::UpdateOnFrame();

        if(SpaceTag::EntitySystem::GameOver())
        {
            paused=true;
        }

        UpdateCircleShapes();
    }

    else if(paused&&!textsAppeared)
    {
        UpdateTextsAppearOnFrame();
    }

    else if(paused&&textsDisappearing)
    {
        UpdateTextsDisappearOnFrame();
    }

    else if(paused&&pressedIndex<4u)
    {
        try
        {
            UpdateTextsOnPressed();
        }

        catch(const std::out_of_range&)
        {
            throw;
        }
    }

    else if(paused&&SpaceTag::EntitySystem::GameOver())
    {
        UpdateCircleShapes();
    }
}
