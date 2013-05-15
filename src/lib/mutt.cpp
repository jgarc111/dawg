/****************************************************************************
 *  Copyright (C) 2009 Reed A. Cartwright, PhD <reed@scit.us>               *
 ****************************************************************************/

#include <dawg/mutt.h>

using namespace dawg;
 
// random zeta distribution with slope z > 1.0
#ifdef DAWG_USE_ZETA_LUC
// Devroye Luc (1986) Non-uniform random variate generation.
//     Springer-Verlag: Berlin. p551
boost::uint32_t dawg::mutt::rand_zeta(double z) {
	double b = pow(2.0, z-1.0);
	double x,t;
	do {
	 x = floor(pow(rand_real(), -1.0/(z-1.0)));
	 t = pow(1.0+1.0/x, z-1.0);
	} while( rand_real()*x*(t-1.0)*b > t*(b-1.0));
	return static_cast<boost::uint32_t>(x);
}
#else
// rejection-inversion method of H\"ormann and Derflinger (1996)
// idea borrowed from Indelible
// optimizations for usage in Dawg
boost::uint32_t dawg::mutt::rand_zeta(double z) {
	double z1 = 1.0-z;
	double z2 = 1.0/z1;
	double s = 2.0-zHi(zH(1.5,z1,z2)-pow(2.0,-z),z1,z2);
	double Him = zH(4294967296.5,z1,z2);
	double Hx0 = zH(0.5,z1,z2)-1.0-Him;
	
	double U, X,K;
	for(;;) {
		U = rand_real();
		U = Him+U*Hx0;
		X = zHi(U,z1,z2);
		K = floor(X+1.5);
		if(K-X < s)
			break;
		if(U > zH(K-0.5,z1,z2)-pow(K,-z))
			break;
	}
	return static_cast<boost::uint32_t>(K);
}
#endif

/* New version based on Marsaglia and Tsang, "A Simple Method for
 * generating gamma variables", ACM Transactions on Mathematical
 * Software, Vol 26, No 3 (2000), p363-372.
 *
 * Implemented by J.D.Lamb@btinternet.com, minor modifications for GSL
 * by Brian Gough
 *
 * Imported from GSL's gamma.c.
 */
double dawg::mutt::rand_gamma(double a, double b) {
	if(a < 1.0)
		return rand_gamma(1.0+a,b)*pow(rand_real(), 1.0/a);

	double x, v, u;
	double d = a - 1.0/3.0;
	double c = (1.0/3.0)/sqrt(d);

	for(;;) {
		do {
			x = rand_normal(1.0);
			v = 1.0 + c * x;
		} while (v <= 0);
		v = v * v * v;
		u = rand_real();
		x *= x;
		if (u < 1 - 0.0331 * x * x) 
			break;
		if (log(u) < 0.5 * x + d * (1 - v + log(v)))
			break;
	}
	return b*d*v;
}

/************************************************************
 * Tables for normal method                                 *
 ************************************************************/

/* tabulated values for the height of the Ziggurat levels */
static const double ytab[128] = {
  1, 0.963598623011, 0.936280813353, 0.913041104253,
  0.892278506696, 0.873239356919, 0.855496407634, 0.838778928349,
  0.822902083699, 0.807732738234, 0.793171045519, 0.779139726505,
  0.765577436082, 0.752434456248, 0.739669787677, 0.727249120285,
  0.715143377413, 0.703327646455, 0.691780377035, 0.68048276891,
  0.669418297233, 0.65857233912, 0.647931876189, 0.637485254896,
  0.62722199145, 0.617132611532, 0.607208517467, 0.597441877296,
  0.587825531465, 0.578352913803, 0.569017984198, 0.559815170911,
  0.550739320877, 0.541785656682, 0.532949739145, 0.524227434628,
  0.515614886373, 0.507108489253, 0.498704867478, 0.490400854812,
  0.482193476986, 0.47407993601, 0.466057596125, 0.458123971214,
  0.450276713467, 0.442513603171, 0.434832539473, 0.427231532022,
  0.419708693379, 0.41226223212, 0.404890446548, 0.397591718955,
  0.390364510382, 0.383207355816, 0.376118859788, 0.369097692334,
  0.362142585282, 0.355252328834, 0.348425768415, 0.341661801776,
  0.334959376311, 0.328317486588, 0.321735172063, 0.31521151497,
  0.308745638367, 0.302336704338, 0.29598391232, 0.289686497571,
  0.283443729739, 0.27725491156, 0.271119377649, 0.265036493387,
  0.259005653912, 0.253026283183, 0.247097833139, 0.241219782932,
  0.235391638239, 0.229612930649, 0.223883217122, 0.218202079518,
  0.212569124201, 0.206983981709, 0.201446306496, 0.195955776745,
  0.190512094256, 0.185114984406, 0.179764196185, 0.174459502324,
  0.169200699492, 0.1639876086, 0.158820075195, 0.153697969964,
  0.148621189348, 0.143589656295, 0.138603321143, 0.133662162669,
  0.128766189309, 0.123915440582, 0.119109988745, 0.114349940703,
  0.10963544023, 0.104966670533, 0.100343857232, 0.0957672718266,
  0.0912372357329, 0.0867541250127, 0.082318375932, 0.0779304915295,
  0.0735910494266, 0.0693007111742, 0.065060233529, 0.0608704821745,
  0.056732448584, 0.05264727098, 0.0486162607163, 0.0446409359769,
  0.0407230655415, 0.0368647267386, 0.0330683839378, 0.0293369977411,
  0.0256741818288, 0.0220844372634, 0.0185735200577, 0.0151490552854,
  0.0118216532614, 0.00860719483079, 0.00553245272614, 0.00265435214565
};

