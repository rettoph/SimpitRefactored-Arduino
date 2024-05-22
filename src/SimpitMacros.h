#ifndef SimpitMacros_h
#define SimpitMacros_h

#include "SimpitMessageTypeProvider.h"
#include "SimpitMessageType.h"
#include "SimpitBuilder.h"
#include "Simpit.h"
#include "function_objects.h"

#define SIMPIT_DECLARE_INCOMING_TYPE(TYPE, MESSAGE_TYPE_ID) \
    template struct GenericIncomingSimpitMessageType<TYPE>; \
    template<> const byte GenericIncomingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_TYPE_ID; \
    template bool SimpitMessageTypeProvider::TryRegisterIncoming<TYPE>(void(*handler)(void*, TYPE*)); \
    template SimpitBuilder SimpitBuilder::RegisterIncoming<TYPE>(void(*handler)(void*, TYPE*));

#define SIMPIT_DECLARE_OUTGOING_TYPE(TYPE, MESSAGE_TYPE_ID) \
    template struct GenericOutgoingSimpitMessageType<TYPE>; \
    template<> const byte GenericOutgoingSimpitMessageType<TYPE>::MessageTypeId = MESSAGE_TYPE_ID; \
    template bool SimpitMessageTypeProvider::TryRegisterOutgoing<TYPE>(); \
    template SimpitBuilder SimpitBuilder::RegisterOutgoing<TYPE>(); \
    template void Simpit::WriteOutgoing<TYPE>(TYPE data);

#endif