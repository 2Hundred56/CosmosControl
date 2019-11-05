/*
 * ResourceManager.h
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_
#include <string>
#include <map>
class BasicTexture;
class PaletteTexture;
class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();
	BasicTexture* LoadTextureBMP(char* key);
protected:
	std::map<std::string, std::string> paths;
	std::map<std::string, BasicTexture*> basicTextures;
};

#endif /* RESOURCEMANAGER_H_ */