/* tabulated values for 2^24 times x[i]/x[i+1],
 * used to accept for U*x[i+1]<=x[i] without any floating point operations */
static const boost::uint32_t ktab[128] = {
  0, 12590644, 14272653, 14988939,
  15384584, 15635009, 15807561, 15933577,
  16029594, 16105155, 16166147, 16216399,
  16258508, 16294295, 16325078, 16351831,
  16375291, 16396026, 16414479, 16431002,
  16445880, 16459343, 16471578, 16482744,
  16492970, 16502368, 16511031, 16519039,
  16526459, 16533352, 16539769, 16545755,
  16551348, 16556584, 16561493, 16566101,
  16570433, 16574511, 16578353, 16581977,
  16585398, 16588629, 16591685, 16594575,
  16597311, 16599901, 16602354, 16604679,
  16606881, 16608968, 16610945, 16612818,
  16614592, 16616272, 16617861, 16619363,
  16620782, 16622121, 16623383, 16624570,
  16625685, 16626730, 16627708, 16628619,
  16629465, 16630248, 16630969, 16631628,
  16632228, 16632768, 16633248, 16633671,
  16634034, 16634340, 16634586, 16634774,
  16634903, 16634972, 16634980, 16634926,
  16634810, 16634628, 16634381, 16634066,
  16633680, 16633222, 16632688, 16632075,
  16631380, 16630598, 16629726, 16628757,
  16627686, 16626507, 16625212, 16623794,
  16622243, 16620548, 16618698, 16616679,
  16614476, 16612071, 16609444, 16606571,
  16603425, 16599973, 16596178, 16591995,
  16587369, 16582237, 16576520, 16570120,
  16562917, 16554758, 16545450, 16534739,
  16522287, 16507638, 16490152, 16468907,
  16442518, 16408804, 16364095, 16301683,
  16207738, 16047994, 15704248, 15472926
};

/* tabulated values of 2^{-24}*x[i] */
static const double wtab[128] = {
  1.62318314817e-08, 2.16291505214e-08, 2.54246305087e-08, 2.84579525938e-08,
  3.10340022482e-08, 3.33011726243e-08, 3.53439060345e-08, 3.72152672658e-08,
  3.8950989572e-08, 4.05763964764e-08, 4.21101548915e-08, 4.35664624904e-08,
  4.49563968336e-08, 4.62887864029e-08, 4.75707945735e-08, 4.88083237257e-08,
  5.00063025384e-08, 5.11688950428e-08, 5.22996558616e-08, 5.34016475624e-08,
  5.44775307871e-08, 5.55296344581e-08, 5.65600111659e-08, 5.75704813695e-08,
  5.85626690412e-08, 5.95380306862e-08, 6.04978791776e-08, 6.14434034901e-08,
  6.23756851626e-08, 6.32957121259e-08, 6.42043903937e-08, 6.51025540077e-08,
  6.59909735447e-08, 6.68703634341e-08, 6.77413882848e-08, 6.8604668381e-08,
  6.94607844804e-08, 7.03102820203e-08, 7.11536748229e-08, 7.1991448372e-08,
  7.2824062723e-08, 7.36519550992e-08, 7.44755422158e-08, 7.52952223703e-08,
  7.61113773308e-08, 7.69243740467e-08, 7.77345662086e-08, 7.85422956743e-08,
  7.93478937793e-08, 8.01516825471e-08, 8.09539758128e-08, 8.17550802699e-08,
  8.25552964535e-08, 8.33549196661e-08, 8.41542408569e-08, 8.49535474601e-08,
  8.57531242006e-08, 8.65532538723e-08, 8.73542180955e-08, 8.8156298059e-08,
  8.89597752521e-08, 8.97649321908e-08, 9.05720531451e-08, 9.138142487e-08,
  9.21933373471e-08, 9.30080845407e-08, 9.38259651738e-08, 9.46472835298e-08,
  9.54723502847e-08, 9.63014833769e-08, 9.71350089201e-08, 9.79732621669e-08,
  9.88165885297e-08, 9.96653446693e-08, 1.00519899658e-07, 1.0138063623e-07,
  1.02247952126e-07, 1.03122261554e-07, 1.04003996769e-07, 1.04893609795e-07,
  1.05791574313e-07, 1.06698387725e-07, 1.07614573423e-07, 1.08540683296e-07,
  1.09477300508e-07, 1.1042504257e-07, 1.11384564771e-07, 1.12356564007e-07,
  1.13341783071e-07, 1.14341015475e-07, 1.15355110887e-07, 1.16384981291e-07,
  1.17431607977e-07, 1.18496049514e-07, 1.19579450872e-07, 1.20683053909e-07,
  1.21808209468e-07, 1.2295639141e-07, 1.24129212952e-07, 1.25328445797e-07,
  1.26556042658e-07, 1.27814163916e-07, 1.29105209375e-07, 1.30431856341e-07,
  1.31797105598e-07, 1.3320433736e-07, 1.34657379914e-07, 1.36160594606e-07,
  1.37718982103e-07, 1.39338316679e-07, 1.41025317971e-07, 1.42787873535e-07,
  1.44635331499e-07, 1.4657889173e-07, 1.48632138436e-07, 1.50811780719e-07,
  1.53138707402e-07, 1.55639532047e-07, 1.58348931426e-07, 1.61313325908e-07,
  1.64596952856e-07, 1.68292495203e-07, 1.72541128694e-07, 1.77574279496e-07,
  1.83813550477e-07, 1.92166040885e-07, 2.05295471952e-07, 2.22600839893e-07
};

