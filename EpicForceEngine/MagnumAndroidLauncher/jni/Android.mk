LOCAL_PATH:= $(call my-dir)

#########################################################################################################
# FMOD Ex Shared Library
# 
include $(CLEAR_VARS)

LOCAL_MODULE            := fmodex
LOCAL_SRC_FILES         := ../../EpicForceEngineLib/SDK/FMOD/Android/lib/$(TARGET_ARCH_ABI)/libfmodex.so
LOCAL_EXPORT_C_INCLUDES := ../../EpicForceEngineLib/SDK/FMOD/Android/inc

include $(PREBUILT_SHARED_LIBRARY)

#########################################################################################################
# libzip
include $(CLEAR_VARS)

# DEBUG MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet
# RELEASE MODE
  LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet

LOCAL_MODULE				:=	libzip

LIBZIP_SRC					:= 	libzip/zip_add.c \
								libzip/zip_add_dir.c \
								libzip/zip_close.c \
								libzip/zip_delete.c \
								libzip/zip_dirent.c \
								libzip/zip_entry_free.c \
								libzip/zip_entry_new.c \
								libzip/zip_err_str.c \
								libzip/zip_error.c \
								libzip/zip_error_clear.c \
								libzip/zip_error_get.c \
								libzip/zip_error_get_sys_type.c \
								libzip/zip_error_strerror.c \
								libzip/zip_error_to_str.c \
								libzip/zip_fclose.c \
								libzip/zip_file_error_clear.c \
								libzip/zip_file_error_get.c \
								libzip/zip_file_get_offset.c \
								libzip/zip_file_strerror.c \
								libzip/zip_filerange_crc.c \
								libzip/zip_fopen.c \
								libzip/zip_fopen_index.c \
								libzip/zip_fread.c \
								libzip/zip_free.c \
								libzip/zip_get_archive_comment.c \
								libzip/zip_get_archive_flag.c \
								libzip/zip_get_file_comment.c \
								libzip/zip_get_num_files.c \
								libzip/zip_get_name.c \
								libzip/zip_memdup.c \
								libzip/zip_name_locate.c \
								libzip/zip_new.c \
								libzip/zip_open.c \
								libzip/zip_rename.c \
								libzip/zip_replace.c \
								libzip/zip_set_archive_comment.c \
								libzip/zip_set_archive_flag.c \
								libzip/zip_set_file_comment.c \
								libzip/zip_source_buffer.c \
								libzip/zip_source_file.c \
								libzip/zip_source_filep.c \
								libzip/zip_source_free.c \
								libzip/zip_source_function.c \
								libzip/zip_source_zip.c \
								libzip/zip_set_name.c \
								libzip/zip_stat.c \
								libzip/zip_stat_index.c \
								libzip/zip_stat_init.c \
								libzip/zip_strerror.c \
								libzip/zip_unchange.c \
								libzip/zip_unchange_all.c \
								libzip/zip_unchange_archive.c \
								libzip/zip_unchange_data.c

LOCAL_SRC_FILES :=	$(LIBZIP_SRC)

include $(BUILD_STATIC_LIBRARY)

#########################################################################################################
# libunzip
include $(CLEAR_VARS)

# DEBUG MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/unzip
# RELEASE MODE
  LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/unzip
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/unzip

LOCAL_MODULE				:=	libunzip

LIBUNZIP_SRC				:= 	../../EpicForceEngineLib/SDK/unzip/ioapi.c \
								../../EpicForceEngineLib/SDK/unzip/mztools.c \
								../../EpicForceEngineLib/SDK/unzip/unzip.c \
								../../EpicForceEngineLib/SDK/unzip/zip.c

LOCAL_SRC_FILES :=	$(LIBUNZIP_SRC)

include $(BUILD_STATIC_LIBRARY)

#########################################################################################################
# libbullet
include $(CLEAR_VARS)

LOCAL_MODULE				:=	libbullet

# DEBUG MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet
# RELEASE MODE
  LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/SDK/Bullet


