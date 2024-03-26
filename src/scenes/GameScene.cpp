#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/Object.h>

#include "../characters/Fish.cpp"
#include "latebit/ResourceManager.h"

using namespace lb;

class WelcomeText : public Object {
public:
  WelcomeText() { this->setType("WelcomeText"); }

  // The draw method is called every frame to draw the object on the screen.
  int draw() override {
    int result = 0;

    // This comes from the CMakeLists.txt file, don't mind it.
    std::string version = LATEBIT_VERSION;

    // Here we are using the Display Manager (DM) to draw text on the screen at
    // a given position.
    result += DM.drawString(this->getPosition() + Vector(0, 30), version,
                            TEXT_ALIGN_CENTER, WHITE);
    return result;
  }
};

class Logo : public Object {
public:
  Logo() {
    // This is the simplest object you can create: you give it a type and a
    // sprite, and, by using `setPosition` you can place it on the screen.
    this->setType("Logo");
    this->setSprite("logo");
  }
};

class GameScene : public Object {
private:
  WelcomeText *welcomeText = new WelcomeText();
  Fish *fish = new Fish();
  Logo *logo = new Logo();

public:
  GameScene() {
    // The scene is a container object for all the objects that will be drawn on
    // the screen.
    // Setting the type will allow you to retrieve the scene later on and to
    // identify it in the logs.
    setType("GameScene");

    // The Display Manager (DM) is responsible for drawing everything on the
    // screen. Here you can set the background color of the scene for example.
    DM.setBackground(Color::BLUE);

    // Here we are retrieving the music we loaded in the main.cpp from the
    // ResourceManager (RM) and playing it.
    auto music = RM.getMusic("music");
    if (music != nullptr) {
      music->play();
    }

    // In the following block we are placing objects in the scene.
    auto center =
        Vector(DM.getHorizontalCells() / 2.0, DM.getVerticalCells() / 2.0);

    auto fishBox = this->fish->getBox();
    auto logoBox = this->logo->getBox();

    this->welcomeText->setPosition(center - Vector(0, 5));

    this->fish->setPosition(
        center - Vector(fishBox.getWidth() / 2, 32 - fishBox.getHeight() / 2));

    this->logo->setPosition(center - Vector(logoBox.getWidth() / 2, 0));
  }
};