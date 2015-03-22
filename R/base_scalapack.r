# ################################################
# ------------------------------------------------
# Linear Equations
# ------------------------------------------------
# ################################################

# ------------------------------------------------
# PDGETRI:    Matrix inverse
# ------------------------------------------------

#' @export
base.rpdgetri <- function(n, a, desca)
{
    aldim <- base.numroc(desca[3:4], desca[5:6], ICTXT=desca[2])
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    out <- .Call(R_PDGETRI, a, as.integer(desca))
    
    if (out$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", out$info, "; returned solution is likely invalid", sep=""))
    
    return( out$A )
}

# ------------------------------------------------
# PDGESV:    Solving Ax=b
# ------------------------------------------------

#' @export
base.rpdgesv <- function(n, nrhs, a, desca, b, descb)
{
    aldim <- base.numroc(desca[3:4], desca[5:6], ICTXT=desca[2])
    bldim <- base.numroc(descb[3:4], descb[5:6], ICTXT=descb[2])
    
    # max of the local dimensions
    mxldims <- c(base.maxdim(aldim), base.maxdim(bldim))
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    if (!is.double(b))
        storage.mode(b) <- "double"
    
    # Call ScaLAPACK
    out <- .Call(R_PDGESV,
                 as.integer(n), as.integer(nrhs), as.integer(mxldims),
                 a, as.integer(desca), b, as.integer(descb))
    
    if (out$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", out$info, "; returned solution is likely invalid", sep=""))
    
    return( out$B ) 
}

# ################################################
# ------------------------------------------------
# Matrix Factorizations
# ------------------------------------------------
# ################################################

# ------------------------------------------------
# PDGESVD:    SVD of x
# ------------------------------------------------

#' @export
base.rpdgesvd <- function(jobu, jobvt, m, n, a, desca, descu, descvt, ..., inplace=FALSE)
{
    size <- min(m, n)
    
    aldim <- dim(a)
    uldim <- base.numroc(descu[3:4], descu[5:6], ICTXT=descu[2])
    vtldim <- base.numroc(descvt[3:4], descvt[5:6], ICTXT=descvt[2])
    
    mxa <- pbdMPI::allreduce(max(aldim), op='max')
    mxu <- pbdMPI::allreduce(max(uldim), op='max')
    mxvt <- pbdMPI::allreduce(max(vtldim), op='max')
    
    if (all(aldim==1))
        desca[9L] <- mxa
    if (all(uldim==1))
        descu[9L] <- mxu
    if (all(vtldim==1))
        descvt[9L] <- mxvt
    
    if (desca[3L]>1){
        if (pbdMPI::allreduce(desca[9L], op='max')==1)
            desca[9L] <- mxa
    }
    if (descu[3L]>1){
        if (pbdMPI::allreduce(descu[9L], op='max')==1)
            desca[9L] <- mxu
    }
    if (descvt[3L]>1){
        if (pbdMPI::allreduce(descvt[9L], op='max')==1)
            desca[9L] <- mxvt
    }
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    # FIXME currently does nothing
    if (inplace)
        inplace <- 'Y'
    else
        inplace <- 'N'
    
    # Call ScaLAPACK
    out <- .Call(R_PDGESVD, 
                        as.integer(m), as.integer(n), as.integer(size),
                        a, as.integer(desca), 
                        as.integer(uldim), as.integer(descu),
                        as.integer(vtldim), as.integer(descvt),
                        as.character(jobu), as.character(jobvt), inplace)
    
    if (out$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", out$info, "; returned solution is likely invalid", sep=""))
    
    ret <- list( d=out$d, u=out$u, vt=out$vt )
    
    return( ret )
}


# ------------------------------------------------
# PDSYEV:    Eigen
# ------------------------------------------------

#' @export
base.rpdsyev <- function(jobz, uplo, n, a, desca, descz)
{
    aldim <- dim(a)
    zldim <- base.numroc(descz[3:4], descz[5:6], ICTXT=descz[2])
    
    mxa <- pbdMPI::allreduce(max(aldim), op='max')
    mxz <- pbdMPI::allreduce(max(zldim), op='max')
    
    if (all(aldim==1))
        desca[9L] <- mxa
    if (all(zldim==1))
        descz[9L] <- mxz
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    # Call ScaLAPACK
    out <- .Call(R_PDSYEV, 
                        as.character(jobz), as.character(uplo),
                        as.integer(n), a, as.integer(desca), as.integer(aldim),
                        as.integer(zldim), as.integer(descz))
    
    if (out$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", out$info, "; returned solution is likely invalid", sep=""))
    
    out$values <- rev(out$values)
    out$info <- NULL
    
    return( out )
}


# ------------------------------------------------
# PDPOTRF:    Cholesky Factorization
# ------------------------------------------------

#' @export
base.rpdpotrf <- function(uplo, n, a, desca)
{
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    # Call ScaLAPACK
    ret <- .Call(R_PDPOTRF,
                 as.integer(n), a, as.integer(desca),
                 as.character(uplo))
    
    if (ret$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", ret$info, "; returned solution is likely invalid", sep=""))
    
    return( ret ) 
}



# ------------------------------------------------
# PDSYEVX:    Eigenvalues...again
# ------------------------------------------------

#' @export
base.rpdsyevx <- function(jobz, range, n, a, desca, vl, vu, il, iu, abstol=1e-8, orfac=1e-3)
{
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    
    # Call ScaLAPACK
    ret <- .Call(R_PDSYEVX,
               as.character(jobz), as.character(range),
               as.integer(n), a, as.integer(desca),
               as.double(vl), as.double(vu), as.integer(il), as.integer(iu),
               as.double(abstol), as.double(orfac))
    
    return( ret )
}


# ------------------------------------------------
# PDGETRF:    LU Decomposition
# ------------------------------------------------

#' @export
base.rpdgetrf <- function(a, desca)
{
    m <- desca[3L]
    n <- desca[4L]
    
    aldim <- dim(a)
    
    mxrow <- base.igamx2d(ICTXT=desca[2L], SCOPE='Row', m=1L, n=1L, x=aldim[1L], lda=1L, RDEST=-1L, CDEST=-1L)
    lipiv <- mxrow + desca[5L]
#    lipiv <- base.maxdim(aldim)[1L] + desca[5L]
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    # Call ScaLAPACK
    out <- .Call(R_PDGETRF,
                 as.integer(m), as.integer(n),
                 a, as.integer(aldim), as.integer(desca),
                 as.integer(lipiv))
    
    if (out$info!=0)
        comm.warning(paste("ScaLAPACK returned INFO=", out$info, "; returned solution is likely invalid", sep=""))
    
    return( out$A ) 
}


# ################################################
# ------------------------------------------------
# Auxillary
# ------------------------------------------------
# ################################################

#' @export
base.indxg2p <- function(INDXGLOB, NB, NPROCS)
{
    
    ISRCPROC <- 0L
    
    ret <- (ISRCPROC + (INDXGLOB - 1L) / NB) %% NPROCS
    
    return( ret )
}



#' @export
numroc2 <- function(N, NB, IPROC, NPROCS)
{
    ISRCPROC <- 0L
    
    MYDIST <- (NPROCS + IPROC -    ISRCPROC) %% NPROCS
    NBLOCKS <- floor(N / NB)
    ldim <- floor(NBLOCKS / NPROCS) * NB
    EXTRABLKS <- NBLOCKS %% NPROCS
    
    if (is.na(EXTRABLKS))
        EXTRABLKS <- 0L
    
    if (MYDIST < EXTRABLKS)
        ldim <- ldim + NB
    else if (MYDIST == EXTRABLKS)
        ldim <- ldim + N %% NB
    
    return(ldim)
}


# matrix norms
#' @export
base.rpdlange <- function(norm, m, n, a, desca)
{
    if (length(norm)>1L)
        norm <- norm[1L]
    
    norm <- toupper(norm)
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    ret <- .Call(R_PDLANGE, 
                norm, as.integer(m), as.integer(n),
                a, as.integer(desca))
    
    return( ret )
}



# Inverse condition number - triangular matrix
base.rpdtrcon <- function(norm, uplo, diag, n, a, desca)
{
    if (length(norm)>1L)
        norm <- norm[1L]
    
    norm <- toupper(norm)
    uplo <- toupper(uplo)
    diag <- toupper(diag)
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    ret <- .Call(R_PDTRCON, 
                norm, uplo, diag, 
                as.integer(n), a, as.integer(desca))
    
    if (ret[2L] < 0)
        comm.warning(paste("INFO =", ret[2L]))
    
    return( ret[1L] )
}



# Inverse condition number - general matrix
#' @export
base.rpdgecon <- function(norm, m, n, a, desca)
{
    if (length(norm)>1L)
        norm <- norm[1L]
    
    norm <- toupper(norm)
    
    if (!is.double(a))
        storage.mode(a) <- "double"
    
    ret <- .Call(R_PDGECON, norm, as.integer(m), as.integer(n), a, as.integer(desca))
    
    if (ret[2] < 0)
        comm.warning(paste("INFO =", ret[2]))
    
    return( ret[1] )
}



# ################################################
# ------------------------------------------------
# Utility
# ------------------------------------------------
# ################################################

# ------------------------------------------------
# PDGEMR2D:    BC redistributions
# ------------------------------------------------

#' @export
base.rpdgemr2d <- function(x, descx, descy)
{
    ldimy <- base.numroc(dim=descy[3L:4L], bldim=descy[5L:6L], ICTXT=descy[2L])
    
    m <- descx[3L]
    n <- descx[4L]
    
    if (!is.double(x))
        storage.mode(x) <- "double"
    
    ret <- .Call(R_PDGEMR2D,
                 as.integer(m), as.integer(n),
                 x, as.integer(descx),
                 as.integer(ldimy), as.integer(descy),
                 as.integer(0)) # context 0 is always passed since pdgemr2d 
                 # requires the grids to have at least 1 processor in common
    
    if (!base.ownany(dim=c(m, n), bldim=descy[5L:6L], ICTXT=descy[2L]))
        ret <- matrix(0.0, 1L, 1L)
    
    return( ret )
}