LIBBULLET_SRC				= 	../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btDefaultSoftBodySolver.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftBody.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftBodyHelpers.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftRigidCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletSoftBody/btSoftSoftCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Character/btKinematicCharacterController.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btContactConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Dynamics/btRigidBody.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Dynamics/Bullet-C-API.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Vehicle/btRaycastVehicle.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletDynamics/Vehicle/btWheelInfo.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btDbvt.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btDispatcher.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btCollisionObject.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btGhostObject.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btManifoldResult.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/btUnionFind.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btBox2dShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btBoxShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btCapsuleShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btCollisionShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btCompoundShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConcaveShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConeShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvex2dShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexHullShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexInternalShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btCylinderShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btEmptyShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btOptimizedBvh.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btShapeHull.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btSphereShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleBuffer.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleCallback.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleMesh.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btContactProcessing.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btGenericPoolAllocator.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btGImpactBvh.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btGImpactShape.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/btTriangleShapeEx.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/gim_box_set.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/gim_contact.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/gim_memory.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/Gimpact/gim_tri_collision.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp \
								../../EpicForceEngineLib/SDK/Bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btAlignedAllocator.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btConvexHull.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btConvexHullComputer.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btGeometryUtil.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btQuickprof.cpp \
								../../EpicForceEngineLib/SDK/Bullet/LinearMath/btSerializer.cpp

LOCAL_SRC_FILES				:=	$(LIBBULLET_SRC)

include $(BUILD_STATIC_LIBRARY)

#########################################################################################################
# libepicforceengine
include $(CLEAR_VARS)

LOCAL_MODULE				:=	libepicforceengine

# DEBUG MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../EpicForceEngineLib/SDK/FMOD/Android/inc -I../../EpicForceEngineLib/SDK/Bullet -I../../EpicForceEngineLib/SDK/unzip -Ilibzip -Ilibpng -Iopenal/include -Imad
# RELEASE MODE
  LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../EpicForceEngineLib/SDK/FMOD/Android/inc -I../../EpicForceEngineLib/SDK/Bullet -I../../EpicForceEngineLib/SDK/unzip -Ilibzip -Ilibpng -Iopenal/include -Imad
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../EpicForceEngineLib/SDK/FMOD/Android/inc -I../../EpicForceEngineLib/SDK/Bullet -I../../EpicForceEngineLib/SDK/unzip -Ilibzip -Ilibpng -Iopenal/include -Imad

