/****************************************************************************
 *  Copyright (C) 2012 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <dawg/subst.h>
#include <cassert>
#include <cstdio>

bool dawg::subst_model::create_alias_tables() {
	std::size_t sz = model_size();
	stat_dist_table_.create(&freqs[0], &freqs[sz]);
	mutation_table_.resize(sz);
	for(std::size_t k = 0; k < sz; ++k)
		mutation_table_[k].create(&table[k][0], &table[k][sz]);
	return true;
}
