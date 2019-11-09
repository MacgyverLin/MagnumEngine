///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "SceneCollision.h"
using namespace EpicForce; 

//////////////////////////////////////////////////////
SceneCollision::HeightField::HeightField() 
: xmin(0), xmax(0)
, zmin(0), zmax(0)
, gridSizeX(0), gridSizeZ(0) 
, numGridX(0), numGridZ(0)
, collisionMode(HF_CM_REPORT_ALWAYS)
, enabled(true)
{
}

SceneCollision::HeightField::~HeightField()
{
}

void SceneCollision::HeightField::init(float xmin_, float xmax_, float zmin_, float zmax_,
											int numGridX_, int numGridZ_,
											float gridSizeX_, float gridSizeZ_, 
											const Vector<float> &heights_)
{
	xmin = xmin_; 
	xmax = xmax_; 
	zmin = zmin_; 
	zmax = zmax_;
	gridSizeX = gridSizeX_;
	gridSizeZ = gridSizeZ_;

	numGridX  = numGridX_;
	numGridZ  = numGridZ_;
	heights.resize( heights_.length() );
	for(int i=0; i<heights.length(); i++)
	{
		heights[i] = heights_[i];
	}
}

void SceneCollision::HeightField::setEnabled(bool enabled_)
{
	enabled = enabled_;
}

bool SceneCollision::HeightField::getEnabled() const
{
	return enabled;
}

void SceneCollision::HeightField::setMode(CollisionMode collisionMode_)
{
	collisionMode = collisionMode_;
}

SceneCollision::HeightField::CollisionMode SceneCollision::HeightField::getMode()
{
	return collisionMode;
}

int SceneCollision::HeightField::getNumGridX()
{
	return numGridX;
}

int SceneCollision::HeightField::getNumGridZ()
{
	return numGridZ;
}

float SceneCollision::HeightField::getGridSizeX()
{
	return gridSizeX;
}

float SceneCollision::HeightField::getGridSizeZ()
{
	return gridSizeZ;
}

bool SceneCollision::HeightField::isInsideRegion(const float &x_, const float &z_)
{
	return x_>=xmin && x_<xmax && z_>=zmin && z_<zmax;
}

bool SceneCollision::HeightField::isInsideRegion(const Vector3 &point_)
{
	return isInsideRegion(point_.X(), point_.Z());
}

float SceneCollision::HeightField::getHeightAt(const float &x_, const float &z_)
{
	if( isInsideRegion(x_, z_) )
	{
		int xidx = Math::Floor((x_ - xmin) / gridSizeX);
		int zidx = Math::Floor((z_ - zmin) / gridSizeZ);
		float xmod = (x_ - xmin) - xidx * gridSizeX;
		float zmod = (z_ - zmin) - zidx * gridSizeZ;
		
		//debug("xidx=%d, zidx=%d", xidx, zidx); 
        
		// +----------> +X
		// | h1       h2
		// |  \________
		// |  |\      |
		// |  | \     |
		// |  |  \    |
		// |  |   \   |
		// |  |    \  |
		// |  |     \ |
		// |  |______\|
		// | h4       h3
		//+Z
		if(xmod>=zmod)
		{
			int i = zidx * (numGridX+1) + xidx;

			float h1 = heights[i                   ];
			float h2 = heights[i + 1               ];
			float h3 = heights[i + 1 + (numGridX+1)];

			//return h1 + xmod * (h2-h1) + zmod * (h3-h1);
			return h2 + (gridSizeX-xmod)/gridSizeX * (h1-h2) + zmod/gridSizeZ * (h3-h2);
		}
		else
		{
			int i = zidx * (numGridX+1) + xidx;

			float h1 = heights[i                   ];
			float h3 = heights[i + 1 + (numGridX+1)];
			float h4 = heights[i     + (numGridX+1)];

			//return h4 + xmod * (h3-h4) + zmod * (h1-h4);
			return h4 + xmod/gridSizeX * (h3-h4) + (gridSizeZ-zmod)/gridSizeZ  * (h1-h4);
		}
	} 
	else
	{
		return Math::MIN_REAL; 
	}
}

