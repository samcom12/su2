/*!
 * \file CMeshVariable.cpp
 * \brief Definition of the variables for mesh motion using a pseudo-elastic approach.
 * \author Ruben Sanchez
 * \version 7.1.1 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2021, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */


#include "../../include/variables/CMeshVariable.hpp"

CMeshVariable::CMeshVariable(unsigned long npoint, unsigned long ndim, CConfig *config) :
  CVariable(npoint, ndim, config) {

  /*--- Booleans that determine the kind of problems ---*/
  bool time_domain = config->GetTime_Domain();

  /*--- Store the dimensionality of the problem ---*/
  nDim = ndim;

  /*--- Initalize the variables that will always be there in a problem with moving mesh ---*/
  Mesh_Coord.resize(nPoint,nDim) = su2double(0.0);
  WallDistance.resize(nPoint) = su2double(1e-9);

  /*--- Initialize the variables necessary when the problem is time domain ---*/
  if (time_domain) {
    Solution_time_n.resize(nPoint,nDim) = su2double(0.0);
    Solution_time_n1.resize(nPoint,nDim) = su2double(0.0);
  }
}

void CMeshVariable::Register_MeshCoord() {
  SU2_OMP_FOR_STAT(roundUpDiv(nPoint,omp_get_num_threads()))
  for (unsigned long iPoint = 0; iPoint < nPoint; iPoint++)
    for (unsigned long iDim = 0; iDim < nDim; iDim++)
      AD::RegisterInput(Mesh_Coord(iPoint,iDim));
  END_SU2_OMP_FOR
}
