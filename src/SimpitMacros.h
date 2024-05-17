#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageType.h"
#include "SimpitBuilder.h"
#include "Simpit.h"

#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE) \
    template class IncomingSimpitMessageType<TYPE>; \
    template SimpitBuilder SimpitBuilder::RegisterIncoming<TYPE>(); \
    template void Simpit::Subscribe<TYPE>(SimpitMessageSubscriber<TYPE>*);

#endif