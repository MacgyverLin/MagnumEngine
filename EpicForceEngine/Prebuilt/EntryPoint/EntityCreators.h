#include "Camera1Entity.h"
static Entity::Creator<Camera1Entity> entityCamera1("Camera1", false);

#include "CameraEntity.h"
static Entity::Creator<CameraEntity> entityCamera("Camera", false);

#include "Player1Entity.h"
static Entity::Creator<Player1Entity> entityPlayer1("Player1", false);

#include "PlayerEntity.h"
static Entity::Creator<PlayerEntity> entityPlayer("Player", false);

#include "TestCubeEntity.h"
static Entity::Creator<TestCubeEntity> entityTestCube("TestCube", false);

