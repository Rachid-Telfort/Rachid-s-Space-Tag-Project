#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Window/Event.hpp>

namespace SpaceTag
{
    struct Scene:sf::Drawable
    {
        Scene()=default;
        Scene(const Scene&)=delete;
        Scene(Scene&&)=delete;
        virtual ~Scene()=default;

        Scene& operator=(const Scene&)& = delete;
        Scene& operator=(Scene&&)& = delete;

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const=0;
        virtual void Reset()=0;
        virtual void UpdateOnEvent(const sf::Event&)=0;
        virtual void UpdateOnFrame()=0;
    };
}

#endif
