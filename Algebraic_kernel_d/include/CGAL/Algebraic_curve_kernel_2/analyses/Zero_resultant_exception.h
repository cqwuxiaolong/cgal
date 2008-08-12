// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL:$
// $Id: $
// 
//
// Author(s)     : Michael Kerber <mkerber@mpi-inf.mpg.de>
//
// ============================================================================

#ifndef CGAL_ACK_ZERO_RESULTANT_EXCEPTION
#define CGAL_ACK_ZERO_RESULTANT_EXCEPTION

CGAL_BEGIN_NAMESPACE

  namespace CGALi {

    /*! 
     * \brief Exception class for not sufficiently generic positions.
     *
     * Must be thrown whenever a curve cannot be analysed because its position
     * is not "good enough".
     */
    template<typename Polynomial>
    class Zero_resultant_exception {
      
      Polynomial curve1,curve2;
      bool one_curve_failure;

    public:

      Zero_resultant_exception(Polynomial c)
        : curve1(c), curve2(c),one_curve_failure(true)
        {}
        
      Zero_resultant_exception(Polynomial c1,Polynomial c2)
        : curve1(c1),curve2(c2),one_curve_failure(false)
        {}
      
    };
  }
CGAL_END_NAMESPACE

#endif
