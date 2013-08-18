/****************************************************************************
 *  Copyright (C) 2012 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <dawg/subst.h>
#include <cassert>
#include <cstdio>

bool dawg::subst_model::create_alias_tables() {
	std::size_t sz = model_size();
	stat_dist.create(&freqs[0], &freqs[sz]);
	mutation.resize(sz);
	for(std::size_t k = 0; k < sz; ++k)
		mutation[k].create(&table[k][0], &table[k][sz]);
	return true;
}
