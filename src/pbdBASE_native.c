/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP COMM_PRINT(SEXP x);
extern SEXP COMM_STOP(char *msg);
extern SEXP COMM_WARNING(char *msg);
extern SEXP R_DALLREDUCE(SEXP X, SEXP LDIM, SEXP DESCX, SEXP OP, SEXP SCOPE);
extern SEXP R_DHILBMK(SEXP N);
extern SEXP R_MKGBLMAT(SEXP SUBX, SEXP DESCX, SEXP RDEST, SEXP CDEST);
extern SEXP R_MKSUBMAT(SEXP GBLX, SEXP LDIM, SEXP DESCX);
extern SEXP R_NUMROC(SEXP N, SEXP NB, SEXP IPROC, SEXP NPROCS);
extern SEXP R_PDCHTRI(SEXP UPLO, SEXP A, SEXP ALDIM, SEXP DESCA, SEXP CLDIM, SEXP DESCC);
extern SEXP R_PDCLVAR(SEXP X, SEXP DESCX, SEXP LSD);
extern SEXP R_PDCROSSPROD(SEXP UPLO, SEXP TRANS, SEXP A, SEXP DESCA, SEXP CLDIM, SEXP DESCC);
extern SEXP R_PDDIAGMK(SEXP LDIM, SEXP DESCX, SEXP DIAG, SEXP LDIAG);
extern SEXP R_PDGDGTK(SEXP X, SEXP LDIM, SEXP DESCX, SEXP LDIAG, SEXP RDEST, SEXP CDEST);
extern SEXP R_PDGECON(SEXP TYPE, SEXP M, SEXP N, SEXP A, SEXP DESCA);
extern SEXP R_PDGELQF(SEXP M, SEXP N, SEXP A, SEXP DESCA);
extern SEXP R_PDGELS(SEXP TOL, SEXP M, SEXP N, SEXP NRHS, SEXP A, SEXP DESCA, SEXP B, SEXP DESCB, SEXP LTAU);
extern SEXP R_PDGEMM(SEXP TRANSA, SEXP TRANSB, SEXP M, SEXP N, SEXP K, SEXP A, SEXP DESCA, SEXP B, SEXP DESCB, SEXP CLDIM, SEXP DESCC);
extern SEXP R_PDGEMR2D(SEXP M, SEXP N, SEXP X, SEXP DESCX, SEXP CLDIM, SEXP DESCB, SEXP CTXT);
extern SEXP R_PDGEQPF(SEXP TOL, SEXP M, SEXP N, SEXP A, SEXP DESCA);
extern SEXP R_PDGESV(SEXP N, SEXP NRHS, SEXP MXLDIMS, SEXP A, SEXP DESCA, SEXP B, SEXP DESCB);
extern SEXP R_PDGESVD(SEXP M, SEXP N, SEXP ASIZE, SEXP A, SEXP DESCA, SEXP ULDIM, SEXP DESCU, SEXP VTLDIM, SEXP DESCVT, SEXP JOBU, SEXP JOBVT, SEXP INPLACE);
extern SEXP R_PDGETRF(SEXP M, SEXP N, SEXP A, SEXP CLDIM, SEXP DESCA, SEXP LIPIV);
extern SEXP R_PDGETRI(SEXP A, SEXP DESCA);
extern SEXP R_PDHILBMK(SEXP LDIM, SEXP DESCX);
extern SEXP R_PDLANGE(SEXP TYPE, SEXP M, SEXP N, SEXP A, SEXP DESCA);
extern SEXP R_PDLAPRNT(SEXP M, SEXP N, SEXP A, SEXP DESCA, SEXP CMATNM, SEXP NOUT);
extern SEXP R_PDMKCPN1(SEXP LDIM, SEXP DESCX, SEXP COEF);
extern SEXP R_PDMVSUM(SEXP X, SEXP LDIM, SEXP DESCX, SEXP Y, SEXP DESCY);
extern SEXP R_PDORGLQ(SEXP M, SEXP N, SEXP K, SEXP A, SEXP DESCA, SEXP TAU);
extern SEXP R_PDORGQR(SEXP M, SEXP N, SEXP K, SEXP A, SEXP ALDIM, SEXP DESCA, SEXP TAU);
extern SEXP R_PDORMQR(SEXP SIDE, SEXP TRANS, SEXP M, SEXP N, SEXP K, SEXP A, SEXP ALDIM, SEXP DESCA, SEXP TAU, SEXP B, SEXP BLDIM, SEXP DESCB);
extern SEXP R_PDPOTRF(SEXP N, SEXP A, SEXP DESCA, SEXP UPLO);
extern SEXP R_PDSWEEP(SEXP X, SEXP LDIM, SEXP DESCX, SEXP VEC, SEXP LVEC, SEXP MARGIN, SEXP FUN);
extern SEXP R_PDSYEVR(SEXP JOBZ, SEXP UPLO, SEXP N, SEXP A, SEXP DESCA, SEXP DESCZ);
extern SEXP R_PDSYEVX(SEXP JOBZ, SEXP RANGE, SEXP N, SEXP A, SEXP DESCA, SEXP VL, SEXP VU, SEXP IL, SEXP IU, SEXP ABSTOL, SEXP ORFAC);
extern SEXP R_PDTRAN(SEXP M, SEXP N, SEXP A, SEXP DESCA, SEXP CLDIM, SEXP DESCC);
extern SEXP R_PDTRCON(SEXP TYPE, SEXP UPLO, SEXP DIAG, SEXP N, SEXP A, SEXP DESCA);
extern SEXP R_PIGEMR2D(SEXP M, SEXP N, SEXP X, SEXP DESCX, SEXP CLDIM, SEXP DESCB, SEXP CTXT);
extern SEXP R_PTRI2ZERO(SEXP UPLO, SEXP DIAG, SEXP X, SEXP LDIM, SEXP DESCX);
extern SEXP R_RCOLCPY(SEXP X, SEXP LDIM, SEXP DESCX, SEXP XCOL, SEXP Y, SEXP DESCY, SEXP YCOL, SEXP LCOLS);
extern SEXP R_RCOLCPY2(SEXP X, SEXP LDIM, SEXP DESCX, SEXP XCOL, SEXP LXCOLS, SEXP Y, SEXP DESCY, SEXP YCOL, SEXP LYCOLS);
extern SEXP R_RL2BLAS(SEXP X, SEXP LDIM, SEXP DESCX, SEXP VEC, SEXP LVEC, SEXP FUN);
extern SEXP R_RL2INSERT(SEXP X, SEXP LDIM, SEXP DESCX, SEXP VEC, SEXP LVEC, SEXP INDI, SEXP LINDI, SEXP INDJ, SEXP LINDJ);
extern SEXP R_RROWCPY(SEXP X, SEXP LDIM, SEXP DESCX, SEXP XROW, SEXP Y, SEXP DESCY, SEXP YROW, SEXP LROWS);
extern SEXP R_RROWCPY2(SEXP X, SEXP LDIM, SEXP DESCX, SEXP XROW, SEXP LXROWS, SEXP Y, SEXP DESCY, SEXP YROW, SEXP LYROWS);
extern SEXP R_blacs_exit(SEXP CONT);
extern SEXP R_blacs_init(SEXP NPROW_in, SEXP NPCOL_in, SEXP ICTXT_in);
extern SEXP R_descinit(SEXP DIM, SEXP BLDIM, SEXP ICTXT, SEXP LLD);
extern SEXP R_dgamn2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_dgamx2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_dgerv2d1(SEXP ICTXT, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_dgesd2d1(SEXP ICTXT, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_dgsum2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_g2lcoord(SEXP dim, SEXP bldim, SEXP gi, SEXP gj, SEXP gridinfo);
extern SEXP R_igamn2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_igamx2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_igsum2d1(SEXP ICTXT, SEXP SCOPE, SEXP M, SEXP N, SEXP A, SEXP LDA, SEXP RDEST, SEXP CDEST);
extern SEXP R_matexp(SEXP A, SEXP p, SEXP t_);
extern SEXP R_nbd(SEXP N, SEXP D);
extern SEXP R_optimal_grid(SEXP NPROCS);
extern SEXP R_p_matexp_pade(SEXP A, SEXP desca, SEXP p);
extern SEXP R_p_matpow_by_squaring(SEXP A, SEXP desca, SEXP b);
extern SEXP R_redist(SEXP desc, SEXP A);
extern SEXP g2l_coords(SEXP ind, SEXP dim, SEXP bldim, SEXP procs, SEXP src);
extern SEXP l2g_coords(SEXP ind, SEXP dim, SEXP bldim, SEXP procs, SEXP myproc);

static const R_CallMethodDef CallEntries[] = {
  {"COMM_PRINT", (DL_FUNC) &COMM_PRINT, 1},
  {"COMM_STOP", (DL_FUNC) &COMM_STOP, 0},
  {"COMM_WARNING", (DL_FUNC) &COMM_WARNING, 0},
  {"R_DALLREDUCE", (DL_FUNC) &R_DALLREDUCE, 5},
  {"R_DHILBMK", (DL_FUNC) &R_DHILBMK, 1},
  {"R_MKGBLMAT", (DL_FUNC) &R_MKGBLMAT, 4},
  {"R_MKSUBMAT", (DL_FUNC) &R_MKSUBMAT, 3},
  {"R_NUMROC", (DL_FUNC) &R_NUMROC, 4},
  {"R_PDCHTRI", (DL_FUNC) &R_PDCHTRI, 6},
  {"R_PDCLVAR", (DL_FUNC) &R_PDCLVAR, 3},
  {"R_PDCROSSPROD", (DL_FUNC) &R_PDCROSSPROD, 6},
  {"R_PDDIAGMK", (DL_FUNC) &R_PDDIAGMK, 4},
  {"R_PDGDGTK", (DL_FUNC) &R_PDGDGTK, 6},
  {"R_PDGECON", (DL_FUNC) &R_PDGECON, 5},
  {"R_PDGELQF", (DL_FUNC) &R_PDGELQF, 4},
  {"R_PDGELS", (DL_FUNC) &R_PDGELS, 9},
  {"R_PDGEMM", (DL_FUNC) &R_PDGEMM, 11},
  {"R_PDGEMR2D", (DL_FUNC) &R_PDGEMR2D, 7},
  {"R_PDGEQPF", (DL_FUNC) &R_PDGEQPF, 5},
  {"R_PDGESV", (DL_FUNC) &R_PDGESV, 7},
  {"R_PDGESVD", (DL_FUNC) &R_PDGESVD, 12},
  {"R_PDGETRF", (DL_FUNC) &R_PDGETRF, 6},
  {"R_PDGETRI", (DL_FUNC) &R_PDGETRI, 2},
  {"R_PDHILBMK", (DL_FUNC) &R_PDHILBMK, 2},
  {"R_PDLANGE", (DL_FUNC) &R_PDLANGE, 5},
  {"R_PDLAPRNT", (DL_FUNC) &R_PDLAPRNT, 6},
  {"R_PDMKCPN1", (DL_FUNC) &R_PDMKCPN1, 3},
  {"R_PDMVSUM", (DL_FUNC) &R_PDMVSUM, 5},
  {"R_PDORGLQ", (DL_FUNC) &R_PDORGLQ, 6},
  {"R_PDORGQR", (DL_FUNC) &R_PDORGQR, 7},
  {"R_PDORMQR", (DL_FUNC) &R_PDORMQR, 12},
  {"R_PDPOTRF", (DL_FUNC) &R_PDPOTRF, 4},
  {"R_PDSWEEP", (DL_FUNC) &R_PDSWEEP, 7},
  {"R_PDSYEVR", (DL_FUNC) &R_PDSYEVR, 6},
  {"R_PDSYEVX", (DL_FUNC) &R_PDSYEVX, 11},
  {"R_PDTRAN", (DL_FUNC) &R_PDTRAN, 6},
  {"R_PDTRCON", (DL_FUNC) &R_PDTRCON, 6},
  {"R_PIGEMR2D", (DL_FUNC) &R_PIGEMR2D, 7},
  {"R_PTRI2ZERO", (DL_FUNC) &R_PTRI2ZERO, 5},
  {"R_RCOLCPY", (DL_FUNC) &R_RCOLCPY, 8},
  {"R_RCOLCPY2", (DL_FUNC) &R_RCOLCPY2, 9},
  {"R_RL2BLAS", (DL_FUNC) &R_RL2BLAS, 6},
  {"R_RL2INSERT", (DL_FUNC) &R_RL2INSERT, 9},
  {"R_RROWCPY", (DL_FUNC) &R_RROWCPY, 8},
  {"R_RROWCPY2", (DL_FUNC) &R_RROWCPY2, 9},
  {"R_blacs_exit", (DL_FUNC) &R_blacs_exit, 1},
  {"R_blacs_init", (DL_FUNC) &R_blacs_init, 3},
  {"R_descinit", (DL_FUNC) &R_descinit, 4},
  {"R_dgamn2d1", (DL_FUNC) &R_dgamn2d1, 8},
  {"R_dgamx2d1", (DL_FUNC) &R_dgamx2d1, 8},
  {"R_dgerv2d1", (DL_FUNC) &R_dgerv2d1, 7},
  {"R_dgesd2d1", (DL_FUNC) &R_dgesd2d1, 7},
  {"R_dgsum2d1", (DL_FUNC) &R_dgsum2d1, 8},
  {"R_g2lcoord", (DL_FUNC) &R_g2lcoord, 5},
  {"R_igamn2d1", (DL_FUNC) &R_igamn2d1, 8},
  {"R_igamx2d1", (DL_FUNC) &R_igamx2d1, 8},
  {"R_igsum2d1", (DL_FUNC) &R_igsum2d1, 8},
  {"R_matexp", (DL_FUNC) &R_matexp, 3},
  {"R_nbd", (DL_FUNC) &R_nbd, 2},
  {"R_optimal_grid", (DL_FUNC) &R_optimal_grid, 1},
  {"R_p_matexp_pade", (DL_FUNC) &R_p_matexp_pade, 3},
  {"R_p_matpow_by_squaring", (DL_FUNC) &R_p_matpow_by_squaring, 3},
  {"R_redist", (DL_FUNC) &R_redist, 2},
  {"g2l_coords", (DL_FUNC) &g2l_coords, 5},
  {"l2g_coords", (DL_FUNC) &l2g_coords, 5},
  {NULL, NULL, 0}
};
void R_init_pbdBASE(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}