#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <iostream>
#include <vector>
#include <cstring>

#include <Math/glmath.hpp>

#include "Window/Inputs.hpp"
#include "Window/Window.hpp"
#include "Window/log.hpp"
#include "Window/Time.hpp"

#include "ResourceManagment/ResourceManager.hpp"
#include "ResourceManagment/SceneManager.hpp"

#include "Utility/Color.hpp"
#include "Utility/TextFormat.h"
#include "Utility/Random.hpp"

#include "Render/Draw2D.hpp"

#include <glad/glad.h>

namespace Engine
{
    void Initialize(int width, int height, const char *title);

    void terminate();

}

#endif