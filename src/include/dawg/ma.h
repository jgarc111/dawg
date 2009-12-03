#pragma once
#ifndef DAWG_MA_H
#define DAWG_MA_H
/****************************************************************************
 *  Copyright (C) 2009 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <string>
#include <vector>

#include <dawg/wood.h>

namespace dawg {

// dawg::ma is a "model argument" structure
struct ma {
#	define XM(name, type, def) type _V(name) ;
#	include <dawg/details/dawgma.xmh>
#	undef XM

	ma() :
#	define XM(name, type, def) _V(name) (def),
#	include <dawg/details/dawgma.xmh>
#	undef XM
	_dummy(0)
	{ }	
private:
	char _dummy; // needed to complete the initialization list
};

}
#endif //DAWG_MA_H
