#define LEN 32000
#define LEN2 256
#define ntimes 200000
#define TYPE float
#define lll LEN
#include "rose_simd.h" 
float X[32000UL];
__SIMD *X_SIMD;
float Y[32000UL];
__SIMD *Y_SIMD;
float Z[32000UL];
float U[32000UL];
float V[32000UL];
//float* __restrict__ array;
float array[256 * 256];
float x[32000UL];
float temp;
int temp_int;
float a[32000UL];
__SIMD *a_SIMD;
float b[32000UL];
__SIMD *b_SIMD;
float c[32000UL];
__SIMD *c_SIMD;
float d[32000UL];
__SIMD *d_SIMD;
float e[32000UL];
__SIMD *e_SIMD;
float aa[256UL][256UL];
__SIMD (*aa_SIMD)[256UL / 4];
float bb[256UL][256UL];
__SIMD (*bb_SIMD)[256UL / 4];
float cc[256UL][256UL];
__SIMD (*cc_SIMD)[256UL / 4];
float tt[256UL][256UL];
int indx[32000UL];
float *__restrict__ xx;
float *yy;

int s000()
{
  int i_nom_1_strip_38;
  int i_nom_1;
  X_SIMD = ((__SIMD *)X);
  Y_SIMD = ((__SIMD *)Y);
  for (int nl = 0; nl < 2 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_1 = 0, i_nom_1_strip_38 = i_nom_1; i_nom_1 <= 31999; (i_nom_1 += 4 , i_nom_1_strip_38 += 1)) {
//			a[i] = b[i] + c[i];
//			X[i] = (Y[i] * Z[i])+(U[i]*V[i]);
      X_SIMD[i_nom_1_strip_38] = _SIMD_add_ps(Y_SIMD[i_nom_1_strip_38],_SIMD_splats_ps(1));
    }
  }
  return 0;
}

int s1112()
{
  int i_nom_2;
  a_SIMD = ((__SIMD *)a);
  b_SIMD = ((__SIMD *)b);
//	linear dependence testing
//	loop reversal
  for (int nl = 0; nl < 200000 * 3; nl++) {
    
#pragma SIMD
    for (i_nom_2 = 32000 - 1; i_nom_2 >= 0; i_nom_2 += -1) {
      a_SIMD[i_nom_2] = _SIMD_add_ps(b_SIMD[i_nom_2],_SIMD_splats_ps(1.));
    }
  }
  return 0;
}

int s113()
{
  int i_nom_3_strip_71;
  int i_nom_3;
//	linear dependence testing
//	a(i)=a(1) but no actual dependence cycle
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_3 = 1, i_nom_3_strip_71 = i_nom_3; i_nom_3 <= 31999; (i_nom_3 += 4 , i_nom_3_strip_71 += 1)) {
      a_SIMD[i_nom_3_strip_71] = _SIMD_add_ps(a_SIMD[0],b_SIMD[i_nom_3_strip_71]);
    }
  }
  return 0;
}

int s212()
{
  int i_nom_4_strip_86;
  int i_nom_4;
  c_SIMD = ((__SIMD *)c);
//	statement reordering
//	dependency needing temporary
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_4 = 0, i_nom_4_strip_86 = i_nom_4; i_nom_4 <= 31998; (i_nom_4 += 4 , i_nom_4_strip_86 += 1)) {
      a_SIMD[i_nom_4_strip_86] = _SIMD_mul_ps(a_SIMD[i_nom_4_strip_86],c_SIMD[i_nom_4_strip_86]);
    }
    for (int i = 0; i < 32000 - 1; i++) {
      b[i] += (a[i + 1] * d[i]);
    }
  }
  return 0;
}

int s221()
{
  int i_nom_5_strip_104;
  int i_nom_5;
  d_SIMD = ((__SIMD *)d);
//	loop distribution
//	loop that is partially recursive
  for (int nl = 0; nl < 200000 / 2; nl++) {
    
#pragma SIMD
    for (i_nom_5 = 1, i_nom_5_strip_104 = i_nom_5; i_nom_5 <= 31999; (i_nom_5 += 4 , i_nom_5_strip_104 += 1)) {
      a_SIMD[i_nom_5_strip_104] = _SIMD_add_ps(a_SIMD[i_nom_5_strip_104],_SIMD_mul_ps(c_SIMD[i_nom_5_strip_104],d_SIMD[i_nom_5_strip_104]));
    }
    for (int i = 1; i < 32000; i++) {
      b[i] = ((b[i - 1] + a[i]) + d[i]);
    }
  }
  return 0;
}

int s222()
{
  int i_nom_7_strip_129;
  int i_nom_7;
  int i_nom_6_strip_122;
  int i_nom_6;
//	loop distribution
//	partial loop vectorizatio recurrence in middle
  for (int nl = 0; nl < 200000 / 2; nl++) {
    
#pragma SIMD
    for (i_nom_6 = 1, i_nom_6_strip_122 = i_nom_6; i_nom_6 <= 31999; (i_nom_6 += 4 , i_nom_6_strip_122 += 1)) {
      a_SIMD[i_nom_6_strip_122] = _SIMD_add_ps(a_SIMD[i_nom_6_strip_122],_SIMD_mul_ps(b_SIMD[i_nom_6_strip_122],c_SIMD[i_nom_6_strip_122]));
    }
    for (int i = 1; i < 32000; i++) {
      e[i] = (e[i - 1] * e[i - 1]);
    }
    
#pragma SIMD
    for (i_nom_7 = 1, i_nom_7_strip_129 = i_nom_7; i_nom_7 <= 31999; (i_nom_7 += 4 , i_nom_7_strip_129 += 1)) {
      a_SIMD[i_nom_7_strip_129] = _SIMD_sub_ps(a_SIMD[i_nom_7_strip_129],_SIMD_mul_ps(b_SIMD[i_nom_7_strip_129],c_SIMD[i_nom_7_strip_129]));
    }
  }
  return 0;
}
// manually loop interchange in 231

