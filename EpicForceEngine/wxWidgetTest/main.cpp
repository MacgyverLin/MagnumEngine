#include "wxdef.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


///////////////////////////////////////////////////////////////
//#define SIMPLE
//#define BUTTON
//#define COMMUNICATE
//#define SIMPLEMENU
//#define SUBMENU
//#define TOOLBAR
//#define TOOLBARS
//#define ABSOLUTELAYOUT
//#define BOXSIZER
//#define BORDER
//#define ALIGN
//#define GOTOCLASS
//#define GRIDSIZER
//#define FLEXGRIDSIZER
//#define MESSAGEDIALOG
//#define FILEDIALOG
//#define FONTDIALOG
//#define CUSTOMDIALOG
//#define CHECKBOX
//#define BITMAPBUTTON
//#define TOGGLEBUTTON
//#define STATICLINE
//#define STATICTEXT
//#define SLIDER
//#define DRAGNDROP
//#define CUSTOMWIDGET
//#define GRADIENT
//#define LINE
//#define PEN
//#define POINTS
//#define REGIONS
//#define SHAPES
//#define BURNING
#define COLORPICKERDIALOG

void initHandler()
{
	wxImage::AddHandler(new wxPNGHandler);
}

#if defined(SIMPLE)

#include "Simple.h"

bool MyApp::OnInit()
{
	initHandler();

    Simple *simple = new Simple(wxT("Simple"));
    simple->Show(true);

    return true;
}

#elif defined(BUTTON)

#include "Button.h"

bool MyApp::OnInit()
{
	initHandler();

    Button *btnapp = new Button(wxT("Button"));
    btnapp->Show(true);

    return true;
}

#elif defined(COMMUNICATE)

#include "Communicate.h"

bool MyApp::OnInit()
{
	initHandler();

    Communicate *communicate = new Communicate(wxT("Widgets communicate"));
    communicate->Show(true);

    return true;
}

#elif defined(SIMPLEMENU)

#include "SimpleMenu.h"

bool MyApp::OnInit()
{
	initHandler();

    SimpleMenu *menu = new SimpleMenu(wxT("Simple Menu"));
    menu->Show(true);

    return true;
}

#elif defined(SUBMENU)

#include "SubMenu.h"

bool MyApp::OnInit()
{
	initHandler();

    SubMenu *smenu = new SubMenu(wxT("Submenu"));
    smenu->Show(true);

    return true;
}

#elif defined(TOOLBAR)

#include "Toolbar.h"

bool MyApp::OnInit()
{
	initHandler();

    Toolbar *toolbar = new Toolbar(wxT("Toolbar"));
    toolbar->Show(true);

    return true;
}

#elif defined(TOOLBARS)

#include "Toolbars.h"

bool MyApp::OnInit()
{
	initHandler();

    Toolbars *toolbars = new Toolbars(wxT("Toolbars"));
    toolbars->Show(true);

    return true;
}

#elif defined(ABSOLUTELAYOUT)

#include "Absolute.h"

bool MyApp::OnInit()
{
	initHandler();

    Absolute *absolute = new Absolute(wxT("Absolute"));
    absolute->Show(true);

    return true;
}

#elif defined(BOXSIZER)

#include "BoxSizer.h"

bool MyApp::OnInit()
{
	initHandler();

    BoxSizer *boxsizer = new BoxSizer(wxT("BoxSizer"));
    boxsizer->Show(true);

    return true;
}

#elif defined(BORDER)

#include "Border.h"

bool MyApp::OnInit()
{
	initHandler();

    Border *border = new Border(wxT("Border"));
    border->Show(true);

    return true;
}

#elif defined(ALIGN)

#include "Align.h"

bool MyApp::OnInit()
{
	initHandler();

    Align *align = new Align(wxT("Align"));
    align->Show(true);

    return true;
}

#elif defined(GOTOCLASS)

#include "GotoClass.h"

bool MyApp::OnInit()
{
	initHandler();

    GotoClass *gotoclass = new GotoClass(wxT("GotoClass"));
    gotoclass->Show(true);

    return true;
}

#elif defined(GRIDSIZER)

#include "GridSizer.h"

bool MyApp::OnInit()
{
	initHandler();

    GridSizer *gs = new GridSizer(wxT("GridSizer"));
    gs->Show(true);

    return true;
}

#elif defined(FLEXGRIDSIZER)

#include "FlexGridSizer.h"

bool MyApp::OnInit()
{
	initHandler();

    FlexGridSizer *fgs = new FlexGridSizer(wxT("FlexGridSizer"));
    fgs->Show(true);

    return true;
}

