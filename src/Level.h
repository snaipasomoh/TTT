#ifndef LEVEL_H
#define LEVEL_H

struct Level{
	virtual void update(int mouseX, int mouseY, bool &mouseDown,
						int &nextLevelNum){}
	virtual ~Level(){}
};

#endif