int s231()
{
  int i_nom_8_strip_145;
  int i_nom_8;
  bb_SIMD = ((__SIMD (*)[256UL / 4])bb);
  aa_SIMD = ((__SIMD (*)[256UL / 4])aa);
//	loop interchange
//	loop with data dependency
  for (int nl = 0; nl < 100 * (200000 / 256); nl++) {
    for (int j = 1; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_8 = 0, i_nom_8_strip_145 = i_nom_8; i_nom_8 <= 255; (i_nom_8 += 4 , i_nom_8_strip_145 += 1)) {
        aa_SIMD[j][i_nom_8_strip_145] = _SIMD_add_ps(aa_SIMD[j - 1][i_nom_8_strip_145],bb_SIMD[j][i_nom_8_strip_145]);
      }
    }
  }
  return 0;
}

int s233()
{
  int i_nom_10_strip_166;
  int i_nom_10;
  int i_nom_9_strip_162;
  int i_nom_9;
  cc_SIMD = ((__SIMD (*)[256UL / 4])cc);
//	loop interchange
//	interchanging with one of two inner loops
  for (int nl = 0; nl < 100 * (200000 / 256); nl++) {
    for (int j = 1; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_9 = 1, i_nom_9_strip_162 = i_nom_9; i_nom_9 <= 255; (i_nom_9 += 4 , i_nom_9_strip_162 += 1)) {
        aa_SIMD[j][i_nom_9_strip_162] = _SIMD_add_ps(aa_SIMD[j - 1][i_nom_9_strip_162],cc_SIMD[j][i_nom_9_strip_162]);
      }
      
#pragma SIMD
      for (i_nom_10 = 1, i_nom_10_strip_166 = i_nom_10; i_nom_10 <= 255; (i_nom_10 += 4 , i_nom_10_strip_166 += 1)) {
        bb_SIMD[j][i_nom_10_strip_166] = _SIMD_add_ps(bb_SIMD[j][i_nom_10_strip_166 - 1],cc_SIMD[j][i_nom_10_strip_166]);
      }
    }
  }
  return 0;
}

int s2233()
{
  int j_nom_12_strip_189;
  int j_nom_12;
  int i_nom_11_strip_183;
  int i_nom_11;
//	loop interchange
//	interchanging with one of two inner loops
  for (int nl = 0; nl < 100 * (200000 / 256); nl++) {
    for (int j = 1; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_11 = 1, i_nom_11_strip_183 = i_nom_11; i_nom_11 <= 255; (i_nom_11 += 4 , i_nom_11_strip_183 += 1)) {
        aa_SIMD[j][i_nom_11_strip_183] = _SIMD_add_ps(aa_SIMD[j - 1][i_nom_11_strip_183],cc_SIMD[j][i_nom_11_strip_183]);
      }
    }
    for (int i = 1; i < 256; i++) {
      
#pragma SIMD
      for (j_nom_12 = 1, j_nom_12_strip_189 = j_nom_12; j_nom_12 <= 255; (j_nom_12 += 4 , j_nom_12_strip_189 += 1)) {
        bb_SIMD[i][j_nom_12_strip_189] = _SIMD_add_ps(bb_SIMD[i - 1][j_nom_12_strip_189],cc_SIMD[i][j_nom_12_strip_189]);
      }
    }
  }
  return 0;
}

int s235()
{
  int i_nom_13_strip_206;
  int i_nom_13;
//	loop interchanging
//	imperfectly nested loops
  for (int nl = 0; nl < 200 * (200000 / 256); nl++) {
    for (int j = 1; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_13 = 0, i_nom_13_strip_206 = i_nom_13; i_nom_13 <= 255; (i_nom_13 += 4 , i_nom_13_strip_206 += 1)) {
        a_SIMD[i_nom_13_strip_206] = _SIMD_add_ps(a_SIMD[i_nom_13_strip_206],_SIMD_mul_ps(b_SIMD[i_nom_13_strip_206],c_SIMD[i_nom_13_strip_206]));
        aa_SIMD[j][i_nom_13_strip_206] = _SIMD_madd_ps(bb_SIMD[j][i_nom_13_strip_206],a_SIMD[i_nom_13_strip_206],aa_SIMD[j - 1][i_nom_13_strip_206]);
      }
    }
  }
  return 0;
}

int s241()
{
  int i_nom_14_strip_224;
  int i_nom_14;
//	node splitting
//	preloading necessary to allow vectorization
  for (int nl = 0; nl < 2 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_14 = 0, i_nom_14_strip_224 = i_nom_14; i_nom_14 <= 31998; (i_nom_14 += 4 , i_nom_14_strip_224 += 1)) {
      a_SIMD[i_nom_14_strip_224] = _SIMD_mul_ps(_SIMD_mul_ps(b_SIMD[i_nom_14_strip_224],c_SIMD[i_nom_14_strip_224]),d_SIMD[i_nom_14_strip_224]);
    }
    for (int i = 0; i < 32000 - 1; i++) {
      b[i] = ((a[i] * a[i + 1]) * d[i]);
    }
  }
  return 0;
}

int s243()
{
  int i_nom_15_strip_243;
  int i_nom_15;
  e_SIMD = ((__SIMD *)e);
//	node splitting
//	false dependence cycle breaking
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_15 = 0, i_nom_15_strip_243 = i_nom_15; i_nom_15 <= 31998; (i_nom_15 += 4 , i_nom_15_strip_243 += 1)) {
      a_SIMD[i_nom_15_strip_243] = _SIMD_madd_ps(c_SIMD[i_nom_15_strip_243],d_SIMD[i_nom_15_strip_243],b_SIMD[i_nom_15_strip_243]);
      b_SIMD[i_nom_15_strip_243] = _SIMD_madd_ps(d_SIMD[i_nom_15_strip_243],e_SIMD[i_nom_15_strip_243],a_SIMD[i_nom_15_strip_243]);
    }
    for (int i = 0; i < 32000 - 1; i++) {
      a[i] = ((a[i + 1] * d[i]) + b[i]);
    }
  }
  return 0;
}

