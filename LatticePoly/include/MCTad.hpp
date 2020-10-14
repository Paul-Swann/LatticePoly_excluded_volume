//
//  MCTad.hpp
//  LatticePoly
//
//  Created by mtortora on 02/12/2019.
//  Copyright © 2019 ENS Lyon. All rights reserved.
//

#ifndef MCTad_hpp
#define MCTad_hpp

#include "MCLiqLattice.hpp"


struct MCBond
{
	MCBond();

	int id1;
	int id2;
	
	int dir;
};


class MCTad
{
public:
	MCTad();
	MCTad& operator= (const MCTad&);
				 
	inline bool isLeftEnd() const {return _isLeftEnd;};
	inline bool isRightEnd() const {return _isRightEnd;};
	inline bool isFork() const {return links == 3;};
	
	inline void setLeftEnd() {_isLeftEnd = true;}
	inline void setRightEnd() {_isRightEnd = true;}

	int pos;
	int type;
	int links;
	
	MCBond* bonds[3];
	MCTad* neighbors[3];
	
private:
	bool _isLeftEnd;
	bool _isRightEnd;
};


#endif /* MCTad_hpp */
