
#include "movieobjects/movieobjects.h"
struct DmeCameraParams_t
{
};

class CSFMSession
{
public:
    CSFMSession();
    ~CSFMSession();

    void Init();
    void Shutdown();

	CDmeCamera*		CreateCamera(DmeCameraParams_t const&);
	CDmeDag*		FindOrCreateScene(CDmeFilmClip*, char const*);
	CDmeGameModel*	CreateEditorGameModel(studiohdr_t*, Vector const&, Quaternion&);
private:
	
};

CSFMSession::CSFMSession()
{
}

CSFMSession::~CSFMSession()
{
}

void CSFMSession::Init()
{
}

void CSFMSession::Shutdown()
{
}

CDmeCamera* CSFMSession::CreateCamera(DmeCameraParams_t const&)
{
	return nullptr;
}

CDmeDag* CSFMSession::FindOrCreateScene(CDmeFilmClip*, char const*)
{
	return nullptr;
}

CDmeGameModel* CSFMSession::CreateEditorGameModel(studiohdr_t*, Vector const&, Quaternion&)
{
	return nullptr;
}