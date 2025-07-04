#ifndef IDISPLAY_HH
#define IDISPLAY_HH

class IDisplay
{
   public:
    virtual void clear()                          = 0;
    virtual void drawPixel(int x, int y, bool on) = 0;
    virtual void present()                        = 0;
    virtual ~IDisplay()                           = default;
};

#endif  // IDISPLAY_HH
