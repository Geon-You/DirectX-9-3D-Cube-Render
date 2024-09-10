#include "MainGame.h"
#include "Device.h"
#include "Ingame.h"

void MainGame::Initialize()
{
	GET_SINGLE(Device)->InitDevice(WinMode::WIN);

	scene = new Ingame();
	scene->Initialize();
}

void MainGame::Update()
{
	scene->Update();
}

void MainGame::Render()
{
	GET_SINGLE(Device)->RenderBegin();
	scene->Render();
	GET_SINGLE(Device)->RenderEnd();
}

void MainGame::Release()
{
	GET_SINGLE(Device)->Destroy();
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
