import AdvancedRayTracer 1.0

import Qt3D.Render 2.12
import Qt3D.Extras 2.12
import Qt3D.Core 2.12
import QtQuick.Scene3D 2.12
import Qt3D.Render 2.12
import Qt3D.Input 2.12

Scene3D {
  id: scene3d
  focus: true
  aspects: ["input", "logic"]
  cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
  
  CustomScene3D {
    id: sceneRoot
    objectName: "customScene3D"

    components: [
      RenderSettings {
        activeFrameGraph: ForwardRenderer {
        clearColor: Qt.rgba(0, 0, 0, 0)
        camera: mainCamera
        }
      },
      InputSettings { }
    ]

    Camera {
      id: mainCamera
      projectionType: CameraLens.PerspectiveProjection
      fieldOfView: 90
      nearPlane : 0.1
      farPlane : 1000.0
      position: Qt.vector3d( 0.0, -20.0, 10.0 )
      upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
      viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }
    
    FirstPersonCameraController { camera: mainCamera 
      linearSpeed: 50
      lookSpeed: 3000
    }
  }
}
