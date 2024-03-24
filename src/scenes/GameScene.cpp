#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/Object.h>

#include "../characters/Fish.cpp"
#include "latebit/ResourceManager.h"

using namespace lb;

class WelcomeText : public Object {
public:
  WelcomeText() { this->setType("WelcomeText"); }

  int draw() override {
    int result = 0;

    // This comes from the CMakeLists.txt file
    std::string version = LATEBIT_VERSION;

    result += DM.drawString(this->getPosition() + Vector(0, 30), version,
                            TEXT_ALIGN_CENTER, WHITE);
    return result;
  }
};

class Logo : public Object {
public:
  Logo() {
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
    setType("GameScene");

    DM.setBackground(Color::BLUE);
    auto music = RM.getMusic("music");

    if (music != nullptr) {
      music->play();
    }

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