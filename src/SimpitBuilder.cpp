#include "SimpitBuilder.h"

SimpitBuilder::SimpitBuilder()
{
    _typeCount = 0;
    _types = (BaseSimpitMessageType**)malloc(sizeof(BaseSimpitMessageType*) * 512);
}

BaseSimpitMessageType** SimpitBuilder::Build()
{
    BaseSimpitMessageType** types = (BaseSimpitMessageType**)malloc(_typeCount * sizeof(BaseSimpitMessageType*));
    for(int i = 0; i < _typeCount; i++)
    {
        types[i] = _types[i];
    }

    free(_types);

    return types;
}