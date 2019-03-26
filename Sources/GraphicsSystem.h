#ifndef GRAPHICSSYSTEM_H_INCLUDED
#define GRAPHICSSYSTEM_H_INCLUDED

#include<memory>
#include<stdexcept>
#include<string>
#include<unordered_map>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/System/Vector2.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Window/VideoMode.hpp>
#include"GameScene.h"
#include"Scene.h"
#include"StartScene.h"

namespace SpaceTag
{
    class GraphicsSystem
    {
        const static std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
        static std::shared_ptr<Scene> scene;

        static sf::Event event;
        static sf::RenderWindow renderWindow;

        static void DrawScene();
        static void ProcessEvent(const sf::Event&);
        static void ResetScene();
        static void SetRenderWindow();
        static void ShowRenderWindow();
        static void UpdateSceneOnEvent(const sf::Event&);
        static void UpdateSceneOnFrame();

        public:
            static sf::Vector2f MapCoordinates(const int, const int);
            static sf::Vector2f MapCoordinates(const sf::Vector2i&);
            static void LoadScene(const std::string&);
            static void Start();
            static void Stop();
    };
}

#endif