int s244()
{
  int i_nom_16_strip_263;
  int i_nom_16;
//	node splitting
//	false dependence cycle breaking
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_16 = 0, i_nom_16_strip_263 = i_nom_16; i_nom_16 <= 31998; (i_nom_16 += 4 , i_nom_16_strip_263 += 1)) {
      a_SIMD[i_nom_16_strip_263] = _SIMD_madd_ps(c_SIMD[i_nom_16_strip_263],d_SIMD[i_nom_16_strip_263],b_SIMD[i_nom_16_strip_263]);
      b_SIMD[i_nom_16_strip_263] = _SIMD_add_ps(c_SIMD[i_nom_16_strip_263],b_SIMD[i_nom_16_strip_263]);
    }
    for (int i = 0; i < 32000 - 1; ++i) {
      a[i + 1] = ((a[i + 1] * d[i]) + b[i]);
    }
  }
  return 0;
}

int s1244()
{
  int i_nom_17_strip_282;
  int i_nom_17;
//	node splitting
//	cycle with ture and anti dependency
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_17 = 0, i_nom_17_strip_282 = i_nom_17; i_nom_17 <= 31998; (i_nom_17 += 4 , i_nom_17_strip_282 += 1)) {
      a_SIMD[i_nom_17_strip_282] = _SIMD_add_ps(_SIMD_madd_ps(b_SIMD[i_nom_17_strip_282],b_SIMD[i_nom_17_strip_282],_SIMD_madd_ps(c_SIMD[i_nom_17_strip_282],c_SIMD[i_nom_17_strip_282],b_SIMD[i_nom_17_strip_282])),c_SIMD[i_nom_17_strip_282]);
    }
    for (int i = 0; i < 32000 - 1; i++) {
      d[i] = (a[i] + a[i + 1]);
    }
  }
  return 0;
}

int s2244()
{
  int i_nom_18_strip_303;
  int i_nom_18;
//	node splitting
//	cycle with ture and anti dependency
  for (int nl = 0; nl < 200000; nl++) {
    for (int i = 0; i < 32000 - 1; i++) {
      a[i + 1] = (b[i] + e[i]);
    }
    
#pragma SIMD
    for (i_nom_18 = 0, i_nom_18_strip_303 = i_nom_18; i_nom_18 <= 31998; (i_nom_18 += 4 , i_nom_18_strip_303 += 1)) {
      a_SIMD[i_nom_18_strip_303] = _SIMD_add_ps(b_SIMD[i_nom_18_strip_303],c_SIMD[i_nom_18_strip_303]);
    }
  }
  return 0;
}

int s251()
{
  int i_nom_19_strip_319;
  int i_nom_19;
//	scalar and array expansion
//	scalar expansion
  float s;
  __SIMD s_SIMD;
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_19 = 0, i_nom_19_strip_319 = i_nom_19; i_nom_19 <= 31999; (i_nom_19 += 4 , i_nom_19_strip_319 += 1)) {
      s_SIMD = _SIMD_madd_ps(c_SIMD[i_nom_19_strip_319],d_SIMD[i_nom_19_strip_319],b_SIMD[i_nom_19_strip_319]);
      a_SIMD[i_nom_19_strip_319] = _SIMD_mul_ps(s_SIMD,s_SIMD);
    }
  }
  return 0;
}

int s1251()
{
  int i_nom_20_strip_337;
  int i_nom_20;
//	scalar and array expansion
//	scalar expansion
  float s;
  __SIMD s_SIMD;
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_20 = 0, i_nom_20_strip_337 = i_nom_20; i_nom_20 <= 31999; (i_nom_20 += 4 , i_nom_20_strip_337 += 1)) {
      s_SIMD = _SIMD_add_ps(b_SIMD[i_nom_20_strip_337],c_SIMD[i_nom_20_strip_337]);
      b_SIMD[i_nom_20_strip_337] = _SIMD_add_ps(a_SIMD[i_nom_20_strip_337],d_SIMD[i_nom_20_strip_337]);
      a_SIMD[i_nom_20_strip_337] = _SIMD_mul_ps(s_SIMD,e_SIMD[i_nom_20_strip_337]);
    }
  }
  return 0;
}

int s2251()
{
  int i_nom_21_strip_356;
  int i_nom_21;
//	scalar and array expansion
//	scalar expansion
  for (int nl = 0; nl < 200000; nl++) {
    float s = (float )0.0;
    __SIMD s_SIMD;
    
#pragma SIMD
    s_SIMD = _SIMD_splats_ps(s);
    for (i_nom_21 = 0, i_nom_21_strip_356 = i_nom_21; i_nom_21 <= 31999; (i_nom_21 += 4 , i_nom_21_strip_356 += 1)) {
      a_SIMD[i_nom_21_strip_356] = _SIMD_mul_ps(s_SIMD,e_SIMD[i_nom_21_strip_356]);
      s_SIMD = _SIMD_add_ps(b_SIMD[i_nom_21_strip_356],c_SIMD[i_nom_21_strip_356]);
      b_SIMD[i_nom_21_strip_356] = _SIMD_add_ps(a_SIMD[i_nom_21_strip_356],d_SIMD[i_nom_21_strip_356]);
    }
  }
  return 0;
}
//int s3251()
//{
//
////	scalar and array expansion
////	scalar expansion
//
//
//	for (int nl = 0; nl < ntimes; nl++) {
//		for (int i = 0; i < LEN-1; i++){
//			a[i+1] = b[i]+c[i];
//		}
//#pragma SIMD
//		for (int i = 0; i < LEN-1; i++){
//			b[i]   = c[i]*e[i];
//			d[i]   = a[i]*e[i];
//		}
//	}
//	return 0;
//}

int s252()
{
  int i_nom_22_strip_396;
  int i_nom_22;
//	scalar and array expansion
//	loop with ambiguous scalar temporary
  float t;
  __SIMD t_SIMD;
  float s;
  __SIMD s_SIMD;
  for (int nl = 0; nl < 200000; nl++) {
    t = ((float )0.0);
    
#pragma SIMD
    t_SIMD = _SIMD_splats_ps(t);
    for (i_nom_22 = 0, i_nom_22_strip_396 = i_nom_22; i_nom_22 <= 31999; (i_nom_22 += 4 , i_nom_22_strip_396 += 1)) {
      s_SIMD = _SIMD_mul_ps(b_SIMD[i_nom_22_strip_396],c_SIMD[i_nom_22_strip_396]);
      a_SIMD[i_nom_22_strip_396] = _SIMD_add_ps(s_SIMD,t_SIMD);
      t_SIMD = s_SIMD;
    }
  }
  return 0;
}

