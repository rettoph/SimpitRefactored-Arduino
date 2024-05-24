#ifndef KerbalSimpitHelper_h
#define KerbalSimpitHelper_h

#include "Simpit.h"
#include "KerbalSimpitMessageTypes.h"

class KerbalSimpitHelper
{
private:
    static Simpit *_simpit;

public:
    static void Init(Simpit *simpit);

    static void SetSASMode(AutoPilotModeEnum mode);
    static void SetAction(ActionGroupFlags action, bool value);
    static void KeyboardInput(short key, Input::Outgoing::KeyboardEmulator::ModifierFlags modifier = Input::Outgoing::KeyboardEmulator::ModifierFlags::NONE);
    static void CycleNavballMode();
    static void TimewarpTo(Warp::Outgoing::TimewarpTo::InstanceEnum instant, float delay);
};

#endif