float SceneCollision::HeightField::getHeightAt(const Vector3 &point_)
{
	return getHeightAt(point_.X(), point_.Z());
}

void SceneCollision::HeightField::read(InputStream &is)
{
	is >> name;
	is >> xmin >> xmax >> zmin >> zmax;
	is >> numGridX  >> numGridZ;
	is >> gridSizeX >> gridSizeZ;
	is >> heights;
	//heights.resize((numGridX+1)*(numGridZ+1));
	//for(int i=0; i<heights.length(); i++)
		//is >> heights[i];
}

void SceneCollision::HeightField::write(OutputStream &os) const
{
	os << name;
	os << xmin << xmax;
	os << zmin << zmax;
	os << numGridX  << numGridZ;
	os << gridSizeX << gridSizeZ;
	os << heights;
}

bool SceneCollision::HeightField::test(const Vector3 &point_)
{
	if( isInsideRegion(point_.X(), point_.Z()) )
		return point_.Y() < getHeightAt(point_);
	else
		return false;
}

bool SceneCollision::HeightField::testSphere(SceneCollision::CastInfo &castInfo_)
{
	if(!enabled)
		return false;

	bool collision = false;

	if( isInsideRegion(castInfo_.inputPosition.X(), castInfo_.inputPosition.Z()) )
	{
		float foot = castInfo_.inputPosition.Y() - castInfo_.inputRadius;
		float dist = foot - getHeightAt(castInfo_.inputPosition);
		switch(collisionMode)
		{
			case HF_CM_REPORT_LESSTHAN:
				collision = (dist <  0);
			break;
			case HF_CM_REPORT_EQUAL:
				collision = (dist == 0);
			break;
			case HF_CM_REPORT_GREATERTHAN:
				collision = (dist >  0);
			break;
			default:
			case HF_CM_REPORT_ALWAYS:
				collision = true;
			break;
		};
		
		if(collision)
			castInfo_.outputPosition += Vector3(0, -dist, 0);
		
		return collision;
	}
	else
	{
		return false;
	}
}

//----------------------------------------------------
SceneCollision::HeightFieldList::HeightFieldList()
{
}

SceneCollision::HeightFieldList::~HeightFieldList()
{
}

SceneCollision::HeightFieldList &SceneCollision::HeightFieldList::operator += (const SceneCollision::HeightFieldList &other)
{
	int oldLength = heightFields.length();
	heightFields.resize(oldLength + other.heightFields.length());

	for(int i=0; i<other.heightFields.length(); i++)
	{
		heightFields[i+oldLength] = other.heightFields[i];
	}

	return *this;
}

int SceneCollision::HeightFieldList::getNumHeightFields() const
{
	return heightFields.length();
}

SceneCollision::HeightField &SceneCollision::HeightFieldList::getHeightField(int i_)
{
	return heightFields[i_];
}

const SceneCollision::HeightField &SceneCollision::HeightFieldList::getHeightField(int i_) const
{
	return heightFields[i_];
}

bool SceneCollision::HeightFieldList::isHeightFieldExists(const char *name_) const
{
	int idx = getHeightFieldIdx(name_);
	
	return idx>=0 && idx<heightFields.length();
}

int SceneCollision::HeightFieldList::getHeightFieldIdx(const char *name_) const
{
	for(int i=0; i<heightFields.length(); i++)
	{
		if(heightFields[i].name==name_)
			return i;
	}

	return -1;	
}

void SceneCollision::HeightFieldList::setHeightFieldEnabled(int i, bool enabled_)
{
	if(i>=0 && i<heightFields.length())
		heightFields[i].setEnabled(enabled_);
}

bool SceneCollision::HeightFieldList::getHeightFieldEnabled(int i) const
{
	if(i>=0 && i<heightFields.length())
		return heightFields[i].getEnabled();
	else
		return false;
}


void SceneCollision::HeightFieldList::read(InputStream &is)
{
	is >> heightFields;
}

void SceneCollision::HeightFieldList::write(OutputStream &os) const
{
	os << heightFields;
}

