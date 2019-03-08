import "../styles"
import AdvancedRayTracer 1.0
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

ColumnLayout {
  GroupBox {
    Layout.fillWidth: true
    Layout.fillHeight: true

    RowLayout {
      anchors.fill: parent.fill
      Layout.fillWidth: true
      Layout.fillHeight: true
    
      Text {
        color: Style.likeWhite
        text: "zIndex: "
        Layout.leftMargin: 5
      }
    
      CustomIntInput {
        id: inpuText
        text: zIndexModel.zIndex()

        onEditingFinished: {
          zIndexModel.setIndex(parseInt(text))
        }
      }
    }
  }        
}