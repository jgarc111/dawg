#pragma once
#ifndef DAWG_SUBST_AA_H
#define DAWG_SUBST_AA_H
/****************************************************************************
 *  Copyright (C) 2009-2010 Reed A. Cartwright, PhD <reed@scit.us>          *
 ****************************************************************************/
 
namespace dawg {
 
// name, followed by params, then freqs
template<typename It1, typename It2>
bool subst_model::create_aagtr(const char *mod_name, It1 first1, It1 last1, It2 first2, It2 last2) {
	double d = 0.0;
	int u = 0;
	_model = residue_exchange::AA;
	// do freqs first
	if(!create_freqs(mod_name, first2, last2, &freqs[0], &freqs[20]))
		return false;
	
	// fill params array
	double params[190];
	u = 0;
	for(;first1 != last1 && u<190;++first1,++u) {
		if(*first1 < 0)
			return DAWG_ERROR("Invalid subst model; aagtr parameter #" << u
				<< " '" << *first1 << "' is not >= 0.");
		params[u] = *first1;
	}
	if(u != 190)
		return DAWG_ERROR("Invalid subst model; aagtr requires 190 parameters.");
	
	// construct substitution matrix
	// do this locally to enable possible optimizations?
	double s[20][20];
	double rs[20];
	u = 0;
	for(int i=0;i<20;++i) {
		s[i][i] = 0.0;
		for(int j=i+1;j<20;++j) {
			s[i][j] = s[j][i] = params[u++];
		}
	}
	// scale the matrix to substitution time and uniformize
	d = 0.0;
	uni_scale = 0.0;
	for(int i=0;i<20;++i) {
		for(int j=0;j<20;++j) {
			s[i][j] *= freqs[j];
			d += s[i][j]*freqs[i];
		}
	}
	for(int i=0;i<20;++i) {
		rs[i] = 0.0;
		for(int j=0;j<20;++j) {
			s[i][j] /= d;
			rs[i] += s[i][j];
		}
		uni_scale = std::max(uni_scale, rs[i]);
	}
	// create pseudosubstitutions and transition frequencies
	for(int i=0;i<20;++i)
		s[i][i] = uni_scale - rs[i];
	for(int i=0;i<20;++i) {
		for(int j=0;j<20;++j)
			s[i][j] /= uni_scale;
	}
	
	// create cumulative frequencies
	d = 0.0;
	for(int i=0;i<19;++i) {
		d += freqs[i];
		freqs[i] = d;
	}
	// we will include 32 sites in our binary search
	// so fill them with 1.0
	std::fill(&freqs[19],&freqs[31], 1.0);
	freqs[19] = 1.0;
	for(int i=0;i<20;++i) {
		d = 0.0;
		for(int j=0;j<19;++j) {
			d += s[i][j];
			table[i][j] = d;
		}
		// we will include 32 sites in our binary search
		// so fill them with 1.0
		std::fill(&table[i][19],&table[i][31], 1.0);
	}
	name = mod_name;
	do_op_f = &subst_model::do_aagtr_f;
	do_op_s = &subst_model::do_aagtr_s;
	
	return true;
}

template<typename It1, typename It2>
bool subst_model::create_equ(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
	};
	static const double p[20] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
	};
	if(first2 != last2) { //+F model
		return create_aagtr("equ+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("eqy", &s[0], &s[190], &p[0], &p[20]);
}


template<typename It1, typename It2>
bool subst_model::create_wag(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		1.02704, 0.738998, 0.0302949, 1.58285, 0.021352, 6.17416, 0.210494, 0.39802,
		0.0467304, 0.0811339, 1.41672, 0.306674, 0.865584, 0.567717, 0.049931, 0.316954,
		0.248972, 0.930676, 0.570025, 0.679371, 0.24941, 0.193335, 0.170135, 0.039437,
		0.127395, 1.05947, 0.0304501, 0.13819, 0.906265, 0.0740339, 0.479855, 2.58443,
		0.088836, 0.373558, 0.890432, 0.323832, 0.397915, 0.384287, 0.0848047, 0.154263,
		2.11517, 0.0613037, 0.499462, 3.17097, 0.257555, 0.893496, 0.390482, 0.103754,
		0.315124, 1.19063, 0.1741, 0.404141, 4.25746, 0.934276, 4.85402, 0.509848,
		0.265256, 5.42942, 0.947198, 0.0961621, 1.12556, 3.95629, 0.554236, 3.01201,
		0.131528, 0.198221, 1.43855, 0.109404, 0.423984, 0.682355, 0.161444, 0.24357,
		0.696198, 0.0999288, 0.556896, 0.415844, 0.171329, 0.195081, 0.908598, 0.0988179,
		0.616783, 5.46947, 0.0999208, 0.330052, 4.29411, 0.113917, 3.8949, 0.869489,
		1.54526, 1.54364, 0.933372, 0.551571, 0.528191, 0.147304, 0.439157, 0.102711,
		0.584665, 2.13715, 0.186979, 5.35142, 0.497671, 0.683162, 0.635346, 0.679489,
		3.0355, 3.37079, 1.40766, 1.07176, 0.704939, 0.545931, 1.34182, 0.740169, 0.31944,
		0.96713, 0.344739, 0.493905, 3.97423, 1.61328, 1.02887, 1.22419, 2.12111, 0.512984,
		0.374866, 0.822765, 0.171903, 0.225833, 0.473307, 1.45816, 1.38698, 0.326622,
		1.51612, 2.03006, 0.795384, 0.857928, 0.554413, 4.37802, 2.00601, 1.00214, 0.152335,
		0.588731, 0.649892, 0.187247, 0.118358, 7.8213, 0.305434, 1.80034, 2.05845, 0.196246,
		0.314887, 0.301281, 0.251849, 0.232739, 1.38823, 0.113133, 0.71707, 0.129767,
		0.156557, 1.52964, 0.336983, 0.262569, 0.212483, 0.137505, 0.665309, 0.515706,
		0.0719167, 0.139405, 0.215737, 1.16392, 0.523742, 0.110864, 0.365369, 0.240735,
		0.543833, 0.325711, 0.196303, 6.45428, 0.103604, 3.87344, 0.42017, 0.133264, 0.398618,
		0.428437, 1.086, 0.216046, 0.22771, 0.381533, 0.786993, 0.291148, 0.31473, 2.48539
	};
	static const double p[20] = {
		0.0866279, 0.0193078, 0.0570451, 0.0580589, 0.0384319, 0.0832518, 0.0244313, 0.048466,
		0.0620286, 0.086209, 0.0195027, 0.0390894, 0.0457631, 0.0367281, 0.043972, 0.0695179,
		0.0610127, 0.0708956, 0.0143859, 0.0352742
	};
	if(first2 != last2) { //+F model
		return create_aagtr("wag+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("wag", &s[0], &s[190], &p[0], &p[20]);
}

template<typename It1, typename It2>
bool subst_model::create_wagstar(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		1.21324, 0.731152, 0.0379056, 1.55788, 0.0284956, 6.04299, 0.213179, 0.485001,
		0.0458258, 0.0873936, 1.41993, 0.312544, 0.88357, 0.588609, 0.0552962, 0.317684,
		0.341479, 0.958529, 0.599188, 0.631713, 0.279542, 0.214596, 0.198958, 0.0390513,
		0.124553, 1.06458, 0.0310522, 0.162975, 0.881639, 0.0719929, 0.480308, 2.45392,
		0.0832422, 0.381514, 0.854485, 0.320597, 0.400822, 0.451124, 0.0869637, 0.154936,
		2.10414, 0.067443, 0.508952, 3.1554, 0.255092, 0.887458, 0.428648, 0.0992829,
		0.294481, 1.14516, 0.184545, 0.40117, 3.94646, 0.877057, 4.81956, 0.514347, 0.233527,
		5.30821, 1.00122, 0.0848492, 1.12717, 3.9337, 0.527321, 2.88102, 0.144354, 0.198404,
		1.51861, 0.109081, 0.444152, 0.720567, 0.165205, 0.254626, 0.722123, 0.111722, 0.588203,
		0.422851, 0.179858, 0.204905, 1.03344, 0.0999068, 0.657364, 5.6037, 0.109241, 0.346823,
		4.87366, 0.125999, 4.19125, 0.873266, 1.64018, 1.62299, 0.913179, 0.589718, 0.568449,
		0.159054, 0.443685, 0.122792, 0.629768, 2.31211, 0.187262, 5.74119, 0.51821, 0.660816,
		0.67416, 0.711498, 3.02808, 3.52499, 1.35221, 1.09965, 0.822025, 0.563999, 1.33618,
		0.876688, 0.321774, 1.05314, 0.351913, 0.554077, 3.90127, 1.54694, 0.87908, 1.35611,
		2.24161, 0.522957, 0.395176, 0.889765, 0.188237, 0.236489, 0.54992, 1.48876, 1.45173,
		0.351564, 1.56873, 2.06787, 0.802531, 0.829315, 0.594177, 4.02507, 1.92496, 1.10899,
		0.155419, 0.588443, 0.653015, 0.190095, 0.119749, 7.48376, 0.300343, 1.82105, 2.03324,
		0.193323, 0.325745, 0.32893, 0.282892, 0.23769, 1.4088, 0.135395, 0.728065, 0.142159,
		0.176397, 1.58681, 0.366467, 0.261223, 0.259584, 0.159261, 0.706082, 0.565299, 0.0746093,
		0.135024, 0.208163, 1.24086, 0.528249, 0.118584, 0.396884, 0.270321, 0.481954, 0.326191,
		0.209621, 6.49269, 0.108982, 4.31772, 0.44009, 0.155623, 0.427718, 0.437069, 1.05269,
		0.212945, 0.210494, 0.386714, 0.742154, 0.286443, 0.353358, 2.42261
	};
	static const double p[20] = {
		0.0866279, 0.0193078, 0.0570451, 0.0580589, 0.0384319, 0.0832518, 0.0244313, 0.048466,
		0.0620286, 0.086209, 0.0195027, 0.0390894, 0.0457631, 0.0367281, 0.043972, 0.0695179,
		0.0610127, 0.0708956, 0.0143859, 0.0352742
	};
	if(first2 != last2) { //+F model
		return create_aagtr("wagstar+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("wagstar", &s[0], &s[190], &p[0], &p[20]);
}

template<typename It1, typename It2>
bool subst_model::create_lg(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		2.489084, 0.395144, 0.062556, 1.038545, 0.003499, 5.243870, 0.253701, 1.105251, 0.017416, 0.018811,
		2.066040, 0.569265, 0.844926, 0.348847, 0.089586, 0.358858, 0.640543, 0.927114, 0.423881, 0.682139,
		0.311484, 0.149830, 0.320627, 0.010690, 0.044265, 1.112727, 0.008705, 0.108882, 0.536518, 0.013266,
		0.282959, 1.807177, 0.023918, 0.296636, 0.697264, 0.159069, 0.395337, 0.594007, 0.015076, 0.069673,
		2.592692, 0.044261, 0.366317, 4.145067, 0.137500, 1.124035, 0.893680, 0.025548, 0.173735, 1.798853,
		0.139538, 0.442472, 4.273607, 0.656604, 6.312358, 0.276818, 0.528768, 5.076149, 0.541712, 0.089525,
		1.437645, 4.509238, 0.191503, 2.145078, 0.068427, 0.371004, 1.177651, 0.075382, 0.394456, 0.419409,
		0.094464, 0.196961, 0.508851, 0.078281, 0.390322, 0.249060, 0.099849, 0.161787, 0.969894, 0.084808,
		0.523386, 4.128591, 0.035855, 0.267959, 4.813505, 0.072854, 3.234294, 0.582457, 1.672569, 1.695752,
		0.624294, 0.425093, 0.534551, 0.123954, 0.363970, 0.052722, 0.390192, 2.426601, 0.126991, 6.326067,
		0.301848, 0.484133, 0.751878, 0.332533, 2.807908, 4.727182, 2.784478, 1.240275, 0.611973, 0.361819,
		1.739990, 0.990012, 0.064105, 0.748683, 0.182287, 0.346960, 4.008358, 1.338132, 1.223828, 0.858151,
		2.139501, 1.143480, 0.425860, 0.604545, 0.165001, 0.129836, 0.584262, 1.033739, 1.136863, 0.302936,
		2.020366, 2.000679, 0.571468, 1.080136, 0.578987, 6.472279, 2.547870, 1.959291, 0.037967, 0.245034,
		0.654683, 0.076701, 0.119013,10.649107, 0.185202, 1.702745, 1.898718, 0.083688, 0.296501, 0.210332,
		0.170887, 0.098369, 2.188158, 0.180717, 0.670128, 0.029890, 0.077852, 2.457121, 0.268491, 0.597054,
		0.111660, 0.049906, 0.619632, 0.696175, 0.045376, 0.095131, 0.236199, 0.593607, 0.248862, 0.140825,
		0.189510, 0.218959, 1.165532, 0.135107, 0.120037, 7.803902, 0.054679, 5.306834, 0.232523, 0.131932,
		0.299648, 0.481306, 0.612025, 0.089613, 0.257336, 0.314440, 0.400547, 0.245841, 0.249313, 3.151815
	};
	static const double p[20] = {
		0.079066, 0.012937, 0.053052, 0.071586, 0.042302, 0.057337, 0.022355, 0.062157, 0.064600, 0.099081,
		0.022951, 0.041977, 0.044040, 0.040767, 0.055941, 0.061197, 0.053287, 0.069147, 0.012066, 0.034155
	};
	if(first2 != last2) { //+F model
		return create_aagtr("lg+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("lg", &s[0], &s[190], &p[0], &p[20]);
}

template<typename It1, typename It2>
bool subst_model::create_jtt(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		0.574478, 0.827445, 0.105625, 1.066681, 0.053907, 7.766557, 0.138293, 0.678335, 0.032522, 0.043829,
		1.740159, 0.546389, 1.272434, 1.115632, 0.050212, 0.219970, 0.724998, 1.032342, 0.243768, 0.453428,
		0.201696, 0.361684, 0.150559, 0.115968, 0.111773, 0.777090, 0.053769, 0.181788, 0.369437, 0.049009,
		0.282466, 1.731684, 0.024521, 0.269840, 0.525096, 0.202562, 0.310007, 0.164593, 0.061486, 0.097485,
		2.500294, 0.069492, 0.540571, 2.335139, 0.146481, 0.469395, 0.409202, 0.190001, 0.175084, 0.436181,
		0.130379, 0.329660, 4.831666, 0.624581, 3.856906, 0.557967, 0.313311, 5.549530, 0.578115, 0.073481,
		0.773313, 4.025778, 0.491003, 2.529517, 0.137289, 0.330720, 1.959599, 0.123653, 0.127164, 0.191994,
		0.148483, 0.208081, 1.141961, 0.098580, 0.216345, 1.060504, 0.164215, 0.121804, 0.556725, 0.091304,
		0.521646, 3.417706, 0.045683, 0.231294, 5.684080, 0.078270, 2.966732, 0.709004, 0.456901, 0.768834,
		1.608126, 0.531678, 1.019843, 0.154899, 0.318483, 0.065314, 1.359652, 3.210671, 0.239195, 6.529255,
		0.372261, 0.431045, 0.451095, 0.710489, 3.021995, 3.887095, 2.155331, 0.589268, 0.312449, 0.943971,
		1.874296, 0.743458, 0.405119, 0.474478, 0.592511, 0.285564, 5.057964, 2.788406, 0.548807, 1.001551,
		4.582565, 0.469823, 0.425159, 0.331584, 0.138904, 0.316862, 0.477355, 2.553806, 0.965641, 0.272514,
		2.114728, 2.351311, 1.176961, 0.523825, 0.650282, 4.777647, 2.924161, 0.621323, 0.315261, 0.465271,
		0.593478, 0.470140, 0.121827, 9.533943, 0.124066, 1.761439, 3.038533, 0.164525, 0.211561, 0.179771,
		0.171995, 0.408532, 1.143980, 0.084329, 1.104181, 0.057466, 0.114381, 0.537922, 0.544180, 0.128193,
		0.134510, 0.089134, 0.530324, 0.201334, 0.027700, 0.069965, 0.172206, 1.257961, 0.310927, 0.080556,
		0.239697, 0.139492, 2.114852, 0.453952, 0.063452, 5.484236, 0.052500, 5.848400, 0.303445, 0.087904,
		0.241094, 0.189870, 0.700693, 0.113850, 0.254745, 0.235601, 0.628608, 0.201094, 0.165473, 0.747889
	}; 
	static const double p[20] = {
		0.076862, 0.020279, 0.051269, 0.061820, 0.040530, 0.074714, 0.022983, 0.052569, 0.059498, 0.091111,
		0.023414, 0.042546, 0.050532, 0.041061, 0.051057, 0.068225, 0.058518, 0.066374, 0.014336, 0.032303
	};
	if(first2 != last2) { //+F model
		return create_aagtr("jtt+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("jtt", &s[0], &s[190], &p[0], &p[20]);
}

template<typename It1, typename It2>
bool subst_model::create_dayhoff(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		0.360016, 1.199805, 0.0,      1.961167, 0.0,     11.388659, 0.183641, 0.0,      0.0,      0.0,
		2.386111, 0.107278, 1.240981, 0.811907, 0.153478, 0.228116, 0.282729, 0.868241, 0.439469, 0.475927,
		0.106802, 0.653416, 0.438074, 0.239248, 0.609526, 1.951951, 0.0,      0.076981, 0.258635, 0.0,
		0.716913, 0.830078, 0.0,      0.267683, 0.270475, 0.460857, 0.406431, 0.0,      0.0,      0.11288,
		1.565160, 0.071514, 0.443504, 2.556685, 0.180629, 0.717840, 0.0,      0.0,      0.304803, 0.92186,
		0.170372, 0.0,      3.332732, 2.411739, 5.230115, 0.984474, 0.0,      8.931515, 1.493409, 0.138503,
		1.385352, 5.290024, 0.768024, 3.148371, 0.341113, 0.0,      2.48592,  0.18755,  0.13394,  0.507003,
		0.110506, 0.347153, 0.933709, 0.119152, 0.335419, 0.316258, 0.170205, 0.419244, 0.887753, 0.0,
		1.348551, 7.086022, 0.0,      0.281581, 6.011613, 0.180393, 1.519078, 0.730772, 1.127499, 1.028509,
		1.526188, 0.267828, 0.232374, 0.0,      0.0,      0.136906, 0.087791, 2.383148, 0.632629, 4.610124,
		0.154924, 0.896321, 0.327059, 1.028313, 2.439939, 4.05187,  1.598356, 0.956097, 0.793999, 0.459901,
		2.322243, 0.353643, 0.247955, 0.954557, 0.171432, 0.619951, 4.885892, 2.427202, 0.561828, 1.53159,
		3.680365, 0.162366, 0.66093,  0.340156, 0.136655, 0.306662, 0.226333, 1.900739, 1.350599, 0.33109,
		1.031534, 2.271697, 0.782857, 0.525651, 0.265745, 5.436674, 2.059564, 0.484678, 0.178316, 0.36725,
		0.123606, 0.538165, 0.438715, 8.810038, 0.10385,  1.745156, 2.565955, 0.158067, 0.485026, 0.346983,
		0.240368, 0.303836, 1.561997, 0.0,      0.0,      0.0,      0.0,      0.762354, 0.0,      0.270564,
		0.0,      0.0,      0.461776, 0.0,      0.224968, 0.0,      0.0,      2.001375, 0.740819, 0.0,
		0.0,      0.244139, 0.953164, 0.0,      0.214717, 6.952629, 0.0,      1.2654,   0.374834, 0.132142,
		0.286572, 0.0,      0.94694,  0.0,      0.0,      0.078012, 0.336289, 0.417839, 0.279379, 0.60807
	};
	static const double p[20] = {
		0.087127, 0.033474, 0.046872, 0.04953, 0.039772, 0.088612, 0.033619, 0.036886, 0.080481, 0.085357,
		0.014753, 0.040432, 0.05068, 0.038255, 0.040904, 0.069577, 0.058542, 0.064718, 0.010494, 0.029916
	};
	if(first2 != last2) { //+F model
		return create_aagtr("dayhoff+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("dayhoff", &s[0], &s[190], &p[0], &p[20]);
}

template<typename It1, typename It2>
bool subst_model::create_molphy(const char *, It1 first1, It1 last1, It2 first2, It2 last2) {
	static const double s[190] = {
		0.365255, 1.196794, 0.007072, 1.943156, 0.004083,11.236928, 0.182627, 0.024074, 0.003597, 0.005491,
		2.376209, 0.108197, 1.230667, 0.799778, 0.151745, 0.225596, 0.283222, 0.855075, 0.429931, 0.467311,
		0.105015, 0.651534, 0.442435, 0.237558, 0.601184, 1.932390, 0.006405, 0.075779, 0.260244, 0.002234,
		0.718366, 0.826204, 0.001843, 0.267785, 0.268704, 0.461627, 0.408223, 0.010824, 0.007180, 0.112160,
		1.560815, 0.071409, 0.439814, 2.556320, 0.182251, 0.706162, 0.039211, 0.032318, 0.296582, 0.900346,
		0.166619, 0.034749, 3.263592, 2.383284, 5.159102, 0.995319, 0.020464, 8.992246, 1.493525, 0.139025,
		1.392474, 5.280613, 0.772963, 3.197574, 0.345815, 0.052957, 2.470839, 0.188814, 0.132571, 0.498468,
		0.109043, 0.343043, 0.916303, 0.117884, 0.334907, 0.315206, 0.166172, 0.420586, 0.893910, 0.006067,
		1.352218, 7.057870, 0.005001, 0.281880, 5.976661, 0.180812, 1.536592, 0.737865, 1.114993, 1.045293,
		1.524901, 0.267257, 0.234872, 0.016493, 0.015501, 0.135634, 0.087085, 2.347959, 0.628428, 4.621249,
		0.155010, 0.878398, 0.329397, 1.018202, 2.447538, 4.028242, 1.609487, 0.946552, 0.780814, 0.453952,
		2.295303, 0.347137, 0.245388, 0.953314, 0.170901, 0.605287, 4.902751, 2.394418, 0.561469, 1.516886,
		3.715525, 0.166031, 0.664453, 0.339684, 0.136975, 0.307796, 0.225599, 1.910180, 1.369705, 0.335177,
		1.022709, 2.314805, 0.784224, 0.533471, 0.267254, 5.447514, 2.051045, 0.488888, 0.176829, 0.361776,
		0.122215, 0.532821, 0.431365, 8.733750, 0.103887, 1.742707, 2.509573, 0.158886, 0.479300, 0.347358,
		0.238484, 0.300312, 1.567787, 0.010673, 0.096295, 0.008979, 0.020261, 0.794428, 0.035705, 0.280386,
		0.027380, 0.009493, 0.486002, 0.044996, 0.238328, 0.009932, 0.026659, 2.092641, 0.771731, 0.011637,
		0.035082, 0.243501, 0.962946, 0.022541, 0.211851, 6.885035, 0.004742, 1.246168, 0.372170, 0.132407,
		0.286614, 0.031862, 0.953314, 0.012138, 0.027880, 0.077505, 0.332907, 0.420039, 0.277033, 0.635541
	};
	static double p[20] = {
		0.087, 0.033, 0.047, 0.050, 0.040, 0.089, 0.034, 0.037, 0.08, 0.085,
		0.015, 0.040, 0.051, 0.038, 0.041, 0.070, 0.058, 0.065, 0.01, 0.030
	};
	if(first2 != last2) { //+F model
		return create_aagtr("molphy+f", &s[0], &s[190], first2, last2);
	}
	return create_aagtr("molphy", &s[0], &s[190], &p[0], &p[20]);
}

} // namespace dawg
 
#endif // DAWG_SUBST_AA_H
 
