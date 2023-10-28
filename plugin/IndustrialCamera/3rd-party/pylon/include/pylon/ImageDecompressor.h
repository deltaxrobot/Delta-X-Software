//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  MP
//-----------------------------------------------------------------------------
/**
* \file
* \brief Declaration of the CImageDecompressor class
*/
#pragma once

#ifndef INCLUDED_IMAGEDECOMPRESSOR_H_C5305647
#define INCLUDED_IMAGEDECOMPRESSOR_H_C5305647

#include <pylon/Platform.h>

#include <GenApi/INodeMap.h>
#include <pylon/PylonUtility.h>
#include <pylon/ReusableImage.h>
#include <pylon/Result.h>
#include <pylon/PixelType.h>
#include <pylon/GrabResultPtr.h>

namespace Pylon
{

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

    /*!
    \enum ECompressionStatus
    \brief Status of a grab buffer/result with compressed data.

           It is possible that images could not be compressed properly by the camera (if the amount of data required for
           compressing an image exceeds the desired compression ratio). If an image was compressed successfully, it will
           have the compression status CompressionStatus_Ok.
    */
    enum ECompressionStatus
    {
        CompressionStatus_Ok,                           //!< Buffer was compressed properly.
        CompressionStatus_BufferOverflow,               //!< Size of compressed image exceeded desired compression ratio.
        CompressionStatus_Error                         //!< Generic error.
    };

    /*!
    \enum EEndianness
    \brief Endianness for parsing the grab buffer/result as defined for the camera technology used.

           If not known, Endianness_Auto can be used to detect the endianness automatically. However, this may take longer.
    */
    enum EEndianness
    {
        Endianness_Little,                              //!< Little endian (e.g., as used in USB3 Vision).
        Endianness_Big,                                 //!< Big endian (e.g., as used in GigE Vision).
        Endianness_Auto                                 //!< Try to detect endianness automatically.
    };

    /*!
    \struct CompressionInfo_t
    \brief The struct containing information about a grab buffer/result.

           You can find more information about the usage of this struct in the description of
           the CImageDecompressor class.
    */
    struct PYLONUTILITY_API CompressionInfo_t
    {
        bool                hasCompressedImage;         ///< True if grab buffer/result provided contains a compressed image (otherwise false if buffer/result is already decompressed).
        ECompressionStatus  compressionStatus;          ///< Status of compression (see ECompressionStatus).
        bool                lossy;                      ///< True if image was compressed lossily (otherwise false if it was compressed losslessly).
        EPixelType          pixelType;                  ///< Pixel type of compressed image.
        size_t              width;                      ///< Width (in pixels) of compressed image.
        size_t              height;                     ///< Height (in pixels) of compressed image.
        size_t              offsetX;                    ///< X offset (in pixels) of compressed image.
        size_t              offsetY;                    ///< Y offset (in pixels) of compressed image.
        size_t              paddingX;                   ///< X padding (line padding; in bytes) of compressed image.
        size_t              paddingY;                   ///< Y padding (image padding; in bytes) of compressed image.
        size_t              decompressedImageSize;      ///< Size (in bytes) required for decompressed image (only valid if hasCompressedImage is true).
        size_t              decompressedPayloadSize;    ///< Size (in bytes; including chunk data) required for decompressed payload (only valid if hasCompressedImage is true).

        /*!
        \brief Creates and initializes a compression info struct.
        \error
        Does not throw C++ exceptions.
        */
        CompressionInfo_t();
    };

    /*!
    \enum ECompressionMode
    \brief Mode used for transferring images.

           The compression mode can have three states. Either compression is disabled in the camera (CompressionMode_Off)
           or the camera compresses the images in one of two ways (CompressionMode_BaslerLossless or CompressionMode_BaslerFixRatio).
    */
    enum ECompressionMode
    {
        CompressionMode_Off,                        //!< Images are transferred uncompressed.
        CompressionMode_BaslerLossless,             //!< Images are transferred with Basler lossless compression.
        CompressionMode_BaslerFixRatio              //!< Images are transferred with Basler fixed ratio compression (which may lead to lossily compressed images).
    };

