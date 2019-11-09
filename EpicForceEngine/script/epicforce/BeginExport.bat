@echo off
cd %EPICFORCE_TOOLS%\x64
c:
IF EXIST EpicForceSkeletalAnimModelExporter.dle (
	ECHO BRANCH1
	IF EXIST EpicForceSkeletalAnimModelExporter1.dle (
		del EpicForceSkeletalAnimModelExporter1.dle
	)
	ren EpicForceSkeletalAnimModelExporter.dle EpicForceSkeletalAnimModelExporter1.dle
) ELSE (
	ECHO BRANCH2
	IF EXIST EpicForceSkeletalAnimModelExporter.dle (
		del EpicForceSkeletalAnimModelExporter.dle
	)
	ren EpicForceSkeletalAnimModelExporter1.dle EpicForceSkeletalAnimModelExporter.dle
)