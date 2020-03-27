// Copyright (c) 2014
// INRIA Saclay-Ile de France (France)
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Marc Glisse

#ifndef CGAL_KERNEL_D_CARTESIAN_FILTER_K_H
#define CGAL_KERNEL_D_CARTESIAN_FILTER_K_H

#include <CGAL/basic.h>
#include <CGAL/NewKernel_d/KernelD_converter.h>
#include <CGAL/NewKernel_d/Filtered_predicate2.h>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>

namespace CGAL {

  // It would be nicer to write the table in the other direction: Orientation_of_points_tag is good up to 6, Side_of_oriented_sphere_tag up to 5, etc.
template<class> struct Functors_without_division { typedef typeset<> type; };
template<> struct Functors_without_division<Dimension_tag<1> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};
template<> struct Functors_without_division<Dimension_tag<2> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};
template<> struct Functors_without_division<Dimension_tag<3> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};
template<> struct Functors_without_division<Dimension_tag<4> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};
template<> struct Functors_without_division<Dimension_tag<5> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};
template<> struct Functors_without_division<Dimension_tag<6> > {
  typedef typeset<Orientation_of_points_tag, Side_of_oriented_sphere_tag> type;
};

template < typename Base_, typename AK_, typename EK_, typename Pred_list = typeset_all >
struct Cartesian_filter_K : public Base_,
  private Store_kernel<EK_>
{
    CGAL_CONSTEXPR Cartesian_filter_K(){}
    CGAL_CONSTEXPR Cartesian_filter_K(int d):Base_(d){}
    //FIXME: or do we want an instance of AK and EK belonging to this kernel,
    //instead of a reference to external ones?
    CGAL_CONSTEXPR Cartesian_filter_K(AK_ const&,EK_ const&b):Base_(),Store_kernel<EK_>(b){}
    CGAL_CONSTEXPR Cartesian_filter_K(int d,AK_ const&,EK_ const&b):Base_(d),Store_kernel<EK_>(b){}
    typedef Base_ Kernel_base;
    typedef AK_ AK;
    typedef EK_ EK;
    CGAL_static_assertion_msg(internal::Do_not_store_kernel<AK>::value, "Only handle stateless kernels as AK");
    AK approximate_kernel()const{return {};}
    typedef typename Store_kernel<EK_>::reference_type EK_rt;
    EK_rt exact_kernel()const{return this->Store_kernel<EK>::kernel();}

    // MSVC is too dumb to perform the empty base optimization.
    typedef boost::mpl::and_<
      internal::Do_not_store_kernel<Kernel_base>,
      internal::Do_not_store_kernel<EK> > Do_not_store_kernel;

    //TODO: C2A/C2E could be able to convert *this into this->kernel() or this->kernel2().
    typedef KernelD_converter<Kernel_base,AK> C2A;
    typedef KernelD_converter<Kernel_base,EK> C2E;

    // fix the types
    // TODO: only fix some types, based on some criterion?
    template<class T> struct Type : Get_type<Kernel_base,T> {};

    template<class T,class D=void,class=typename Get_functor_category<Cartesian_filter_K,T>::type, bool=Pred_list::template contains<T>::value> struct Functor :
      Inherit_functor<Kernel_base,T,D> {};
    template<class T,class D> struct Functor<T,D,Predicate_tag,true> {
      typedef typename Get_functor<AK, T>::type AP;
      typedef typename Get_functor<EK, T>::type EP;
      typedef Filtered_predicate2<Cartesian_filter_K,EP,AP,C2E,C2A> type;
    };
// TODO:
//    template<class T> struct Functor<T,No_filter_tag,Predicate_tag> :
//            Kernel_base::template Functor<T,No_filter_tag> {};
// TODO:
// detect when Less_cartesian_coordinate doesn't need filtering
};

} //namespace CGAL

#endif // CGAL_KERNEL_D_CARTESIAN_FILTER_K_H
