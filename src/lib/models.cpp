/****************************************************************************
 *  Copyright (C) 2012 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <dawg/subst.h>
#include <cassert>
#include <cstdio>
#include <algorithm>

bool dawg::subst_model::uniformize_over_rates(const std::vector<double> &rates) {
	return true;
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


inline boost::uint64_t uint64_bound(double bound) {
	assert((0.0 <= bound && bound < 1.0));
	return static_cast<boost::uint64_t>(ceil(bound*9007199254740992.0)) << 11;
}

// vose method for creating alias tables
// http://www.keithschwarz.com/darts-dice-coins/
void alias_table_64(const double *pp, boost::uint64_t *q, boost::uint32_t *a) {
	double d=0.0, f=0.0, p[64];
	// use pairs-summation to control error
	for(int i=0;i<64;i+=2) {
		d += pp[i]; f += pp[i+1];
	}
	f = 64.0/(d+f);
	for(int i=0;i<64;++i)
		p[i] = pp[i]*f;
	std::size_t g,m,mm;
	for(g=0; g<64 && p[g] <  1.0; ++g)
		/*noop*/;
	for(m=0; m<64 && p[m] >= 1.0; ++m)
		/*noop*/;
	mm = m+1;
	while(g < 64 && m < 64) {
		q[m] = uint64_bound(p[m]);
		a[m] = static_cast<boost::uint32_t>(g);
		p[g] = (p[g]+p[m])-1.0;
		if(p[g] >= 1.0 || mm <= g) {
			for(m=mm;m<64 && p[m] >= 1.0; ++m)
				/*noop*/;
			mm = m+1;
		} else
			m = g;
		for(; g<64 && p[g] <  1.0; ++g)
			/*noop*/;
	}
	if(g < 64) {
		q[g] = std::numeric_limits<boost::uint64_t>::max();
		a[g] = static_cast<boost::uint32_t>(g);
		for(g=g+1; g<64; ++g) {
			if(p[g] < 1.0)
				continue;
			q[g] = std::numeric_limits<boost::uint64_t>::max();
			a[g] = static_cast<boost::uint32_t>(g);
		}
	}
	if(m < 64) {
		q[m] = std::numeric_limits<boost::uint64_t>::max();
		a[m] = static_cast<boost::uint32_t>(m);
		for(m=mm; m<64; ++m) {
			if(p[m] > 1.0)
				continue;
			q[m] = std::numeric_limits<boost::uint64_t>::max();
			a[m] = static_cast<boost::uint32_t>(m);
		}
	}
}


/*
bool dawg::subst_model::create_alias_tables() {
	alias_table_64(&freqs[0], &stat_dist_p_[0], &stat_dist_a_[0]);
	for(int i=0;i<64;++i)
		alias_table_64(&table[i][0], &mutation_p_[i][0], &mutation_a_[i][0]);
	return true;
}
*/

bool dawg::subst_model::create_alias_tables() {
	stat_dist_table_.create(&freqs[0], &freqs[64]);
	for(std::size_t k = 0; k < 64; ++k)
		mutation_table_[k].create(&table[k][0], &table[k][64]);
	return true;
}
