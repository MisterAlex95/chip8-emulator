#ifndef IWINDOW_HH
#define IWINDOW_HH

class IWindow
{
   public:
    virtual ~IWindow()                                                    = default;
    virtual bool pollEvent(Event& event)                                  = 0;
    virtual void clear()                                                  = 0;
    virtual void present()                                                = 0;
    virtual void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void fillRect(int x, int y, int w, int h)                     = 0;
    virtual void delay(uint32_t ms)                                       = 0;
};

#endif  // IWINDOW_HH
