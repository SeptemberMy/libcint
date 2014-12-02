/*
 * Copyright (C) 2013  Qiming Sun <osirpt.sun@gmail.com>
 * Description: code generated by  gen-code.cl
 */
#include <string.h>
#include "cint_bas.h"
#include "cart2sph.h"
#include "g2e.h"
#include "optimizer.h"
#include "cint1e.h"
#include "cint2e.h"
#include "misc.h"
#include "fblas.h"
#include "c2f.h"
/* <k i|GAUNT |SIGMA DOT P j SIGMA DOT P l> : i,jin electron 1; k,lin electron 2
 * = (i SIGMA DOT P j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_cint2e_ssp1ssp2(double *g,
double *gout, const int *idx, const CINTEnvVars *envs, int gout_empty) {
const double *env = envs->env;
const int nf = envs->nf;
const int i_l = envs->i_l;
const int j_l = envs->j_l;
const int k_l = envs->k_l;
const int l_l = envs->l_l;
const double *ri = envs->ri;
const double *rj = envs->rj;
const double *rk = envs->rk;
const double *rl = envs->rl;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double *g4 = g3 + envs->g_size * 3;
double s[9];
G2E_D_L(g1, g0, i_l+0, j_l+1, k_l+0, l_l+0);
G2E_D_J(g2, g0, i_l+0, j_l+0, k_l, l_l);
G2E_D_J(g3, g1, i_l+0, j_l+0, k_l, l_l);
for (n = 0; n < nf; n++, idx+=3) {
ix = idx[0];
iy = idx[1];
iz = idx[2];
CINTdset0(9, s);
for (i = 0; i < envs->nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[0] = + (1*s[8]) + (1*s[4]);
gout[1] = + (-1*s[1]);
gout[2] = + (-1*s[2]);
gout[3] = + (1*s[5]) + (-1*s[7]);
gout[4] = + (-1*s[3]);
gout[5] = + (1*s[8]) + (1*s[0]);
gout[6] = + (-1*s[5]);
gout[7] = + (-1*s[2]) + (1*s[6]);
gout[8] = + (-1*s[6]);
gout[9] = + (-1*s[7]);
gout[10] = + (1*s[4]) + (1*s[0]);
gout[11] = + (1*s[1]) + (-1*s[3]);
gout[12] = + (1*s[7]) + (-1*s[5]);
gout[13] = + (-1*s[6]) + (1*s[2]);
gout[14] = + (1*s[3]) + (-1*s[1]);
gout[15] = + (1*s[0]) + (1*s[4]) + (1*s[8]);
gout += 16;
} else {
gout[0] += + (1*s[8]) + (1*s[4]);
gout[1] += + (-1*s[1]);
gout[2] += + (-1*s[2]);
gout[3] += + (1*s[5]) + (-1*s[7]);
gout[4] += + (-1*s[3]);
gout[5] += + (1*s[8]) + (1*s[0]);
gout[6] += + (-1*s[5]);
gout[7] += + (-1*s[2]) + (1*s[6]);
gout[8] += + (-1*s[6]);
gout[9] += + (-1*s[7]);
gout[10] += + (1*s[4]) + (1*s[0]);
gout[11] += + (1*s[1]) + (-1*s[3]);
gout[12] += + (1*s[7]) + (-1*s[5]);
gout[13] += + (-1*s[6]) + (1*s[2]);
gout[14] += + (1*s[3]) + (-1*s[1]);
gout[15] += + (1*s[0]) + (1*s[4]) + (1*s[8]);
gout += 16;
}}}
void cint2e_ssp1ssp2_optimizer(CINTOpt **opt, const int *atm, const int natm,
const int *bas, const int nbas, const double *env) {
int ng[] = {0, 1, 0, 1, 0, 0, 0, 0, 0};
CINTuse_all_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int cint2e_ssp1ssp2(double *opkijl, const int *shls,
const int *atm, const int natm,
const int *bas, const int nbas, const double *env, CINTOpt *opt) {
int ng[] = {0, 1, 0, 1, 0, 2, 4, 4, 1};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_cint2e_ssp1ssp2;
envs.common_factor *= 1;
return CINT2e_spinor_drv(opkijl, &envs, opt, &c2s_si_2e1i, &c2s_si_2e2i);
}
OPTIMIZER2F_(cint2e_ssp1ssp2_optimizer);
C2Fo_(cint2e_ssp1ssp2)
/* <k RC CROSS SIGMA i|GAUNT |j SIGMA DOT P l> : i,jin electron 1; k,lin electron 2
 * = (RC CROSS SIGMA i j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_cint2e_cg_ssa10ssp2(double *g,
double *gout, const int *idx, const CINTEnvVars *envs, int gout_empty) {
const double *env = envs->env;
const int nf = envs->nf;
const int i_l = envs->i_l;
const int j_l = envs->j_l;
const int k_l = envs->k_l;
const int l_l = envs->l_l;
const double *ri = envs->ri;
const double *rj = envs->rj;
const double *rk = envs->rk;
const double *rl = envs->rl;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double *g4 = g3 + envs->g_size * 3;
double s[9];
double dri[3];
dri[0] = ri[0] - env[PTR_COMMON_ORIG+0];
dri[1] = ri[1] - env[PTR_COMMON_ORIG+1];
dri[2] = ri[2] - env[PTR_COMMON_ORIG+2];
G2E_D_L(g1, g0, i_l+1, j_l+0, k_l+0, l_l+0);
G2E_RCI(g2, g0, i_l+0, j_l, k_l, l_l);
G2E_RCI(g3, g1, i_l+0, j_l, k_l, l_l);
for (n = 0; n < nf; n++, idx+=3) {
ix = idx[0];
iy = idx[1];
iz = idx[2];
CINTdset0(9, s);
for (i = 0; i < envs->nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[0] = + (1*s[5]) + (-1*s[7]);
gout[1] = 0;
gout[2] = 0;
gout[3] = + (1*s[8]) + (1*s[4]);
gout[4] = + (1*s[6]);
gout[5] = + (1*s[5]);
gout[6] = + (1*s[8]);
gout[7] = + (-1*s[3]);
gout[8] = + (-1*s[3]);
gout[9] = + (-1*s[4]);
gout[10] = + (-1*s[7]);
gout[11] = + (-1*s[6]);
gout[12] = + (1*s[4]) + (1*s[8]);
gout[13] = + (-1*s[3]);
gout[14] = + (-1*s[6]);
gout[15] = + (1*s[7]) + (-1*s[5]);
gout[16] = + (-1*s[2]);
gout[17] = + (-1*s[7]);
gout[18] = + (-1*s[8]);
gout[19] = + (-1*s[1]);
gout[20] = 0;
gout[21] = + (-1*s[2]) + (1*s[6]);
gout[22] = 0;
gout[23] = + (1*s[8]) + (1*s[0]);
gout[24] = + (1*s[0]);
gout[25] = + (1*s[1]);
gout[26] = + (1*s[6]);
gout[27] = + (-1*s[7]);
gout[28] = + (-1*s[1]);
gout[29] = + (1*s[0]) + (1*s[8]);
gout[30] = + (-1*s[7]);
gout[31] = + (-1*s[6]) + (1*s[2]);
gout[32] = + (1*s[1]);
gout[33] = + (1*s[4]);
gout[34] = + (1*s[5]);
gout[35] = + (-1*s[2]);
gout[36] = + (-1*s[0]);
gout[37] = + (-1*s[3]);
gout[38] = + (-1*s[2]);
gout[39] = + (-1*s[5]);
gout[40] = 0;
gout[41] = 0;
gout[42] = + (1*s[1]) + (-1*s[3]);
gout[43] = + (1*s[4]) + (1*s[0]);
gout[44] = + (-1*s[2]);
gout[45] = + (-1*s[5]);
gout[46] = + (1*s[0]) + (1*s[4]);
gout[47] = + (1*s[3]) + (-1*s[1]);
gout += 48;
} else {
gout[0] += + (1*s[5]) + (-1*s[7]);
gout[1] += 0;
gout[2] += 0;
gout[3] += + (1*s[8]) + (1*s[4]);
gout[4] += + (1*s[6]);
gout[5] += + (1*s[5]);
gout[6] += + (1*s[8]);
gout[7] += + (-1*s[3]);
gout[8] += + (-1*s[3]);
gout[9] += + (-1*s[4]);
gout[10] += + (-1*s[7]);
gout[11] += + (-1*s[6]);
gout[12] += + (1*s[4]) + (1*s[8]);
gout[13] += + (-1*s[3]);
gout[14] += + (-1*s[6]);
gout[15] += + (1*s[7]) + (-1*s[5]);
gout[16] += + (-1*s[2]);
gout[17] += + (-1*s[7]);
gout[18] += + (-1*s[8]);
gout[19] += + (-1*s[1]);
gout[20] += 0;
gout[21] += + (-1*s[2]) + (1*s[6]);
gout[22] += 0;
gout[23] += + (1*s[8]) + (1*s[0]);
gout[24] += + (1*s[0]);
gout[25] += + (1*s[1]);
gout[26] += + (1*s[6]);
gout[27] += + (-1*s[7]);
gout[28] += + (-1*s[1]);
gout[29] += + (1*s[0]) + (1*s[8]);
gout[30] += + (-1*s[7]);
gout[31] += + (-1*s[6]) + (1*s[2]);
gout[32] += + (1*s[1]);
gout[33] += + (1*s[4]);
gout[34] += + (1*s[5]);
gout[35] += + (-1*s[2]);
gout[36] += + (-1*s[0]);
gout[37] += + (-1*s[3]);
gout[38] += + (-1*s[2]);
gout[39] += + (-1*s[5]);
gout[40] += 0;
gout[41] += 0;
gout[42] += + (1*s[1]) + (-1*s[3]);
gout[43] += + (1*s[4]) + (1*s[0]);
gout[44] += + (-1*s[2]);
gout[45] += + (-1*s[5]);
gout[46] += + (1*s[0]) + (1*s[4]);
gout[47] += + (1*s[3]) + (-1*s[1]);
gout += 48;
}}}
void cint2e_cg_ssa10ssp2_optimizer(CINTOpt **opt, const int *atm, const int natm,
const int *bas, const int nbas, const double *env) {
int ng[] = {1, 0, 0, 1, 0, 0, 0, 0, 0};
CINTuse_all_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int cint2e_cg_ssa10ssp2(double *opkijl, const int *shls,
const int *atm, const int natm,
const int *bas, const int nbas, const double *env, CINTOpt *opt) {
int ng[] = {1, 0, 0, 1, 0, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_cint2e_cg_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_spinor_drv(opkijl, &envs, opt, &c2s_si_2e1, &c2s_si_2e2i);
}
OPTIMIZER2F_(cint2e_cg_ssa10ssp2_optimizer);
C2Fo_(cint2e_cg_ssa10ssp2)
/* <k R CROSS SIGMA i|GAUNT |j SIGMA DOT P l> : i,jin electron 1; k,lin electron 2
 * = (R CROSS SIGMA i j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_cint2e_giao_ssa10ssp2(double *g,
double *gout, const int *idx, const CINTEnvVars *envs, int gout_empty) {
const double *env = envs->env;
const int nf = envs->nf;
const int i_l = envs->i_l;
const int j_l = envs->j_l;
const int k_l = envs->k_l;
const int l_l = envs->l_l;
const double *ri = envs->ri;
const double *rj = envs->rj;
const double *rk = envs->rk;
const double *rl = envs->rl;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double *g4 = g3 + envs->g_size * 3;
double s[9];
G2E_D_L(g1, g0, i_l+1, j_l+0, k_l+0, l_l+0);
G2E_R_I(g2, g0, i_l+0, j_l, k_l, l_l);
G2E_R_I(g3, g1, i_l+0, j_l, k_l, l_l);
for (n = 0; n < nf; n++, idx+=3) {
ix = idx[0];
iy = idx[1];
iz = idx[2];
CINTdset0(9, s);
for (i = 0; i < envs->nrys_roots; i++) {
s[0] += g3[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g2[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g2[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g1[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g0[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g0[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g1[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g0[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g0[ix+i] * g0[iy+i] * g3[iz+i];
}
if (gout_empty) {
gout[0] = + (1*s[5]) + (-1*s[7]);
gout[1] = 0;
gout[2] = 0;
gout[3] = + (1*s[8]) + (1*s[4]);
gout[4] = + (1*s[6]);
gout[5] = + (1*s[5]);
gout[6] = + (1*s[8]);
gout[7] = + (-1*s[3]);
gout[8] = + (-1*s[3]);
gout[9] = + (-1*s[4]);
gout[10] = + (-1*s[7]);
gout[11] = + (-1*s[6]);
gout[12] = + (1*s[4]) + (1*s[8]);
gout[13] = + (-1*s[3]);
gout[14] = + (-1*s[6]);
gout[15] = + (1*s[7]) + (-1*s[5]);
gout[16] = + (-1*s[2]);
gout[17] = + (-1*s[7]);
gout[18] = + (-1*s[8]);
gout[19] = + (-1*s[1]);
gout[20] = 0;
gout[21] = + (-1*s[2]) + (1*s[6]);
gout[22] = 0;
gout[23] = + (1*s[8]) + (1*s[0]);
gout[24] = + (1*s[0]);
gout[25] = + (1*s[1]);
gout[26] = + (1*s[6]);
gout[27] = + (-1*s[7]);
gout[28] = + (-1*s[1]);
gout[29] = + (1*s[0]) + (1*s[8]);
gout[30] = + (-1*s[7]);
gout[31] = + (-1*s[6]) + (1*s[2]);
gout[32] = + (1*s[1]);
gout[33] = + (1*s[4]);
gout[34] = + (1*s[5]);
gout[35] = + (-1*s[2]);
gout[36] = + (-1*s[0]);
gout[37] = + (-1*s[3]);
gout[38] = + (-1*s[2]);
gout[39] = + (-1*s[5]);
gout[40] = 0;
gout[41] = 0;
gout[42] = + (1*s[1]) + (-1*s[3]);
gout[43] = + (1*s[4]) + (1*s[0]);
gout[44] = + (-1*s[2]);
gout[45] = + (-1*s[5]);
gout[46] = + (1*s[0]) + (1*s[4]);
gout[47] = + (1*s[3]) + (-1*s[1]);
gout += 48;
} else {
gout[0] += + (1*s[5]) + (-1*s[7]);
gout[1] += 0;
gout[2] += 0;
gout[3] += + (1*s[8]) + (1*s[4]);
gout[4] += + (1*s[6]);
gout[5] += + (1*s[5]);
gout[6] += + (1*s[8]);
gout[7] += + (-1*s[3]);
gout[8] += + (-1*s[3]);
gout[9] += + (-1*s[4]);
gout[10] += + (-1*s[7]);
gout[11] += + (-1*s[6]);
gout[12] += + (1*s[4]) + (1*s[8]);
gout[13] += + (-1*s[3]);
gout[14] += + (-1*s[6]);
gout[15] += + (1*s[7]) + (-1*s[5]);
gout[16] += + (-1*s[2]);
gout[17] += + (-1*s[7]);
gout[18] += + (-1*s[8]);
gout[19] += + (-1*s[1]);
gout[20] += 0;
gout[21] += + (-1*s[2]) + (1*s[6]);
gout[22] += 0;
gout[23] += + (1*s[8]) + (1*s[0]);
gout[24] += + (1*s[0]);
gout[25] += + (1*s[1]);
gout[26] += + (1*s[6]);
gout[27] += + (-1*s[7]);
gout[28] += + (-1*s[1]);
gout[29] += + (1*s[0]) + (1*s[8]);
gout[30] += + (-1*s[7]);
gout[31] += + (-1*s[6]) + (1*s[2]);
gout[32] += + (1*s[1]);
gout[33] += + (1*s[4]);
gout[34] += + (1*s[5]);
gout[35] += + (-1*s[2]);
gout[36] += + (-1*s[0]);
gout[37] += + (-1*s[3]);
gout[38] += + (-1*s[2]);
gout[39] += + (-1*s[5]);
gout[40] += 0;
gout[41] += 0;
gout[42] += + (1*s[1]) + (-1*s[3]);
gout[43] += + (1*s[4]) + (1*s[0]);
gout[44] += + (-1*s[2]);
gout[45] += + (-1*s[5]);
gout[46] += + (1*s[0]) + (1*s[4]);
gout[47] += + (1*s[3]) + (-1*s[1]);
gout += 48;
}}}
void cint2e_giao_ssa10ssp2_optimizer(CINTOpt **opt, const int *atm, const int natm,
const int *bas, const int nbas, const double *env) {
int ng[] = {1, 0, 0, 1, 0, 0, 0, 0, 0};
CINTuse_all_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int cint2e_giao_ssa10ssp2(double *opkijl, const int *shls,
const int *atm, const int natm,
const int *bas, const int nbas, const double *env, CINTOpt *opt) {
int ng[] = {1, 0, 0, 1, 0, 2, 4, 4, 3};
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_cint2e_giao_ssa10ssp2;
envs.common_factor *= 1;
return CINT2e_spinor_drv(opkijl, &envs, opt, &c2s_si_2e1, &c2s_si_2e2i);
}
OPTIMIZER2F_(cint2e_giao_ssa10ssp2_optimizer);
C2Fo_(cint2e_giao_ssa10ssp2)
/* <k G i|GAUNT |SIGMA DOT P j SIGMA DOT P l> : i,jin electron 1; k,lin electron 2
 * = (G i SIGMA DOT P j|GAUNT |k SIGMA DOT P l) */
