#include <R.h>
#include <Rinternals.h>
#include "base_global.h"

/* For computing LLS solution, either over or under-determined. */
/* In the case that A is rank deficient, the 'limited pivoting  */
/* strategy from R's dqrls.f is used. I don't think this is     */
/* numerically stable, but it's the cost of preserving the      */
/* order of the model matrix, which has important interpretive  */
/* value.                                                       */
SEXP R_PDGELS(SEXP TOL, SEXP M, SEXP N, SEXP NRHS,
  SEXP A, SEXP ALDIM, SEXP DESCA,
  SEXP B, SEXP BLDIM, SEXP DESCB,
  SEXP LTAU)
{
  int i, *pt_ALDIM = INTEGER(ALDIM), *pt_BLDIM = INTEGER(BLDIM);
  int lwork = -1;
  const int IJ = 1;
  
  double *pt_ORG, *pt_COPY, *pt_FT, *p_work;
  const double tmp = 0;
  double work = 0;
  
  char trans = 'N';
  
  SEXP RET, RET_NAMES, INFO, A_OUT, B_OUT, FT, RSD, TAU, IPIV, RANK;
  
  /* set up return */
  PROTECT(RET = allocVector(VECSXP, 8));
  PROTECT(RET_NAMES = allocVector(STRSXP, 8));
  
  PROTECT(INFO = allocVector(INTSXP, 1));
  PROTECT(A_OUT = allocMatrix(REALSXP, pt_ALDIM[0], pt_ALDIM[1]));
  PROTECT(B_OUT = allocMatrix(REALSXP, pt_BLDIM[0], pt_BLDIM[1]));
  PROTECT(FT = allocMatrix(REALSXP, pt_BLDIM[0], pt_BLDIM[1]));
  PROTECT(RSD = allocMatrix(REALSXP, pt_BLDIM[0], pt_BLDIM[1]));
  PROTECT(TAU = allocVector(REALSXP, INTEGER(LTAU)[0]));
  PROTECT(IPIV = allocVector(INTSXP, pt_ALDIM[1]));
  PROTECT(RANK = allocVector(INTSXP, 1));
  
  SET_VECTOR_ELT(RET, 0, INFO);
  SET_VECTOR_ELT(RET, 1, A_OUT);
  SET_VECTOR_ELT(RET, 2, B_OUT);
  SET_VECTOR_ELT(RET, 3, FT);
  SET_VECTOR_ELT(RET, 4, RSD);
  SET_VECTOR_ELT(RET, 5, TAU);
  SET_VECTOR_ELT(RET, 6, IPIV);
  SET_VECTOR_ELT(RET, 7, RANK);
  
  SET_STRING_ELT(RET_NAMES, 0, mkChar("INFO")); 
  SET_STRING_ELT(RET_NAMES, 1, mkChar("A")); 
  SET_STRING_ELT(RET_NAMES, 2, mkChar("B")); 
  SET_STRING_ELT(RET_NAMES, 3, mkChar("FT")); 
  SET_STRING_ELT(RET_NAMES, 4, mkChar("RSD")); 
  SET_STRING_ELT(RET_NAMES, 5, mkChar("TAU")); 
  SET_STRING_ELT(RET_NAMES, 6, mkChar("IPIV"));
  SET_STRING_ELT(RET_NAMES, 7, mkChar("RANK")); 
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  /* Copy A and B since pdgels writes in place, also initialize */
  /* FT = 0 */
  pt_ORG = REAL(A);
  pt_COPY = REAL(A_OUT);
  for(i = 0; i < pt_ALDIM[0] * pt_ALDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  pt_ORG = REAL(B);
  pt_COPY = REAL(B_OUT);
  pt_FT = REAL(FT);
  
  for(i = 0; i < pt_BLDIM[0] * pt_BLDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    *pt_FT = 0;
    pt_FT++;
    pt_ORG++;
    pt_COPY++;
  }
  
  /* workspace query */
  INTEGER(INFO)[0] = 0;
  F77_CALL(rpdgels)(REAL(TOL), &trans, 
    INTEGER(M), INTEGER(N), INTEGER(NRHS),
    &tmp, &IJ, &IJ, INTEGER(DESCA),
    &tmp, &IJ, &IJ, INTEGER(DESCB),
    &tmp, &tmp,
    &tmp, &work, &lwork, 
    &IJ, &IJ, INTEGER(INFO));
  
  /* allocate work vector and compute LLS solution */
  lwork = (int) work;
  p_work = (double *) R_alloc(lwork, sizeof(double));
  
  INTEGER(INFO)[0] = 0;
  F77_CALL(rpdgels)(REAL(TOL), &trans, 
    INTEGER(M), INTEGER(N), INTEGER(NRHS),
    REAL(A_OUT), &IJ, &IJ, INTEGER(DESCA),
    REAL(B_OUT), &IJ, &IJ, INTEGER(DESCB),
    REAL(FT), REAL(RSD),
    REAL(TAU), p_work, &lwork, 
    INTEGER(IPIV), INTEGER(RANK), INTEGER(INFO));
  
  /* Return. */
  UNPROTECT(10);
  return(RET);
} 



/* ----------------------------------------------------- */
/*           QR functions no one will ever use           */
/* ----------------------------------------------------- */


/* For computing Q*y or Q^T*y */
SEXP R_PDORMQR(SEXP SIDE, SEXP TRANS, SEXP M, SEXP N, SEXP K,
  SEXP A, SEXP ALDIM, SEXP DESCA, 
  SEXP TAU,
  SEXP B, SEXP BLDIM, SEXP DESCB)
{
  int i, *pt_ALDIM = INTEGER(ALDIM), *pt_BLDIM = INTEGER(BLDIM);
  int lwork = -1;
  const int IJ = 1;
  
  double *pt_ORG, *pt_COPY, *A_OUT;
  double work = 0;
  const double tmp = 0;
  
  double *p_work, *tau;
  
  SEXP RET, RET_NAMES, INFO, B_OUT;
  
  /* Protect R objects. */
  PROTECT(RET = allocVector(VECSXP, 2));
  PROTECT(RET_NAMES = allocVector(STRSXP, 2));
  PROTECT(INFO = allocVector(INTSXP, 1));
  PROTECT(B_OUT = allocMatrix(REALSXP, pt_BLDIM[0], pt_BLDIM[1]));
  
  SET_VECTOR_ELT(RET, 0, INFO);
  SET_VECTOR_ELT(RET, 1, B_OUT);
  SET_STRING_ELT(RET_NAMES, 0, mkChar("info")); 
  SET_STRING_ELT(RET_NAMES, 1, mkChar("B")); 
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  /* Copy A and B since pdormqr writes in place */
  A_OUT = (double *) R_alloc(pt_ALDIM[0] * pt_ALDIM[1], sizeof(double));
  pt_ORG = REAL(A);
  pt_COPY = A_OUT;
  for(i = 0; i < pt_ALDIM[0] * pt_ALDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  pt_ORG = REAL(B);
  pt_COPY = REAL(B_OUT);
  for(i = 0; i < pt_BLDIM[0] * pt_BLDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  /* workspace query */
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdormqr)(CHARPT(SIDE, 0), CHARPT(TRANS, 0),
    INTEGER(M), INTEGER(N), INTEGER(K), 
    &tmp, &IJ, &IJ, INTEGER(DESCA), 
    &tmp,
    &tmp, &IJ, &IJ, INTEGER(DESCB),
    &work, &lwork, INTEGER(INFO)[0]);
  
  /* allocate work vector and compute Q*y or Q^T*y */
  lwork = (int) work;
  p_work = (double *) R_alloc(lwork, sizeof(double));
  
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdormqr)(CHARPT(SIDE, 0), CHARPT(TRANS, 0),
    INTEGER(M), INTEGER(N), INTEGER(K), 
    REAL(A_OUT), &IJ, &IJ, INTEGER(DESCA), 
    tau,
    REAL(B_OUT), &IJ, &IJ, INTEGER(DESCB),
    p_work, &lwork, INTEGER(INFO)[0]);
  
  /* Return. */
  UNPROTECT(4);
  return(RET);
} 







/* recovering Q from a QR */
SEXP R_PDORGQR(SEXP M, SEXP N, SEXP K,
  SEXP A, SEXP ALDIM, SEXP DESCA, 
  SEXP TAU)
{
  int i, *pt_ALDIM = INTEGER(ALDIM);
  int lwork = -1;
  const int IJ = 1;
  
  double *pt_ORG, *pt_COPY;
  double work = 0;
  const double tmp = 0;
  
  double *p_work;
  
  SEXP RET, RET_NAMES, INFO, A_OUT;
  
  /* Protect R objects. */
  PROTECT(RET = allocVector(VECSXP, 2));
  PROTECT(RET_NAMES = allocVector(STRSXP, 2));
  PROTECT(INFO = allocVector(INTSXP, 1));
  PROTECT(A_OUT = allocMatrix(REALSXP, pt_ALDIM[0], pt_ALDIM[1]));
  
  SET_VECTOR_ELT(RET, 0, INFO);
  SET_VECTOR_ELT(RET, 1, A_OUT);
  SET_STRING_ELT(RET_NAMES, 0, mkChar("info")); 
  SET_STRING_ELT(RET_NAMES, 1, mkChar("A")); 
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  /* Copy A since pdorgqr writes in place */
  pt_ORG = REAL(A);
  pt_COPY = A_OUT;
  for(i = 0; i < pt_ALDIM[0] * pt_ALDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  /* workspace query */
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdorgqr)(INTEGER(M), INTEGER(N), INTEGER(K), 
    &tmp, &IJ, &IJ, INTEGER(DESCA), 
    &tmp,
    &work, &lwork, INTEGER(INFO)[0]);
  
  /* allocate work vector and compute Q*y or Q^T*y */
  lwork = (int) work;
  p_work = (double *) R_alloc(lwork, sizeof(double));
  
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdorgqr)(INTEGER(M), INTEGER(N), INTEGER(K), 
    REAL(A_OUT), &IJ, &IJ, INTEGER(DESCA), 
    REAL(TAU),
    p_work, &lwork, INTEGER(INFO)[0]);
  
  /* Return. */
  UNPROTECT(4);
  return(RET);
} 





