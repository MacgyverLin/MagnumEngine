///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BillBoardRenderer_h_
#define _BillBoardRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "BillBoard.h"
#include "GXContext.h"
#include "VisualEffect.h"
#include "GXVertexBuffer.h"
using namespace Magnum;

namespace Magnum
{

/**
* BillBoardRenderer.
* BillBoardRenderer render BillBoard on editor screen.
* @see RendererBase, BillBoard
*/
class BillBoardRenderer : public RendererBase
{
friend class BillBoard;
////////////////////////////////////////////////////////////////
public:
	/**
	* BillBoardRenderer Constructor.
	* To Construct the BillBoardRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	BillBoardRenderer(Component::Owner &owner_);

	/**
	* BillBoardRenderer Destructor.
	* To Destruct BillBoardRenderer and remove from its owner.
	*/
	virtual ~BillBoardRenderer();

	DECLARE_COMPONENT(BillBoardRenderer, RendererBase, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer.
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const
	{
		return 0x00000002;
	}

	/**
	* add BillBoard to the Renderer.
	* @param billBoard, a BillBoard
	* @see BillBoard
	*/
	void add(BillBoard &billBoard);

	/**
	* remove BillBoard from the Renderer.
	* @param billBoard, a BillBoard
	* @see BillBoard
	*/
	void remove(BillBoard &billBoard);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<BillBoard *>	billBoards;
};

};

#endif
