//
//  RoomNode.cpp
//  Taverna
//
//  Created by Bennett Schalich on 2/3/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "RoomNode.h"

RoomNode::RoomNode(Vector2 centerPos, int rowLen, int colLen, int ID)
{
   this->centerPos = centerPos;
   this->rowLen = rowLen;
   this->colLen = colLen;
   this->ID = ID;
}

RoomNode::~RoomNode()
{
    
}

Vector2 RoomNode::getCenterPos()
{
   return centerPos;
}

Vector2 RoomNode::getDims()
{
   return Vector2(rowLen, colLen);
}

int RoomNode::getID()
{
   return ID;
}