static void CINTgout2e_cint2e_gssp1ssp2(double *g,
double *gout, const int *idx, const CINTEnvVars *envs, int gout_empty) {
const double *env = envs->env;
const int nf = envs->nf;
const int i_l = envs->i_l;
const int j_l = envs->j_l;
const int k_l = envs->k_l;
const int l_l = envs->l_l;
const double *ri = envs->ri;
const double *rj = envs->rj;
const double *rk = envs->rk;
const double *rl = envs->rl;
int ix, iy, iz, i, n;
double *g0 = g;
double *g1 = g0 + envs->g_size * 3;
double *g2 = g1 + envs->g_size * 3;
double *g3 = g2 + envs->g_size * 3;
double *g4 = g3 + envs->g_size * 3;
double *g5 = g4 + envs->g_size * 3;
double *g6 = g5 + envs->g_size * 3;
double *g7 = g6 + envs->g_size * 3;
double *g8 = g7 + envs->g_size * 3;
double s[27];
double rirj[3];
rirj[0] = ri[0] - rj[0];
rirj[1] = ri[1] - rj[1];
rirj[2] = ri[2] - rj[2];
double c[3];
c[0] = 1 * rirj[0];
c[1] = 1 * rirj[1];
c[2] = 1 * rirj[2];
G2E_D_L(g1, g0, i_l+1, j_l+1, k_l+0, l_l+0);
G2E_D_J(g2, g0, i_l+1, j_l+0, k_l, l_l);
G2E_D_J(g3, g1, i_l+1, j_l+0, k_l, l_l);
G2E_R0I(g4, g0, i_l+0, j_l, k_l, l_l);
G2E_R0I(g5, g1, i_l+0, j_l, k_l, l_l);
G2E_R0I(g6, g2, i_l+0, j_l, k_l, l_l);
G2E_R0I(g7, g3, i_l+0, j_l, k_l, l_l);
for (n = 0; n < nf; n++, idx+=3) {
ix = idx[0];
iy = idx[1];
iz = idx[2];
CINTdset0(27, s);
for (i = 0; i < envs->nrys_roots; i++) {
s[0] += g7[ix+i] * g0[iy+i] * g0[iz+i];
s[1] += g6[ix+i] * g1[iy+i] * g0[iz+i];
s[2] += g6[ix+i] * g0[iy+i] * g1[iz+i];
s[3] += g5[ix+i] * g2[iy+i] * g0[iz+i];
s[4] += g4[ix+i] * g3[iy+i] * g0[iz+i];
s[5] += g4[ix+i] * g2[iy+i] * g1[iz+i];
s[6] += g5[ix+i] * g0[iy+i] * g2[iz+i];
s[7] += g4[ix+i] * g1[iy+i] * g2[iz+i];
s[8] += g4[ix+i] * g0[iy+i] * g3[iz+i];
s[9] += g3[ix+i] * g4[iy+i] * g0[iz+i];
s[10] += g2[ix+i] * g5[iy+i] * g0[iz+i];
s[11] += g2[ix+i] * g4[iy+i] * g1[iz+i];
s[12] += g1[ix+i] * g6[iy+i] * g0[iz+i];
s[13] += g0[ix+i] * g7[iy+i] * g0[iz+i];
s[14] += g0[ix+i] * g6[iy+i] * g1[iz+i];
s[15] += g1[ix+i] * g4[iy+i] * g2[iz+i];
s[16] += g0[ix+i] * g5[iy+i] * g2[iz+i];
s[17] += g0[ix+i] * g4[iy+i] * g3[iz+i];
s[18] += g3[ix+i] * g0[iy+i] * g4[iz+i];
s[19] += g2[ix+i] * g1[iy+i] * g4[iz+i];
s[20] += g2[ix+i] * g0[iy+i] * g5[iz+i];
s[21] += g1[ix+i] * g2[iy+i] * g4[iz+i];
s[22] += g0[ix+i] * g3[iy+i] * g4[iz+i];
s[23] += g0[ix+i] * g2[iy+i] * g5[iz+i];
s[24] += g1[ix+i] * g0[iy+i] * g6[iz+i];
s[25] += g0[ix+i] * g1[iy+i] * g6[iz+i];
s[26] += g0[ix+i] * g0[iy+i] * g7[iz+i];
}
if (gout_empty) {
gout[0] = + (-1*c[1]*s[26]) + (1*c[2]*s[17]) + (-1*c[1]*s[22]) + (1*c[2]*s[13]);
gout[1] = + (1*c[1]*s[19]) + (-1*c[2]*s[10]);
gout[2] = + (1*c[1]*s[20]) + (-1*c[2]*s[11]);
gout[3] = + (-1*c[1]*s[23]) + (1*c[2]*s[14]) + (1*c[1]*s[25]) + (-1*c[2]*s[16]);
gout[4] = + (1*c[1]*s[21]) + (-1*c[2]*s[12]);
gout[5] = + (-1*c[1]*s[26]) + (1*c[2]*s[17]) + (-1*c[1]*s[18]) + (1*c[2]*s[9]);
gout[6] = + (1*c[1]*s[23]) + (-1*c[2]*s[14]);
gout[7] = + (1*c[1]*s[20]) + (-1*c[2]*s[11]) + (-1*c[1]*s[24]) + (1*c[2]*s[15]);
gout[8] = + (1*c[1]*s[24]) + (-1*c[2]*s[15]);
gout[9] = + (1*c[1]*s[25]) + (-1*c[2]*s[16]);
gout[10] = + (-1*c[1]*s[22]) + (1*c[2]*s[13]) + (-1*c[1]*s[18]) + (1*c[2]*s[9]);
gout[11] = + (-1*c[1]*s[19]) + (1*c[2]*s[10]) + (1*c[1]*s[21]) + (-1*c[2]*s[12]);
gout[12] = + (-1*c[1]*s[25]) + (1*c[2]*s[16]) + (1*c[1]*s[23]) + (-1*c[2]*s[14]);
gout[13] = + (1*c[1]*s[24]) + (-1*c[2]*s[15]) + (-1*c[1]*s[20]) + (1*c[2]*s[11]);
gout[14] = + (-1*c[1]*s[21]) + (1*c[2]*s[12]) + (1*c[1]*s[19]) + (-1*c[2]*s[10]);
gout[15] = + (-1*c[1]*s[18]) + (1*c[2]*s[9]) + (-1*c[1]*s[22]) + (1*c[2]*s[13]) + (-1*c[1]*s[26]) + (1*c[2]*s[17]);
gout[16] = + (-1*c[2]*s[8]) + (1*c[0]*s[26]) + (-1*c[2]*s[4]) + (1*c[0]*s[22]);
gout[17] = + (1*c[2]*s[1]) + (-1*c[0]*s[19]);
gout[18] = + (1*c[2]*s[2]) + (-1*c[0]*s[20]);
gout[19] = + (-1*c[2]*s[5]) + (1*c[0]*s[23]) + (1*c[2]*s[7]) + (-1*c[0]*s[25]);
gout[20] = + (1*c[2]*s[3]) + (-1*c[0]*s[21]);
gout[21] = + (-1*c[2]*s[8]) + (1*c[0]*s[26]) + (-1*c[2]*s[0]) + (1*c[0]*s[18]);
gout[22] = + (1*c[2]*s[5]) + (-1*c[0]*s[23]);
gout[23] = + (1*c[2]*s[2]) + (-1*c[0]*s[20]) + (-1*c[2]*s[6]) + (1*c[0]*s[24]);
gout[24] = + (1*c[2]*s[6]) + (-1*c[0]*s[24]);
gout[25] = + (1*c[2]*s[7]) + (-1*c[0]*s[25]);
gout[26] = + (-1*c[2]*s[4]) + (1*c[0]*s[22]) + (-1*c[2]*s[0]) + (1*c[0]*s[18]);
gout[27] = + (-1*c[2]*s[1]) + (1*c[0]*s[19]) + (1*c[2]*s[3]) + (-1*c[0]*s[21]);
gout[28] = + (-1*c[2]*s[7]) + (1*c[0]*s[25]) + (1*c[2]*s[5]) + (-1*c[0]*s[23]);
gout[29] = + (1*c[2]*s[6]) + (-1*c[0]*s[24]) + (-1*c[2]*s[2]) + (1*c[0]*s[20]);
gout[30] = + (-1*c[2]*s[3]) + (1*c[0]*s[21]) + (1*c[2]*s[1]) + (-1*c[0]*s[19]);
gout[31] = + (-1*c[2]*s[0]) + (1*c[0]*s[18]) + (-1*c[2]*s[4]) + (1*c[0]*s[22]) + (-1*c[2]*s[8]) + (1*c[0]*s[26]);
gout[32] = + (-1*c[0]*s[17]) + (1*c[1]*s[8]) + (-1*c[0]*s[13]) + (1*c[1]*s[4]);
gout[33] = + (1*c[0]*s[10]) + (-1*c[1]*s[1]);
gout[34] = + (1*c[0]*s[11]) + (-1*c[1]*s[2]);
gout[35] = + (-1*c[0]*s[14]) + (1*c[1]*s[5]) + (1*c[0]*s[16]) + (-1*c[1]*s[7]);
gout[36] = + (1*c[0]*s[12]) + (-1*c[1]*s[3]);
gout[37] = + (-1*c[0]*s[17]) + (1*c[1]*s[8]) + (-1*c[0]*s[9]) + (1*c[1]*s[0]);
gout[38] = + (1*c[0]*s[14]) + (-1*c[1]*s[5]);
gout[39] = + (1*c[0]*s[11]) + (-1*c[1]*s[2]) + (-1*c[0]*s[15]) + (1*c[1]*s[6]);
gout[40] = + (1*c[0]*s[15]) + (-1*c[1]*s[6]);
gout[41] = + (1*c[0]*s[16]) + (-1*c[1]*s[7]);
gout[42] = + (-1*c[0]*s[13]) + (1*c[1]*s[4]) + (-1*c[0]*s[9]) + (1*c[1]*s[0]);
gout[43] = + (-1*c[0]*s[10]) + (1*c[1]*s[1]) + (1*c[0]*s[12]) + (-1*c[1]*s[3]);
gout[44] = + (-1*c[0]*s[16]) + (1*c[1]*s[7]) + (1*c[0]*s[14]) + (-1*c[1]*s[5]);
gout[45] = + (1*c[0]*s[15]) + (-1*c[1]*s[6]) + (-1*c[0]*s[11]) + (1*c[1]*s[2]);
gout[46] = + (-1*c[0]*s[12]) + (1*c[1]*s[3]) + (1*c[0]*s[10]) + (-1*c[1]*s[1]);
gout[47] = + (-1*c[0]*s[9]) + (1*c[1]*s[0]) + (-1*c[0]*s[13]) + (1*c[1]*s[4]) + (-1*c[0]*s[17]) + (1*c[1]*s[8]);
gout += 48;
} else {
gout[0] += + (-1*c[1]*s[26]) + (1*c[2]*s[17]) + (-1*c[1]*s[22]) + (1*c[2]*s[13]);
gout[1] += + (1*c[1]*s[19]) + (-1*c[2]*s[10]);
gout[2] += + (1*c[1]*s[20]) + (-1*c[2]*s[11]);
gout[3] += + (-1*c[1]*s[23]) + (1*c[2]*s[14]) + (1*c[1]*s[25]) + (-1*c[2]*s[16]);
gout[4] += + (1*c[1]*s[21]) + (-1*c[2]*s[12]);
gout[5] += + (-1*c[1]*s[26]) + (1*c[2]*s[17]) + (-1*c[1]*s[18]) + (1*c[2]*s[9]);
gout[6] += + (1*c[1]*s[23]) + (-1*c[2]*s[14]);
gout[7] += + (1*c[1]*s[20]) + (-1*c[2]*s[11]) + (-1*c[1]*s[24]) + (1*c[2]*s[15]);
gout[8] += + (1*c[1]*s[24]) + (-1*c[2]*s[15]);
gout[9] += + (1*c[1]*s[25]) + (-1*c[2]*s[16]);
gout[10] += + (-1*c[1]*s[22]) + (1*c[2]*s[13]) + (-1*c[1]*s[18]) + (1*c[2]*s[9]);
gout[11] += + (-1*c[1]*s[19]) + (1*c[2]*s[10]) + (1*c[1]*s[21]) + (-1*c[2]*s[12]);
gout[12] += + (-1*c[1]*s[25]) + (1*c[2]*s[16]) + (1*c[1]*s[23]) + (-1*c[2]*s[14]);
gout[13] += + (1*c[1]*s[24]) + (-1*c[2]*s[15]) + (-1*c[1]*s[20]) + (1*c[2]*s[11]);
gout[14] += + (-1*c[1]*s[21]) + (1*c[2]*s[12]) + (1*c[1]*s[19]) + (-1*c[2]*s[10]);
gout[15] += + (-1*c[1]*s[18]) + (1*c[2]*s[9]) + (-1*c[1]*s[22]) + (1*c[2]*s[13]) + (-1*c[1]*s[26]) + (1*c[2]*s[17]);
gout[16] += + (-1*c[2]*s[8]) + (1*c[0]*s[26]) + (-1*c[2]*s[4]) + (1*c[0]*s[22]);
gout[17] += + (1*c[2]*s[1]) + (-1*c[0]*s[19]);
gout[18] += + (1*c[2]*s[2]) + (-1*c[0]*s[20]);
gout[19] += + (-1*c[2]*s[5]) + (1*c[0]*s[23]) + (1*c[2]*s[7]) + (-1*c[0]*s[25]);
gout[20] += + (1*c[2]*s[3]) + (-1*c[0]*s[21]);
gout[21] += + (-1*c[2]*s[8]) + (1*c[0]*s[26]) + (-1*c[2]*s[0]) + (1*c[0]*s[18]);
gout[22] += + (1*c[2]*s[5]) + (-1*c[0]*s[23]);
gout[23] += + (1*c[2]*s[2]) + (-1*c[0]*s[20]) + (-1*c[2]*s[6]) + (1*c[0]*s[24]);
gout[24] += + (1*c[2]*s[6]) + (-1*c[0]*s[24]);
gout[25] += + (1*c[2]*s[7]) + (-1*c[0]*s[25]);
gout[26] += + (-1*c[2]*s[4]) + (1*c[0]*s[22]) + (-1*c[2]*s[0]) + (1*c[0]*s[18]);
gout[27] += + (-1*c[2]*s[1]) + (1*c[0]*s[19]) + (1*c[2]*s[3]) + (-1*c[0]*s[21]);
gout[28] += + (-1*c[2]*s[7]) + (1*c[0]*s[25]) + (1*c[2]*s[5]) + (-1*c[0]*s[23]);
gout[29] += + (1*c[2]*s[6]) + (-1*c[0]*s[24]) + (-1*c[2]*s[2]) + (1*c[0]*s[20]);
gout[30] += + (-1*c[2]*s[3]) + (1*c[0]*s[21]) + (1*c[2]*s[1]) + (-1*c[0]*s[19]);
gout[31] += + (-1*c[2]*s[0]) + (1*c[0]*s[18]) + (-1*c[2]*s[4]) + (1*c[0]*s[22]) + (-1*c[2]*s[8]) + (1*c[0]*s[26]);
gout[32] += + (-1*c[0]*s[17]) + (1*c[1]*s[8]) + (-1*c[0]*s[13]) + (1*c[1]*s[4]);
gout[33] += + (1*c[0]*s[10]) + (-1*c[1]*s[1]);
gout[34] += + (1*c[0]*s[11]) + (-1*c[1]*s[2]);
gout[35] += + (-1*c[0]*s[14]) + (1*c[1]*s[5]) + (1*c[0]*s[16]) + (-1*c[1]*s[7]);
gout[36] += + (1*c[0]*s[12]) + (-1*c[1]*s[3]);
gout[37] += + (-1*c[0]*s[17]) + (1*c[1]*s[8]) + (-1*c[0]*s[9]) + (1*c[1]*s[0]);
gout[38] += + (1*c[0]*s[14]) + (-1*c[1]*s[5]);
gout[39] += + (1*c[0]*s[11]) + (-1*c[1]*s[2]) + (-1*c[0]*s[15]) + (1*c[1]*s[6]);
gout[40] += + (1*c[0]*s[15]) + (-1*c[1]*s[6]);
gout[41] += + (1*c[0]*s[16]) + (-1*c[1]*s[7]);
gout[42] += + (-1*c[0]*s[13]) + (1*c[1]*s[4]) + (-1*c[0]*s[9]) + (1*c[1]*s[0]);
gout[43] += + (-1*c[0]*s[10]) + (1*c[1]*s[1]) + (1*c[0]*s[12]) + (-1*c[1]*s[3]);
gout[44] += + (-1*c[0]*s[16]) + (1*c[1]*s[7]) + (1*c[0]*s[14]) + (-1*c[1]*s[5]);
gout[45] += + (1*c[0]*s[15]) + (-1*c[1]*s[6]) + (-1*c[0]*s[11]) + (1*c[1]*s[2]);
gout[46] += + (-1*c[0]*s[12]) + (1*c[1]*s[3]) + (1*c[0]*s[10]) + (-1*c[1]*s[1]);
gout[47] += + (-1*c[0]*s[9]) + (1*c[1]*s[0]) + (-1*c[0]*s[13]) + (1*c[1]*s[4]) + (-1*c[0]*s[17]) + (1*c[1]*s[8]);
gout += 48;
}}}
void cint2e_gssp1ssp2_optimizer(CINTOpt **opt, const int *atm, const int natm,
const int *bas, const int nbas, const double *env) {
int ng[] = {1, 1, 0, 1, 0, 0, 0, 0, 0};
CINTuse_all_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int cint2e_gssp1ssp2(double *opkijl, const int *shls,
const int *atm, const int natm,
const int *bas, const int nbas, const double *env, CINTOpt *opt) {
int ng[] = {1, 1, 0, 1, 0, 3, 4, 4, 3};
const int i_sh = shls[0];
const int j_sh = shls[1];
const int k_sh = shls[2];
const int l_sh = shls[3];
if (bas(ATOM_OF, i_sh) == bas(ATOM_OF, j_sh)) {
int ip = CINTlen_spinor(i_sh, bas) * bas(NCTR_OF,i_sh);
int jp = CINTlen_spinor(j_sh, bas) * bas(NCTR_OF,j_sh);
int kp = CINTlen_spinor(k_sh, bas) * bas(NCTR_OF,k_sh);
int lp = CINTlen_spinor(l_sh, bas) * bas(NCTR_OF,l_sh);
CINTdset0(kp * ip * jp * lp * OF_CMPLX * ng[TENSOR], opkijl);
return 0; }
CINTEnvVars envs;
CINTinit_int2e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout2e_cint2e_gssp1ssp2;
envs.common_factor *= 0.5;
return CINT2e_spinor_drv(opkijl, &envs, opt, &c2s_si_2e1, &c2s_si_2e2i);
}
OPTIMIZER2F_(cint2e_gssp1ssp2_optimizer);
C2Fo_(cint2e_gssp1ssp2)
