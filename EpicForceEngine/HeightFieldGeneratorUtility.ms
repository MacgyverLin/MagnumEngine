fn generateHeightField heightField target =
(
	convertToMesh heightField
	
	lastvalue = heightField.pos.z
	for i = 1 to heightField.numverts do
	(
		p = getVert heightField i
		
		r = ray [p.x, p.y, p.z] [0, 0, -10000]
		
		intersect = IntersectRayEx target r
		if(intersect!=undefined) then
		(
			-- format "% %\n" r.pos intersect[1].pos
			lastvalue = intersect[1].pos.z
			
			setVert heightField i [p.x, p.y, intersect[1].pos.z]
		)
		else
		(
			setVert heightField i [p.x, p.y, lastvalue]
		)
	)

	update heightField
)

fn isHeightField node =
(
	heightFieldString = getUserProp node "TYPE"			
	
	return heightFieldString=="HEIGHT_FIELD";
)

fn isBrush node =
(
	brushString = getUserProp node "TYPE"			
	
	return brushString=="BRUSH";
)

fn generatorHeightFields a =
(
	for i = 1 to Geometry.count do
	(
		if(isHeightField Geometry[i] and not(Geometry[i].isNodeHidden) and not(Geometry[i].isFrozen) ) then
		(
			for j = 1 to Geometry.count do
			(
				if( not(isHeightField Geometry[j]) and not(isBrush Geometry[j]) and not(Geometry[j].isNodeHidden) and not(Geometry[j].isFrozen) ) then
				(
					generateHeightField Geometry[i] Geometry[j]
				)
			)
		)
	)
)

-------------------------------------------------------------------------------------------------
Utility HeightFieldGeneratorUtility "HeightFieldGeneratorUtility"
(
	Button generateButton "Generate"
	spinner maxheight "Maxheight" value:1000
	
	on generateButton pressed do
	(
		generatorHeightFields 1
	)
)