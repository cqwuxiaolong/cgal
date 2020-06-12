// Copyright (c) 1997
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#ifndef CGAL_IO_FILE_WRITER_VRML_2_H
#define CGAL_IO_FILE_WRITER_VRML_2_H

#include <CGAL/basic.h>

#include <CGAL/IO/VRML/VRML_2_ostream.h>

#include <iostream>
#include <cstddef>

namespace CGAL {

class File_writer_VRML_2
{
  VRML_2_ostream* m_os;
  std::size_t m_facets;

public:
  File_writer_VRML_2() {}
  std::ostream& out() const { return m_os->os(); }

  void write_header(VRML_2_ostream& o,
                    std::size_t vertices,
                    std::size_t halfedges,
                    std::size_t facets)
  {
    m_os = &o;
    m_facets = facets;

    out() << "        #-- Begin of Polygon Mesh\n";
    out() << "        # " << vertices << " vertices\n";
    out() << "        # " << halfedges << " halfedges\n";
    out() << "        # " << facets << " facets\n";
    out() << "        Group {\n"
             "            children [\n"
             "                Shape {\n"
             "                    appearance Appearance { material USE Material }\n"
             "                    geometry IndexedFaceSet {\n"
             "                        convex FALSE\n"
             "                        solid  FALSE\n"
             "                        coord  Coordinate {\n"
             "                            point [" << std::endl;
  }

  void write_footer() const
  {
    out() << "                        ] #coordIndex\n"
             "                    } #geometry\n"
             "                } #Shape\n"
             "            ] #children\n"
             "        } #Group" << std::endl;
  }

  void write_vertex( const double x, const double y, const double z)
  {
    out() << "                                "
          << oformat(x) << ' ' << oformat(y) << ' ' << oformat(z) << ',' << '\n';
  }

  void write_facet_header() const
  {
    out() << "                            ] #point\n"
             "                        } #coord Coordinate\n"
             "                        coordIndex  [" << std::endl;
  }

  void write_facet_begin( std::size_t) { out() << "                            "; }
  void write_facet_vertex_index( std::size_t idx) { out() << idx << ',';}
  void write_facet_end() { out() << "-1,\n"; }
};

} // namespace CGAL

#endif // CGAL_IO_FILE_WRITER_VRML_2_H //
