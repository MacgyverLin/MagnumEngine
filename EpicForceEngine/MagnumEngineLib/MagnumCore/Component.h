///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Component_h_
#define _Component_h_

#include "FileIO.h"
#include "Array.h"
#include "Delegate.h"
#include "Frame3.h"
#include "ColorRGBA.h"
#include "SRTTransform.h"
#include "IComponentDebugRenderer.h"
#include "reflection.h"
using namespace agm::reflection;

namespace Magnum
{

#define DECLARE_COMPONENT(className, superClassName, editorActive) \
CLASS(className, superClassName); \
virtual bool isEditorModeActive() const \
{ \
	return editorActive; \
}

/**
* Component.
* Component is the base class of all components
* @see Component
*/
class Component
{
public:
	class Owner;
	friend class Component::Owner;

	/**
	* Owner.
	* Owner is the base class of owner of component. Owner contains basic information.
	* @see Frame3
	*/
	class Owner : public Frame3
	{
	friend class Component;
	friend class Entity;
	friend class EntityReader;
	friend class EntityWriter;
	private:
		Owner(const Owner &owner);
		Owner &operator = (const Owner &owner);
	public:
		/**
		* Owner Constructor
		* To Construct the Owner
		*/
		Owner();

		/**
		* Owner Destructor
		* To Destructor the Owner
		*/
		virtual ~Owner();

		CLASS(Component::Owner, agm::reflection::NullClass);

		/////////////////////////////////////////////////////////////
		/**
		* Set the Name of Owner
		* @param value_, String, the Name of Owner
		*/
		/**
		* Get the Name of Owner
		* @return String, the Name of Owner
		*/
		PROPERTY(String      , Name);

		/**
		* Set the Tag of Owner
		* @param value_, String, the Tag of Owner
		*/
		/**
		* Get the Tag of Owner
		* @return String, the Tag of Owner
		*/
		PROPERTY(String      , Tag );

		/**
		* Set the Layer of Owner, Layer value is used for Camera or Collision Filtering
		* @param value_, unsigned int, the Layer of Owner
		*/
		/**
		* Get the Layer of Owner, Layer value is used for Camera or Collision Filtering
		* @return unsigned int, the Layer of Owner
		*/
		PROPERTY(unsigned int, Layer);

		/**
		* Set the Activation State of Owner, if the owner is not active, it become non functional as well as all of its component
		* @param value_, bool, the Activation State of Owner
		*/
		/**
		* Get the Activation State of Owner, if the owner is not active, it become non functional as well as all of its component
		* @return bool, the Activation State of Owner
		*/
		PROPERTY(bool        , Active);

		/**
		* Set the Static State of Owner, if the component is not static, it will be optimized for physics 
		* @param value_, bool, the Static State of Owner
		*/
		/**
		* Get the Static State of Owner, if the component is not static, it will be optimized for physics 
		* @return bool, the Static State of Owner
		*/
		PROPERTY(bool        , Static);

		/**
		* Set the Transform of Owner, the transform will shared across the owner and component
		* @param value_, bool, the Transform of Owner
		*/
		/**
		* Get the Transform of Owner, the transform will shared across the owner and component
		* @return bool, the Transform of Owner
		*/
		PROPERTY_CUSTOM_FUNC
		(
			SRTTransform, Transform,
			{
				SRTTransform srt;

				const Matrix4 &mat = getLocalTransform();
				mat.ToSRT(srt.S(), srt.R(), srt.T());

				return srt;
			}
			,
			{
				Matrix4 mat;
				mat.FromSRT(value.S(), value.R(), value.T());

				setLocalTransform(mat);
			}
		);
		/////////////////////////////////////////////////////////////
	public:
		unsigned int getUniqueID() const;

		//void setName(const char *name_);
		//const char *getName() const;

		//void setTag(const char *tag_);
		//const char *getTag() const;
	
		//void setLayer(unsigned int layer_);
		//unsigned int getLayer() const;

		//void activate();
		//void deactivate();
		//bool isActive() const;

		/**
		* Get the Number of Components,  
		* @return int, the Num of Components in this Owner
		*/
		int getNumComponents() const;

		/**
		* Get the Components at index i  
		* @param index, int of the component
		* @return Component *, the Components at index i
		*/
		Component *getComponent(int i);

		/**
		* Get the Components at index i
		* @param index, int of the component
		* @return const Component *, the Components at index i
		*/
		const Component *getComponent(int i) const;

		/**
		* Get the Components by its name  
		* @param const char * of the component
		* @return const Component *, the Components with specified name
		*/
		Component *getComponent(const char *name_);

		/**
		* Get the Components by its name  
		* @param const char * of the component
		* @return const Component *, the Components with specified name
		*/
		const Component *getComponent(const char *name_) const;

		/**
		* Check if currently in Editor Mode
		* @param bool is in Editor Mode
		* @return	true if in editor mode
		*			false if in not editor mode
		*/
		virtual bool isEditorModeActive() const;

		/**
		* Set this owner in as the SELECTED Owner  
		*/
		void select();

		/**
		* If this owner is the SELECTED Owner, set it as unselected  
		*/
		void unselect();

		/**
		* Check if this owner in the SELECTED Owner  
		*/
		bool isSelected() const;

		/**
		* Get the SELECTED Owner  
		*/
		static Component::Owner *getSelected();

		/**
		* Construct the Component, it do construct for itself  by calling onConstruct method
		* and also call the construct method of all its component
		* @return true if construction is success, return false if fail
		*/
		bool construct();

