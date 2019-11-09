#ifndef _ResourceImportDragDrop_h_
#define _ResourceImportDragDrop_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
using namespace Magnum;

class ResourceImportDataObject : public wxDataObjectSimple
{
public:
    // ctor: you can specify the text here or in SetText(), or override
    // GetText()
    ResourceImportDataObject(const char *path_, const char *extension_)
	: wxDataObjectSimple("ResourceImportDataObject")
    , _path(path_)
	, _extension(extension_)
	{
	}

    // virtual functions which you may override if you want to provide text on
    // demand only - otherwise, the trivial default versions will be used
    // implement base class pure virtuals
    // ----------------------------------

    // some platforms have 2 and not 1 format for text data
    virtual size_t GetDataSize() const;
    virtual bool GetDataHere(void *buf) const;
    virtual bool SetData(size_t len, const void *buf);
    // Must provide overloads to avoid hiding them (and warnings about it)
    virtual size_t GetDataSize(const wxDataFormat&) const
    {
        return GetDataSize();
    }
    virtual bool GetDataHere(const wxDataFormat&, void *buf) const
    {
        return GetDataHere(buf);
    }
    virtual bool SetData(const wxDataFormat&, size_t len, const void *buf)
    {
        return SetData(len, buf);
    }

	const char *getPath() const
	{
		return _path.text();
	}

	const char *getExtension() const
	{
		return _extension.text();
	}
private:
    String _path;
	String _extension;

    DECLARE_NO_COPY_CLASS(ResourceImportDataObject)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class ResourceImportDropTarget : public wxDropTarget
{
public:
    ResourceImportDropTarget(const char *extension_);

    virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

    virtual bool onDropResourceImport(const char *path, const char *extension) = 0;
private:
    DECLARE_NO_COPY_CLASS(ResourceImportDropTarget)
	
	String _extension;
};

#endif