int s253()
{
  int i_nom_23_strip_415;
  int i_nom_23;
//	scalar and array expansion
//	scalar expansio assigned under if
  float s;
  __SIMD s_SIMD;
  void *cmpReturn_416;
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_23 = 0, i_nom_23_strip_415 = i_nom_23; i_nom_23 <= 31999; (i_nom_23 += 4 , i_nom_23_strip_415 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpgt_ps(a_SIMD[i_nom_23_strip_415],b_SIMD[i_nom_23_strip_415],&cmpReturn_416);
      a_SIMD[i_nom_23_strip_415] = _SIMD_sel_ps(a_SIMD[i_nom_23_strip_415],s_SIMD,&cmpReturn_416);
      c_SIMD[i_nom_23_strip_415] = _SIMD_sel_ps(c_SIMD[i_nom_23_strip_415],_SIMD_add_ps(c_SIMD[i_nom_23_strip_415],s_SIMD),&cmpReturn_416);
      s_SIMD = _SIMD_sel_ps(s_SIMD,_SIMD_neg_ps(_SIMD_msub_ps(b_SIMD[i_nom_23_strip_415],d_SIMD[i_nom_23_strip_415],a_SIMD[i_nom_23_strip_415])),&cmpReturn_416);
    }
  }
  return 0;
}

int s254()
{
  int i_nom_24_strip_437;
  int i_nom_24;
//	scalar and array expansion
//	carry around variable
  float x;
  __SIMD x_SIMD;
  for (int nl = 0; nl < 4 * 200000; nl++) {
    x = b[32000 - 1];
    
#pragma SIMD
    x_SIMD = _SIMD_splats_ps(x);
    for (i_nom_24 = 0, i_nom_24_strip_437 = i_nom_24; i_nom_24 <= 31999; (i_nom_24 += 4 , i_nom_24_strip_437 += 1)) {
      a_SIMD[i_nom_24_strip_437] = _SIMD_mul_ps(_SIMD_add_ps(b_SIMD[i_nom_24_strip_437],x_SIMD),_SIMD_splats_ps(.5));
      x_SIMD = b_SIMD[i_nom_24_strip_437];
    }
  }
  return 0;
}
// %2.5

int s255()
{
  int i_nom_25_strip_459;
  int i_nom_25;
//	scalar and array expansion
//	carry around variables, 2 levels
  float x;
  __SIMD x_SIMD;
  float y;
  __SIMD y_SIMD;
  for (int nl = 0; nl < 200000; nl++) {
    x = b[32000 - 1];
    y = b[32000 - 2];
    
#pragma SIMD
    x_SIMD = _SIMD_splats_ps(x);
    y_SIMD = _SIMD_splats_ps(y);
    for (i_nom_25 = 0, i_nom_25_strip_459 = i_nom_25; i_nom_25 <= 31999; (i_nom_25 += 4 , i_nom_25_strip_459 += 1)) {
      a_SIMD[i_nom_25_strip_459] = _SIMD_mul_ps(_SIMD_add_ps(_SIMD_add_ps(b_SIMD[i_nom_25_strip_459],x_SIMD),y_SIMD),_SIMD_splats_ps(.333));
      y_SIMD = x_SIMD;
      x_SIMD = b_SIMD[i_nom_25_strip_459];
    }
  }
  return 0;
}
// %2.5

int s256()
{
  int j_nom_26_strip_480;
  int j_nom_26;
//	scalar and array expansion
//	array expansion
  for (int nl = 0; nl < 10 * (200000 / 256); nl++) {
    for (int i = 0; i < 256; i++) {
      
#pragma SIMD
      for (j_nom_26 = 1, j_nom_26_strip_480 = j_nom_26; j_nom_26 <= 255; (j_nom_26 += 4 , j_nom_26_strip_480 += 1)) {
        a_SIMD[j_nom_26_strip_480] = _SIMD_sub_ps(_SIMD_splats_ps(1.),a_SIMD[j_nom_26_strip_480 - 1]);
        cc_SIMD[j_nom_26_strip_480][i] = _SIMD_madd_ps(bb_SIMD[j_nom_26_strip_480][i],d_SIMD[j_nom_26_strip_480],a_SIMD[j_nom_26_strip_480]);
      }
    }
  }
  return 0;
}
//int s258()
//{
//
////	scalar and array expansion
////	wrap-around scalar under an if
//
//
//	float s;
//	for (int nl = 0; nl < ntimes/10; nl++) {
//		s = 0.;
//#pragma SIMD
//		for (int i = 0; i < LEN; ++i) {
//			if (a[i] > 0.) {
//				s = d[i] * d[i];
//			}
//			b[i] = s * c[i] + d[i];
//			e[i] = (s + (float)1.) * aa[0][i];
//		}
//	}
//	return 0;
//}

int s261()
{
  int i_nom_27_strip_525;
  int i_nom_27;
//	scalar and array expansion
//	wrap-around scalar under an if
  float t;
  __SIMD t_SIMD;
  for (int nl = 0; nl < 200000; nl++) {
    for (int i = 1; i < 32000; ++i) {
      t = (a[i] + b[i]);
      a[i] = (t + c[i - 1]);
    }
    
#pragma SIMD
    for (i_nom_27 = 1, i_nom_27_strip_525 = i_nom_27; i_nom_27 <= 31999; (i_nom_27 += 4 , i_nom_27_strip_525 += 1)) {
      t_SIMD = _SIMD_mul_ps(c_SIMD[i_nom_27_strip_525],d_SIMD[i_nom_27_strip_525]);
      c_SIMD[i_nom_27_strip_525] = t_SIMD;
    }
  }
  return 0;
}

