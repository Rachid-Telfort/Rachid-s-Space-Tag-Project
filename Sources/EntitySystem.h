#ifndef ENTITYSYSTEM_H_INCLUDED
#define ENTITYSYSTEM_H_INCLUDED

#include<chrono>
#include<cmath>
#include<random>
#include<ratio>
#include<vector>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/ConvexShape.hpp>
#include<SFML/Graphics/Rect.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Window/Mouse.hpp>
#include<SFML/Window/VideoMode.hpp>
#include"GraphicsSystem.h"

namespace SpaceTag
{
    class EntitySystem
    {
        static bool tagged;

        static std::default_random_engine defaultRandomEngine;
        static std::random_device randomDevice;
        static std::uniform_int_distribution<unsigned char> uniformIntDistribution;
        static std::vector<sf::CircleShape> circleShapes;

        static std::chrono::duration<float, std::milli> duration;
        static std::chrono::time_point<std::chrono::steady_clock> endPoint;
        static std::chrono::time_point<std::chrono::steady_clock> startPoint;

        static sf::ConvexShape convexShape;

        static void SetCircleShape(sf::CircleShape&);
        static void SetCircleShapePosition(sf::CircleShape&, const unsigned char);
        static void SetConvexShape();

        static void UpdateCircleShapesOnFrame();
        static void UpdateCircleShapeWithinBounds(sf::CircleShape&);
        static void UpdateCollisionsOnFrame();
        static void UpdateConvexShapeWithinBounds();
        static void UpdateConvexShapeOnFrame();

        public:
            static void DrawEntities(sf::RenderTarget&);
            static bool GameOver();
            static void Reset();
            static void Start();
            static void UpdateOnFrame();
    };
}

#endif