LIBEPICFORCEENGINE_SRC		:= 	../../EpicForceEngineLib/EpicForceCore/AABB2.cpp \
								../../EpicForceEngineLib/EpicForceCore/AABB3.cpp \
								../../EpicForceEngineLib/EpicForceCore/AnimBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/Arc2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Array.cpp \
								../../EpicForceEngineLib/EpicForceCore/AttributesBlock.cpp \
								../../EpicForceEngineLib/EpicForceCore/Audio.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioClip.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioListener.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioListenerBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioSourceBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/AudioStream.cpp \
								../../EpicForceEngineLib/EpicForceCore/BasicScene.cpp \
								../../EpicForceEngineLib/EpicForceCore/BezierCurve2.cpp \
								../../EpicForceEngineLib/EpicForceCore/BezierCurve3.cpp \
								../../EpicForceEngineLib/EpicForceCore/BillBoard.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVHTriangleMeshCollider.cpp \
								../../EpicForceEngineLib/EpicForceCore/BillBoardRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/Box3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/BoxShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/BSplineBasis.cpp \
								../../EpicForceEngineLib/EpicForceCore/BSplineCurve2.cpp \
								../../EpicForceEngineLib/EpicForceCore/BSplineCurve3.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVector2.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVector3.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVector4.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVHTriangleMeshCollider.cpp \
								../../EpicForceEngineLib/EpicForceCore/BVHTriangleMeshShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/CameraComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/Capsule3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Capsule3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/CapsuleBound.cpp \
								../../EpicForceEngineLib/EpicForceCore/CapsuleShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Circle2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Circle3.cpp \
								../../EpicForceEngineLib/EpicForceCore/ClassIndexMap.cpp \
								../../EpicForceEngineLib/EpicForceCore/ColorRGB.cpp \
								../../EpicForceEngineLib/EpicForceCore/ColorRGBA.cpp \
								../../EpicForceEngineLib/EpicForceCore/Component.cpp \
								../../EpicForceEngineLib/EpicForceCore/Cone3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Cone3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/ConeShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/ConvexHull3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/ConvexHullShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Cube.cpp \
								../../EpicForceEngineLib/EpicForceCore/CubeRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/Curve2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Curve3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Cylinder3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Cylinder3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/CylinderShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Delegate.cpp \
								../../EpicForceEngineLib/EpicForceCore/DiffuseMapCube.cpp \
								../../EpicForceEngineLib/EpicForceCore/DiffuseMapCubeRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/DiffuseMapSpecularMapCube.cpp \
								../../EpicForceEngineLib/EpicForceCore/DiffuseMapSpecularMapCubeRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/EditorCameraComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/EditorGizmo.cpp \
								../../EpicForceEngineLib/EpicForceCore/EditorGizmoRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/EMath.cpp \
								../../EpicForceEngineLib/EpicForceCore/Entity.cpp \
								../../EpicForceEngineLib/EpicForceCore/EntityFieldReader.cpp \
								../../EpicForceEngineLib/EpicForceCore/EntityFieldWriter.cpp \
								../../EpicForceEngineLib/EpicForceCore/EntityPropertyReader.cpp \
								../../EpicForceEngineLib/EpicForceCore/EntityPropertyWriter.cpp \
								../../EpicForceEngineLib/EpicForceCore/EpicPrefab.cpp \
								../../EpicForceEngineLib/EpicForceCore/EpicScene.cpp \
								../../EpicForceEngineLib/EpicForceCore/EString.cpp \
								../../EpicForceEngineLib/EpicForceCore/ESystem.cpp \
								../../EpicForceEngineLib/EpicForceCore/FileIO.cpp \
								../../EpicForceEngineLib/EpicForceCore/Font.cpp \
								../../EpicForceEngineLib/EpicForceCore/Frame3.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXAttribute.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXBlendState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXColorBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXContext.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXCullState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXDebugRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXDef.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXDepthBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXDepthTestState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXFrameBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXIndexBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXPixelBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXPolygonOffsetState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXPrimitive.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXRenderTarget.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXShaderProgram.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXStencilOpState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXStencilTestState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXTexture.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXTexture2D.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXTextureCube.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXTextureFilterState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXTextureWrapState.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXUniform.cpp \
								../../EpicForceEngineLib/EpicForceCore/GXVertexBuffer.cpp \
								../../EpicForceEngineLib/EpicForceCore/HeightFieldCollider.cpp \
								../../EpicForceEngineLib/EpicForceCore/HeightFieldShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/IComponentDebugRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/Input.cpp \
								../../EpicForceEngineLib/EpicForceCore/InputStream.cpp \
								../../EpicForceEngineLib/EpicForceCore/IO.cpp \
								../../EpicForceEngineLib/EpicForceCore/IVector2.cpp \
								../../EpicForceEngineLib/EpicForceCore/IVector3.cpp \
								../../EpicForceEngineLib/EpicForceCore/IVector4.cpp \
								../../EpicForceEngineLib/EpicForceCore/Line2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Line3.cpp \
								../../EpicForceEngineLib/EpicForceCore/List.cpp \
								../../EpicForceEngineLib/EpicForceCore/Lozenge3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Matrix2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Matrix3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Matrix4.cpp \
								../../EpicForceEngineLib/EpicForceCore/MultipleCurve2.cpp \
								../../EpicForceEngineLib/EpicForceCore/MultipleCurve3.cpp \
								../../EpicForceEngineLib/EpicForceCore/OrthographicCameraComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/OutputStream.cpp \
								../../EpicForceEngineLib/EpicForceCore/ParticleEmitter.cpp \
								../../EpicForceEngineLib/EpicForceCore/ParticleEmitterRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/PerspectiveCameraComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/Physics3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Plane3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Platform.cpp \
								../../EpicForceEngineLib/EpicForceCore/Polyhedron3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Polynomial1.cpp \
								../../EpicForceEngineLib/EpicForceCore/Primitive.cpp \
								../../EpicForceEngineLib/EpicForceCore/ProjectModelViewBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/PVRTexConvert.cpp \
								../../EpicForceEngineLib/EpicForceCore/PVRTexLoad.cpp \
								../../EpicForceEngineLib/EpicForceCore/Quadratic2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Quadratic3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Quaternion.cpp \
								../../EpicForceEngineLib/EpicForceCore/Ray2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Ray3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Rectangle2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Rectangle3.cpp \
								../../EpicForceEngineLib/EpicForceCore/ReflectedClassFieldReader.cpp \
								../../EpicForceEngineLib/EpicForceCore/ReflectedClassFieldWriter.cpp \
								../../EpicForceEngineLib/EpicForceCore/ReflectedClassPropertyReader.cpp \
								../../EpicForceEngineLib/EpicForceCore/ReflectedClassPropertyWriter.cpp \
								../../EpicForceEngineLib/EpicForceCore/reflection.cpp \
								../../EpicForceEngineLib/EpicForceCore/RendererBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/RenderStatesBlock.cpp \
								../../EpicForceEngineLib/EpicForceCore/ResourceAccess.cpp \
								../../EpicForceEngineLib/EpicForceCore/ResourceImport.cpp \
								../../EpicForceEngineLib/EpicForceCore/ResourcePath.cpp \
								../../EpicForceEngineLib/EpicForceCore/Scene.cpp \
								../../EpicForceEngineLib/EpicForceCore/Segment2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Segment3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Selection3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Service.cpp \
								../../EpicForceEngineLib/EpicForceCore/ShaderProgramBlock.cpp \
								../../EpicForceEngineLib/EpicForceCore/Shape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/SingleCurve2.cpp \
								../../EpicForceEngineLib/EpicForceCore/SingleCurve3.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimation.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimBlender.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimModel.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimModelComponent.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkeletalAnimModelRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkySphere.cpp \
								../../EpicForceEngineLib/EpicForceCore/SkySphereRenderer.cpp \
								../../EpicForceEngineLib/EpicForceCore/Sphere3.cpp \
								../../EpicForceEngineLib/EpicForceCore/SphereBound.cpp \
								../../EpicForceEngineLib/EpicForceCore/Sphere3Collider.cpp \
								../../EpicForceEngineLib/EpicForceCore/SphereShape3.cpp \
								../../EpicForceEngineLib/EpicForceCore/SpriteAnimation.cpp \
								../../EpicForceEngineLib/EpicForceCore/SRTTransform.cpp \
								../../EpicForceEngineLib/EpicForceCore/Stage.cpp \
								../../EpicForceEngineLib/EpicForceCore/StageAndroidPlatformDepFunc.cpp \
								../../EpicForceEngineLib/EpicForceCore/StagePCPlatformDepFunc.cpp \
								../../EpicForceEngineLib/EpicForceCore/State.cpp \
								../../EpicForceEngineLib/EpicForceCore/StateMachine.cpp \
								../../EpicForceEngineLib/EpicForceCore/TCBSpline2.cpp \
								../../EpicForceEngineLib/EpicForceCore/TCBSpline3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Tetrahedron3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Text.cpp \
								../../EpicForceEngineLib/EpicForceCore/Texture2DBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/Texture2DFile.cpp \
								../../EpicForceEngineLib/EpicForceCore/TextureBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/TextureCubeBase.cpp \
								../../EpicForceEngineLib/EpicForceCore/TextureCubeFile.cpp \
								../../EpicForceEngineLib/EpicForceCore/TextureUniformsBlock.cpp \
								../../EpicForceEngineLib/EpicForceCore/tinystr.cpp \
								../../EpicForceEngineLib/EpicForceCore/tinyxml.cpp \
								../../EpicForceEngineLib/EpicForceCore/tinyxmlerror.cpp \
								../../EpicForceEngineLib/EpicForceCore/tinyxmlparser.cpp \
								../../EpicForceEngineLib/EpicForceCore/Transform.cpp \
								../../EpicForceEngineLib/EpicForceCore/Triangle2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Triangle3.cpp \
								../../EpicForceEngineLib/EpicForceCore/UniformsBlock.cpp \
								../../EpicForceEngineLib/EpicForceCore/Vector10.cpp \
								../../EpicForceEngineLib/EpicForceCore/Vector2.cpp \
								../../EpicForceEngineLib/EpicForceCore/Vector3.cpp \
								../../EpicForceEngineLib/EpicForceCore/Vector4.cpp \
								../../EpicForceEngineLib/EpicForceCore/Video.cpp \
								../../EpicForceEngineLib/EpicForceCore/VehicleCollider.cpp \
								../../EpicForceEngineLib/EpicForceCore/VisualEffect.cpp \
								../../EpicForceEngineLib/EpicForceCore/ZipFile.cpp
								
