#include "BlockRegistryModule.h"
#include "BlockType.h"
#include "Engine.h"


bool BlockRegistryModule::init(Engine* engine) {
	// Register blocks
	registerBlock({ 1, "Dirt", true, {0,0,32,32}});
	return true; // Initialization successful
}