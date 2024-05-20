#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageType.h"
#include "SimpitBuilder.h"
#include "Simpit.h"

#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE) \
    template class IncomingSimpitMessageType<TYPE>; \
    template SimpitBuilder SimpitBuilder::RegisterIncoming<TYPE>(); \
    template void Simpit::Subscribe<TYPE>(SimpitMessageSubscriber<TYPE>*);

#define SIMPIT_DECLARE_OUTGOING_TYPE(TYPE) \
    template class OutgoingSimpitMessageType<TYPE>; \
    template SimpitBuilder SimpitBuilder::RegisterOutgoing<TYPE>(); \
    template void Simpit::WriteOutgoing<TYPE>(TYPE data);

#endif