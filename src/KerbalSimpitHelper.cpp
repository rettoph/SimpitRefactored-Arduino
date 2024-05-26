#include "KerbalSimpitHelper.h"

#include "KerbalSimpitMessageTypes.h"

Simpit* KerbalSimpitHelper::_simpit = nullptr;

void KerbalSimpitHelper::Init(Simpit *simpit)
{
    KerbalSimpitHelper::_simpit = simpit;
}

void KerbalSimpitHelper::SetSASMode(AutoPilotModeEnum mode)
{
    Vessel::Outgoing::AutopilotMode message = Vessel::Outgoing::AutopilotMode();
    message.Value = mode;

    KerbalSimpitHelper::_simpit->WriteOutgoing(message);
}

void KerbalSimpitHelper::SetAction(ActionGroupFlags action, bool value)
{
    if(value == true)
    {
        Vessel::Outgoing::ActionGroupActivate message = Vessel::Outgoing::ActionGroupActivate();
        message.Flags = action;

        KerbalSimpitHelper::_simpit->WriteOutgoing(message);
    }
    else 
    {
        Vessel::Outgoing::ActionGroupDeactivate message = Vessel::Outgoing::ActionGroupDeactivate();
        message.Flags = action;

        KerbalSimpitHelper::_simpit->WriteOutgoing(message);
    }
}

void KerbalSimpitHelper::KeyboardInput(short key, Input::Outgoing::KeyboardEmulator::ModifierFlags modifier)
{
    Input::Outgoing::KeyboardEmulator message = Input::Outgoing::KeyboardEmulator();
    message.Key = key;
    message.Modifier = modifier;

    KerbalSimpitHelper::_simpit->WriteOutgoing(message);
}

void KerbalSimpitHelper::CycleNavballMode()
{
    KerbalSimpitHelper::_simpit->WriteOutgoing(NavBall::Outgoing::NavballMode());
}

void KerbalSimpitHelper::TimewarpTo(Warp::Outgoing::TimewarpTo::InstanceEnum instant, float delay)
{
    Warp::Outgoing::TimewarpTo message = Warp::Outgoing::TimewarpTo();
    message.Instant = instant;
    message.Delay = delay;

    KerbalSimpitHelper::_simpit->WriteOutgoing(message);
}