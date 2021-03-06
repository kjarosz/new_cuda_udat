/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                               */
/*    This file is part of Cuda-Wndchrm.                                         */
/*    Copyright (C) 2017 Kamil Jarosz, Christopher K. Horton and Tyler Wiersing  */
/*                                                                               */
/*    This library is free software; you can redistribute it and/or              */
/*    modify it under the terms of the GNU Lesser General Public                 */
/*    License as published by the Free Software Foundation; either               */
/*    version 2.1 of the License, or (at your option) any later version.         */
/*                                                                               */
/*    This library is distributed in the hope that it will be useful,            */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU          */
/*    Lesser General Public License for more details.                            */
/*                                                                               */
/*    You should have received a copy of the GNU Lesser General Public           */
/*    License along with this library; if not, write to the Free Software        */
/*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA  */
/*                                                                               */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef CUDASIGNATURES_H
#define CUDASIGNATURES_H


#include <string>
#include <vector>

#include "image/image_matrix.h"

#include "signatures.h"
#include "constants.h"
#include "utils/DirectoryListing.h"



// 256 MB Batch Limit
const int BATCH_SIZE = 268435456;

const int MAXIMUM_CUDA_THREADS = 356;



// SECTION A - Main Interface
//------------------------------------------------------------------------------
std::vector<ClassSignatures> compute_signatures(char *root_dir, char **class_dirs, int class_count);
ClassSignatures              compute_class_signatures(std::string class_dir);
std::vector<FileSignatures>  compute_signatures_on_cuda(std::vector<ImageMatrix *> &matrices);

void                         save_signatures(std::vector<ClassSignatures> &class_signatures, char *root_dir);



// SECTION B.a - Auxiliary Types
//------------------------------------------------------------------------------
struct CudaImages
{
  int        count;

  pix_data **pixels;
  int       *widths;
  int       *heights;
  int       *depths;
  int       *bits;
};



// SECTION B.b - Auxiliary Functions
//------------------------------------------------------------------------------
bool          get_next_batch(DirectoryListing *listing, std::vector<ImageMatrix *> &images);
bool          batch_is_full(std::vector<ImageMatrix *> &images);

bool          supported_format(const char *filename);
ImageMatrix*  load_image_matrix(const char *filename);

void          move_images_to_cuda(std::vector<ImageMatrix *> &images, CudaImages &cuda_images);
void          delete_cuda_images(CudaImages &cuda_images);

std::vector<FileSignatures> &merge_signatures(std::vector<FileSignatures> &dst, std::vector<FileSignatures> &src);
int                          find_in_vector(std::vector<std::string> &vector, std::string value);



// SECTION C - Cuda Algorithms
//------------------------------------------------------------------------------
std::vector<FileSignatures> compute_zernike_on_cuda(const std::vector<ImageMatrix *> &images, CudaImages &cuda_images);
std::vector<FileSignatures> compute_haralick_on_cuda(const std::vector<ImageMatrix *> &images, CudaImages &cuda_images);
std::vector<FileSignatures> compute_histogram_on_cuda(const std::vector<ImageMatrix *> &images, CudaImages &cuda_images);
std::vector<FileSignatures> compute_fractals_on_cuda(const std::vector<ImageMatrix *> &images, CudaImages &cuda_images);
std::vector<FileSignatures> compute_chebyshev_on_cuda(const std::vector<ImageMatrix *> &images, CudaImages &cuda_images);



#endif // CUDASIGNATURES_H
