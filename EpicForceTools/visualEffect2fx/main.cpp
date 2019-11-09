#include <windows.h>
#include "tinyxml.h"
#include "GXDef.h"
#include "VisualEffect.h"
#include "VisualEffect2FX.h"

int main(int argc, char **argv)
{
	//VisualEffect::ResourceImporter resouceImporter("test");
	//if( !resouceImporter.onExportFile("test.visualEffect", "test.vfx") )
		//return false;

	//VisualEffect2FX visualEffect2FX;
	//if( !visualEffect2FX.convert("test.visualEffect2", "test.fx") )
		//return false;

	/*
	VisualEffect2GLSL visualEffect2GLSL;
	if( !visualEffect2GLSL.convert("test.xml", "test.glfx") )
		return false;
	*/

	// Make xml: <?xml ..><Hello>World</Hello>
	TiXmlDocument doc;
	TiXmlElement *element = new TiXmlElement("Hello");
	element->SetAttribute("param", "test");
	TiXmlText *text = new TiXmlText("World");
	element->LinkEndChild( text );
	//doc.LinkEndChild( decl );
	doc.LinkEndChild( element );
	doc.SaveFile( "madeByHand.xml" );

	return 0;
}