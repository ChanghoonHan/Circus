#include <iostream>
#include "Scene.h"

BitMapManager* Scene::m_lpbitMapManager = NULL;

void Scene::SetBitMapManager(BitMapManager* lpbitMapManager)
{
	m_lpbitMapManager = lpbitMapManager;
}

Scene::Scene()
{
}

Scene::~Scene()
{
}
