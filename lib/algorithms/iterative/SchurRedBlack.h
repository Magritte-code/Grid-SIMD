#ifndef GRID_SCHUR_RED_BLACK_H
#define GRID_SCHUR_RED_BLACK_H


  /*
   * Red black Schur decomposition
   *
   *  M = (Mee Meo) =  (1             0 )   (Mee   0               )  (1 Mee^{-1} Meo)
   *      (Moe Moo)    (Moe Mee^-1    1 )   (0   Moo-Moe Mee^-1 Meo)  (0   1         )
   *                =         L                     D                     U
   *
   * L^-1 = (1              0 )
   *        (-MoeMee^{-1}   1 )   
   * L^{dag} = ( 1       Mee^{-dag} Moe^{dag} )
   *           ( 0       1                    )
   * L^{-d}  = ( 1      -Mee^{-dag} Moe^{dag} )
   *           ( 0       1                    )
   *
   * U^-1 = (1   -Mee^{-1} Meo)
   *        (0    1           )
   * U^{dag} = ( 1                 0)
   *           (Meo^dag Mee^{-dag} 1)
   * U^{-dag} = (  1                 0)
   *            (-Meo^dag Mee^{-dag} 1)
   ***********************
   *     M psi = eta
   ***********************
   *Odd
   * i)   (D_oo)^{\dag} D_oo psi_o = (D_oo)^dag L^{-1}  eta_o
   *                        eta_o' = (D_oo)^dag (eta_o - Moe Mee^{-1} eta_e)
   *Even
   * ii)  Mee psi_e + Meo psi_o = src_e
   *
   *   => sol_e = M_ee^-1 * ( src_e - Meo sol_o )...
   *
   */
namespace Grid {

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Take a matrix and form a Red Black solver calling a Herm solver
  // Use of RB info prevents making SchurRedBlackSolve conform to standard interface
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class Field> class SchurRedBlackSolve {
  private:
    HermitianOperatorFunction<Field> & _HermitianRBSolver;
    int CBfactorise;
  public:

    /////////////////////////////////////////////////////
    // Wrap the usual normal equations Schur trick
    /////////////////////////////////////////////////////
  SchurRedBlackSolve(HermitianOperatorFunction<Field> &HermitianRBSolver)  :
     _HermitianRBSolver(HermitianRBSolver) 
    { 
      CBfactorise=0;
    };

    template<class Matrix>
      void operator() (Matrix & _Matrix,const Field &in, Field &out){

      // FIXME CGdiagonalMee not implemented virtual function
      // FIXME use CBfactorise to control schur decomp
      GridBase *grid = _Matrix._cbgrid;
      GridBase *fgrid= _Matrix._grid;
 
      Field src_e(grid);
      Field src_o(grid);
      Field sol_e(grid);
      Field sol_o(grid);
      Field   tmp(grid);
      Field  Mtmp(grid);
      Field resid(fgrid);

      pickCheckerboard(Even,src_e,in);
      pickCheckerboard(Odd ,src_o,in);

      /////////////////////////////////////////////////////
      // src_o = Mdag * (source_o - Moe MeeInv source_e)
      /////////////////////////////////////////////////////
      _Matrix.MooeeInv(src_e,tmp);     assert(  tmp.checkerboard ==Even);
      _Matrix.Meooe   (tmp,Mtmp);      assert( Mtmp.checkerboard ==Odd);     
      tmp=src_o-Mtmp;                  assert(  tmp.checkerboard ==Odd);     
      _Matrix.MpcDag(tmp,src_o);       assert(src_o.checkerboard ==Odd);       

      //////////////////////////////////////////////////////////////
      // Call the red-black solver
      //////////////////////////////////////////////////////////////
      HermitianCheckerBoardedOperator<Matrix,Field> _HermOpEO(_Matrix);
      std::cout << "SchurRedBlack solver calling the MpcDagMp solver" <<std::endl;
      _HermitianRBSolver(_HermOpEO,src_o,sol_o);  assert(sol_o.checkerboard==Odd);

      ///////////////////////////////////////////////////
      // sol_e = M_ee^-1 * ( src_e - Meo sol_o )...
      ///////////////////////////////////////////////////
      _Matrix.Meooe(sol_o,tmp);        assert(  tmp.checkerboard   ==Even);
      src_e = src_e-tmp;               assert(  src_e.checkerboard ==Even);
      _Matrix.MooeeInv(src_e,sol_e);   assert(  sol_e.checkerboard ==Even);
     
      setCheckerboard(out,sol_e); assert(  sol_e.checkerboard ==Even);
      setCheckerboard(out,sol_o); assert(  sol_o.checkerboard ==Odd );

      // Verify the unprec residual
      _Matrix.M(out,resid); 
      resid = resid-in;
      RealD ns = norm2(in);
      RealD nr = norm2(resid);

      std::cout << "SchurRedBlack solver true unprec resid "<< sqrt(nr/ns) <<" nr "<< nr <<" ns "<<ns << std::endl;
    }     
  };

}
#endif