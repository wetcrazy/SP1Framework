#ifndef _SKILLS_H
#define _SKILLS_H

#include "map.h"
#include "_AI.h"
#include "uicontrol.h"

void processSkill(Console * handle, double dTime);
void ProcessSkillBoss(double dtime);

void resetSkillStunCharges();
short getSkillStunCharges();

#endif