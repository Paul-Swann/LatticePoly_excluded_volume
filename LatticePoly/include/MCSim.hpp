//
//  MCSim.hpp
//  LatticePoly
//
//  Created by mtortora on 29/11/2019.
//  Copyright © 2019 ENS Lyon. All rights reserved.
//

#ifndef MCSIM_HPP_
#define MCSIM_HPP_

#include "MCHeteroPoly.hpp"


class IMCSim
{
public:
	virtual ~IMCSim() {};

	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void DumpVTK(int) = 0;
	virtual void PrintStats() = 0;

	int step;
};


template<class lattice, class polymer>
class MCSim: public IMCSim
{
public:
	MCSim();
	~MCSim();

	void Init();
	void Run();
	void DumpVTK(int);
	void PrintStats();
	
private:
	void InitRNG();
	void UpdateTAD();
	void UpdateSpin();

	bool MetropolisMove(double);
	bool ArrheniusMove(double, double);
	
	unsigned long long acceptCountLiq;
	unsigned long long acceptCountPoly;
	
	lattice* lat;
	polymer* pol;
	
	std::mt19937_64 rngEngine;
	std::uniform_real_distribution<double> rngDistrib{0., 1.};
};


#endif /* MCSim_hpp */
