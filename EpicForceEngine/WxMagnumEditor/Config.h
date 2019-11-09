///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Config_h_
#define _Config_h_

#include "wxdef.h"
#include "Array.h"
using namespace Magnum;

class Config
{
public:
	Config();
	~Config();

	static Config &instance();

	void setLanguage(int language);
	void setRecentProjectPaths(const Vector<wxString> &recentProjectPaths);

	int getLanguage() const;
	const Vector<wxString> &getRecentProjectPaths() const;
protected:
	void readAllValues();
	void writeAllValues();
private:

/////////////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
	static Config *_instance;
	
	wxConfig *config;

	int language;
	Vector<wxString> recentProjectPaths;

};

#endif