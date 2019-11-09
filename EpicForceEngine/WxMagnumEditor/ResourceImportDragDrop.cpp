#include "ResourceImportDragDrop.h"
#include "InputStream.h"
#include "OutputStream.h"

size_t ResourceImportDataObject::GetDataSize() const
{
	Vector<unsigned char> buffer;
	MemOutputStream os(buffer);

	os << _path;
	os << _extension;

	int a = os.tell();
	return os.tell();
}

bool ResourceImportDataObject::GetDataHere(void *buf) const
{
	Vector<unsigned char> buffer;
	MemOutputStream os(buffer);

	os << _path;
	os << _extension;

	memcpy(buf, &buffer[0], os.tell());

	return true;
}

bool ResourceImportDataObject::SetData(size_t WXUNUSED(len), const void *buf_)
{
	MemInputStream is((const unsigned char *)buf_, 100000);

	is >> _path;
	is >> _extension;

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceImportDropTarget::ResourceImportDropTarget(const char *extension_)
: _extension(extension_)
{
    SetDataObject(new ResourceImportDataObject("", extension_));
}

wxDragResult ResourceImportDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if ( !GetData() )
        return wxDragNone;

	ResourceImportDataObject *dobj = (ResourceImportDataObject *)m_dataObject;

	if(_extension==dobj->getExtension())
		return onDropResourceImport( dobj->getPath(), dobj->getExtension() ) ? def : wxDragNone;
	else
	{
		wxString message;
		message.Printf("This slot expects a \".%s\" file", _extension.text());
		wxMessageBox(message, "Error");
		
		return wxDragNone;
	}
}