int s271()
{
  int i_nom_28_strip_542;
  int i_nom_28;
  void *cmpReturn_543;
//	control flow
//	loop with singularity handling
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_28 = 0, i_nom_28_strip_542 = i_nom_28; i_nom_28 <= 31999; (i_nom_28 += 4 , i_nom_28_strip_542 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpgt_ps(b_SIMD[i_nom_28_strip_542],_SIMD_splats_ps(0.0),&cmpReturn_543);
      a_SIMD[i_nom_28_strip_542] = _SIMD_sel_ps(a_SIMD[i_nom_28_strip_542],_SIMD_add_ps(a_SIMD[i_nom_28_strip_542],_SIMD_mul_ps(b_SIMD[i_nom_28_strip_542],c_SIMD[i_nom_28_strip_542])),&cmpReturn_543);
    }
  }
  return 0;
}
//int s272(float t)
//{
//
////	control flow
////	loop with independent conditional
//
//	for (int nl = 0; nl < ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			if (e[i] >= t) {
//				a[i] += c[i] * d[i];
//				b[i] += c[i] * c[i];
//			}
//		}
//	}
//	return 0;
//}

int s273()
{
  int i_nom_30_strip_584;
  int i_nom_30;
  int i_nom_29_strip_578;
  int i_nom_29;
  void *cmpReturn_580;
//	control flow
//	simple loop with dependent conditional
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_29 = 0, i_nom_29_strip_578 = i_nom_29; i_nom_29 <= 31999; (i_nom_29 += 4 , i_nom_29_strip_578 += 1)) {
      a_SIMD[i_nom_29_strip_578] = _SIMD_add_ps(a_SIMD[i_nom_29_strip_578],_SIMD_mul_ps(d_SIMD[i_nom_29_strip_578],e_SIMD[i_nom_29_strip_578]));
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmplt_ps(a_SIMD[i_nom_29_strip_578],_SIMD_splats_ps(0.0),&cmpReturn_580);
      b_SIMD[i_nom_29_strip_578] = _SIMD_sel_ps(b_SIMD[i_nom_29_strip_578],_SIMD_add_ps(b_SIMD[i_nom_29_strip_578],_SIMD_mul_ps(d_SIMD[i_nom_29_strip_578],e_SIMD[i_nom_29_strip_578])),&cmpReturn_580);
    }
    
#pragma SIMD
    for (i_nom_30 = 0, i_nom_30_strip_584 = i_nom_30; i_nom_30 <= 31999; (i_nom_30 += 4 , i_nom_30_strip_584 += 1)) {
      c_SIMD[i_nom_30_strip_584] = _SIMD_add_ps(c_SIMD[i_nom_30_strip_584],_SIMD_mul_ps(a_SIMD[i_nom_30_strip_584],d_SIMD[i_nom_30_strip_584]));
    }
  }
  return 0;
}

int s274()
{
  int i_nom_31_strip_600;
  int i_nom_31;
  void *cmpReturn_602;
//	control flow
//	complex loop with dependent conditional
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_31 = 0, i_nom_31_strip_600 = i_nom_31; i_nom_31 <= 31999; (i_nom_31 += 4 , i_nom_31_strip_600 += 1)) {
      a_SIMD[i_nom_31_strip_600] = _SIMD_madd_ps(e_SIMD[i_nom_31_strip_600],d_SIMD[i_nom_31_strip_600],c_SIMD[i_nom_31_strip_600]);
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpgt_ps(a_SIMD[i_nom_31_strip_600],_SIMD_splats_ps(0.0),&cmpReturn_602);
      a_SIMD[i_nom_31_strip_600] = _SIMD_sel_ps(_SIMD_mul_ps(d_SIMD[i_nom_31_strip_600],e_SIMD[i_nom_31_strip_600]),a_SIMD[i_nom_31_strip_600],&cmpReturn_602);
      b_SIMD[i_nom_31_strip_600] = _SIMD_sel_ps(b_SIMD[i_nom_31_strip_600],_SIMD_add_ps(a_SIMD[i_nom_31_strip_600],b_SIMD[i_nom_31_strip_600]),&cmpReturn_602);
    }
  }
  return 0;
}

int s275()
{
  int i_nom_32_strip_622;
  int i_nom_32;
  void *cmpReturn_623;
//	control flow
//	if around inner loop, interchanging needed
  for (int nl = 0; nl < 10 * (200000 / 256); nl++) {
    for (int j = 1; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_32 = 0, i_nom_32_strip_622 = i_nom_32; i_nom_32 <= 255; (i_nom_32 += 4 , i_nom_32_strip_622 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
        _SIMD_cmpgt_ps(aa_SIMD[0][i_nom_32_strip_622],_SIMD_splats_ps(0.0),&cmpReturn_623);
        aa_SIMD[j][i_nom_32_strip_622] = _SIMD_sel_ps(aa_SIMD[j][i_nom_32_strip_622],_SIMD_madd_ps(bb_SIMD[j][i_nom_32_strip_622],cc_SIMD[j][i_nom_32_strip_622],aa_SIMD[j - 1][i_nom_32_strip_622]),&cmpReturn_623);
      }
    }
  }
  return 0;
}

int s2275()
{
  int i_nom_33_strip_640;
  int i_nom_33;
//	loop distribution is needed to be able to interchange
  for (int nl = 0; nl < 100 * (200000 / 256); nl++) {
    for (int j = 0; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_33 = 0, i_nom_33_strip_640 = i_nom_33; i_nom_33 <= 255; (i_nom_33 += 4 , i_nom_33_strip_640 += 1)) {
        aa_SIMD[j][i_nom_33_strip_640] = _SIMD_madd_ps(bb_SIMD[j][i_nom_33_strip_640],cc_SIMD[j][i_nom_33_strip_640],aa_SIMD[j][i_nom_33_strip_640]);
        a_SIMD[i_nom_33_strip_640] = _SIMD_madd_ps(c_SIMD[i_nom_33_strip_640],d_SIMD[i_nom_33_strip_640],b_SIMD[i_nom_33_strip_640]);
      }
    }
  }
  return 0;
}
//int s276()
//{
//
////	control flow
////	if test using loop index
//
//	int mid = (LEN/2);
//	for (int nl = 0; nl < 4*ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			if (i+1 < mid) {
//				a[i] += b[i] * c[i];
//			} else {
//				a[i] += b[i] * d[i];
//			}
//		}
//	}
//	return 0;
//}

