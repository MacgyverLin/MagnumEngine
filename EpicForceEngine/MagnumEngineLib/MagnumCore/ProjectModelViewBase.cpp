#include "ProjectModelViewBase.h"
using namespace Magnum;

#if defined(WIN32)
ProjectModelBase::ProjectModelBase()
: flags(0)
{
}

ProjectModelBase::~ProjectModelBase()
{
	for(int i=0; i<views.length(); i++)
	{
		views[i]->model = 0;
	}
}

void ProjectModelBase::addView(ProjectViewBase *view)
{
	views.push() = view;

	view->model =  this;
}

int ProjectModelBase::getNumViews() const
{
	return views.length();
}

void ProjectModelBase::removeView(ProjectViewBase *view)
{
	int idx = views.search(view);
	if(idx>=0)
	{
		views.remove(idx);
	}
}

bool ProjectModelBase::hasChanged(int flags_)
{
	return (flags & flags_)!=0;
}

void ProjectModelBase::notifyViews()
{
	const Vector<unsigned char> buffer;

	notifyViews(buffer);
}

void ProjectModelBase::notifyViews(const Vector<unsigned char> &buffer)
{
	if( hasChanged(ProjectModelBase::ALL) )
	{
		for(int i=0; i<views.length(); i++)
		{
			views[i]->disableUIEvent();

			views[i]->notify(flags, *this, buffer);

			views[i]->enableUIEvent();
		}

		clearChanged(flags);
	}
}

void ProjectModelBase::setChanged(int flags_)
{
	flags |= flags_;
}

void ProjectModelBase::clearChanged(int flags_)
{
	flags &= ~flags_;
}

////////////////////////////////////////////////////////////////////////////////////
ProjectViewBase::ProjectViewBase()
: model(0)
{
}

ProjectViewBase::~ProjectViewBase()
{
	if(model)
	{
		model->removeView(this);
	}
}

ProjectModelBase &ProjectViewBase::getModel()
{
	return *model;
}

#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif