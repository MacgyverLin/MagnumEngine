@echo off
cd %EPICFORCE_TOOLS%\x64
c:
IF EXIST EpicForceSkeletalAnimModelExporter.dle (
	del EpicForceSkeletalAnimModelExporter.dle
)

IF EXIST EpicForcePhysicsSceneExporter.dle (
	del EpicForcePhysicsSceneExporter.dle
)

IF EXIST EpicForceHeightFieldExporter.dle (
	del EpicForceHeightFieldExporter.dle
)

IF EXIST EpicForceBVHTriangleMeshExporter.dle (
	del EpicForceBVHTriangleMeshExporter.dle
)

copy EpicForceSkeletalAnimModelExporter EpicForceSkeletalAnimModelExporter.dle
copy EpicForcePhysicsSceneExporter EpicForcePhysicsSceneExporter.dle
copy EpicForceHeightFieldExporter EpicForceHeightFieldExporter.dle
copy EpicForceBVHTriangleMeshExporter EpicForceBVHTriangleMeshExporter.dle

