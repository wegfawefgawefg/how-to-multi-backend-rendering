#pragma once

#include <memory>
#include <string>

#include "renderer/IRenderer.hpp"

namespace demo {

std::unique_ptr<IRenderer> createRenderer(const std::string& backend_name);

} // namespace demo
