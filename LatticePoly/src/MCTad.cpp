//
//  MCTad.cpp
//  LatticePoly
//
//  Created by mtortora on 02/12/2019.
//  Copyright © 2019 ENS Lyon. All rights reserved.
//

#include "MCTad.hpp"


MCLink::MCLink()
{
	id1 = -1;
	id2 = -1;
	dir = 0;
}

MCTad::MCTad()
{
	pos = -1;
	type = 0;
	links = 0;

	_isLeftEnd = false;
	_isRightEnd = false;
}

MCTad::MCTad(const MCTad& tad)
{
	pos = tad.pos;
	type = tad.type;
	links = 0;

	_isLeftEnd = tad.isLeftEnd();
	_isRightEnd = tad.isRightEnd();
}
