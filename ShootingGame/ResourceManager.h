#pragma once

#include "Singleton.h"

// ���ҽ� ������ ���ӿ��� �پ��ϰ� ����.
// �ؽ�ó / �޽� / ���� / ����Ʈ ���..
// ��� ���ҽ����� �����ϴ� �Ŵ���
class ResourceManager : public singleTon<ResourceManager>
{
	friend singleTon<ResourceManager>;
	ResourceManager() {}
public:

	void Init();
	void Destroy();	// ���ҽ� ����

	class LineMesh* GetLineMesh(string meshName);
	class TextureResource* GetTexture(string meshName);

private:
	//class LineMesh* _lineMesh = nullptr;
	//unordered_map<string, class LineMesh*> _lineMeshes;

	unordered_map<string, class TextureResource*> _textures;
};

