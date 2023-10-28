//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2020-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  DV, JS
//-----------------------------------------------------------------------------
/**
\file
\brief Contains a class to access one component of a multi-component grab result.
*/

#ifndef INCLUDED_PYLONDATACOMPONENT_H
#define INCLUDED_PYLONDATACOMPONENT_H

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/PixelType.h>
#include <pylon/PayloadType.h>
#include <pylon/Image.h>


namespace Pylon
{
    // Forward declaration
    class CGrabResultPtr;
    class GrabResult;

    /**
     * \brief Lists the possible component types.
     *
     * Use this value to determine what kind of data is stored in a component.
     * You can call Pylon::CPylonDataComponent::GetComponentType().
    */
    enum EComponentType
    {
        ComponentType_Undefined = 0x00,     //!< The component type is not known or hasn't been set.
        ComponentType_Intensity = 0x01,     //!< Component contains intensity values
        ComponentType_Range = 0x04,         //!< Component contains range values
        ComponentType_Confidence = 0x06     //!< Component contains confidence value
    };


    /**
     * \class  CPylonDataComponent
     * \brief  Provides methods for accessing a single component of CPylonDataContainer.
     *
     * \copydetails Pylon::CPylonDataContainer
    */
    class PYLONBASE_API CPylonDataComponent
    {
    public:
        /*!
         * \brief Creates an empty component.
         *
         * The default constructor will create an empty component.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataComponent();

        /*!
         * \brief Creates a copy of an existing component.
         *
         * \param rhs Source component to copy.
         *
         * When creating a copy of a component, only the reference to the data in the container is copied.
         * The actual data pointed to by Pylon::CPylonDataComponent::GetData() will not be copied.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataComponent( const CPylonDataComponent& rhs );

        /*!
         * \brief Destroys a pylon data component object. 
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        ~CPylonDataComponent( );

        /*!
         * \brief Assigns the data of another component to this component by copying.
         *
         * \param rhs Source component to copy.
         *
         * When assigning a copy of a component, only the metadata is copied.
         * The actual data pointed to by Pylon::CPylonDataComponent::GetData() will not be copied.
         *
         * \post
         * <ul>
         * <li>Any container previously referenced is released.
         * <li>The container of the component passed is referenced.
         * <li>No container is referenced if the component passed is invalid.
         * </ul>
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataComponent& operator=( const CPylonDataComponent& rhs );

        /**
         * \brief Provides a Pylon::IImage interface to the component.
         *
         * This cast operator allows passing the component to image format converters,
         * save functions, or any other functions that require an IImage object.
         * The returned image is invalid if the component is invalid or cannot be converted to an image.
         *
         * \attention The returned reference is only valid as long as the component is not destroyed.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        operator const Pylon::IImage& () const;

        /**
         * \brief Can be used to check whether the component is valid.
         *
         * \return Returns false if the component does not contain valid data or hasn't been initialized yet.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        bool IsValid() const;


        /**
         * \brief Get the type of data this component contains.
         *
         * \return Returns the type of data in this component. See \c Pylon::EComponentType for values.
         *
         * Use this function to distinguish between different component types like
         * intensity values or range values. See Pylon::EComponentType for values.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        EComponentType GetComponentType() const;


        /**
         * \brief Get the type of pixels this component contains.
         *
         * \return Returns an enumeration value describing the pixels in the component. See \c Pylon::EPixelType for values.
         *         If the component does not contain valid data or contains a unknown pixel format, \c PixelType_Unknown is returned.
         *
         * Use this function to determine how to interpret the data returned by \c Pylon::CPylonDataComponent::GetData().
         * \note Not all components contain pixel data. Only components of type
         *       ComponentType_Intensity, ComponentType_Range, and ComponentType_Confidence return a valid pixel type.
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        EPixelType GetPixelType() const;


        /**
         * \brief Get the current number of columns.
         *
         * \return Returns the current number of columns or 0 if the component is invalid.
         *
         * \error
         *     Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        uint32_t GetWidth() const;


        /**
         * \brief Get the current number of rows.
         *
         * \return Returns the current number of rows or 0 if the component is invalid.
         *
         * \error
         *     Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        uint32_t GetHeight() const;


        /**
         * \brief Get the starting column.
         *
         * \return Returns the starting column.
         *
         * \error
         *     Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        uint32_t GetOffsetX() const;


        /**
         * \brief Get the starting row.
         *
         * \return Returns the starting row.
         *
         * \error
         *     Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        uint32_t GetOffsetY() const;


        /**
         * \brief Get the number of extra bytes at the end of each row.
         *
         * \return Returns the number of extra bytes at the end of each row.
         *
         * \error
         *     Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        size_t GetPaddingX() const;


        /**
         * \brief Get the pointer to the data contained in the component.
         *
         * \return Returns a pointer to the data contained in the component.
         *
         * Use this pointer to access the data in this component.
         * The size in bytes of the buffer can be obtained by calling Pylon::CPylonDataComponent::GetDataSize().
         * Call Pylon::CPylonDataComponent::GetPixelFormat() and other methods to determine how to interpret the data.
         *
         * \error
         *    Does not throw C++ exceptions.
        */
        const void* GetData() const;


        /**
         * \brief Get the size of the buffer returned by Pylon::CPylonDataComponent::GetData().
         *
         * \return Returns the size in bytes of the buffer returned by Pylon::CPylonDataComponent::GetData().
         *
         * \error
         *    Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        size_t GetDataSize() const;


        /**
         * \brief Get the camera-specific time the data was created on the camera.
         *
         * \return Returns the camera-specific time the data was created on the camera
         *         or 0 if the time is not available.
         *
         * \note Timestamp generation is available only on some camera models.
         *
         * \error
         *    Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        uint64_t GetTimeStamp() const;


        /**
         * \brief Get the stride in bytes for the component.
         *
         * \param[out] strideBytes On successful return, the stride value can be read from this output parameter.
         *
         * \return Returns true if the stride could be computed successfully and is returned in the output parameter.
         *         Returns false if the preconditions are not met or the component doesn't contain valid data.
         *         If the function returns false, the value of strideBytes is undefined.
         *
         * This method uses \c Pylon::ComputeStride() to compute the component's stride value.
         * The stride describes the amount of bytes to advance from one row to the next.
         *
         * \pre
         *  <ul>
         *      <li> The component type must be Pylon::ComponentType_Intensity, Pylon::ComponentType_Range, or Pylon::ComponentType_Confidence.
         *      <li> The preconditions of \c ComputeStride() must be met.
         *  </ul>
         *
         * \error
         *    Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        bool GetStride( size_t& strideBytes ) const;

    protected:
        class CPylonDataComponentImpl;
        CPylonDataComponentImpl* m_pImpl;
    };

} // namespace Pylon

#endif // INCLUDED_PYLONDATACOMPONENT_H
