#pragma once

#include "globals.h"

#include "Shape3D.hpp"
// #include <QEntity>
// #include <Qt3DExtras>
// #include <Qt3DRender>

#include <memory>

namespace ART {
namespace Logic {

class Square : public Shape3D {

public:
  Square(std::string id, Qt3DCore::QEntity *parent);

private:
};
} // namespace Logic
} // namespace ART