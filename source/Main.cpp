#include <GameImp.h>
#include <MemoryLeak.h>

int main( int argc, char ** argv )
{
	/// Memoryleak checking for windows.
	#if defined _WIN32 || defined _WIN64
		#ifdef _DEBUG
				 _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		#endif
	#endif

	GameImp game;
	return game.Run(argc, argv );
}