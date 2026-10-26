/*
	    ,*-.		PROJECT : TROUBLE
	    |  |		DESCRIPTION : AAA VIDEO GAME BUILT IN C++ ON THE WINDOWS API WITH ZERO EXTERNAL DEPENDENCIES.
	,.  |  |		REPOSITORY : HTTPS://GITHUB.COM/M-MONTOYA-P/TROUBLE.GIT
	| |_|  | ,.		STARTED : OCT. 25TH, 2026
	`---.  |_| |	LICENSE : PROPRIETARY
	    |  .--`		VERSION : 0.0.0
	    |  |		STATUS : IN DEVELOPMENT
	  ._|__|_*		AUTHOR : LUIS MANUEL MONTOYA PILÓN
*/
#include "Common.hpp"

_Use_decl_annotations_
int APIENTRY wWinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPWSTR lpCmdLine, [[maybe_unused]] int nShowCmd)
{
	// 1. Default (🌵) - Mensajes generales o genéricos
	Utils::Logger::TLog(Utils::Logger::ELogType::Default, "WELCOME TO 'TROUBLE' PROJECT!");

	return 0;
}