#elif defined(MESSAGEDIALOG)

#include "MessageDialog.h"

bool MyApp::OnInit()
{
	initHandler();

    MessageDialog *md = new MessageDialog(wxT("MessageDialog"));
    md->Show(true);

    return true;
}

#elif defined(FILEDIALOG)

#include "FileDialog.h"

bool MyApp::OnInit()
{
	initHandler();

    FileDialog *fd = new FileDialog(wxT("FileDialog"));
    fd->Show(true);

    return true;
}

#elif defined(FONTDIALOG)

#include "FontDialog.h"

bool MyApp::OnInit()
{
	initHandler();

    FontDialog *fd = new FontDialog(wxT("FontDialog"));
    fd->Show(true);

    return true;
}

#elif defined(CUSTOMDIALOG)

#include "CustomDialog.h"

bool MyApp::OnInit()
{
	initHandler();

    CustomDialog *cd = new CustomDialog(wxT("CustomDialog"));
    cd->Show(true);

    return true;
}

#elif defined(CHECKBOX)

#include "CheckBox.h"

bool MyApp::OnInit()
{
	initHandler();

    CheckBox *cb = new CheckBox(wxT("CheckBox"));
    cb->Show(true);

    return true;
}

#elif defined(BITMAPBUTTON)

#include "BitmapButton.h"

bool MyApp::OnInit()
{
	initHandler();

    BitmapButton *bb = new BitmapButton(wxT("BitmapButton"));
    bb->Show(true);

    return true;
}

#elif defined(TOGGLEBUTTON)

#include "ToggleButton.h"

bool MyApp::OnInit()
{
	initHandler();

    ToggleButton *tb = new ToggleButton(wxT("ToggleButton"));
    tb->Show(true);

    return true;
}

#elif defined(STATICLINE)

#include "StaticLine.h"

bool MyApp::OnInit()
{
	initHandler();

    StaticLine *sl = new StaticLine(wxT("StaticLine"));
    sl->Show(true);

    return true;
}

#elif defined(STATICTEXT)

#include "StaticText.h"

bool MyApp::OnInit()
{
	initHandler();

    StaticText *st = new StaticText(wxT("StaticText"));
    st->Show(true);

    return true;
}

#elif defined(SLIDER)

#include "Slider.h"

bool MyApp::OnInit()
{
	initHandler();

    Slider *sl = new Slider(wxT("Slider"));
    sl->Show(true);

    return true;
}

#elif defined(DRAGNDROP)

#include "DragNDrop.h"

bool MyApp::OnInit()
{
	initHandler();

    TextDrop *td = new TextDrop(wxT("TextDrop"));
    td->Show(true);

    return true;
}

#elif defined(GRADIENT)

#include "Gradient.h"

bool MyApp::OnInit()
{
	initHandler();

    Gradient *gradient = new Gradient(wxT("Gradient"));
    gradient->Show(true);

    return true;
}

#elif defined(LINE)

#include "Line.h"

bool MyApp::OnInit()
{
	initHandler();

    Line *line = new Line(wxT("Line"));
    line->Show(true);

    return true;
}

#elif defined(PEN)

#include "Pen.h"

bool MyApp::OnInit()
{
	initHandler();

    Pen *pen = new Pen(wxT("Pen"));
    pen->Show(true);

    return true;
}

#elif defined(POINTS)

#include "Points.h"

bool MyApp::OnInit()
{
	initHandler();

    Points *points = new Points(wxT("Points"));
    points->Show(true);

    return true;
}

#elif defined(REGIONS)

#include "Regions.h"

bool MyApp::OnInit()
{
	initHandler();

    Regions *regions = new Regions(wxT("Regions"));
    regions->Show(true);

    return true;
}

#elif defined(SHAPES)

#include "Shapes.h"

bool MyApp::OnInit()
{
	initHandler();

    Shapes *shapes = new Shapes(wxT("Shapes"));
    shapes->Show(true);

    return true;
}

#elif defined(BURNING)

#include "Burning.h"

bool MyApp::OnInit()
{
	initHandler();

    Burning *burning = new Burning(wxT("Burning"));
    burning->Show(true);

    return true;
}

#else COLORPICKERDIALOG

#include "ColorPickerDialog.h"

bool MyApp::OnInit()
{
	initHandler();

    ColorPickerDialog *colorPickerDialog = new ColorPickerDialog(wxT("ColorPickerDialog"));
    colorPickerDialog->Show(true);

    return true;
}

#endif
