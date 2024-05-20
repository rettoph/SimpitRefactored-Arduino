#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageType.h"
#include "SimpitBuilder.h"
#include "Simpit.h"

// Generic catch-all implementation.


#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE, MESSAGE_ID) \
    template class IncomingSimpitMessageType<TYPE>; \
    template<> const byte IncomingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_ID; \
    template SimpitBuilder SimpitBuilder::RegisterIncoming<TYPE>(); \
    template void Simpit::RegisterCallback<TYPE>(void (*callback)(void*, TYPE*));

#define SIMPIT_DECLARE_OUTGOING_TYPE(TYPE, MESSAGE_ID) \
    template class OutgoingSimpitMessageType<TYPE>; \
    template<> const byte OutgoingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_ID; \
    template SimpitBuilder SimpitBuilder::RegisterOutgoing<TYPE>(); \
    template void Simpit::WriteOutgoing<TYPE>(TYPE data);

#endif