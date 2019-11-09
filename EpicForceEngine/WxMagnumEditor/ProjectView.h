#ifndef _ProjectView_h_
#define _ProjectView_h_

#include "wxdef.h"
#include "GameDescriptor.h"
#include "InputData.h"
#include <MagnumEngine.h>

#include "ResourceImporterView.h"
#include "EntityCreatorsView.h"
#include "DebugView.h"
#include "SceneView.h"
#include "InspectorView.h"
#include "HierarchyView.h"
#include "FileToolBarView.h"
#include "EditToolBarView.h"
#include "PlayModeToolBarView.h"
#include "BuildModeToolBarView.h"
#include "OperationModeToolBarView.h"
#include "MiscAToolBarView.h"
#include "MiscBToolBarView.h"
#include "Config.h"
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView : public wxFrame, public ProjectViewBase
{
public:
	ProjectView(const wxString& title);
	virtual ~ProjectView();
	
	static ProjectView &instance();

	bool						initStage(int width, int height, int editorWidth, int editorHeight);
	bool						processStage();
	void						terminateStage();
protected:
private:
	void						initUI();
	void						initMenuBar();

	void						diableUI(unsigned int flags);
	void						enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
public:
	void						updateKeyBoard();
	void						updateJoyPad();
	void						addMouseUp(int modifier, int id, float x, float y);
	void						addMouseDown(int modifier, int id, float x, float y);
	void						addMouseMove(int modifier, int id, float x, float y);
	void						addWheelMotion(int modifier, float x, float y, int axis, int value);
protected:
private:
	const ClassIndexMap			&getClassIndexMap() const;

	String						fixBackslash(const wxString &s);

	static long long			getCurrentTimeMSFunc_();
	static void					infoPrintFunc(const char *buf_);
	static void					debugPrintFunc(int i, const char *buf_);
	static void					panicPrintFunc(const char *buf_);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void						onSize(wxSizeEvent &evt);
	void						onMouseEnter(wxMouseEvent &evt);
	void						onMouseLeave(wxMouseEvent &evt);

	void						onMenuSelected(wxCommandEvent &evt);
	void						onFileMenuSelected(wxCommandEvent &evt);
	void						onEditMenuSelected(wxCommandEvent &evt);
	void						onOpsMenuSelected(wxCommandEvent &evt);
	void						onMiscAMenuSelected(wxCommandEvent &evt);
	void						onMiscBMenuSelected(wxCommandEvent &evt);
	void						onDebugRunMenuSelected(wxCommandEvent &evt);
	void						onHelpMenuSelected(wxCommandEvent &evt);
	void						onBuildMenuSelected(wxCommandEvent &evt);
////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void				notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void				disableUIEvent();
	virtual void				enableUIEvent();
public:
protected:
private:
	ClassIndexMap				classIndexMap;
	
	EntityCreatorsView			*entityCreatorsView;
	DebugView					*debugView;	
	SceneView					*sceneView;
	ResourceImporterView		*resourceImporterView;

	InspectorView				*inspectorView;	
	HierarchyView				*hierarchyView;
	FileToolBarView				*fileToolBarView;
	EditToolBarView				*editToolBarView;
	OperationModeToolBarView	*operationModeToolBarView;
	PlayModeToolBarView			*playModeToolBarView;
	BuildModeToolBarView		*buildModeToolBarView;
	MiscAToolBarView			*miscAToolBarView;
	MiscBToolBarView			*miscBToolBarView;

	Config						config;

	wxAuiManager				m_mgr;

	int							viewWidth;
	int							viewHeight;

	static ProjectView	*_instance;
};

#endif