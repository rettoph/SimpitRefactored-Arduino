#include "SimpitBuilder.h"
#include "CoreSimpitMessageTypeIds.h"

SIMPIT_DECLARE_OUTGOING_TYPE(EchoRequest, SIMPIT_CORE_OUTGOING_ECHO_REQUEST_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(EchoResponse, SIMPIT_CORE_OUTGOING_ECHO_RESPONSE_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(CloseSerialPort, SIMPIT_CORE_OUTGOING_CLOSE_SERIAL_PORT_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(RegisterHandler, SIMPIT_CORE_OUTGOING_REGISTER_HANDLER_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(DeregisterHandler, SIMPIT_CORE_OUTGOING_DEREGISTER_HANDLER_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(CustomLog, SIMPIT_CORE_OUTGOING_CUSTOM_LOG_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(Request, SIMPIT_CORE_OUTGOING_REQUEST_MESSAGE_ID);

SIMPIT_DECLARE_INCOMING_TYPE(EchoRequest, SIMPIT_CORE_INCOMING_ECHO_REQUEST_ID);

SimpitBuilder::SimpitBuilder()
{
    _typeCount = 0;
    _types = (BaseSimpitMessageType**)malloc(sizeof(BaseSimpitMessageType*) * 512);

    this->RegisterOutgoing<CustomLog>();
}

Simpit* SimpitBuilder::Build(Stream &serial)
{
    BaseSimpitMessageType** types = (BaseSimpitMessageType**)malloc(_typeCount * sizeof(BaseSimpitMessageType*));
    for(int i = 0; i < _typeCount; i++)
    {
        types[i] = _types[i];
    }

    free(_types);

    Simpit* simpit = new Simpit(types, _typeCount, serial);

    return simpit;
}