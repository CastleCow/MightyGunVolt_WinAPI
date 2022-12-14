#pragma once

#include "resource.h"

//========================================
//##    전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

//========================================
//##			윈도우 설정				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1280
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//========================================
//##			게임씬 그룹				##
//========================================

enum class GroupScene
{
	Title,

	TileTool,

	Stage01,
	Stage02,
	Stage03,
	Stage04,

	Size,
};

//========================================
//##				레이어				##
//========================================

enum class Layer
{
	Default,
	BackGround,
	Map,
	Tile,
	Player,
	Missile,
	Monster,
	MonsterBullet,
	BossBullet,
	Skill,

	Ui,
	Size,
};

//========================================
//##				타일					##
//========================================

enum class TypeTile
{
	None,
	Ground,
	Platform,
	Wall,
	Next,

	Size,
};