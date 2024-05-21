#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageTypeProvider.h"
#include "SimpitMessageType.h"
#include "SimpitBuilder.h"
#include "Simpit.h"
#include "function_objects.h"

// Generic catch-all implementation.


#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE, MESSAGE_ID) \
    template class IncomingSimpitMessageType<TYPE>; \
    template<> const byte IncomingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_ID; \
    template bool SimpitMessageTypeProvider::TryRegisterIncoming<TYPE>(); \
    template SimpitBuilder SimpitBuilder::RegisterIncoming<TYPE>(); \
    template SimpitBuilder SimpitBuilder::RegisterIncomingHandler<TYPE>(FunctionObject<void(void*, TYPE*)> handler);

#define SIMPIT_DECLARE_OUTGOING_TYPE(TYPE, MESSAGE_ID) \
    template class OutgoingSimpitMessageType<TYPE>; \
    template<> const byte OutgoingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_ID; \
    template bool SimpitMessageTypeProvider::TryRegisterOutgoing<TYPE>(); \
    template SimpitBuilder SimpitBuilder::RegisterOutgoing<TYPE>(); \
    template void Simpit::WriteOutgoing<TYPE>(TYPE data);

#endif