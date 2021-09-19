#include <inttypes.h>
#include <Arduino.h>

#define EVENT_NONE 0
#define EVENT_EVERY 1
#define EVENT_OSCILLATE 2
#define MAX_NUMBER_OF_EVENTS (10)

#define TIMER_NOT_AN_EVENT (-2)
#define NO_TIMER_AVAILABLE (-1)

class Event
{

public:
  Event(void)
  {
    eventType = EVENT_NONE;
  };

  void update(void)
  {
    unsigned long now = millis();
    update(now);
  }

  void update(unsigned long now)
  {
    if (now - lastEventTime >= period)
    {
      switch (eventType)
      {
      case EVENT_EVERY:
        (*callback)();
        break;

      case EVENT_OSCILLATE:
        pinState = !pinState;
        digitalWrite(pin, pinState);
        break;
      }
      lastEventTime = now;
      count++;
    }
    if (repeatCount > -1 && count >= repeatCount)
    {
      eventType = EVENT_NONE;
    }
  }

  int8_t eventType;
  unsigned long period;
  int repeatCount;
  uint8_t pin;
  uint8_t pinState;
  void (*callback)(void);
  unsigned long lastEventTime;
  int count;
};

class Timer
{

public:
  Timer(void)
  {
  }

  int8_t every(unsigned long period, void (*callback)(void), int repeatCount)
  {
    int8_t i = findFreeEventIndex();
    if (i == -1)
      return -1;

    _events[i].eventType = EVENT_EVERY;
    _events[i].period = period;
    _events[i].repeatCount = repeatCount;
    _events[i].callback = callback;
    _events[i].lastEventTime = millis();
    _events[i].count = 0;
    return i;
  }

  int8_t every(unsigned long period, void (*callback)(void))
  {
    return every(period, callback, -1);
  }

  int8_t after(unsigned long duration, void (*callback)(void))
  {
    return every(duration, callback, 1);
  }

  int8_t oscillate(uint8_t pin, unsigned long period, uint8_t startingValue)
  {
    return oscillate(pin, period, startingValue, -1);
  }

  int8_t oscillate(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount)
  {
    int8_t i = findFreeEventIndex();
    if (i == NO_TIMER_AVAILABLE)
      return NO_TIMER_AVAILABLE;

    _events[i].eventType = EVENT_OSCILLATE;
    _events[i].pin = pin;
    _events[i].period = period;
    _events[i].pinState = startingValue;
    digitalWrite(pin, startingValue);
    _events[i].repeatCount = repeatCount * 2;
    _events[i].lastEventTime = millis();
    _events[i].count = 0;
    return i;
  }

  int8_t pulse(uint8_t pin, unsigned long period, uint8_t startingValue)
  {
    return oscillate(pin, period, startingValue, 1);
  }

  int8_t pulseImmediate(uint8_t pin, unsigned long period, uint8_t pulseValue)
  {
    int8_t id(oscillate(pin, period, pulseValue, 1));
    if (id >= 0 && id < MAX_NUMBER_OF_EVENTS)
    {
      _events[id].repeatCount = 1;
    }
    return id;
  }

  void stop(int8_t id)
  {
    if (id >= 0 && id < MAX_NUMBER_OF_EVENTS)
    {
      _events[id].eventType = EVENT_NONE;
    }
  }

  void update(void)
  {
    unsigned long now = millis();
    update(now);
  }

  void update(unsigned long now)
  {
    for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
    {
      if (_events[i].eventType != EVENT_NONE)
      {
        _events[i].update(now);
      }
    }
  }

protected:
  Event _events[MAX_NUMBER_OF_EVENTS];
  int8_t findFreeEventIndex(void)
  {
    for (int8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
    {
      if (_events[i].eventType == EVENT_NONE)
      {
        return i;
      }
    }
    return NO_TIMER_AVAILABLE;
  }
};