bool SceneCollision::HeightFieldList::test(const Vector3 &point_)
{
	for(int i=0; i<heightFields.length(); i++)
	{
		if(heightFields[i].test(point_))
			return true;
	}

	return false;
}

bool SceneCollision::HeightFieldList::testSphere(SceneCollision::CastInfo &castInfo_)
{
	castInfo_.outputFraction  = 1.0f;

	for(int i=0; i<heightFields.length(); i++)
	{
		if(heightFields[i].testSphere(castInfo_))
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////
SceneCollision::Brush::Brush() 
: enabled(true)
{
}

SceneCollision::Brush::~Brush()
{
}

bool SceneCollision::Brush::add(const Plane3 &plane_)
{
	for(int i=0; i<planes.length(); i++)
	{
		if(planes[i].isCoplanar(plane_) )
			return false;
	}	

	planes.push() = plane_;

	return true;
}

void SceneCollision::Brush::setEnabled(bool enabled_)
{
	enabled = enabled_;
}

bool SceneCollision::Brush::getEnabled() const
{
	return enabled;
}

void SceneCollision::Brush::read(InputStream &is)
{
	is >> name;
	is >> planes;

	/*
	int numPlanes;
	is >> numPlanes;
	assert(numPlanes!=0);

	planes.resize(numPlanes);
	for(int i=0; i<numPlanes; i++)
	{
		is >> planes[i].Normal[0] >> planes[i].Normal[1] >> planes[i].Normal[2] >> planes[i].Constant;
	}
	*/
}

void SceneCollision::Brush::write(OutputStream &os) const
{
	os << name;
	os << planes;
}

void SceneCollision::Brush::testSphere(SceneCollision::CastInfo &castInfo_)
{
	if(!enabled)
		return;

	float		startFraction	= -1.0f;
	float		endFraction		=  1.0f;
	bool		 startsOut		= false;
	bool		endsOut			= false;
	Vector3		*outputNormal	= 0;
#ifdef SMOOTHER_WII_COLLISION
	float		EPSILON			= 0.0001f;
#else
	float		EPSILON			= 0.01f;	
#endif

	if(planes.length()==0)
		return;

	float		startsIn_startDistance	= Math::MIN_REAL;
	Vector3		*startsIn_outputNormal	= &planes[0].Normal;

	for (int i=0; i<planes.length(); i++)
	{
		float startDistance, endDistance;
		float offset = -castInfo_.inputRadius;
		#if 0
		if(info_.type == TraceInfo::POINT_CAST)
		{
			offset = 0;
		}
		else if (info_.type == TraceInfo::SPHERE_CAST)
		{
			offset = -info_.inputRadius;
		}
		else if (info_.type == TraceInfo::AABB_CAST)
		{
			offset = 0;
			for (int j=0; j<3; j++)
				offset +=  -Math::FAbs(planes[i].Normal[j] * info_.inputExtent[j]);
		}
		else if (info_.type == TraceInfo::BOX_CAST)
		{
			offset = 0;
			for (int j=0; j<3; j++)
				offset +=  -Math::FAbs(planes[i].Normal.Dot(info_.inputAxis[j]) * info_.inputExtent[j]);
		}
		#endif
		startDistance = planes[i].Normal.Dot(castInfo_.inputPosition						    	) - planes[i].Constant + offset;
		endDistance   = planes[i].Normal.Dot(castInfo_.inputPosition + castInfo_.inputDistance) - planes[i].Constant + offset;

		if (startDistance > 0)
			startsOut = true;
		else
		{
			if(startsIn_startDistance < startDistance)
			{
				startsIn_startDistance	= startDistance;
				startsIn_outputNormal	= &planes[i].Normal;
			}
		}
		if (endDistance > 0)
			endsOut = true;

		// make sure the trace isn't completely on one side of the brush
		if (startDistance > 0 && endDistance > 0)
		{   // both are in front of the plane, its outside of this brush
			return;
		}
		if (startDistance <= 0 && endDistance <= 0)
		{   // both are behind this plane, it will get clipped by another one
			continue;
		}

		if (startDistance > endDistance)
		{   // line is entering into the brush
			float fraction = (startDistance - EPSILON) / (startDistance - endDistance);
			if (fraction > startFraction)
			{
				startFraction = fraction;
				outputNormal  = &planes[i].Normal;
			}
		}
		else
		{   // line is leaving the brush
			float fraction = (startDistance + EPSILON) / (startDistance - endDistance);
			if (fraction < endFraction)
				endFraction = fraction;
		}
	}

	if(!startsOut)
	{
		castInfo_.outputStartOut = false;
		castInfo_.outputFraction = -0.1f;
		castInfo_.outputNormal   = startsIn_outputNormal;
		//debug("%d, info_.outputNormal= %x, startsIn_outputNormal=%x", 
			   //planes.length(), info_.outputNormal, startsIn_outputNormal);

		if (endsOut == false)
			castInfo_.outputAllSolid = true;

		return;
	}

	if (startFraction < endFraction)
	{
		if (startFraction > -1 && startFraction < castInfo_.outputFraction)
		{
			//if (startFraction < 0) // correction for floating point error.
				//startFraction = 0;
			castInfo_.outputFraction = startFraction;
			castInfo_.outputNormal   = outputNormal;
		}
	}
}

//-------------------------------------------------------------
SceneCollision::BrushList::BrushList()
{
}

SceneCollision::BrushList::~BrushList()
{
}

SceneCollision::BrushList &SceneCollision::BrushList::operator += (const SceneCollision::BrushList &other)
{
	int oldLength = brushes.length();
	brushes.resize(oldLength + other.brushes.length());

	for(int i=0; i<other.brushes.length(); i++)
	{
		brushes[i+oldLength] = other.brushes[i];
	}

	return *this;
}

int SceneCollision::BrushList::getNumBrushes() const
{
	return brushes.length();
}

SceneCollision::Brush &SceneCollision::BrushList::getBrush(int i_)
{
	return brushes[i_];
}

const SceneCollision::Brush &SceneCollision::BrushList::getBrush(int i_) const
{
	return brushes[i_];
}

bool SceneCollision::BrushList::isBrushExists(const char *name_) const
{
	int idx = getBrushIdx(name_);
	
	return idx>=0 && idx<brushes.length();
}

int SceneCollision::BrushList::getBrushIdx(const char *name_) const
{
	for(int i=0; i<brushes.length(); i++)
	{
		if(brushes[i].name==name_)
			return i;
	}

	return -1;	
}

void SceneCollision::BrushList::setBrushEnabled(int i, bool enabled_)
{
	if(i>=0 && i<brushes.length())
		brushes[i].setEnabled(enabled_);
}

bool SceneCollision::BrushList::getBrushEnabled(int i) const
{
	if(i>=0 && i<brushes.length())
		return brushes[i].getEnabled();
	else
		return false;
}


void SceneCollision::BrushList::read(InputStream &is)
{
	is >> brushes;
}

void SceneCollision::BrushList::write(OutputStream &os) const
{
	os << brushes;
}

bool SceneCollision::BrushList::testSphere(SceneCollision::CastInfo &castInfo_)
{
	castInfo_.outputStartOut  = true;
	castInfo_.outputAllSolid  = false;
	castInfo_.outputFraction  = 1.0f;
	castInfo_.outputNormal    = 0;

	for(int i=0; i<brushes.length(); i++)
		brushes[i].testSphere(castInfo_);

	bool collision = false;
	if (castInfo_.outputFraction == 1.0f)
	{	
		// nothing blocked the trace
		collision = false;
		castInfo_.outputPosition = castInfo_.inputPosition + castInfo_.inputDistance;
	}
	else
	{	
		// collided with something 
		collision = true;
		castInfo_.outputPosition = castInfo_.inputPosition + castInfo_.outputFraction * castInfo_.inputDistance;
	}

	return collision;
}

//////////////////////////////////////////////////////////////////////
SceneCollision::Data::Data()
{
}

SceneCollision::Data::~Data()
{
}

SceneCollision::Data &SceneCollision::Data::operator += (const SceneCollision::Data &other)
{
	brushList		+= other.brushList;
	heightFieldList += other.heightFieldList;

	return *this;
}

int SceneCollision::Data::getNumHeightFields() const
{
	return heightFieldList.getNumHeightFields();
}

SceneCollision::HeightField &SceneCollision::Data::getHeightField(int i_)
{
	return heightFieldList.getHeightField(i_);
}

const SceneCollision::HeightField &SceneCollision::Data::getHeightField(int i_) const
{
	return heightFieldList.getHeightField(i_);
}

bool SceneCollision::Data::isHeightFieldExists(const char *name_) const
{
	return heightFieldList.isHeightFieldExists(name_);
}

int SceneCollision::Data::getHeightFieldIdx(const char *name_) const
{
	return heightFieldList.getHeightFieldIdx(name_);
}

void SceneCollision::Data::setHeightFieldEnabled(int i_, bool enabled_)
{
	heightFieldList.setHeightFieldEnabled(i_, enabled_);
}

bool SceneCollision::Data::getHeightFieldEnabled(int i_) const
{
	return heightFieldList.getHeightFieldEnabled(i_);
}

int SceneCollision::Data::getNumBrushes() const
{
	return brushList.getNumBrushes();
}

SceneCollision::Brush &SceneCollision::Data::getBrush(int i_)
{
	return brushList.getBrush(i_);
}

const SceneCollision::Brush &SceneCollision::Data::getBrush(int i_) const
{
	return brushList.getBrush(i_);
}

bool SceneCollision::Data::isBrushExists(const char *name_) const
{
	return brushList.isBrushExists(name_);
}

int SceneCollision::Data::getBrushIdx(const char *name_) const
{
	return brushList.getBrushIdx(name_);
}

void SceneCollision::Data::setBrushEnabled(int i_, bool enabled_)
{
	brushList.setBrushEnabled(i_, enabled_);
}

bool SceneCollision::Data::getBrushEnabled(int i_) const
{
	return brushList.getBrushEnabled(i_);
}

bool SceneCollision::Data::test(Vector3 &point_)
{
	return false;
}

bool SceneCollision::Data::testSphere(SceneCollision::CastInfo &castInfo_)
{
	castInfo_.collided			= false;
	castInfo_.outputPosition	= castInfo_.inputPosition;

	bool temp1=false, temp2=false, temp3=false;
	do
	{
		temp2 |= brushList.testSphere(castInfo_);
		
		if(!castInfo_.outputStartOut)
		{
			assert(castInfo_.outputNormal);
			castInfo_.outputPosition = castInfo_.inputPosition + *castInfo_.outputNormal * (-castInfo_.outputFraction);
			break;
		}
		else
		{
			if(castInfo_.outputFraction<=0.99f)
			{
				assert(castInfo_.outputNormal);
				Vector3 dist_n		= *castInfo_.outputNormal * castInfo_.inputDistance.Dot(*castInfo_.outputNormal);
				Vector3 dist_t		= castInfo_.inputDistance - dist_n;
				dist_t				= dist_t * (1.0f - castInfo_.outputFraction);

				castInfo_.inputPosition	= castInfo_.outputPosition;
				castInfo_.inputDistance	= dist_t;
			}
			else
			{
				castInfo_.outputPosition = castInfo_.inputPosition + castInfo_.inputDistance;
			}
		}
	}while(castInfo_.outputFraction<=0.99f);

	temp3 = heightFieldList.testSphere(castInfo_);

	castInfo_.collided = temp2 || temp3;
	if(castInfo_.collided)
	{
		if(castInfo_.outputNormal)
		{
			castInfo_.contactPoint		= castInfo_.outputPosition - (*castInfo_.outputNormal) * castInfo_.inputRadius;
			castInfo_.contactNormal		= *castInfo_.outputNormal;
			castInfo_.penetrationDepth	= castInfo_.inputRadius;
		}
		else
		{
			castInfo_.contactPoint		= castInfo_.outputPosition - Vector3::UNIT_Y * castInfo_.inputRadius;
			castInfo_.contactNormal		= Vector3::UNIT_Y;
			castInfo_.penetrationDepth	= castInfo_.inputRadius;
		}
	}

	return castInfo_.collided;
}

void SceneCollision::Data::read(InputStream &is)
{
	is >> platform;
	is >> version;

	is >> brushList;
	is >> heightFieldList;
}

void SceneCollision::Data::write(OutputStream &os) const
{
	os << platform;
	os << version;

	os << brushList;
	os << heightFieldList;
}

//////////////////////////////////////////////////////////////////////
#ifdef EXPORTER
#else
SceneCollision::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}

SceneCollision::Resource::~Resource()
{
	onDestroy();
}

unsigned char *SceneCollision::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void SceneCollision::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;

	buffer.destroy();
}

