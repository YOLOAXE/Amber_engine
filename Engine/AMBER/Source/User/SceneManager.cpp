#include "SceneManager.hpp"

namespace Ge
{
	void SceneManager::addScene(std::string name, Scene * s)
	{
		m_mapScene[name] = s;
	}

	void SceneManager::removeScene(std::string name)
	{
		m_mapScene.erase(name);
	}

	void SceneManager::loadEntryScene()
	{
		if (m_mapScene.size() > 0)
		{
			currentScene = m_mapScene.begin()->second;
			currentScene->load();
		}
	}

	void SceneManager::loadScene(std::string name)
	{
		if (m_mapScene.count(name) == 0)
		{
			return;
		}
		if (currentScene != nullptr)
		{
			currentScene->unload();
		}
		currentScene = m_mapScene[name];
		currentScene->load();
	}
}