/* reduces upper trapezoidal to traingular form */
SEXP R_PDTZRZF(SEXP M, SEXP N, 
  SEXP A, SEXP ALDIM, SEXP DESCA, 
  SEXP TAU)
{
  int i, *pt_ALDIM = INTEGER(ALDIM);
  int lwork = -1;
  const int IJ = 1;
  
  double *pt_ORG, *pt_COPY;
  double work = 0;
  const double tmp = 0;
  
  double *p_work;
  
  SEXP RET, RET_NAMES, INFO, A_OUT;
  
  /* Protect R objects. */
  PROTECT(RET = allocVector(VECSXP, 2));
  PROTECT(RET_NAMES = allocVector(STRSXP, 2));
  PROTECT(INFO = allocVector(INTSXP, 1));
  PROTECT(A_OUT = allocMatrix(REALSXP, pt_ALDIM[0], pt_ALDIM[1]));
  
  SET_VECTOR_ELT(RET, 0, INFO);
  SET_VECTOR_ELT(RET, 1, A_OUT);
  SET_STRING_ELT(RET_NAMES, 0, mkChar("info")); 
  SET_STRING_ELT(RET_NAMES, 1, mkChar("A")); 
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  /* Copy A since pdorgqr writes in place */
  pt_ORG = REAL(A);
  pt_COPY = A_OUT;
  for(i = 0; i < pt_ALDIM[0] * pt_ALDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  /* workspace query */
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdorgqr)(INTEGER(M), INTEGER(N),
    &tmp, &IJ, &IJ, INTEGER(DESCA), 
    &tmp,
    &work, &lwork, INTEGER(INFO)[0]);
  
  /* allocate work vector and compute Q*y or Q^T*y */
  lwork = (int) work;
  p_work = (double *) R_alloc(lwork, sizeof(double));
  
  INTEGER(INFO)[0] = 0;
  F77_CALL(pdorgqr)(INTEGER(M), INTEGER(N), 
    REAL(A_OUT), &IJ, &IJ, INTEGER(DESCA), 
    REAL(TAU),
    p_work, &lwork, INTEGER(INFO)[0]);
  
  /* Return. */
  UNPROTECT(4);
  return(RET);
} 




