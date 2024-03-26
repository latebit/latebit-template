#include <latebit/EventOut.h>
#include <latebit/EventStep.h>
#include <latebit/Object.h>
#include <latebit/WorldManager.h>

using namespace lb;

class Bubbles : public Object {
public:
  Bubbles(Vector position) {
    // This tiny object is a bubble that floats up the screen and disappears
    // when it reaches the top. We give it a type and assign it a sprite that we
    // have loaded in the main.cpp. Again you can pick the sprites by their
    // label ("bubbles" in this case)
    setType("Bubbles");
    setSprite("bubbles");

    // latebit supports collisions between objects. Marking this object as
    // SPECTRAL means that it will not collide with other objects. You can read
    // more about solidness in latebit/Object.h
    setSolidness(SPECTRAL);

    // We set the velocity of the bubble to float up the screen
    setVelocity(Vector(0, -1));

    // Altitude is a property of the object that determines the order in which
    // objects are drawn on the screen. The higher the altitude, the later the
    // object is drawn. This is useful when you want to draw objects on top of
    // others.
    setAltitude(2);

    // We set the position of the bubble to the position we received in the
    // constructor
    setPosition(position);

    // We subscribe to the OUT_EVENT here, to mark the bubble for deletion when
    // it goes out of the screen. We will handle this in the eventHandler()
    subscribe(OUT_EVENT);
  }

  // This is where we handle the events we subscribed to.
  // In this case, we are only interested in the OUT_EVENT, which we use to mark
  // the bubble for deletion when it goes out of the screen.
  int eventHandler(const Event *p_e) override {
    if (p_e->getType() == OUT_EVENT) {
      WM.markForDelete(this);
      return 1;
    }

    return 0;
  }
};

class Fish : public Object {
public:
  Fish() {
    // This is your first character!
    // It is a fish that swims in the middle of the screen and honestly does not
    // do much. We give it a type and assign it a sprite that we have loaded in
    // the main.cpp. You can pick the sprites by their label ("fish" in this
    // case)
    setType("Fish");
    setSprite("fish");

    // This is how you can make your game objects interactive.
    // By subscribing to events, you can make your objects react to them.
    // Here we are subscribing to the STEP_EVENT, which is triggered every
    // frame. We are using it to spawn bubbles every now and then (see
    // eventHandler())
    subscribe(STEP_EVENT);
  }

  // This is where we handle the events we subscribed to.
  // In this case, we are only interested in the STEP_EVENT, which we use to
  // spawn bubbles from time to time.
  int eventHandler(const Event *p_e) override {
    if (p_e->getType() == STEP_EVENT) {
      if (rand() % 100 == 0) {
        new Bubbles(getPosition() + Vector(16, 0));
      }
      return 1;
    }

    return 0;
  }
};