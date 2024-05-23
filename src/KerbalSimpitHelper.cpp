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