int s2711()
{
  int i_nom_34_strip_677;
  int i_nom_34;
  void *cmpReturn_678;
//	control flow
//	semantic if removal
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_34 = 0, i_nom_34_strip_677 = i_nom_34; i_nom_34 <= 31999; (i_nom_34 += 4 , i_nom_34_strip_677 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpne_ps(b_SIMD[i_nom_34_strip_677],_SIMD_splats_ps(0.0),&cmpReturn_678);
      a_SIMD[i_nom_34_strip_677] = _SIMD_sel_ps(a_SIMD[i_nom_34_strip_677],_SIMD_add_ps(a_SIMD[i_nom_34_strip_677],_SIMD_mul_ps(b_SIMD[i_nom_34_strip_677],c_SIMD[i_nom_34_strip_677])),&cmpReturn_678);
    }
  }
  return 0;
}

int s2712()
{
  int i_nom_35_strip_694;
  int i_nom_35;
  void *cmpReturn_695;
//	control flow
//	if to elemental min
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_35 = 0, i_nom_35_strip_694 = i_nom_35; i_nom_35 <= 31999; (i_nom_35 += 4 , i_nom_35_strip_694 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpgt_ps(a_SIMD[i_nom_35_strip_694],b_SIMD[i_nom_35_strip_694],&cmpReturn_695);
      a_SIMD[i_nom_35_strip_694] = _SIMD_sel_ps(a_SIMD[i_nom_35_strip_694],_SIMD_add_ps(a_SIMD[i_nom_35_strip_694],_SIMD_mul_ps(b_SIMD[i_nom_35_strip_694],c_SIMD[i_nom_35_strip_694])),&cmpReturn_695);
    }
  }
  return 0;
}

int s1281()
{
  int i_nom_36_strip_713;
  int i_nom_36;
//	crossing thresholds
//	index set splitting
//	reverse data access
  float x;
  __SIMD x_SIMD;
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_36 = 0, i_nom_36_strip_713 = i_nom_36; i_nom_36 <= 31999; (i_nom_36 += 4 , i_nom_36_strip_713 += 1)) {
      x_SIMD = _SIMD_add_ps(_SIMD_madd_ps(a_SIMD[i_nom_36_strip_713],d_SIMD[i_nom_36_strip_713],_SIMD_mul_ps(b_SIMD[i_nom_36_strip_713],c_SIMD[i_nom_36_strip_713])),e_SIMD[i_nom_36_strip_713]);
      a_SIMD[i_nom_36_strip_713] = _SIMD_sub_ps(x_SIMD,_SIMD_splats_ps(1.));
      b_SIMD[i_nom_36_strip_713] = x_SIMD;
    }
  }
  return 0;
}
//int s293()
//{
//
////	loop peeling
////	a(i)=a(0) with actual dependence cycle, loop is vectorizable
//
//	for (int nl = 0; nl < 4*ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[i] = a[0];
//		}
//	}
//	return 0;
//}

int s2101()
{
  int i_nom_37_strip_746;
  int i_nom_37;
//	diagonals
//	main diagonal calculation
//	jump in data access
  for (int nl = 0; nl < 10 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_37 = 0, i_nom_37_strip_746 = i_nom_37; i_nom_37 <= 255; (i_nom_37 += 4 , i_nom_37_strip_746 += 1)) {
      aa_SIMD[i_nom_37_strip_746][i_nom_37_strip_746] = _SIMD_add_ps(aa_SIMD[i_nom_37_strip_746][i_nom_37_strip_746],_SIMD_mul_ps(bb_SIMD[i_nom_37_strip_746][i_nom_37_strip_746],cc_SIMD[i_nom_37_strip_746][i_nom_37_strip_746]));
    }
  }
  return 0;
}

int s2102()
{
  int i_nom_39_strip_768;
  int i_nom_39;
  int i_nom_38_strip_763;
  int i_nom_38;
//	diagonals
//	identity matrix, best results vectorize both inner and outer loops
  for (int nl = 0; nl < 100 * (200000 / 256); nl++) {
    for (int j = 0; j < 256; j++) {
      
#pragma SIMD
      for (i_nom_38 = 0, i_nom_38_strip_763 = i_nom_38; i_nom_38 <= 255; (i_nom_38 += 4 , i_nom_38_strip_763 += 1)) {
        aa_SIMD[j][i_nom_38_strip_763] = _SIMD_splats_ps(0.0);
      }
    }
    
#pragma SIMD
    for (i_nom_39 = 0, i_nom_39_strip_768 = i_nom_39; i_nom_39 <= 255; (i_nom_39 += 4 , i_nom_39_strip_768 += 1)) {
      aa_SIMD[i_nom_39_strip_768][i_nom_39_strip_768] = _SIMD_splats_ps(1.);
    }
  }
  return 0;
}

int s351()
{
  int i_nom_40_strip_784;
  int i_nom_40;
//	loop rerolling
//	unrolled saxpy
  float alpha = c[0];
  __SIMD alpha_SIMD;
  for (int nl = 0; nl < 8 * 200000; nl++) {
    
#pragma SIMD
    alpha_SIMD = _SIMD_splats_ps(alpha);
    for (i_nom_40 = 0, i_nom_40_strip_784 = i_nom_40; i_nom_40 <= 31999; (i_nom_40 += 4 , i_nom_40_strip_784 += 1)) {
      a_SIMD[i_nom_40_strip_784] = _SIMD_add_ps(a_SIMD[i_nom_40_strip_784],_SIMD_mul_ps(alpha_SIMD,b_SIMD[i_nom_40_strip_784]));
    }
  }
  return 0;
}

