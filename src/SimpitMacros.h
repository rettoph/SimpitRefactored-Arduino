#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageTypeProvider.h"
#include "SimpitMessageType.h"
#include "Simpit.h"
#include "function_objects.h"

#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE, MESSAGE_TYPE_ID) \
    template<> const byte GenericIncomingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_TYPE_ID;

#define SIMPIT_DECLARE_OUTGOING_TYPE(TYPE, MESSAGE_TYPE_ID) \
    template<> const byte GenericOutgoingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_TYPE_ID;

#endif