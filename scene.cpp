#include "DxLib.h"
#include "common.h"
#include "scene.h"
#include "SceneTitle.h"
#include "SceneTutorial.h"
#include "SceneGame.h"
#include "SceneClear.h"


BaseScene *sceneManager::m_pScene = nullptr;
bool sceneManager::start;

void sceneManager::changeScene(SCENE scene)
{
	if (m_pScene)
	{
		delete m_pScene;
		start = true;
	}

	switch (scene)
	{
	case TITLE:
		m_pScene = new title();
		break;
	case TUTORIAL:
		m_pScene = new SceneTutorial();
		break;
	case SCENE::GAME:
		m_pScene = new SceneGame();
		break;
	case SCENE::CLEAR:
		m_pScene = new SceneClear();
		break;
	default:
		break;
	}
}

void sceneManager::Init()
{
	m_pScene->Init();
}
void sceneManager::unInit()
{
	m_pScene->unInit();
}
void sceneManager::Update()
{
	m_pScene->Update();
}
void sceneManager::Draw()
{
	m_pScene->Draw();
	if (debugFlg)
	{
		m_pScene->Debug();
	}
}

void sceneManager::execute()
{
	if (m_pScene == nullptr)return;
	if (start)
	{
		Init();
		start = false;
	}
	else
	{
		Update();

		Draw();
	}

}