/*
 *     Ziggurat method as implemented in GSL
 *     George Marsaglia, Wai Wan Tsang
 *     The Ziggurat Method for Generating Random Variables
 *     Journal of Statistical Software, vol. 5 (2000), no. 8
 *     http://www.jstatsoft.org/v05/i08/
 */
 /* position of right-most step */
#define PARAM_R 3.44428647676
double dawg::mutt::rand_normal(double sigma) {
	boost::uint32_t i, j;
	int sign;
	double x, y;

	for(;;) {
		boost::uint32_t k = rand_uint32();
		i = (k & 0xFF);
		j = (k >> 8) & 0xFFFFFF;

		sign = (i & 0x80) ? +1 : -1;
		i &= 0x7f;

		x = j * wtab[i];

		if (j < ktab[i])
			break;

		if(i < 127) {
			double y0 = ytab[i], y1 = ytab[i + 1];
			double U1 = rand_real();
			y = y1 + (y0 - y1) * U1;
		} else {
			double U1 = rand_real();
			double U2 = rand_real();
			x = PARAM_R - log(U1) / PARAM_R;
			y = exp(-PARAM_R * (x - 0.5 * PARAM_R)) * U2;
		}

		if (y < exp(-0.5 * x * x))
			break;
    }
	return sign * sigma * x;	
}

/************************************************************
 * Tables for exponential                                   *
 ************************************************************/

