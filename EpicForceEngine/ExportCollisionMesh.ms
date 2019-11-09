-----------------------------------------------------------------------------------------------
fn writeVector2 fptr v = 
(
	WriteFloat fptr v.x
	WriteFloat fptr v.y
)

fn writeVector3 fptr v =
(
	WriteFloat fptr v.x
	WriteFloat fptr v.z
	WriteFloat fptr -v.y
)

------------------------------------------------------------------------------------------------------------------------
fn exportMeshVertices fptr mesh =	
(
	numVertices = mesh.numverts
	writeLong fptr numVertices

	for i = 1 to mesh.numverts do
	(
		v1 = (in coordsys world getvert $ i)
		v1.x = v1.x * 0.1;
		v1.y = v1.y * 0.1;
		v1.z = v1.z * 0.1;
		
		writeVector3 fptr v1
		
		format "%\n"  v1
	)
)

fn exportMeshIndices fptr mesh =	
(
	numIndices = mesh.numFaces * 3
	WriteLong fptr numIndices

	for i = 1 to mesh.numFaces do
	(
		fidx = getface $ i
		fidx[1] = fidx[1]-1
		fidx[2] = fidx[2]-1
		fidx[3] = fidx[3]-1

		writeLong fptr fidx[1]
		writeLong fptr fidx[2]
		writeLong fptr fidx[3]
		
		format "% % %\n" fidx[1] fidx[3] fidx[2] 
	)
)

fn exportMeshMaterialIndices fptr mesh =	
(
	numTriangles = mesh.numFaces
	WriteLong fptr numTriangles
	
	for i = 1 to mesh.numFaces do
	(
		matIdx = getFaceMatID $ i
		matIdx = matIdx - 1
		
		writeLong fptr matIdx
		
		format "%\n" matIdx
	)
)

fn exportCollisionMesh fptr =
(
	if(selection.count==1) then
	(
		if(selection[1].classid[1]==-464580429 and selection[1].classid[2]==0) then
		(
			exportMeshVertices fptr selection[1]
			exportMeshIndices fptr selection[1]
			exportMeshMaterialIndices fptr selection[1]			
		)
		else
		(
			messagebox "Can export editable mesh Only"
		)
	)
	else
	(
		messagebox "Please select 1 and only 1 mesh"
	)
)

-------------------------------------------------------------------------------------------------
Utility HeightFieldGeneratorUtility "HeightFieldGeneratorUtility"
(
	Button generateButton "Generate"
	
	on generateButton pressed do
	(
		filename = getSaveFileName "Select File to save" types:"BVHTriangleMesh|*.bvhtrimesh"
		if(filename!=undefined) then
		(
			fptr = fopen filename "wb"

			exportCollisionMesh fptr
			
			FClose fptr
		)
	)
)