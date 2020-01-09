#include <Rosetta/Commons/Macros.hpp>

#if defined(ROSETTASTONE_WINDOWS)
#include <crtdbg.h>
#include <tchar.h>

#include <Rosetta/Games/Game.hpp>

#ifdef _DEBUG
#define new new (_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    RosettaStone::Game game1, game2;
    game1.RefCopyFrom(game2);

    return 0;
}
#else
int main(int argc, char* argv[])
{
    return 0;
}
#endif