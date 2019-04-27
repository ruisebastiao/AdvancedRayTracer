#include "MetalRoughMaterial.hpp"

namespace ART {
namespace Logic {
namespace Modules {

MetalRoughMaterial::MetalRoughMaterial(Shape3D &parent, std::string id, Qt3DExtras::QMetalRoughMaterial *material)
    : Material<Qt3DExtras::QMetalRoughMaterial>{parent, id, material} {
  material->setBaseColor(QColor(125, 125, 125));
  material->setRoughness(0.10);
  material->setMetalness(0.95);
}
MetalRoughMaterial::~MetalRoughMaterial() {}

} // namespace Modules
} // namespace Logic
} // namespace ART