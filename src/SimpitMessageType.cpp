#include "SimpitMessageType.h"

BaseSimpitMessageType::BaseSimpitMessageType(byte messageTypeId, SimpitMessageTypeEnum type)
{
    this->Id = messageTypeId;
    this->Type = type;
}