void SceneCollision::Resource::onDestroy()
{
	buffer.destroy();
}

int SceneCollision::Resource::getNumHeightFields() const
{
	return data.getNumHeightFields();
}

SceneCollision::HeightField &SceneCollision::Resource::getHeightField(int i_)
{
	return data.getHeightField(i_);
}

const SceneCollision::HeightField &SceneCollision::Resource::getHeightField(int i_) const
{
	return data.getHeightField(i_);
}

bool SceneCollision::Resource::isHeightFieldExists(const char *name_) const
{
	return data.isHeightFieldExists(name_);
}

int SceneCollision::Resource::getHeightFieldIdx(const char *name_) const
{
	return data.getHeightFieldIdx(name_);
}

void SceneCollision::Resource::setHeightFieldEnabled(int i_, bool enabled_)
{
	data.setHeightFieldEnabled(i_, enabled_);
}

bool SceneCollision::Resource::getHeightFieldEnabled(int i_) const
{
	return data.getHeightFieldEnabled(i_);
}

int SceneCollision::Resource::getNumBrushes() const
{
	return data.getNumBrushes();
}

SceneCollision::Brush &SceneCollision::Resource::getBrush(int i_)
{
	return data.getBrush(i_);
}

const SceneCollision::Brush &SceneCollision::Resource::getBrush(int i_) const
{
	return data.getBrush(i_);
}

