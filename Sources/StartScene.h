#ifndef STARTSCENE_H_INCLUDED
#define STARTSCENE_H_INCLUDED

#include<array>
#include<chrono>
#include<cstddef>
#include<random>
#include<ratio>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/PrimitiveType.hpp>
#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Vertex.hpp>
#include<SFML/System/Vector2.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Window/VideoMode.hpp>
#include"GraphicsSystem.h"
#include"Scene.h"

namespace SpaceTag
{
    class StartScene:public Scene
    {
        bool textsAppeared;
        bool titleTextPositioned;
        unsigned char alpha;
        unsigned char count;
        unsigned char pressedIndex;

        std::array<sf::Text, 2u> texts;
        std::array<sf::Vertex, 1000u> vertices;
        std::default_random_engine defaultRandomEngine;
        std::random_device randomDevice;
        std::uniform_int_distribution<unsigned char> uniformIntDistribution;
        std::uniform_real_distribution<float> xAxisPositionDistribution;
        std::uniform_real_distribution<float> yAxisPositionDistribution;

        std::chrono::time_point<std::chrono::steady_clock> textsEndPoint;
        std::chrono::time_point<std::chrono::steady_clock> textsStartPoint;
        std::chrono::time_point<std::chrono::steady_clock> titleTextEndPoint;
        std::chrono::time_point<std::chrono::steady_clock> titleTextStartPoint;
        std::chrono::time_point<std::chrono::steady_clock> verticesEndPoint;
        std::chrono::time_point<std::chrono::steady_clock> verticesStartPoint;
        std::chrono::duration<float, std::milli> textsDuration;
        std::chrono::duration<float, std::milli> titleTextDuration;
        std::chrono::duration<float, std::milli> verticesDuration;

        sf::Font font;
        sf::Text titleText;

        void DrawTexts(sf::RenderTarget&) const;

        void SetText(const std::size_t);
        void SetTexts();
        void SetTitleText();
        void SetVertices();

        void UpdatePressedIndex(const sf::Event::MouseButtonEvent&);
        void UpdateTextOnPressed(const unsigned char);
        void UpdateTextsOnFrame();
        void UpdateTextsOnMouseButtonEvent(const sf::Event::MouseButtonEvent&);
        void UpdateTextsOnPressed();
        void UpdateTitleText();
        void UpdateVertices();

        public:
            StartScene();
            StartScene(const StartScene&)=delete;
            StartScene(StartScene&&)=delete;
            ~StartScene()=default;

            StartScene& operator=(const StartScene&)=delete;
            StartScene& operator=(StartScene&&)=delete;

            void draw(sf::RenderTarget&, sf::RenderStates) const;
            void Reset();
            void UpdateOnEvent(const sf::Event&);
            void UpdateOnFrame();
    };
}

#endif
