#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>

#include "main-controller.hpp"
#include "menu-controller.hpp"
#include "SidebarController.hpp"
#include "RendererController.hpp"

#include "menu-model.hpp"
#include "SidebarModel.hpp"
#include "RendererModel.hpp"

int main(int argc, char *argv[])
{
  QApplication::setApplicationName("AdvancedRayTracer");
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  
  QStringList fonts = QStringList{} << ":/fonts/Hack-Regular.ttf" << ":/fonts/Hack-Bold.ttf"
                                    << ":/fonts/Hack-BoldItalic.ttf" << ":/fonts/Hack-Italic.ttf"
                                    << ":/fonts/fontello.ttf";

  for (const auto& font : fonts) {
    if (QFontDatabase::addApplicationFont(font) == -1) {
        qWarning() << "Failed to load font: " << font;
    }
  }

  qmlRegisterType<ART::Controllers::MainController>("AdvancedRayTracer", 1, 0, "MainController");
  qmlRegisterType<ART::Controllers::MenuController>("AdvancedRayTracer", 1, 0, "MenuController");
  qmlRegisterType<ART::Controllers::SidebarController>("AdvancedRayTracer", 1, 0, "SidebarController");
  qmlRegisterType<ART::Controllers::RendererController>("AdvancedRayTracer", 1, 0, "RendererController");

  ART::Controllers::MainController mainController;

  auto menuModel = new ART::Models::MenuModel;
  mainController.menuController()->setModel(menuModel);

  auto sidebarModel = new ART::Models::SidebarModel;
  mainController.sidebarController()->setModel(sidebarModel);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("mainController", &mainController);
  engine.rootContext()->setContextProperty("menuModel", menuModel);
  engine.rootContext()->setContextProperty("sidebarModel", sidebarModel);
  engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  mainController.dumpObjectTree();
  return QApplication::exec();
}