int s352()
{
  int i_nom_41;
//	loop rerolling
//	unrolled dot product
  float dot;
  __SIMD dot_SIMD;
  for (int nl = 0; nl < 8 * 200000; nl++) {
    dot = ((float )0.0);
    
#pragma SIMD
    dot_SIMD = _SIMD_splats_ps(dot);
    for (i_nom_41 = 0; i_nom_41 <= 31999; i_nom_41 += 5) {
      dot_SIMD = _SIMD_madd_ps(a_SIMD[i_nom_41 + 4],b_SIMD[i_nom_41 + 4],_SIMD_madd_ps(a_SIMD[i_nom_41 + 3],b_SIMD[i_nom_41 + 3],_SIMD_madd_ps(a_SIMD[i_nom_41 + 2],b_SIMD[i_nom_41 + 2],_SIMD_madd_ps(a_SIMD[i_nom_41 + 1],b_SIMD[i_nom_41 + 1],_SIMD_madd_ps(a_SIMD[i_nom_41],b_SIMD[i_nom_41],dot_SIMD)))));
    }
  }
  return 0;
}
//int s431()
//{
//
////	parameters
////	parameter statement
//
//	int k1=1;
//	int k2=2;
//	int k=2*k1-k2;
//
//	for (int nl = 0; nl < ntimes*10; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[i] = a[i+k] + b[i];
//		}
//	}
//	return 0;
//}

int s441()
{
  int i_nom_43_strip_844;
  int i_nom_43;
  int i_nom_42_strip_836;
  int i_nom_42;
  void *cmpReturn_837;
  void *cmpReturn_845;
//	non-logical if's
//	arithmetic if
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_42 = 0, i_nom_42_strip_836 = i_nom_42; i_nom_42 <= 31999; (i_nom_42 += 4 , i_nom_42_strip_836 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmplt_ps(d_SIMD[i_nom_42_strip_836],_SIMD_splats_ps(0.0),&cmpReturn_837);
      a_SIMD[i_nom_42_strip_836] = _SIMD_sel_ps(_SIMD_add_ps(a_SIMD[i_nom_42_strip_836],_SIMD_mul_ps(c_SIMD[i_nom_42_strip_836],c_SIMD[i_nom_42_strip_836])),_SIMD_add_ps(a_SIMD[i_nom_42_strip_836],_SIMD_mul_ps(b_SIMD[i_nom_42_strip_836],c_SIMD[i_nom_42_strip_836])),&cmpReturn_837);
    }
    
#pragma SIMD
    for (i_nom_43 = 0, i_nom_43_strip_844 = i_nom_43; i_nom_43 <= 31999; (i_nom_43 += 4 , i_nom_43_strip_844 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpeq_ps(d_SIMD[i_nom_43_strip_844],_SIMD_splats_ps(0.0),&cmpReturn_845);
      a_SIMD[i_nom_43_strip_844] = _SIMD_sel_ps(_SIMD_add_ps(a_SIMD[i_nom_43_strip_844],_SIMD_mul_ps(c_SIMD[i_nom_43_strip_844],c_SIMD[i_nom_43_strip_844])),_SIMD_add_ps(a_SIMD[i_nom_43_strip_844],_SIMD_mul_ps(b_SIMD[i_nom_43_strip_844],b_SIMD[i_nom_43_strip_844])),&cmpReturn_845);
    }
  }
  return 0;
}

int s451()
{
  int i_nom_44_strip_863;
  int i_nom_44;
//	intrinsic functions
//	intrinsics
  for (int nl = 0; nl < 200000 / 5; nl++) {
    
#pragma SIMD
    for (i_nom_44 = 0, i_nom_44_strip_863 = i_nom_44; i_nom_44 <= 31999; (i_nom_44 += 4 , i_nom_44_strip_863 += 1)) {
      a_SIMD[i_nom_44_strip_863] = _SIMD_add_epi32(_SIMD_sin_epi32(b_SIMD[i_nom_44_strip_863]),_SIMD_cos_epi32(c_SIMD[i_nom_44_strip_863]));
    }
  }
  return 0;
}
//int s452()
//{
//
////	intrinsic functions
////	seq function
//
//	for (int nl = 0; nl < 4*ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[i] = b[i] + c[i] * (float) (i+1);
//		}
//	}
//	return 0;
//}
//

int s453()
{
  int i_nom_45_strip_895;
  int i_nom_45;
//	induction varibale recognition
  float s;
  __SIMD s_SIMD;
  for (int nl = 0; nl < 200000 * 2; nl++) {
    s = 0.0;
    
#pragma SIMD
    s_SIMD = _SIMD_splats_ps(s);
    for (i_nom_45 = 0, i_nom_45_strip_895 = i_nom_45; i_nom_45 <= 31999; (i_nom_45 += 4 , i_nom_45_strip_895 += 1)) {
      s_SIMD = _SIMD_add_ps(s_SIMD,_SIMD_splats_ps(2.));
      a_SIMD[i_nom_45_strip_895] = _SIMD_mul_ps(s_SIMD,b_SIMD[i_nom_45_strip_895]);
    }
  }
  return 0;
}
//
//int s491(int* __restrict__ ip)
//{
//
////	vector semantics
////	indirect addressing on lhs, store in sequence
////	scatter is required
//
//	for (int nl = 0; nl < ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[ip[i]] = b[i] + c[i] * d[i];
//		}
//	}
//	return 0;
//}
//
//int s4112(int* __restrict__ ip, float s)
//{
//
////	indirect addressing
////	sparse saxpy
////	gather is required
//
//	for (int nl = 0; nl < ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[i] += b[ip[i]] * s;
//		}
//	}
//	return 0;
//}
//
//int s4113(int* __restrict__ ip)
//{
//
////	indirect addressing
////	indirect addressing on rhs and lhs
////	gather and scatter is required
//
//
//	for (int nl = 0; nl < ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[ip[i]] = b[ip[i]] + c[i];
//		}
//	}
//	return 0;
//}
//