LOCAL_SRC_FILES				:=	$(LIBEPICFORCEENGINE_SRC)

include $(BUILD_STATIC_LIBRARY)

#########################################################################################################
# libgame
include $(CLEAR_VARS)

LOCAL_MODULE				:=	libgame
 
# DEBUG MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../Game -I../../Game/EntryPoint -I../../Game/Scenes -I../../Game/Entities
# RELEASE MODE
  LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../Game -I../../Game/EntryPoint -I../../Game/Scenes -I../../Game/Entities
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/ -I../../EpicForceEngineLib/EpicForceCore/ -I../../Game -I../../Game/EntryPoint -I../../Game/Scenes -I../../Game/Entities

LIBGAME_ENTITIES_SRC		:=		../../Game/Entities/EditorEntity.cpp \
									../../Game/Entities/MacDemoAudioListenerEntity.cpp \
									../../Game/Entities/MacDemoAudioSourceEntity.cpp \
									../../Game/Entities/MacDemoBGMEntity.cpp \
									../../Game/Entities/MacDemoBillBoardEntity.cpp \
									../../Game/Entities/MacDemoCameraEntity.cpp \
									../../Game/Entities/MacDemoCubeEntity.cpp \
									../../Game/Entities/MacDemoDiffuseMapCubeEntity.cpp \
									../../Game/Entities/MacDemoDiffuseMapSpecularMapCubeEntity.cpp \
									../../Game/Entities/MacDemoLevelEntity.cpp \
									../../Game/Entities/MacDemoParticleEmitterEntity.cpp \
									../../Game/Entities/MacDemoPhysics3SkeletalAnimModelEntity.cpp \
									../../Game/Entities/MacDemoPlaneEntity.cpp \
									../../Game/Entities/MacDemoSkySphereEntity.cpp \
									../../Game/Entities/RacerCameraEntity.cpp \
									../../Game/Entities/RacerMainPlayerCar2Entity.cpp \
									../../Game/Entities/RacerMainPlayerCarEntity.cpp \
									../../Game/Entities/RacerSkySphereEntity.cpp \
									../../Game/Entities/RacerTrackGeneratorEntity.cpp \
									../../Game/Entities/ReflectEntity.cpp

