#pragma once

#include <cstdint>

enum class PacketType
{
    Login,
    Move,
    Attack
};

struct PacketHeader{
    uint16_t Size;
    PacketType Type;
};

struct MovePacket{
    PacketHeader Header;
    int X;
    int Y;
};
