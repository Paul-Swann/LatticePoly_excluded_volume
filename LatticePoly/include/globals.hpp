//
//  globals.hpp
//  LatticePoly
//
//  Created by mtortora on 29/11/2019.
//  Copyright © 2019 ENS Lyon. All rights reserved.
//

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include <string>


// Box linear dimension
#define L 27

// Chain length
#define Nchain 9827

// Custom macros/compile-time constants
#define SQR(x) ((x)*(x))
#define CUB(x) ((x)*(x)*(x))

#define L2 SQR(L)
#define L3 CUB(L)
#define Ntot (4*L3)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define __DATA_PATH TOSTRING(__DPATH__)


// Runtime global parameters
extern std::string outputDir;
extern std::string latticeType;
extern std::string polyType;

extern int Nrelax;
extern int Nmeas;
extern int Ninter;

extern int NliqMC;
extern int Ndrop;

extern int Ndom;
extern int Nloc;

extern unsigned long long Tcpl;

extern bool InitDrop;

extern double Kint;

extern double R;
extern double Ldens;

extern double Jll;
extern double Jlp;
extern double Jpp;


#endif /* globals_hpp */
