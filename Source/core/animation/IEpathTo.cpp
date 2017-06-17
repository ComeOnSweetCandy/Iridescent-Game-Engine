#define __IE_DLL_EXPORTS__
#include "IEPathTo.h"

IE_BEGIN

IEPathTo::IEPathTo(IEArray * paths)
{
	m_paths = paths;
	m_course = 0.0f;
	m_speed = 1.0f;
}

IEPathTo::~IEPathTo()
{
	m_paths->Release();
}

void IEPathTo::Initialization()
{
	m_curPathIndex = m_paths->Count() - 1;
}

IEPathTo * IEPathTo::Create(IEArray * paths)
{
	IEPathTo * object = new IEPathTo(paths);
	object->Initialization();
	return object;
}

void IEPathTo::CompletedAction(IENode * node)
{
	if (!m_hasCompletedAction)
	{
		m_hasCompletedAction = true;
		ClearCurPath(node);
	}
}

void IEPathTo::SetCircle()
{

}

void IEPathTo::SetLoop()
{

}

bool IEPathTo::Run(IENode * node)
{
	CompletedAction(node);

	float distance = m_vDistance.Length();
	float segment = m_speed * IETime::Share()->GetLastFrapPassingTime();
	float ratio = segment / distance;
	IEVector displacement = m_vDistance*ratio;

	//node->AssembleDisplacement();
	//node->SetDisplacement(displacement);

	IEVector ** vectors = (IEVector**)m_paths->GetContainer();
	if ((IEVector(node->GetTranslate()[0], node->GetTranslate()[1]) - m_startPosi).Length() >= m_vDistance.Length())
	{
		IEVector * path = vectors[m_curPathIndex];
		node->SetTranslate(path->m_x, path->m_y);

		m_curPathIndex--;
	}
	if (m_curPathIndex < 0)
	{
		return true;
	}
	else
	{
		ClearCurPath(node);
	}
	return false;
}

void IEPathTo::ClearCurPath(IENode * node)
{
	const float * translate = node->GetTranslate();
	m_course = 0.0f;
	
	IEVector ** vectors = (IEVector**)m_paths->GetContainer();
	IEVector * path = vectors[m_curPathIndex];

	m_vDistance = *path - IEVector(translate[0], translate[1]);
	m_startPosi = IEVector(translate[0], translate[1]);
}

IE_END