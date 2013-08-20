/****************************************************************************
 *  Copyright (C) 2012 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <dawg/subst.h>
#include <cassert>
#include <cstdio>
#include <algorithm>

bool dawg::subst_model::uniformize_over_rates(const std::vector<double> &rates) {
	std::size_t sz = model_size();
	std::vector<double> work(sz, 0.0);
	rate_mutation_table_.resize(rates.size());

	// identify max rate
	double max_rate = *std::max_element(rates.begin(), rates.end());
	// construct tables
	for(std::size_t k=0;k<rates.size();++k) {
		rate_mutation_table_[k].resize(sz);
		for(std::size_t i=0; i<sz; ++i) {
			// fill work table for row i and rate k
			for(std::size_t j=0; j<sz; ++j)
				work[j] = table[i][j]*uniform_scale()*rates[k];
			// create more pseudomutations
			work[i] += uniform_scale()*(max_rate - rates[k]);
			// rescale
			for(std::size_t j=0; j<sz; ++j)
				work[j] /= uniform_scale()*max_rate;
			// construct sampling table
			rate_mutation_table_[k][i].create_inplace(work);
		}
	}
	// save scale
	uni_rate_scale_ = max_rate;
	return true;
}

bool dawg::subst_model::create_alias_tables() {
	stat_dist_table_.create(&freqs[0], &freqs[64]);
	for(std::size_t k = 0; k < 64; ++k)
		mutation_table_[k].create(&table[k][0], &table[k][64]);
	return true;
}