/* solve a triangular system*/
SEXP R_PDTRSV(SEXP UPLO, SEXP TRANS, SEXP DIAG,
  SEXP N,
  SEXP A, SEXP ALDIM, SEXP DESCA,
  SEXP B, SEXP BLDIM, SEXP DESCB)
{
  int i, *pt_ALDIM = INTEGER(ALDIM), *pt_BLDIM = INTEGER(BLDIM);
  const int IJ = 1;
  
  double *pt_ORG, *pt_COPY;
  
  SEXP RET, RET_NAMES, INFO, A_OUT, B_OUT;
  
  /* Protect R objects. */
  PROTECT(RET = allocVector(VECSXP, 3));
  PROTECT(RET_NAMES = allocVector(STRSXP, 3));
  PROTECT(INFO = allocVector(INTSXP, 1));
  PROTECT(A_OUT = allocMatrix(REALSXP, pt_ALDIM[0], pt_ALDIM[1]));
  PROTECT(B_OUT = allocMatrix(REALSXP, pt_BLDIM[0], pt_BLDIM[1]));
  
  SET_VECTOR_ELT(RET, 0, INFO);
  SET_VECTOR_ELT(RET, 1, A_OUT);
  SET_VECTOR_ELT(RET, 2, B_OUT);
  
  SET_STRING_ELT(RET_NAMES, 0, mkChar("info")); 
  SET_STRING_ELT(RET_NAMES, 1, mkChar("A")); 
  SET_STRING_ELT(RET_NAMES, 3, mkChar("B")); 
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  /* Copy A and B since pdtrsv writes in place */
  pt_ORG = REAL(A);
  pt_COPY = A_OUT;
  for(i = 0; i < pt_ALDIM[0] * pt_ALDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  pt_ORG = REAL(B);
  pt_COPY = REAL(B_OUT);
  for(i = 0; i < pt_BLDIM[0] * pt_BLDIM[1]; i++){
    *pt_COPY = *pt_ORG;
    pt_ORG++;
    pt_COPY++;
  }
  
  INTEGER(INFO)[0] = 0;
  pdtrsv_(CHARPT(UPLO, 0), CHARPT(TRANS, 0), CHARPT(DIAG, 0), 
    INTEGER(N)[0], 
    REAL(A_OUT), IJ, IJ, INTEGER(DESCA),
    REAL(B_OUT), IJ, IJ, INTEGER(DESCB),
    IJ);
  
  /* Return. */
  UNPROTECT(4);
  return(RET);
}
  