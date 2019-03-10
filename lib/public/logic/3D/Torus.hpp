#pragma once

#include "globals.h"

#include "Shape3D.hpp"
// #include <QEntity>
// #include <Qt3DExtras>
// #include <Qt3DRender>

#include <memory>

namespace ART {
namespace Logic {

class Torus : public Shape3D {

public:
  Torus(std::string id, Qt3DCore::QEntity *parent);

private:
};
} // namespace Logic
} // namespace ART