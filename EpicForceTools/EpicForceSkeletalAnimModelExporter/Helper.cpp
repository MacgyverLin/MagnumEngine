#include "Helper.h"
#include "Array.h"
using namespace EpicForce;
using namespace std;

String Helper::trim(const String &str)
{
	int start = str.find_first_not_of(" ");
	int end   = str.find_last_not_of(" ");

	return str.substr(start, end-start+1);
}

void Helper::tokenize(Vector<String> &tokens, const String &str, const String &delimiters)
{
	tokens.clear();

	// skip delimiters at beginning.
	int lastPos = str.find_first_not_of(delimiters, 0);
	
	// find first "non-delimiter".
	int pos = str.find_first_of(delimiters, lastPos);

	while( pos!=-1 || lastPos!=-1 )
	{
		// found a token, add it to the vector.
		tokens.push() = str.substr(lastPos, pos - lastPos).text();

		tokens.back() = trim(tokens.back());
	
		// skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
	
		// find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void Helper::parseValues(Vector<String> &values, const String &str)
{
	values.clear();

	tokenize(values, str.text(), ",;");
}

bool Helper::parseDefaultValues(Vector<String> &values, const String &str)
{
	int start = str.find_first_of("({");
	start += 1;

	int end   = str.find_last_of(")}");

	parseValues(values, str.substr(start, end-start) );

	return values.length()!=0;
}

#include "decomp.h"

void Helper::convertMatrixToVector10(Vector3 &t, Quaternion &q, Vector3 &k, const GMatrix &tm, float metersPerUnit)
{
	AffineParts ap;
	float rotAngle;
	Point3 rotAxis;
	float scaleAxAngle;
	Point3 scaleAxis;
	::Matrix3 m = tm.ExtractMatrix3();

	decomp_affine(m, &ap);

	// Quaternions are dumped as angle axis.
	AngAxisFromQ(ap.q, &rotAngle, rotAxis);
	AngAxisFromQ(ap.u, &scaleAxAngle, scaleAxis);

	t = Vector3(ap.t.x, ap.t.y, ap.t.z)*metersPerUnit;
	q = Quaternion(ap.q.w, ap.q.x, ap.q.y, ap.q.z);
	k = Vector3(ap.k.x, ap.k.y, ap.k.z);
	//ap.t.x,ap.t.y,ap.t.z;
	//ap.q.x, ap.q.y, ap.q.z, ap.q.w;
	//ap.k.x, ap.k.y, ap.k.z, ap.u.x, ap.u.y, ap.u.z, ap.u.w;
}