const double dawg::mutt::ew[256] = {
	4.71471682773886080e-019, 3.46143273630631480e-021, 5.68330688314998230e-021, 7.44331793141216200e-021,
	8.95158635607294880e-021, 1.02976811985570430e-020, 1.15289456925934260e-020, 1.26738074819867670e-020,
	1.37508474326061920e-020, 1.47729693863348570e-020, 1.57495520255682210e-020, 1.66876579110596870e-020,
	1.75927586852268040e-020, 1.84691932464338150e-020, 1.93204697172731940e-020, 2.01494715731247230e-020,
	2.09586025802857520e-020, 2.17498913246209390e-020, 2.25250682689608570e-020, 2.32856236585187150e-020,
	2.40328517760154320e-020, 2.47678852758942640e-020, 2.54917221816048390e-020, 2.62052473716708570e-020,
	2.69092498673588550e-020, 2.76044368810530560e-020, 2.82914453361951370e-020, 2.89708513926217800e-020,
	2.96431783830428570e-020, 3.03089034724765190e-020, 3.09684632827298540e-020, 3.16222586716608320e-020,
	3.22706588172334060e-020, 3.29140047259410090e-020, 3.35526122616396970e-020, 3.41867747724801130e-020,
	3.48167653792023480e-020, 3.54428389766340130e-020, 3.60652339911220130e-020, 3.66841739293150610e-020,
	3.72998687478067490e-020, 3.79125160683488560e-020, 3.85223022594227930e-020, 3.91294034017356110e-020,
	3.97339861525476550e-020, 4.03362085215333770e-020, 4.09362205690387540e-020, 4.15341650360611360e-020,
	4.21301779139849090e-020, 4.27243889610165040e-020, 4.33169221713391100e-020, 4.39078962022234110e-020,
	4.44974247636616540e-020, 4.50856169745204320e-020, 4.56725776887164320e-020, 4.62584077944968060e-020,
	4.68432044895409840e-020, 4.74270615342847530e-020, 4.80100694855932990e-020, 4.85923159126712310e-020,
	4.91738855968893830e-020, 4.97548607170260600e-020, 5.03353210212608200e-020, 5.09153439871185700e-020,
	5.14950049704382890e-020, 5.20743773443317670e-020, 5.26535326290013790e-020, 5.32325406132007010e-020,
	5.38114694680458000e-020, 5.43903858538182250e-020, 5.49693550203401970e-020, 5.55484409014494360e-020,
	5.61277062040531760e-020, 5.67072124921981480e-020, 5.72870202665549580e-020, 5.78671890396811250e-020,
	5.84477774073957480e-020, 5.90288431165715590e-020, 5.96104431296243120e-020, 6.01926336859577610e-020,
	6.07754703606011850e-020, 6.13590081202587040e-020, 6.19433013769725360e-020, 6.25284040395873720e-020,
	6.31143695631894190e-020, 6.37012509966810960e-020, 6.42891010286412270e-020, 6.48779720316103950e-020,
	6.54679161049316010e-020, 6.60589851162683210e-020, 6.66512307419139540e-020, 6.72447045060000590e-020,
	6.78394578187042930e-020, 6.84355420135532980e-020, 6.90330083839104100e-020, 6.96319082187336640e-020,
	7.02322928376850790e-020, 7.08342136256683560e-020, 7.14377220668689440e-020, 7.20428697783667910e-020,
	7.26497085433899450e-020, 7.32582903442742770e-020, 7.38686673951923670e-020, 7.44808921747131860e-020,
	7.50950174582518150e-020, 7.57110963504676580e-020, 7.63291823176678710e-020, 7.69493292202722970e-020,
	7.75715913453947460e-020, 7.81960234395955560e-020, 7.88226807418593220e-020, 7.94516190168520870e-020,
	8.00828945885116430e-020, 8.07165643740252640e-020, 8.13526859182491360e-020, 8.19913174286244680e-020,
	8.26325178106456310e-020, 8.32763467039370150e-020, 8.39228645189956980e-020, 8.45721324746586240e-020,
	8.52242126363542100e-020, 8.58791679551997860e-020, 8.65370623080081410e-020, 8.71979605382682060e-020,
	8.78619284981671860e-020, 8.85290330917237210e-020, 8.91993423191041270e-020, 8.98729253221966830e-020,
	9.05498524315219580e-020, 9.12301952145602020e-020, 9.19140265255806790e-020, 9.26014205570613750e-020,
	9.32924528927918350e-020, 9.39872005627560700e-020, 9.46857420998974570e-020, 9.53881575988725400e-020,
	9.60945287769061580e-020, 9.68049390368662010e-020, 9.75194735326827430e-020, 9.82382192372429280e-020,
	9.89612650129003430e-020, 9.96887016847455820e-020, 1.00420622116792890e-019, 1.01157121291246950e-019,
	1.01898296391023450e-019, 1.02644246885707680e-019, 1.03395074621146310e-019, 1.04150883912879860e-019,
	1.04911781643635920e-019, 1.05677877365117440e-019, 1.06449283404335170e-019, 1.07226114974749560e-019,
	1.08008490292504700e-019, 1.08796530698055710e-019, 1.09590360783511160e-019, 1.10390108526033870e-019,
	1.11195905427667040e-019, 1.12007886661978090e-019, 1.12826191227940130e-019, 1.13650962111500740e-019,
	1.14482346455320230e-019, 1.15320495737196020e-019, 1.16165565957728380e-019, 1.17017717837823440e-019,
	1.17877117026674480e-019, 1.18743934320910940e-019, 1.19618345895657750e-019, 1.20500533548305140e-019,
	1.21390684955852160e-019, 1.22288993946755710e-019, 1.23195660788291850e-019, 1.24110892490518180e-019,
	1.25034903128016150e-019, 1.25967914180689990e-019, 1.26910154895007150e-019, 1.27861862667183800e-019,
	1.28823283449948360e-019, 1.29794672184660380e-019, 1.30776293260719000e-019, 1.31768421004369580e-019,
	1.32771340199209890e-019, 1.33785346640908930e-019, 1.34810747728887530e-019, 1.35847863097970510e-019,
	1.36897025293309740e-019, 1.37958580492199860e-019, 1.39032889276766310e-019, 1.40120327461905160e-019,
	1.41221286983300570e-019, 1.42336176850844390e-019, 1.43465424173341220e-019, 1.44609475261009040e-019,
	1.45768796812990470e-019, 1.46943877197881720e-019, 1.48135227836181760e-019, 1.49343384694573240e-019,
	1.50568909903091280e-019, 1.51812393507532510e-019, 1.53074455370930820e-019, 1.54355747239604770e-019,
	1.55656954991196930e-019, 1.56978801084316280e-019, 1.58322047231906820e-019, 1.59687497323351580e-019,
	1.61076000623646640e-019, 1.62488455281819890e-019, 1.63925812185217000e-019, 1.65389079201440660e-019,
	1.66879325855743970e-019, 1.68397688498702340e-019, 1.69945376027218840e-019, 1.71523676231590770e-019,
	1.73133962852773020e-019, 1.74777703447474420e-019, 1.76456468174758790e-019, 1.78171939636940530e-019,
	1.79925923930450210e-019, 1.81720363089853850e-019, 1.83557349141418730e-019, 1.85439140022894230e-019,
	1.87368177675254550e-019, 1.89347108672260490e-019, 1.91378807827706460e-019, 1.93466405311854220e-019,
	1.95613317922682700e-019, 1.97823285300613920e-019, 2.00100412055813600e-019, 2.02449217006391830e-019,
	2.04874691019208930e-019, 2.07382365323456300e-019, 2.09978392659544470e-019, 2.12669644272165630e-019,
	2.15463826613089370e-019, 2.18369622766598260e-019, 2.21396865164347390e-019, 2.24556748286422480e-019,
	2.27862093003490030e-019, 2.31327678381957620e-019, 2.34970662735802630e-019, 2.38811124384385250e-019,
	2.42872765439059560e-019, 2.47183841413289050e-019, 2.51778409613187640e-019, 2.56698037208118890e-019,
	2.61994188335547880e-019, 2.67731642297788230e-019, 2.73993528060310480e-019, 2.80888988354654820e-019,
	2.88565314533794040e-019, 2.97228096493208380e-019, 3.07176710687380720e-019, 3.18871682302931680e-019,
	3.33075833936959410e-019, 3.51193601859832110e-019, 3.76274187013285970e-019, 4.17261574149610710e-019
};

