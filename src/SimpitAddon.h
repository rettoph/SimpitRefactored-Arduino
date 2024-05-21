#ifndef SimpitAddon_h
#define SimpitAddon_h

class SimpitBuilder;

class SimpitAddon
{
public:
    virtual void Register(SimpitBuilder builder) = 0;
};

#endif