		/**
		* Start the Component, it do start it for itself  by calling onStart method
		* and also call the start method of all its component
		*/
		void start();

		/**
		* PreUpdate the Component, it do preUpdate for itself  by calling onPreUpdate method
		* and also call the preUpdate method of all its component
		*/
		void preUpdate(float dt);

		/**
		* Update the Component, it do update for itself  by calling onUpdate method
		* and also call the update method of all its component
		*/
		void update(float dt);

		/**
		* PostUpdate the Component, it do postUpdate for itself  by calling onPostUpdate method
		* and also call the postUpdate method of all its component
		*/
		void postUpdate(float dt);

		/**
		* pause the Component, it do pause for itself by calling onPause method
		* and also call the onPause method of all its component
		*/
		void pause();

		/**
		* resume the Component, it do resume for itself by calling onResume method
		* and also call the onResume method of all its component
		*/
		void resume();

		/**
		* stop the Component, it do stop for itself by calling onStop method
		* and also call the onStop method of all its component
		*/
		void stop();

		/**
		* destruct the Component, it do destruct for itself by calling onDestruct method
		* and also call the onDestruct method of all its component
		*/
		void destruct();

		/**
		* call by Editor Service for Debug Rendering
		*/
		void debugRender(IComponentDebugRenderer &debugRenderer);

		/**
		* read method for Serialization
		* @param is, the InputStream for Serialization
		*/
		void read(InputStream &is);

		/**
		* write method for Serialization
		* @param os, the OutputStream for Serialization
		*/
		void write(OutputStream &os) const;
	protected:
		/**
		* Handle Construct Event of the Component
		* @return true if construction is success, return false if fail
		*/
		virtual bool onConstruct(){ return true; };

		/**
		* Handle Start Event of the Component
		*/
		virtual void onStart(){};

		/**
		* Handle onPreUpdate Event of the Component
		* @param delta elapse of the game cycle
		*/
		virtual void onPreUpdate(float dt){};

		/**
		* Handle Update Event of the Component
		* @param delta elapse of the game cycle
		*/
		virtual void onUpdate(float dt){};

		/**
		* Handle onPostUpdate Event of the Component
		* @param delta elapse of the game cycle
		*/
		virtual void onPostUpdate(float dt){};

		/**
		* Handle Pause Event of the Component
		*/
		virtual void onPause(){};

		/**
		* Handle Resume Event of the Component
		*/
		virtual void onResume(){};

		/**
		* Handle Stop Event of the Component
		*/
		virtual void onStop(){};

		/**
		* Handle Destruct Event of the Component
		*/
		virtual void onDestruct(){};

		/**
		* Handle the Debug Rendering Event
		*/
		virtual void onDebugRender(IComponentDebugRenderer &debugRenderer){};

		static Component::Owner *selected;		/**< the selected Components */
	private:
		void setUniqueID(unsigned int uniqueID_);
		int getComponentIdx(const char *name_) const;
	/////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		unsigned int		_uniqueID;
		Vector<Component *>	_components;
	};

/////////////////////////////////////////////////////////////
private:
	Component(const Component &component);
	Component &operator = (const Component &component);
public:
	Component(Component::Owner &owner_);
	virtual ~Component();

	CLASS(Component, agm::reflection::NullClass);

	/**
	* Set the Enabled State of Owner, if the component is not active, it become non functional.
	* @param value_, bool, the Enabled State of Owner
	*/
	/**
	* Get the Enabled State of Owner, if the component is not active, it become non functional.
	* @return bool, the Enabled State of Owner
	*/
	PROPERTY(bool, Enabled);

	/**
	* Set the Name of Owner
	* @param value_, String, the Name of Owner
	*/
	/**
	* Get the Name of Owner
	* @return String, the Name of Owner
	*/
	PROPERTY(String, Name);
/////////////////////////////////////////////////////////////
public:
	Component::Owner &getOwner();
	const Component::Owner &getOwner() const;

	virtual bool isEditorModeActive() const = 0;
protected:
private:
	/**
	* Construct the Component, it do construct for itself by calling onConstruct method
	* @return true if construction is success, return false if fail
	*/
	bool construct();

	/**
	* Start the Component, it do start it for itself  by calling onStart method
	*/
	void start();

	/**
	* PreUpdate the Component, it do preUpdate for itself  by calling onPreUpdate method
	*/
	void preUpdate(float dt);

	/**
	* Update the Component, it do update for itself  by calling onUpdate method
	*/
	void update(float dt);

	/**
	* PostUpdate the Component, it do postUpdate for itself  by calling onPostUpdate method
	*/
	void postUpdate(float dt);

	/**
	* pause the Component, it do pause for itself by calling onPause method
	*/
	void pause();

	/**
	* resume the Component, it do resume for itself by calling onResume method
	*/
	void resume();

	/**
	* stop the Component, it do stop for itself by calling onStop method
	*/
	void stop();

	/**
	* destruct the Component, it do destruct for itself by calling onDestruct method
	*/
	void destruct();

	/**
	* call by owner for Debug Rendering
	*/
	void debugRender(IComponentDebugRenderer &debugRenderer);

	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct(){ return true; };

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart(){};

	/**
	* Handle onPreUpdate Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onPreUpdate(float dt){};

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt){};

	/**
	* Handle onPostUpdate Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onPostUpdate(float dt){};

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause(){};

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume(){};

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop(){};

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct(){};

	/**
	* Handle the Debug Rendering Event
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer){};
private:
/////////////////////////////////////////////////////////////
public:
protected:
private:
	Component::Owner	&_owner;
};

};

#endif
