//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2020-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  DV, JS
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains a class to access multi-component grab results
*/

#ifndef INCLUDED_PYLONDATACONTAINER_H
#define INCLUDED_PYLONDATACONTAINER_H

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/PixelType.h>
#include <pylon/PayloadType.h>



namespace Pylon
{
    // Forward declaration
    class CGrabResultPtr;
    class GrabResult;
    class CPylonDataComponent;

    /**
     * \class  CPylonDataContainer
     * \brief  Provides methods for accessing grab results consisting of multiple components.
     *
     * Some cameras can return complex grab results consisting of multiple components.
     * For example, Basler blaze cameras return a data stream that is composed of range, intensity,
     * and confidence components.
     * To access the individual components, you can use the \c CPylonDataContainer class.
     *
     * A \c CPylonDataContainer can hold one or more components.
     * You can obtain a container by calling \c Pylon::CGrabResultData::GetDataContainer().
     * You can then use the container to query for the number of components by calling \c Pylon::CGrabResultData::GetDataComponentCount().
     * To retrieve a specific component, you can call \c Pylon::CGrabResultData::GetDataComponent().
     * Each component in the container can be used to access the actual data, e.g., the range values, and its metadata.
     *
     * \attention Any \c CPylonDataContainer or \c CPylonDataComponent will hold a reference to the \c CGrabResultData
     *            from which it has been created. To allow the instant camera to reuse the \c CGrabResultData
     *            and prevent buffer underruns, you must destroy the \c CPylonDataContainer and all its \c CPylonDataComponent objects.
     *
     * \threading
     *      This class is not thread-safe.
     *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
    */
    class PYLONBASE_API CPylonDataContainer
    {
    public:
        /**
         * \brief Creates a \c CPylonDataContainer from a given \c CGrabResultPtr.
         * \param ptrGrabResult The grab result to create a container from.
         *
         * Creates a \c CPylonDataContainer from a given \c CGrabResultPtr.
         * The \c CPylonDataContainer instance created will hold a reference to the \c CGrabResultData from which it has been created.
         * To allow the instant camera to reuse the grab result and prevent buffer underruns,
         * you must destroy the \c CPylonDataContainer.
         *
         * \post
         *  <ul>
         *      <li> A new reference to the grab result passed in ptrGrabResult has been set.
         *  </ul>
         *
         * \error
         *      Does not throw an exception if the \c CGrabResultPtr was invalid or points to an invalid/unsuccessful result.
         *      Instead, an empty container is returned.
         *      Can throw exceptions if the data in the result is invalid or malformed.
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        explicit CPylonDataContainer( const CGrabResultPtr& ptrGrabResult );


        /**
         * \brief Creates a \c CPylonDataContainer from a given \c GrabResult.
         * \param grabResult The grab result to create a container from.
         *
         * Creates a \c CPylonDataContainer from a given \c GrabResult.
         * The \c CPylonDataContainer instance created is only valid as long as the associated buffer
         * is not queued or deregistered and deleted.
         *
         * \error
         *      Does not throw an exception if the GrabResult contains an unsuccessful result.
         *      Instead, an empty container is returned.
         *      Can throw exceptions if the data in the buffer of the GrabResult is invalid or malformed.
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        explicit CPylonDataContainer( const GrabResult& grabResult );


        /**
         * \brief Creates a \c CPylonDataContainer by loading the data from the file passed.
         *
         * \copydetails Pylon::CPylonDataContainer::Load()
         *
        */
        explicit CPylonDataContainer( const Pylon::String_t& filename );


        /**
         * \brief Creates an empty \c CPylonDataContainer.
         *
         * Creates an empty \c CPylonDataContainer.
         * The \c CPylonDataContainer instance created will not be valid.
         *
         * \error
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataContainer();


        /**
         * \brief Creates a shallow copy of an existing \c CPylonDataContainer.
         * \param rhs Container to copy from.
         *
         * \post
         *  <ul>
         *      <li> A new reference to the grab result or buffer of the container passed in rhs has been set.
         *  </ul>
         *
         * \error
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataContainer( const CPylonDataContainer& rhs );


        /**
         * \brief Destroys the \c CPylonDataContainer instance. If the instance has been created through a GrabResultPtr,
         *        the reference to that \c CGrabResultData will be released.
         *
         * \post
         *  <ul>
         *      <li> The reference to a grab result or buffer has been released.
         *  </ul>
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        ~CPylonDataContainer();


        /**
         * \brief Assigns a shallow copy of the \c CPylonDataContainer to this instance.
         * \param rhs CPylonDataContainer to copy data from.
         * \return Returns a reference to the current instance.
         *
         * \post
         *  <ul>
         *      <li> The reference to a previous grab result or buffer has been released.
         *      <li> A new reference to the grab result or buffer of the container passed in rhs has been set.
         *  </ul>
         *
         * \error
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        CPylonDataContainer& operator=( const CPylonDataContainer& rhs );


        /**
         * \brief Returns the number of components contained in the container.
         * \return Returns the number of components contained in the container.
         *
         * You can use the return value to iterate over the existing components by calling \c Pylon::CPylonDataContainer::GetDataComponent().
         *
         * \error
         *      Does not throw C++ exceptions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        size_t GetDataComponentCount() const;


        /**
         * \brief Returns a specific component from the container.
         * \param index Index of the component to return. The index must be less than the value returned by \c Pylon::CPylonDataContainer::GetComponentCount().
         * \return Returns the component specified by the index parameter.
         *
         * \error
         *      Throws an exception if the index parameter is out of range.
         *      Can throw exceptions in low-memory conditions.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        const CPylonDataComponent GetDataComponent( const size_t index ) const;


        /**
         * \brief Saves the container to disk.
         * \param filename Name and path of the file to save the container to.
         *
         * \pre
         *      The container must contain at least one component.
         *
         * \error
         *      Throws an exception if the container cannot be saved.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        void Save( const Pylon::String_t& filename ) const;

        /**
         * \brief Loads a container from a file.
         * \param filename Name and path of the file to load.
         *
         * Loads a container and all its components from a file on disk.
         *
         * \post
         *  <ul>
         *      <li> The reference to a previous grab result or buffer has been released.
         *      <li> A new buffer has been allocated to hold the data loaded.
         *  </ul>
         *
         * \error
         *      Throws an exception if the container cannot be read.
         *      Throws an exception if the contents of the file does not contain a valid container.
         *
         * \threading
         *      This class is not thread-safe.
         *      If you access the same instance from multiple threads, you must make sure to synchronize the access accordingly.
        */
        void Load( const Pylon::String_t& filename );

    private:
        class CPylonDataContainerImpl;
        CPylonDataContainerImpl* m_pImpl;
    };
}

#endif // INCLUDED_PYLONDATACONTAINER_H