LIBGAME_ENTRYPOINT_SRC		:=		../../Game/EntryPoint/EpicForceGame.cpp

LIBGAME_SCENES_SRC			:=		../../Game/Scenes/MacDemoScene.cpp \
									../../Game/Scenes/ModelViewEditorScene.cpp \
									../../Game/Scenes/PlayModeScene.cpp \
									../../Game/Scenes/ProjectModel.cpp \
									../../Game/Scenes/ProjectModelFSM.cpp
									
LIBGAME_SRC					:= 		$(LIBGAME_ENTRYPOINT_SRC) $(LIBGAME_SCENES_SRC) $(LIBGAME_ENTITIES_SRC)	

LOCAL_SRC_FILES				:=		$(LIBGAME_SRC)

include $(BUILD_STATIC_LIBRARY)

#########################################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE				:= libEpicForceJNI

# DEBUG MODE
# LOCAL_CPPFLAGS 			:= -fmax-errors=10 -Wno-psabi -w -O0 -DGL_GLEXT_PROTOTYPES -D_DEBUG -DNEED_DEBUG -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/
# RELEASE MODE
  LOCAL_CPPFLAGS 			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG              -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/
# FINAL MODE
# LOCAL_CPPFLAGS			:= -fmax-errors=10 -Wno-psabi -w -O3 -DGL_GLEXT_PROTOTYPES -DNDEBUG -DFINAL      -I$(NDK)/sources/cxx-stl/gnu-libstdc++/include/

LOCAL_SRC_FILES				:=	EpicForceJNI.cpp \
								InputData.cpp
								
LOCAL_LDLIBS				:= -llog -lGLESv2 -lz 
LOCAL_STATIC_LIBRARIES		:= libgame libepicforceengine libunzip libzip libbullet libgnustl_static
LOCAL_SHARED_LIBRARIES		:= fmodex

include $(BUILD_SHARED_LIBRARY)