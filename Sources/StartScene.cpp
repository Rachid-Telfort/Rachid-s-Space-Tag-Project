#include"StartScene.h"

void SpaceTag::StartScene::DrawTexts(sf::RenderTarget& renderTarget) const
{
    for(const sf::Text& text:texts)
    {
        renderTarget.draw(text);
    }
}

void SpaceTag::StartScene::SetText(const std::size_t index)
{
    switch(index)
    {
        case 0u:
        {
            texts[index].setString("START GAME");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/2u);

            break;
        }

        case 1u:
        {
            texts[index].setString("QUIT GAME");
            sf::FloatRect floatRect(texts[index].getLocalBounds());
            texts[index].setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
            texts[index].setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height*3u/4u);

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::StartScene::SetTexts()
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

void SpaceTag::StartScene::SetTitleText()
{
    titleText.setCharacterSize(sf::VideoMode::getDesktopMode().width/10u);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setFont(font);
    titleText.setOutlineColor(sf::Color::Red);
    titleText.setOutlineThickness(1.0f);
    titleText.setString("SPACE TAG");

    sf::FloatRect floatRect(titleText.getLocalBounds());

    titleText.setOrigin(floatRect.left+floatRect.width/2.0f, floatRect.top+floatRect.height/2.0f);
    titleText.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height+floatRect.height/4.0f);
}

void SpaceTag::StartScene::SetVertices()
{
    for(sf::Vertex& vertex:vertices)
    {
        vertex.position.x=xAxisPositionDistribution(defaultRandomEngine);
        vertex.position.y=yAxisPositionDistribution(defaultRandomEngine);
    }
}

void SpaceTag::StartScene::UpdatePressedIndex(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
    sf::Vector2f vector2f(SpaceTag::GraphicsSystem::MapCoordinates(mouseButtonEvent.x, mouseButtonEvent.y));

    for(std::size_t index(0u); index<texts.size(); ++index)
    {
        if(texts[index].getGlobalBounds().contains(vector2f))
        {
            pressedIndex=index;

            break;
        }
    }
}

void SpaceTag::StartScene::UpdateTextOnPressed(const unsigned char index)
{
    switch(index)
    {
        case 0u:
        {
            try
            {
                SpaceTag::GraphicsSystem::LoadScene("Game Scene");
            }

            catch(const std::out_of_range&)
            {
                throw;
            }

            break;
        }

        case 1u:
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

void SpaceTag::StartScene::UpdateTextsOnFrame()
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

void SpaceTag::StartScene::UpdateTextsOnMouseButtonEvent(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
    switch(mouseButtonEvent.button)
    {
        case sf::Mouse::Left:
        {
            if(textsAppeared)
            {
                UpdatePressedIndex(mouseButtonEvent);
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void SpaceTag::StartScene::UpdateTextsOnPressed()
{
    textsEndPoint=std::chrono::steady_clock::now();
    textsDuration=textsEndPoint-textsStartPoint;

    if(textsDuration.count()>=20.0f)
    {
        texts[pressedIndex].setFillColor(sf::Color(uniformIntDistribution(defaultRandomEngine), uniformIntDistribution(defaultRandomEngine), uniformIntDistribution(defaultRandomEngine)));
        texts[pressedIndex].setOutlineColor(sf::Color(uniformIntDistribution(defaultRandomEngine), uniformIntDistribution(defaultRandomEngine), uniformIntDistribution(defaultRandomEngine)));

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

void SpaceTag::StartScene::UpdateTitleText()
{
    titleTextEndPoint=std::chrono::steady_clock::now();
    titleTextDuration=titleTextEndPoint-titleTextStartPoint;

    if(titleTextDuration.count()>=20.0f)
    {
        titleText.move(0.0f, -10.0f);

        if(titleText.getPosition().y<=sf::VideoMode::getDesktopMode().height/4u)
        {
            titleTextPositioned=true;
            titleText.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height/4.0f);
        }

        else
        {
            titleTextStartPoint=std::chrono::steady_clock::now();
        }
    }
}

void SpaceTag::StartScene::UpdateVertices()
{
    verticesEndPoint=std::chrono::steady_clock::now();
    verticesDuration=verticesEndPoint-verticesStartPoint;

    if(verticesDuration.count()>=50.0f)
    {
        SetVertices();
        verticesStartPoint=std::chrono::steady_clock::now();
    }
}

SpaceTag::StartScene::StartScene():textsAppeared(false), titleTextPositioned(false), alpha('\0'), count('\0'), pressedIndex(2u), defaultRandomEngine(randomDevice()), uniformIntDistribution(0u, 255u), xAxisPositionDistribution(0.0f, sf::VideoMode::getDesktopMode().width), yAxisPositionDistribution(0.0f, sf::VideoMode::getDesktopMode().height)
{
    if(font.loadFromFile("Assets/Graphics/SpaceTagFont.ttf"))
    {
        SetTexts();
        SetTitleText();
    }

    SetVertices();
}

void SpaceTag::StartScene::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
    renderTarget.draw(vertices.data(), vertices.size(), sf::Points);
    DrawTexts(renderTarget);
    renderTarget.draw(titleText);
}

void SpaceTag::StartScene::Reset()
{
    textsAppeared=false;
    titleTextPositioned=false;
    alpha='\0';
    count='\0';
    pressedIndex=2u;

    textsEndPoint=std::chrono::steady_clock::now();
    textsStartPoint=textsEndPoint;
    titleTextEndPoint=std::chrono::steady_clock::now();
    titleTextStartPoint=titleTextEndPoint;
    verticesEndPoint=std::chrono::steady_clock::now();
    verticesStartPoint=verticesEndPoint;

    for(sf::Text& text:texts)
    {
        text.setFillColor(sf::Color(255u, 255u, 0u, 0u));
        text.setOutlineColor(sf::Color(255u, 0u, 0u, 0u));
    }

    sf::FloatRect floatRect(titleText.getLocalBounds());
    titleText.setPosition(sf::VideoMode::getDesktopMode().width/2u, sf::VideoMode::getDesktopMode().height+floatRect.height/4.0f);
}

void SpaceTag::StartScene::UpdateOnEvent(const sf::Event& event)
{
    switch(event.type)
    {
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

void SpaceTag::StartScene::UpdateOnFrame()
{
    UpdateVertices();

    if(!titleTextPositioned)
    {
        UpdateTitleText();
    }

    else if(!textsAppeared)
    {
        UpdateTextsOnFrame();
    }

    if(pressedIndex<2u)
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
}
