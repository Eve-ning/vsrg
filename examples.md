## Your Own Implementations

You are free to use these libraries to work with your own game.

Here are some known examples that you can work off of if you have special objects in your game.

An popular inheritance would be:
```
class LandMine : public HitObject {
public:
    LandMine(double hp_drain, ...) : HitObject(...), hp_drain_(hp_drain) {}
    ~LandMine() {}
    double getHpDrain() const { return hp_drain_; }
    void setHpDrain(double hp_drain) { hp_drain_ = hp_drain; }
    ...
private:
    double hp_drain_;
}
```

Inheriting off of `EventObject` makes it so that it's not restricted with a column. It is currently used for timing, but kiai can be used integrated with them.
```
#include <TimingPoint.h>
#include <ScrollPoint.h>
class KiaiPoint {
    KiaiPoint(std::shared_ptr<EventPoint> start_point,
              std::shared_ptr<EventPoint> end_point) :
              start_point_(start_point), end_point_(end_point) {}
    ~KiaiPoint() {} // Shared Pointers do not need destructor

    bool isBetween() const;
    Color getColor() const;
    ...
private:
    std::shared_ptr<EventPoint> start_point_;
    std::shared_ptr<EventPoint> end_point_;
    Color color_;
}
```

