#include<cstddef>
#include"EntitySystem.h"
#include"GraphicsSystem.h"

int main()
{
    SpaceTag::EntitySystem::Start();

    try
    {
        SpaceTag::GraphicsSystem::Start();
    }

    catch(const std::out_of_range&)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
