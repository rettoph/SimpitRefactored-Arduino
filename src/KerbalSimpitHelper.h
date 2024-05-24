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
    static void EmulateKeypress(short key, Input::Outgoing::KeyboardEmulator::ModifierFlags modifier = Input::Outgoing::KeyboardEmulator::ModifierFlags::NONE);
};

#endif