int va()
{
  int i_nom_46_strip_961;
  int i_nom_46;
//	control loops
//	vector assignment
  for (int nl = 0; nl < 200000 * 10; nl++) {
    
#pragma SIMD
    for (i_nom_46 = 0, i_nom_46_strip_961 = i_nom_46; i_nom_46 <= 31999; (i_nom_46 += 4 , i_nom_46_strip_961 += 1)) {
      a_SIMD[i_nom_46_strip_961] = b_SIMD[i_nom_46_strip_961];
    }
  }
  return 0;
}
//int vag( int* __restrict__ ip)
//{
//
////	control loops
////	vector assignment, gather
////	gather is required
//
//	clock_t start_t, end_t, clock_dif; double clock_dif_sec;
//
//
//	init( "vag  ");
//	start_t = clock();
//
//	for (int nl = 0; nl < 2*ntimes; nl++) {
//		for (int i = 0; i < LEN; i++) {
//			a[i] = b[ip[i]];
//		}
//		dummy(a, b, c, d, e, aa, bb, cc, 0.);
//	}
//	end_t = clock(); clock_dif = end_t - start_t;
//	clock_dif_sec = (double) (clock_dif/1000000.0);
//	printf("vag\t %.2f \t\t", clock_dif_sec);;
//	check(1);
//	return 0;
//}
//
//// %5.1
//
//int vas( int* __restrict__ ip)
//{
//
////	control loops
////	vector assignment, scatter
////	scatter is required
//
//	clock_t start_t, end_t, clock_dif; double clock_dif_sec;
//
//
//	init( "vas  ");
//	start_t = clock();
//
//	for (int nl = 0; nl < 2*ntimes; nl++) {
//		for (int i = 0; i < LEN; i++) {
//			a[ip[i]] = b[i];
//		}
//		dummy(a, b, c, d, e, aa, bb, cc, 0.);
//	}
//	end_t = clock(); clock_dif = end_t - start_t;
//	clock_dif_sec = (double) (clock_dif/1000000.0);
//	printf("vas\t %.2f \t\t", clock_dif_sec);;
//	check(1);
//	return 0;
//}
//

int vif()
{
  int i_nom_47_strip_1030;
  int i_nom_47;
  void *cmpReturn_1031;
//	control loops
//	vector if
  for (int nl = 0; nl < 200000; nl++) {
    
#pragma SIMD
    for (i_nom_47 = 0, i_nom_47_strip_1030 = i_nom_47; i_nom_47 <= 31999; (i_nom_47 += 4 , i_nom_47_strip_1030 += 1)) {
/* if statement is converted into vectorizaed conditional statement */
      _SIMD_cmpgt_ps(b_SIMD[i_nom_47_strip_1030],_SIMD_splats_ps(0.0),&cmpReturn_1031);
      a_SIMD[i_nom_47_strip_1030] = _SIMD_sel_ps(a_SIMD[i_nom_47_strip_1030],b_SIMD[i_nom_47_strip_1030],&cmpReturn_1031);
    }
  }
  return 0;
}

int vpv()
{
  int i_nom_48_strip_1048;
  int i_nom_48;
//	control loops
//	vector plus vector
  for (int nl = 0; nl < 200000 * 10; nl++) {
    
#pragma SIMD
    for (i_nom_48 = 0, i_nom_48_strip_1048 = i_nom_48; i_nom_48 <= 31999; (i_nom_48 += 4 , i_nom_48_strip_1048 += 1)) {
      a_SIMD[i_nom_48_strip_1048] = _SIMD_add_ps(a_SIMD[i_nom_48_strip_1048],b_SIMD[i_nom_48_strip_1048]);
    }
  }
  return 0;
}

int vtv()
{
  int i_nom_49_strip_1064;
  int i_nom_49;
//	control loops
//	vector times vector
// Function Body
  for (int nl = 0; nl < 200000 * 10; nl++) {
    
#pragma SIMD
    for (i_nom_49 = 0, i_nom_49_strip_1064 = i_nom_49; i_nom_49 <= 31999; (i_nom_49 += 4 , i_nom_49_strip_1064 += 1)) {
      a_SIMD[i_nom_49_strip_1064] = _SIMD_mul_ps(a_SIMD[i_nom_49_strip_1064],b_SIMD[i_nom_49_strip_1064]);
    }
  }
  return 0;
}
// %5.1

int vpvtv()
{
  int i_nom_50_strip_1082;
  int i_nom_50;
//	control loops
//	vector plus vector times vector
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_50 = 0, i_nom_50_strip_1082 = i_nom_50; i_nom_50 <= 31999; (i_nom_50 += 4 , i_nom_50_strip_1082 += 1)) {
      a_SIMD[i_nom_50_strip_1082] = _SIMD_add_ps(a_SIMD[i_nom_50_strip_1082],_SIMD_mul_ps(b_SIMD[i_nom_50_strip_1082],c_SIMD[i_nom_50_strip_1082]));
    }
  }
  return 0;
}
// %5.1
//int vpvts( float s)
//{
//
////	control loops
////	vector plus vector times scalar
//
//	for (int nl = 0; nl < ntimes; nl++) {
//#pragma SIMD
//		for (int i = 0; i < LEN; i++) {
//			a[i] += b[i] * s;
//		}
//	}
//	return 0;
//}

int vpvpv()
{
  int i_nom_51_strip_1115;
  int i_nom_51;
//	control loops
//	vector plus vector plus vector
  for (int nl = 0; nl < 4 * 200000; nl++) {
    
#pragma SIMD
    for (i_nom_51 = 0, i_nom_51_strip_1115 = i_nom_51; i_nom_51 <= 31999; (i_nom_51 += 4 , i_nom_51_strip_1115 += 1)) {
      a_SIMD[i_nom_51_strip_1115] = _SIMD_add_ps(a_SIMD[i_nom_51_strip_1115],_SIMD_add_ps(b_SIMD[i_nom_51_strip_1115],c_SIMD[i_nom_51_strip_1115]));
    }
  }
  return 0;
}

int vtvtv()
{
//	control loops
//	vector times vector times vector
  for (int nl = 0; nl < 4 * 200000; nl++) {
    for (int i = 0; i < 32000; i++) {
      a[i] = ((a[i] * b[i]) * c[i]);
    }
  }
  return 0;
}
