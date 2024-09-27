#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

class Light 
{ 
  private:
    bool on ;      // A light witch may be on or off.

  protected:

  public:  
    Light ();      // Makes a new light
    ~Light();

    void toggle(); // If light is on turn it off , if off turn it on
    bool isOn();   // is the light on ?
};

#endif
