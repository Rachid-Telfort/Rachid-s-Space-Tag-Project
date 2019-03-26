#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include<array>
#include<chrono>
#include<ratio>
#include<stdexcept>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/ConvexShape.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Window/VideoMode.hpp>
#include"EntitySystem.h"
#include"GraphicsSystem.h"
#include"Scene.h"

namespace SpaceTag
{
    class GameScene:public Scene
    {
        bool paused;
        bool textsAppeared;
        bool textsDisappearing;
        unsigned char alpha;
        unsigned char count;
        unsigned char pressedIndex;

        std::array<sf::CircleShape, 100u> circleShapes;
        std::array<sf::Text, 4u> texts;
        std::default_random_engine defaultRandomEngine;
        std::random_device randomDevice;
        std::uniform_int_distribution<unsigned char> colorDistribution;
        std::uniform_int_distribution<unsigned char> pointCountDistribution;
        std::uniform_real_distribution<float> radiusDistribution;
        std::uniform_real_distribution<float> xAxisPositionDistribution;
        std::uniform_real_distribution<float> yAxisPositionDistribution;

        std::chrono::duration<float, std::milli> circleShapesDuration;
        std::chrono::duration<float, std::milli> textsDuration;
        std::chrono::time_point<std::chrono::steady_clock> circleShapesEndPoint;
        std::chrono::time_point<std::chrono::steady_clock> circleShapesStartPoint;
        std::chrono::time_point<std::chrono::steady_clock> textsEndPoint;
        std::chrono::time_point<std::chrono::steady_clock> textsStartPoint;

        sf::Font font;

        void DrawCircleShapes(sf::RenderTarget&) const;
        void DrawTexts(sf::RenderTarget&) const;

        void SetCircleShapes();
        void SetText(const std::size_t);
        void SetTexts();

        void UpdateCircleShapes();
        void UpdatePressedIndex(const sf::Event::MouseButtonEvent&);
        void UpdateTextOnPressed(const unsigned char);
        void UpdateTextsAppearOnFrame();
        void UpdateTextsDisappearOnFrame();
        void UpdateTextsOnMouseButtonEvent(const sf::Event::MouseButtonEvent&);
        void UpdateTextsOnPressed();

        public:
            GameScene();
            GameScene(const GameScene&)=delete;
            GameScene(GameScene&&)=delete;
            ~GameScene()=default;

            GameScene& operator=(const GameScene&)=delete;
            GameScene& operator=(GameScene&&)=delete;

            void draw(sf::RenderTarget&, sf::RenderStates) const;
            void Reset();
            void UpdateOnEvent(const sf::Event&);
            void UpdateOnFrame();
    };
}

#endif