const double dawg::mutt::ef[256] = {
	1.00000000000000000e+000, 9.38143680862175370e-001, 9.00469929925746930e-001, 8.71704332381204040e-001,
	8.47785500623989940e-001, 8.26993296643050660e-001, 8.08421651523008710e-001, 7.91527636972495950e-001,
	7.75956852040115890e-001, 7.61463388849896510e-001, 7.47868621985195330e-001, 7.35038092431423710e-001,
	7.22867659593572240e-001, 7.11274760805076230e-001, 7.00192655082788380e-001, 6.89566496117078210e-001,
	6.79350572264765580e-001, 6.69506316731924960e-001, 6.60000841078999920e-001, 6.50805833414571210e-001,
	6.41896716427266200e-001, 6.33251994214366180e-001, 6.24852738703665980e-001, 6.16682180915207660e-001,
	6.08725382079622120e-001, 6.00968966365232340e-001, 5.93400901691733540e-001, 5.86010318477268140e-001,
	5.78787358602845140e-001, 5.71723048664825930e-001, 5.64809192912400390e-001, 5.58038282262587670e-001,
	5.51403416540641510e-001, 5.44898237672439830e-001, 5.38516872002862020e-001, 5.32253880263043430e-001,
	5.26104213983619840e-001, 5.20063177368233710e-001, 5.14126393814748670e-001, 5.08289776410642990e-001,
	5.02549501841347830e-001, 4.96901987241549660e-001, 4.91343869594032650e-001, 4.85871987341885030e-001,
	4.80483363930454320e-001, 4.75175193037377490e-001, 4.69944825283960090e-001, 4.64789756250426290e-001,
	4.59707615642137800e-001, 4.54696157474615610e-001, 4.49753251162755110e-001, 4.44876873414548620e-001,
	4.40065100842354010e-001, 4.35316103215636740e-001, 4.30628137288459000e-001, 4.25999541143034510e-001,
	4.21428728997616740e-001, 4.16914186433003040e-001, 4.12454465997161290e-001, 4.08048183152032510e-001,
	4.03694012530530390e-001, 3.99390684475231180e-001, 3.95136981833290270e-001, 3.90931736984797220e-001,
	3.86773829084137770e-001, 3.82662181496009890e-001, 3.78595759409580900e-001, 3.74573567615902210e-001,
	3.70594648435146060e-001, 3.66658079781514210e-001, 3.62762973354817830e-001, 3.58908472948749830e-001,
	3.55093752866787520e-001, 3.51318016437483390e-001, 3.47580494621637040e-001, 3.43880444704502460e-001,
	3.40217149066780080e-001, 3.36589914028677610e-001, 3.32998068761808990e-001, 3.29440964264136380e-001,
	3.25917972393556240e-001, 3.22428484956089170e-001, 3.18971912844957240e-001, 3.15547685227128950e-001,
	3.12155248774179610e-001, 3.08794066934560190e-001, 3.05463619244590260e-001, 3.02163400675693530e-001,
	2.98892921015581850e-001, 2.95651704281261250e-001, 2.92439288161892630e-001, 2.89255223489677690e-001,
	2.86099073737076830e-001, 2.82970414538780750e-001, 2.79868833236972870e-001, 2.76793928448517300e-001,
	2.73745309652802920e-001, 2.70722596799059970e-001, 2.67725419932044740e-001, 2.64753418835062150e-001,
	2.61806242689362920e-001, 2.58883549749016170e-001, 2.55985007030415320e-001, 2.53110290015629400e-001,
	2.50259082368862240e-001, 2.47431075665327540e-001, 2.44625969131892020e-001, 2.41843469398877130e-001,
	2.39083290262449090e-001, 2.36345152457059560e-001, 2.33628783437433290e-001, 2.30933917169627360e-001,
	2.28260293930716620e-001, 2.25607660116683960e-001, 2.22975768058120110e-001, 2.20364375843359440e-001,
	2.17773247148700470e-001, 2.15202151075378630e-001, 2.12650861992978220e-001, 2.10119159388988230e-001,
	2.07606827724221980e-001, 2.05113656293837650e-001, 2.02639439093708960e-001, 2.00183974691911210e-001,
	1.97747066105098820e-001, 1.95328520679563190e-001, 1.92928149976771300e-001, 1.90545769663195360e-001,
	1.88181199404254260e-001, 1.85834262762197080e-001, 1.83504787097767440e-001, 1.81192603475496260e-001,
	1.78897546572478280e-001, 1.76619454590494830e-001, 1.74358169171353410e-001, 1.72113535315319980e-001,
	1.69885401302527550e-001, 1.67673618617250080e-001, 1.65478041874935920e-001, 1.63298528751901730e-001,
	1.61134939917591950e-001, 1.58987138969314130e-001, 1.56854992369365150e-001, 1.54738369384468030e-001,
	1.52637142027442800e-001, 1.50551185001039840e-001, 1.48480375643866740e-001, 1.46424593878344890e-001,
	1.44383722160634720e-001, 1.42357645432472150e-001, 1.40346251074862400e-001, 1.38349428863580180e-001,
	1.36367070926428830e-001, 1.34399071702213600e-001, 1.32445327901387490e-001, 1.30505738468330770e-001,
	1.28580204545228200e-001, 1.26668629437510670e-001, 1.24770918580830930e-001, 1.22886979509545110e-001,
	1.21016721826674790e-001, 1.19160057175327640e-001, 1.17316899211555530e-001, 1.15487163578633510e-001,
	1.13670767882744290e-001, 1.11867631670056280e-001, 1.10077676405185360e-001, 1.08300825451033760e-001,
	1.06537004050001630e-001, 1.04786139306570140e-001, 1.03048160171257700e-001, 1.01322997425953630e-001,
	9.96105836706371320e-002, 9.79108533114922130e-002, 9.62237425504328250e-002, 9.45491893760558730e-002,
	9.28871335560435690e-002, 9.12375166310401970e-002, 8.96002819100328860e-002, 8.79753744672702450e-002,
	8.63627411407569270e-002, 8.47623305323681460e-002, 8.31740930096323970e-002, 8.15979807092374190e-002,
	8.00339475423199050e-002, 7.84819492016064350e-002, 7.69419431704805170e-002, 7.54138887340584100e-002,
	7.38977469923647460e-002, 7.23934808757087520e-002, 7.09010551623718430e-002, 6.94204364987287830e-002,
	6.79515934219366430e-002, 6.64944963853398160e-002, 6.50491177867538050e-002, 6.36154319998073760e-002,
	6.21934154085410360e-002, 6.07830464454796600e-002, 5.93843056334202800e-002, 5.79971756312006590e-002,
	5.66216412837428700e-002, 5.52576896766970300e-002, 5.39053101960460800e-002, 5.25644945930716850e-002,
	5.12352370551262810e-002, 4.99175342827063790e-002, 4.86113855733795040e-002, 4.73167929131815610e-002,
	4.60337610761751840e-002, 4.47622977329432890e-002, 4.35024135688881970e-002, 4.22541224133162540e-002,
	4.10174413804148400e-002, 3.97923910233741390e-002, 3.85789955030748710e-002, 3.73772827729593820e-002,
	3.61872847819314430e-002, 3.50090376973974310e-002, 3.38425821508743580e-002, 3.26879635089595550e-002,
	3.15452321728936220e-002, 3.04144439104666220e-002, 2.92956602246374110e-002, 2.81889487639786460e-002,
	2.70943837809558030e-002, 2.60120466451342210e-002, 2.49420264197317870e-002, 2.38844205115581740e-002,
	2.28393354063852400e-002, 2.18068875042835810e-002, 2.07872040725781140e-002, 1.97804243380097400e-002,
	1.87867007446960240e-002, 1.78062004109113550e-002, 1.68391068260399410e-002, 1.58856218399731560e-002,
	1.49459680116911480e-002, 1.40203914031819430e-002, 1.31091649312549910e-002, 1.22125924262553780e-002,
	1.13310135978346000e-002, 1.04648101810299810e-002, 9.61441364250221160e-003, 8.78031498580897700e-003,
	7.96307743801704350e-003, 7.16335318363499080e-003, 6.38190593731918340e-003, 5.61964220720548910e-003,
	4.87765598354239580e-003, 4.15729512083379700e-003, 3.46026477783690400e-003, 2.78879879357407570e-003,
	2.14596774371890710e-003, 1.53629978030157260e-003, 9.67269282327174320e-004, 4.54134353841496600e-004
};

