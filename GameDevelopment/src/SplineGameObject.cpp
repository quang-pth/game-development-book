#include "include/SplineGameObject.h"
#include "include/Game.h"
#include "include/Spline.h"
#include "include/SplineCamera.h"

SplineGameObject::SplineGameObject(Game* game, const std::string& name) :
	GameObject(game, name)
{
	mCamera = new SplineCamera(this);

	Spline path;
	path.AddControlPoint(Vector3::Zero);
	for (int i = 0; i < 5; i++)
	{
		if (i % 2 == 0)
		{
			path.AddControlPoint(Vector3(300.0f * (i + 1), 300.0f, 300.0f));
		}
		else
		{
			path.AddControlPoint(Vector3(300.0f * (i + 1), 0.0f, 0.0f));
		}
	}

	mCamera->SetSpline(path);
	mCamera->SetPaused(false);
}

SplineGameObject::~SplineGameObject()
{
}

void SplineGameObject::RestartSpline()
{
	mCamera->Restart();
}
