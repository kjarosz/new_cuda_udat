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

#ifndef _CUDA_UTIL_H
#define _CUDA_UTIL_H



#include <cuda.h>



template <class T>
cudaError move_host_to_cuda(T *data, unsigned int size, T* &output)
{
  cudaError status = cudaMalloc(&output, size * sizeof(T));
  if (status != cudaSuccess) {
    output = 0;
    return status;
  }

  status = cudaMemcpy(output, data, size * sizeof(T), cudaMemcpyHostToDevice);
  if (status != cudaSuccess) {
    cudaFree(output);
    output = 0;
  }
  return status;
}



template <class T>
cudaError move_cuda_to_host(T *data, unsigned int size, T* &output)
{
  T *host_data = new T[size];
  cudaError status = cudaMemcpy(host_data, data, size * sizeof(T), cudaMemcpyDeviceToHost);
  if(status != cudaSuccess) {
    delete [] host_data;
    host_data = 0;
  }
  output = host_data;
  return status;
}



template <class T>
cudaError cuda_alloc_multivar_array(unsigned int sizes[], unsigned int count, T** &output)
{
  cudaError status;
  unsigned int i;

  output = 0;

  T** rows = new T*[count];
  for(i = 0; i < count; i++) {
    status = cudaMalloc(&(rows[i]), sizeof(T) * sizes[i]);

    if (status != cudaSuccess)
      break;
  }

  if (status == cudaSuccess)
  {
    status = cudaMalloc(&output, sizeof(T*) * count);

    if( status == cudaSuccess ) {
      status = cudaMemcpy(output, rows, sizeof(T*) * count, cudaMemcpyHostToDevice);
    }
  }

  if (status != cudaSuccess) {
    for(int j = i-1; j >= 0; j--) {
      cudaFree(rows[i]);
    }
    cudaFree(output);
    output = 0;
  }

  delete [] rows;
  return status;
}



template <class T>
cudaError cuda_alloc_cube_array(unsigned int rowsize, unsigned int count, T** &output)
{
  unsigned int *sizes = new unsigned int[count];
  for(unsigned int i = 0; i < count; i++)
    sizes[i] = rowsize;

  cudaError status = cuda_alloc_multivar_array(sizes, count, output);
  delete [] sizes;

  return status;
}



template <class T>
cudaError cuda_free_multidim_arr(T **arr, unsigned int count)
{
  if (arr == 0)
    return cudaSuccess;

  T** rows = new T*[count];
  cudaMemcpy(rows, arr, sizeof(T*) * count, cudaMemcpyDeviceToHost);
  for(unsigned int i = 0; i < count; i++) {
    cudaFree(rows[i]);
  }
  delete [] rows;
  cudaFree(arr);

  return cudaSuccess;
}



#endif // _CUDA_UTIL_H