#define U UINT64_C
const boost::uint64_t dawg::mutt::ek[256] = {
	U(0xe290a13924be2800), U(0x0000000000000000), U(0x9beadebce18ae800), U(0xc377ac71f9e02000),
	U(0xd4ddb99075853000), U(0xde893fb8ca23d800), U(0xe4a8e87c4328d800), U(0xe8dff16ae1cb8000),
	U(0xebf2deab58c59800), U(0xee49a6e8b9637800), U(0xf0204efd64ee4800), U(0xf19bdb8ea3c1b000),
	U(0xf2d458bbe5bd2000), U(0xf3da104b78236800), U(0xf4b86d784571e000), U(0xf577ad8a7784f800),
	U(0xf61de83da32ac000), U(0xf6afb7843cce6800), U(0xf730a57372b44000), U(0xf7a37651b0e68000),
	U(0xf80a5bb6eea51800), U(0xf867189d3cb5a800), U(0xf8bb1b4f8fbbc800), U(0xf9079062292b9000),
	U(0xf94d70ca8d43b000), U(0xf98d8c7dcaa99800), U(0xf9c8928abe084800), U(0xf9ff175b734a6000),
	U(0xfa319996bc47d800), U(0xfa6085f8e9d07800), U(0xfa8c3a62e1991800), U(0xfab5084e1f660800),
	U(0xfadb36c84cccb800), U(0xfaff041086846800), U(0xfb20a6ea22bb8000), U(0xfb404fb42cb3d000),
	U(0xfb5e295158173800), U(0xfb7a59e99727a800), U(0xfb95038c8789d800), U(0xfbae44ba684ec000),
	U(0xfbc638d822e60800), U(0xfbdcf89209ffa800), U(0xfbf29a303cfc5000), U(0xfc0731df1089c000),
	U(0xfc1ad1ed6c8b1800), U(0xfc2d8b02b5c89800), U(0xfc3f6c4d92131800), U(0xfc5083ac9ba7d800),
	U(0xfc60ddd1e9cd7000), U(0xfc7086622e825000), U(0xfc7f881009f0b800), U(0xfc8decb41ac70800),
	U(0xfc9bbd623d7ec800), U(0xfca9027c5b26e000), U(0xfcb5c3c319c49800), U(0xfcc20864b4449000),
	U(0xfccdd70a35d40800), U(0xfcd935e34bf80000), U(0xfce42ab0db8bd000), U(0xfceebace7ec02000),
	U(0xfcf8eb3b0d0e7800), U(0xfd02c0a049b60800), U(0xfd0c3f59d199d000), U(0xfd156b7b5e27e000),
	U(0xfd1e48d670341800), U(0xfd26daff73551800), U(0xfd2f2552684bf800), U(0xfd372af7233c1000),
	U(0xfd3eeee528f62800), U(0xfd4673e73543b000), U(0xfd4dbc9e72ff8000), U(0xfd54cb856dc2c000),
	U(0xfd5ba2f2c4119800), U(0xfd62451ba02c2800), U(0xfd68b415fcff5800), U(0xfd6ef1dabc160800),
	U(0xfd75004790eb7000), U(0xfd7ae120c583e800), U(0xfd809612dbd0a800), U(0xfd8620b40effa800),
	U(0xfd8b8285b78fe000), U(0xfd90bcf594b1d800), U(0xfd95d15efd425800), U(0xfd9ac10bfa70c800),
	U(0xfd9f8d364df06800), U(0xfda437086566b800), U(0xfda8bf9e3c9ff000), U(0xfdad28062fed5000),
	U(0xfdb17141bff2d000), U(0xfdb59c4648085800), U(0xfdb9a9fda83cc000), U(0xfdbd9b46e3ed4000),
	U(0xfdc170f6b5d05000), U(0xfdc52bd81a3fb000), U(0xfdc8ccacd07ba000), U(0xfdcc542dd3902000),
	U(0xfdcfc30bcb793000), U(0xfdd319ef77143800), U(0xfdd6597a0f60b800), U(0xfdd98245a48a2800),
	U(0xfddc94e575272000), U(0xfddf91e64014e800), U(0xfde279ce914cb000), U(0xfde54d1f0a06a800),
	U(0xfde80c52a47d0000), U(0xfdeab7def394e000), U(0xfded50345eb36000), U(0xfdefd5be59fa1000),
	U(0xfdf248e39b26f800), U(0xfdf4aa064b4b0000), U(0xfdf6f98435894800), U(0xfdf937b6f30ba800),
	U(0xfdfb64f414571800), U(0xfdfd818d48262000), U(0xfdff8dd07fed9000), U(0xfe018a08122c4800),
	U(0xfe03767adaa5a000), U(0xfe05536c58a14000), U(0xfe07211ccb4c5800), U(0xfe08dfc94c532800),
	U(0xfe0a8fabe8ca1800), U(0xfe0c30fbb87a6000), U(0xfe0dc3ecf3a5a000), U(0xfe0f48b107521800),
	U(0xfe10bf76a82ef800), U(0xfe122869e4200000), U(0xfe1383b4327e1000), U(0xfe14d17c83188000),
	U(0xfe1611e74c023000), U(0xfe1745169635a800), U(0xfe186b2a09177000), U(0xfe19843ef4e07800),
	U(0xfe1a90705bf64000), U(0xfe1b8fd6fb37c000), U(0xfe1c828951443800), U(0xfe1d689ba4bfd000),
	U(0xfe1e4220099a4800), U(0xfe1f0f26655a0000), U(0xfe1fcfbc726d4800), U(0xfe2083edc2830800),
	U(0xfe212bc3bfeb4000), U(0xfe21c745adfe3800), U(0xfe225678a8895800), U(0xfe22d95fa23f4800),
	U(0xfe234ffb62282800), U(0xfe23ba4a800d9000), U(0xfe2418495fddd000), U(0xfe2469f22bffb800),
	U(0xfe24af3cce90e000), U(0xfe24e81ee9858800), U(0xfe25148bcda1a000), U(0xfe253474703fe000),
	U(0xfe2547c75fdc6800), U(0xfe254e70b754f800), U(0xfe25485a0fd1b000), U(0xfe25356a71450800),
	U(0xfe2515864173b000), U(0xfe24e88f316f1800), U(0xfe24ae64296fa000), U(0xfe2466e132f60800),
	U(0xfe2411df611bd000), U(0xfe23af34b6f73800), U(0xfe233eb40bf41800), U(0xfe22c02cee01c000),
	U(0xfe22336b81711000), U(0xfe2198385e5cd000), U(0xfe20ee586b707000), U(0xfe20358cb5dfb800),
	U(0xfe1f6d92465b1000), U(0xfe1e9621f2c9f000), U(0xfe1daef02c8da800), U(0xfe1cb7accb0a6800),
	U(0xfe1bb002d22ca000), U(0xfe1a9798349b9000), U(0xfe196e0d9140d800), U(0xfe1832fdebc44000),
	U(0xfe16e5fe5f932000), U(0xfe15869dccfd0000), U(0xfe1414647fe78000), U(0xfe128ed3cf8b2000),
	U(0xfe10f565b69cf000), U(0xfe0f478c633ab800), U(0xfe0d84b1bdd9e800), U(0xfe0bac36e6687800),
	U(0xfe09bd73a6b5c000), U(0xfe07b7b5d920b000), U(0xfe059a40c26d2000), U(0xfe03644c5d7f8800),
	U(0xfe011504979b2800), U(0xfdfeab887b95d000), U(0xfdfc26e94a448000), U(0xfdf986297e306800),
	U(0xfdf6c83bb8663000), U(0xfdf3ec0193eee000), U(0xfdf0f04a5d30a800), U(0xfdedd3d1aa204000),
	U(0xfdea953dcfc13000), U(0xfde7331e3100d800), U(0xfde3abe9626f2800), U(0xfddffdfb1dbd5000),
	U(0xfddc2791ff351000), U(0xfdd826cd068c7000), U(0xfdd3f9a8d3856800), U(0xfdcf9dfc95b0d000),
	U(0xfdcb1176a55fe000), U(0xfdc65198ba50c000), U(0xfdc15bb3b2daa000), U(0xfdbc2ce2dc4ae800),
	U(0xfdb6c206aaaca000), U(0xfdb117becb4a1800), U(0xfdab2a6379bf1000), U(0xfda4f5fdfb4e9800),
	U(0xfd9e76401f3a3800), U(0xfd97a67a9ce20000), U(0xfd9081922142a000), U(0xfd8901f2d4b02800),
	U(0xfd812182170e1800), U(0xfd78d98e23cd3800), U(0xfd7022bb3f083000), U(0xfd66f4edf96b9800),
	U(0xfd5d473200305800), U(0xfd530f9ccff94800), U(0xfd48432b7b351000), U(0xfd3cd59a8469e800),
	U(0xfd30b9368f909800), U(0xfd23dea45f500000), U(0xfd16349e2e04a800), U(0xfd07a7a3ef98b000),
	U(0xfcf8219b5df05800), U(0xfce7895bcfcde800), U(0xfcd5c220ad5e2800), U(0xfcc2aadbc17dc800),
	U(0xfcae1d5e81fbd000), U(0xfc97ed4e778f9800), U(0xfc7fe6d4d720e800), U(0xfc65ccf39c2fc000),
	U(0xfc4957623cb04000), U(0xfc2a2fc826dc8000), U(0xfc07ee19b01cd800), U(0xfbe213c1cf493000),
	U(0xfbb8051ac1567000), U(0xfb890078d120e800), U(0xfb5411a5b9a96000), U(0xfb18000547133800),
	U(0xfad334827f1e3000), U(0xfa839276708b9800), U(0xfa263b32e37ed800), U(0xf9b72d1c52cd2000),
	U(0xf930a1a281a04800), U(0xf889f023d820a000), U(0xf7b577d2be5f3800), U(0xf69c650c40a8f000),
	U(0xf51530f0916d9000), U(0xf2cb0e3c5933e800), U(0xeeefb15d605d8800), U(0xe6da6ecf27460000)
};
#undef U
