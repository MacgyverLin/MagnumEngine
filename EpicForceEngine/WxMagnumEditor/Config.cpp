#include "Config.h"

Config *Config::_instance = 0;

Config::Config()
: config(0)
, language(1)
{
	assert(_instance == 0);
	_instance = this;

	config = new wxConfig(wxT("config.ini"));
	readAllValues();
}

Config::~Config()
{
	assert(_instance!=0);
	_instance = 0;

	if(config)
	{
		writeAllValues();
		
		delete config;
		config = 0;
	}
}

Config &Config::instance()
{
	return *_instance;
}

void Config::setLanguage(int language_)
{
	language = language_;
}

void Config::setRecentProjectPaths(const Vector<wxString> &recentProjectPaths_)
{
	recentProjectPaths = recentProjectPaths_;
}

int Config::getLanguage() const
{
	return language;
}

const Vector<wxString> &Config::getRecentProjectPaths() const
{
	return recentProjectPaths;
}

void Config::readAllValues()
{
	assert(config);

	config->Read(_T("Setting/Language")					, &language);

	int numRecentProjects = 0;
	config->Read(_T("Setting/NumRecentProjects")		, &numRecentProjects);
	
	recentProjectPaths.resize(numRecentProjects);
	for(int i=0; i<recentProjectPaths.length(); i++)
	{
		wxString key;
		key.Printf(_T("Setting/RecentProjects%d"), i);
		
		config->Read(key, &recentProjectPaths[i]);
	}
}

void Config::writeAllValues()
{
	assert(config);

	config->Write(_T("Setting/Language")				, language);
	
	int numRecentProjects = recentProjectPaths.length();
	config->Write(_T("Setting/NumRecentProjects")		, numRecentProjects);
	for(int i=0; i<recentProjectPaths.length(); i++)
	{
		wxString key;
		key.Printf(_T("Setting/RecentProjects%d"), i);
		
		config->Write(key, recentProjectPaths[i]);
	}
}