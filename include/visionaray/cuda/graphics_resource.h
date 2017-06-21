// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#ifndef VSNRAY_CUDA_GRAPHICS_RESOURCE_H
#define VSNRAY_CUDA_GRAPHICS_RESOURCE_H 1

#include <cuda_runtime_api.h>

#include <visionaray/detail/macros.h>
#include <visionaray/export.h>

namespace visionaray
{
namespace cuda
{

class graphics_resource
{
public:

    VSNRAY_EXPORT graphics_resource();
    VSNRAY_EXPORT ~graphics_resource();

    VSNRAY_EXPORT cudaGraphicsResource_t get() const;

    VSNRAY_EXPORT cudaError_t register_buffer(unsigned buffer, cudaGraphicsRegisterFlags flags = cudaGraphicsRegisterFlagsNone);
    VSNRAY_EXPORT cudaError_t register_image(unsigned image, unsigned target, cudaGraphicsRegisterFlags flags = cudaGraphicsRegisterFlagsNone);
    VSNRAY_EXPORT cudaError_t unregister();

    VSNRAY_EXPORT void* map(size_t* size);
    VSNRAY_EXPORT void* map();
    VSNRAY_EXPORT void unmap();

    VSNRAY_EXPORT void* dev_ptr() const;

private:

    VSNRAY_NOT_COPYABLE(graphics_resource)

    cudaGraphicsResource_t resource_;
    void* dev_ptr_;

};

} // cuda
} // visionaray

#endif // VSNRAY_CUDA_GRAPHICS_RESOURCE_H