    /*!
    \class CImageDecompressor
    \brief Provides convenient access to cameras that support image compression and helps with decompressing these images.

           A decompressor requires a compression descriptor in order to be able to decompress images. You can set
           a compression descriptor via the constructor or the SetCompressionDescriptor methods (in both cases,
           either using the node map or manually).

           A compression descriptor can be identified via a hash. This hash can be used to identify the matching
           compression descriptor for a particular compressed image. It can be computed using the
           ComputeCompressionDescriptorHash method or retrieved from the camera, decompressor, or a grab buffer/result
           using one of the GetCompressionDescriptorHash methods.

           Grab buffers/results may contain different kinds of data. You can use the
           decompressor's GetCompressionInfo methods to distinguish between them. For that to work, a
           grab buffer/result must have been received successfully and it must contain the
           payload type chunk (for grab results you can get the payload type using the
           GetPayloadType method).

           If compression info for the grab buffer/result provided is available,
           GetCompressionInfo returns true and you will receive the compression info
           via the CompressionInfo_t struct.
           If the field hasCompressedImage in the struct is true, the grab buffer/result
           contains a compressed image. In this case, you should check the compressionStatus
           field in the struct to check whether the camera was able to compress
           the image properly. The camera can't compress an image if the amount of
           data required for compressing the image exceeds the desired compression ratio.
           The image can be decompressed if compressionStatus is CompressionStatus_Ok.
           If the field hasCompressedImage in the struct is false, the grab buffer/result
           contains an already decompressed image. In this case, the decompressedImageSize
           and decompressedPayloadSize fields will not be used. All other fields contain
           information about the decompressed data.
    */
    class PYLONUTILITY_API CImageDecompressor
    {
    public:
        /*!
        \brief Creates an empty decompressor without compression descriptor.

               This constructor does not initialize the decompressor with a compression descriptor. You will have to
               initialize the decompressor first by using one of the SetCompressionDescriptor methods in order to be
               able to decompress images. You will get an exception if you access methods that require the decompressor
               to be initialized (see method descriptions for which methods are affected by that precondition).
        \error
        Throws an exception if no memory can be allocated.
        */
        CImageDecompressor();

        /*!
        \brief Creates a decompressor by copying from another decompressor.
        \param[in] imageDecompressor Decompressor to copy from during initialization.
        \error
        Throws an exception if no memory can be allocated.
        */
        explicit CImageDecompressor( const CImageDecompressor& imageDecompressor );

        /*!
        \brief Creates a decompressor and initializes it with the compression descriptor provided.
        \param[in] pCompressionDescriptor Pointer to the compression descriptor. This parameter must not be NULL.
        \param[in] sizeCompressionDescriptor Size of the data (in bytes) of the compression descriptor.
        \error
        Throws an exception if no memory can be allocated or the compression descriptor provided is invalid (e.g., because it is corrupt)
        or incompatible (e.g., because a compression descriptor of a newer compression implementation is passed).
        */
        CImageDecompressor( const void* pCompressionDescriptor, size_t sizeCompressionDescriptor );

