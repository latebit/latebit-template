#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/world/WorldManager.h>
#include <latebit/core/world/Object.h>
#include <latebit/core/ResourceManager.h>

#include "../characters/Fish.cpp"

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
                            TextAlignment::CENTER, Color::WHITE);
    
    // You can use special glyphs to represent input buttons. This is useful
    // for on-screen instructions and settings.
    char msg[26];
    snprintf(msg, sizeof(msg), "Press %c to play a sound", InputGlyph::A);
    result += DM.drawString(this->getPosition() + Vector(0, 50), msg, TextAlignment::CENTER, Color::PEACH);

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

class GameScene : public Scene {
public:
  GameScene() {
    // Here we are defining the objects that will appean in our GameScene.
    // The GameScene owns the objects and it ensures that they are cleaned up.
    auto logo = this->createObject<Logo>();
    auto welcomeText = this->createObject<WelcomeText>();

    // Some objects are more complex and need parameters to be created. In this
    // case, we are passing the GameScene to the Fish object so it can create
    // Bubbles.
    auto fish = this->createObject<Fish>(this);
    
    // The Display Manager (DM) is responsible for drawing everything on the
    // screen. Here you can set the background color of the scene for example.
    DM.setBackground(Color::BLUE);

    // Here we are retrieving the music we loaded in the main.cpp from the
    // ResourceManager (RM) and playing it.
    const auto music = RM.getMusic("music");
    if (music != nullptr) {
      music->play(true);
    }

    // In the following block we are placing objects in the scene.
    const auto center = Vector(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);

    // To place objects in the screen we need to know how "big" they are.
    // A box is a simplified, rectangular representation of an object's boundaries. 
    // It defines the minimum and maximum extents of the object along each axis,
    // providing an efficient way to perform collision detection and spatial queries.
    const auto fishBox = fish->getBox();
    const auto logoBox = logo->getBox();

    // Positions are defined by bidimensional vectors. You can perform standard
    // vector operations on them. Take a look at the header for the Vector class
    // for more information.
    welcomeText->setPosition(center - Vector(0, 5));

    fish->setPosition(
        center - Vector(fishBox.getWidth() / 2, 32 - fishBox.getHeight() / 2));

    logo->setPosition(center - Vector(logoBox.getWidth() / 2, 0));

    // Now you are ready to see how the objects we have manipulated are defined.
    // Go check the WelcomeText, Logo, and Fish to start implementing your first objects.
  }

  void onActivated() override {
    // This method is called when the scene is activated. You can use it to
    // initialize the scene or to perform actions when the scene is shown.
  }

  void onDeactivated() override {
    // This method is called when the scene is deactivated. You can use it to
    // clean up resources or to perform actions when the scene is hidden.
  }
};