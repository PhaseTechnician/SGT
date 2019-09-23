#include "Script.h"

Position position={0,0};

void MoveToward(int orientation, float tileCount)
{

}

inline void Open(void)
{
	ServerSetAngle(0,SERVER_5);
}

inline void Close(void)
{
	ServerSetAngle(180,SERVER_5);
}