        /*!
        \brief Creates a decompressor and initializes it with a compression descriptor that is retrieved from the camera's node map.
        \param[in] nodeMap Node map of the camera to be used for retrieving the compression descriptor.
        \error
        Throws an exception if no memory can be allocated or no proper compression descriptor can be retrieved from the camera.
        */
        explicit CImageDecompressor( GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Destroys the decompressor instance.
        \error
        Does not throw C++ exceptions.
        \threading
        This method is thread-safe.
        */
        ~CImageDecompressor();

        /*!
        \brief Determines whether the decompressor already has a compression descriptor.
        \return Returns true if the decompressor is already initialized with a compression descriptor or false otherwise.
        \error
        Does not throw C++ exceptions.
        \threading
        This method is thread-safe.
        */
        bool HasCompressionDescriptor() const;

        /*!
        \brief Resets the compression descriptor in the decompressor.
        \note After calling this method, no images can be decompressed by the decompressor because it is
              back in uninitialized state.
        \error
        Does not throw C++ exceptions.
        \threading
        This method is thread-safe.
        */
        void ResetCompressionDescriptor();

        /*!
        \brief Initializes a decompressor with the compression descriptor provided.
        \param[in] pCompressionDescriptor Pointer to the compression descriptor. This parameter must not be NULL.
        \param[in] sizeCompressionDescriptor Size of the data (in bytes) of the compression descriptor.
        \error
        Throws an exception if no memory can be allocated or the compression descriptor provided is invalid (e.g., because it is corrupt)
        or incompatible (e.g., because a compression descriptor of a newer compression implementation is passed).
        \threading
        This method is thread-safe.
        */
        void SetCompressionDescriptor( const void* pCompressionDescriptor, size_t sizeCompressionDescriptor );

        /*!
        \brief Initializes a decompressor with a compression descriptor that is retrieved from the camera's node map.
        \param[in] nodeMap Node map of the camera to be used for retrieving the compression descriptor.
        \error
        Throws an exception if no memory can be allocated or no proper compression descriptor can be retrieved from the camera.
        \threading
        This method is thread-safe.
        */
        void SetCompressionDescriptor( GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Retrieves the current compression mode from the camera's node map.

               This indicates which kind of compression is active or whether compression is not enabled (or unavailable).
        \param[in] nodeMap Node map of the camera to be used for retrieving the compression mode.
        \return Returns the current compression mode of the camera.
        \error
        Throws an exception if an error is encountered while determining the compression mode.
        \threading
        This method is thread-safe.
        */
        static ECompressionMode GetCompressionMode( GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Gets the currently set compression descriptor.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.
        \param[out] pCompressionDescriptor Pointer to the buffer that will receive the compression descriptor or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeCompressionDescriptor On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor (if pCompressionDescriptor is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor.
                       This parameter must not be NULL.
        \error
        Throws an exception if the decompressor has no compression descriptor set or the input parameters are
        invalid (e.g., if the size provided is not sufficient to hold the compression descriptor).
        \threading
        This method is thread-safe.
        */
        void GetCompressionDescriptor( void* pCompressionDescriptor, size_t* pSizeCompressionDescriptor ) const;

        /*!
        \brief Gets the current compression descriptor from the camera's node map.

               This method requires image compression to be enabled in the camera. You can determine this via the
               GetCompressionMode method.
        \param[out] pCompressionDescriptor Pointer to the buffer that will receive the compression descriptor or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeCompressionDescriptor On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor (if pCompressionDescriptor is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor.
                       This parameter must not be NULL.
        \param[in] nodeMap Node map of the camera to be used for retrieving the compression descriptor.
        \error
        Throws an exception if compression is not enabled in the camera (or unavailable) or the input parameters are
        invalid (e.g., if the size provided is not sufficient to hold the compression descriptor).
        \threading
        This method is thread-safe.
        */
        static void GetCompressionDescriptor( void* pCompressionDescriptor, size_t* pSizeCompressionDescriptor, GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Gets compression information about a grab buffer.
        \param[out] compressionInfo Reference to the struct that will receive the compression information if the grab buffer contains such information.
        \param[in] pGrabBuffer Pointer to the grab buffer that holds the compressed data. This parameter must not be NULL.
        \param[in] payloadSize Payload size (in bytes) of the data received (must be less or equal to the size of the grab buffer).
        \param[in] endianness Endianness of the grab buffer's content. If not known, auto detection can be used.
        \return Returns true if compression information could be extracted from the the grab buffer or false otherwise.
        \error
        Throws an exception if the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        static bool GetCompressionInfo( CompressionInfo_t& compressionInfo, const void* pGrabBuffer, size_t payloadSize, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Gets compression information about a grab result.
        \param[out] compressionInfo Reference to the struct that will receive the compression information if the grab result contains such information.
        \param[in] grabResult Grab result that holds the compressed data.
        \param[in] endianness Endianness of the grab result content. If not known, auto detection can be used.
        \return Returns true if compression information could be extracted from the the grab result or false otherwise.
        \error
        Throws an exception if the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        static bool GetCompressionInfo( CompressionInfo_t& compressionInfo, const Pylon::GrabResult& grabResult, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Gets compression information about a grab result.
        \param[out] compressionInfo Reference to the struct that will receive the compression information if the grab result contains such information.
        \param[in] grabResultPtr Pointer to grab result that holds the compressed data.
        \param[in] endianness Endianness of the grab result content. If not known, auto detection can be used.
        \return Returns true if compression information could be extracted from the the grab result or false otherwise.
        \error
        Throws an exception if the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        static bool GetCompressionInfo( CompressionInfo_t& compressionInfo, const Pylon::CGrabResultPtr grabResultPtr, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Computes the hash for a given compression descriptor.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \param[in] pCompressionDescriptor Pointer to the compression descriptor. This parameter must not be NULL.
        \param[in] sizeCompressionDescriptor Size of the data (in bytes) of the compression descriptor.
        \error
        Throws an exception if the input parameters are invalid (e.g., if the size provided is not sufficient to hold
        the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        static void ComputeCompressionDescriptorHash( void* pHash, size_t* pSizeHash, const void* pCompressionDescriptor, size_t sizeCompressionDescriptor );

        /*!
        \brief Gets the hash of the currently set compression descriptor.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \error
        Throws an exception if the decompressor has no compression descriptor set or the input parameters are
        invalid (e.g., if the size provided is not sufficient to hold the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        void GetCompressionDescriptorHash( void* pHash, size_t* pSizeHash ) const;

        /*!
        \brief Gets the hash of the current compression descriptor from the camera's node map.

               This method requires image compression to be enabled in the camera. You can determine this via the
               GetCompressionMode method.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \param[in] nodeMap Node map of the camera to be used for retrieving the compression descriptor hash.
        \error
        Throws an exception if compression is not active in the camera (or unavailable) or the input parameters
        are invalid (e.g., if the size provided is not sufficient to hold the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        static void GetCompressionDescriptorHash( void* pHash, size_t* pSizeHash, GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Gets the hash of the compression descriptor that is required for decompressing the grab buffer provided.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \param[in] pGrabBuffer Pointer to the grab buffer that holds the compressed data. This parameter must not be NULL.
        \param[in] payloadSize Payload size (in bytes) of the data received (must be less or equal to the size of the grab buffer).
        \param[in] endianness Endianness of the grab buffer's content. If not known, auto detection can be used.
        \error
        Throws an exception if the grab buffer does not contain compressed data, the data is corrupt, or the input
        parameters are invalid (e.g., if the size provided is not sufficient to hold the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        static void GetCompressionDescriptorHash( void* pHash, size_t* pSizeHash, const void* pGrabBuffer, size_t payloadSize, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Gets the hash of the compression descriptor that is required for decompressing the grab result provided.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \param[in] grabResult Grab result that holds the compressed data.
        \param[in] endianness Endianness of the grab result content. If not known, auto detection can be used.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, or the input
        parameters are invalid (e.g., if the size provided is not sufficient to hold the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        static void GetCompressionDescriptorHash( void* pHash, size_t* pSizeHash, const Pylon::GrabResult& grabResult, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Gets the hash of the compression descriptor that is required for decompressing the grab result provided.
        \param[out] pHash Pointer to the buffer that will receive the compression descriptor hash or
                    NULL if you only want to get the size of the buffer for buffer allocation.
        \param[in,out] pSizeHash On input, the variable specifies the size of the buffer (in bytes)
                       for the compression descriptor hash (if pHash is not NULL).
                       On output, the variable will receive the actual buffer size required for the current
                       compression descriptor hash.
                       This parameter must not be NULL.
        \param[in] grabResultPtr Pointer to grab result that holds the compressed data.
        \param[in] endianness Endianness of the grab result content. If not known, auto detection can be used.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, or the input
        parameters are invalid (e.g., if the size provided is not sufficient to hold the compression descriptor hash).
        \threading
        This method is thread-safe.
        */
        static void GetCompressionDescriptorHash( void* pHash, size_t* pSizeHash, const Pylon::CGrabResultPtr grabResultPtr, EEndianness endianness = Endianness_Auto );

        /*!
        \brief Gets size (in bytes) required for allocating buffers for decompressing the images during streaming.

               This method requires image compression to be enabled in the camera. You can determine this via the
               GetCompressionMode method.
        \param[in] nodeMap Node map of the camera to be used for retrieving the image size required for decompression.
        \return Returns the buffer size (in bytes) required for image decompression.
        \error
        Throws an exception if an error is encountered while determining the image size required for decompression.
        \threading
        This method is thread-safe.
        */
        static size_t GetImageSizeForDecompression( GENAPI_NAMESPACE::INodeMap& nodeMap );

        /*!
        \brief Decompresses the image of the grab buffer provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab buffer provided must contain a compressed image that has been received without errors.
        \param[out] pOutputBuffer Pointer to the buffer that will receive the decompressed image. This parameter must
                    not be NULL.
        \param[in,out] pSizeOutputBuffer On input, the variable specifies the size of the buffer (in bytes)
                       for the decompressed image (must be larger or equal to the value in the decompressedImageSize
                       field in the CompressionInfo_t struct received via the GetCompressionInfo methods;
                       alternatively, the GetImageSizeForDecompression method can be used to get the image
                       size required for decompression).
                       On output, the variable will receive the actual buffer size required for the decompressed image.
                       This parameter must not be NULL.
        \param[in] pGrabBuffer Pointer to the grab buffer that holds the compressed data. This parameter must not be NULL.
        \param[in] payloadSize Payload size (in bytes) of the data received (must be less or equal to the size of the grab buffer).
        \return Returns the struct with the compression information of the compressed image.
        \error
        Throws an exception if the grab buffer does not contain compressed data, the data is corrupt, the image cannot
        be decompressed, or the input parameters are invalid (e.g., if the size provided is not sufficient to hold the
        decompressed image).
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( void* pOutputBuffer, size_t* pSizeOutputBuffer, const void* pGrabBuffer, size_t payloadSize ) const;

        /*!
        \brief Decompresses the image of the grab result provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab result provided must contain a compressed image that has been received without errors.
        \param[out] pOutputBuffer Pointer to the buffer that will receive the decompressed image. This parameter must
                    not be NULL.
        \param[in,out] pSizeOutputBuffer On input, the variable specifies the size of the buffer (in bytes)
                       for the decompressed image (must be larger or equal to the value in the decompressedImageSize
                       field in the CompressionInfo_t struct received via the GetCompressionInfo
                       methods; alternatively, the GetImageSizeForDecompression method can be used to get the image
                       size required for decompression).
                       On output, the variable will receive the actual buffer size required for the decompressed image.
                       This parameter must not be NULL.
        \param[in] grabResult Grab result that holds the compressed data.
        \return Returns the struct with the compression information about the compressed image.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, the image cannot
        be decompressed or the input parameters are invalid (e.g., if the size provided is not sufficient to hold the
        decompressed image).
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( void* pOutputBuffer, size_t* pSizeOutputBuffer, const Pylon::GrabResult& grabResult ) const;

        /*!
        \brief Decompresses the image of the grab result provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab result provided must contain a compressed image that has been received without errors.
        \param[out] pOutputBuffer Pointer to the buffer that will receive the decompressed image. This parameter must
                    not be NULL.
        \param[in,out] pSizeOutputBuffer On input, the variable specifies the size of the buffer (in bytes)
                       for the decompressed image (must be larger or equal to the value in the decompressedImageSize
                       field in the CompressionInfo_t struct received via the GetCompressionInfo methods;
                       alternatively, the GetImageSizeForDecompression method can be used to get the image
                       size required for decompression).
                       On output, the variable will receive the actual buffer size required for the decompressed image.
                       This parameter must not be NULL.
        \param[in] grabResultPtr Pointer to grab result that holds the compressed data.
        \return Returns the struct with the compression information about the compressed image.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, the image cannot
        be decompressed or the input parameters are invalid (e.g., if the size provided is not sufficient to hold the
        decompressed image).
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( void* pOutputBuffer, size_t* pSizeOutputBuffer, const Pylon::CGrabResultPtr grabResultPtr ) const;

        /*!
        \brief Decompresses the image of the grab buffer provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab buffer provided must contain a compressed image that has been received without errors.
        \param[out] destinationImage Image object (e.g., instance of CPylonImage) that will be filled with the decompressed
                    image (will be resized if required).
        \param[in] pGrabBuffer Pointer to the grab buffer that holds the compressed data. This parameter must not be NULL.
        \param[in] payloadSize Payload size (in bytes) of the data received (must be less or equal to the size of the grab buffer).
        \return Returns the struct with the compression information about the compressed image.
        \error
        Throws an exception if the grab buffer does not contain compressed data, the data is corrupt, the image cannot
        be decompressed or the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( IReusableImage& destinationImage, const void* pGrabBuffer, size_t payloadSize ) const;

        /*!
        \brief Decompresses the image of the grab result provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab result provided must contain a compressed image that has been received without errors.
        \param[out] destinationImage Image object (e.g., instance of CPylonImage) that will be filled with the decompressed
                    image (will be resized if required).
        \param[in] grabResult Grab result that holds the compressed data.
        \return Returns the struct with the compression information about the compressed image.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, the image cannot be
        decompressed, or the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( IReusableImage& destinationImage, const Pylon::GrabResult& grabResult ) const;

        /*!
        \brief Decompresses the image of the grab result provided.

               This method requires that a compression descriptor has been set previously via the constructor or
               the SetCompressionDescriptor methods. You can determine this via the HasCompressionDescriptor method.

               The grab result provided must contain a compressed image that has been received without errors.
        \param[out] destinationImage Image object (e.g., instance of CPylonImage) that will be filled with the decompressed
                    image (will be resized if required).
        \param[in] grabResultPtr Pointer to grab result that holds the compressed data.
        \return Returns the struct with the compression information about the compressed image.
        \error
        Throws an exception if the grab result does not contain compressed data, the data is corrupt, the image cannot be
        decompressed, or the input parameters are invalid.
        \threading
        This method is thread-safe.
        */
        CompressionInfo_t DecompressImage( IReusableImage& destinationImage, const Pylon::CGrabResultPtr grabResultPtr ) const;

        /*!
        \brief Copies the decompressor.
        \param[in] imageDecompressor The source decompressor.
        \return Returns a reference to the destination decompressor.
        \error
        Does not throw C++ exceptions.
        \threading
        This method is thread-safe.
        */
        CImageDecompressor& operator = ( const CImageDecompressor& imageDecompressor );

        /*!
        \brief Compares this instance with another decompressor.
        \param[in] imageDecompressor The decompressor on the right-hand side of the comparison.
        \return True if both decompressors are equal or false otherwise.
        \error
        Does not throw C++ exceptions.
        \threading
        This method is thread-safe.
        */
        bool operator == ( const CImageDecompressor& imageDecompressor );

    private:
        struct Impl_t;

        Impl_t* m_pImpl;
    };

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

} //namespace Pylon

#endif // INCLUDED_IMAGEDECOMPRESSOR_H_C5305647