bool SceneCollision::Resource::isBrushExists(const char *name_) const
{
	return data.isBrushExists(name_);
}

int SceneCollision::Resource::getBrushIdx(const char *name_) const
{
	return data.getBrushIdx(name_);
}

void SceneCollision::Resource::setBrushEnabled(int i_, bool enabled_)
{
	data.setBrushEnabled(i_, enabled_);
}

bool SceneCollision::Resource::getBrushEnabled(int i_) const
{
	return data.getBrushEnabled(i_);
}

bool SceneCollision::Resource::test(Vector3 &point_)
{
	return data.test(point_);
}

bool SceneCollision::Resource::testSphere(SceneCollision::CastInfo &castInfo_)
{
	return data.testSphere(castInfo_);
}

////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
SceneCollision::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

SceneCollision::ResourceImporter::~ResourceImporter()
{
}

bool SceneCollision::ResourceImporter::initiate()
{
	return true;
}

void SceneCollision::ResourceImporter::terminate()
{
}

bool SceneCollision::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool SceneCollision::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return defaultDeleteFileFunc(srcFilename_);
}
#endif
////////////////////////////////////////////////////////////////
SceneCollision *SceneCollision::_instance = 0;

SceneCollision::SceneCollision()
: Collision(CT_SCENE)
{
	assert(_instance==0);

	_instance = this;

	//specific catagory for the background scene collision
	setCategory(1);
	//scene collision responds to no collisions
	setAttribute(0);
}

SceneCollision::~SceneCollision()
{
	assert(_instance!=0);

	_instance = 0;

	destruct();
}

SceneCollision &SceneCollision::instance()
{
	assert(_instance);

	return *_instance;
}

bool SceneCollision::construct(const char *name_)
{
	return append(name_);
}

bool SceneCollision::append(const char *name_)
{
	SceneCollision::Resource *resource = SceneCollision::Resource::get(name_);
	if(!resource)
		return false;

	sceneData += resource->data;

	return true;
}

void SceneCollision::destruct()
{
}

bool SceneCollision::test(Vector3 &point_)
{
	return sceneData.test(point_);
}

bool SceneCollision::testSphere(SceneCollision::CastInfo &castInfo_)
{
	return sceneData.testSphere(castInfo_);
}

#endif