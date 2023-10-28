//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief  Function and classes for initializing the pylon runtime.
*/
#pragma once

#ifndef PYLONBASE_H__
#define PYLONBASE_H__

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>

#ifdef PYLONBASE_EXPORTS
#  define PYLONBASE_API APIEXPORT
#else
#  define PYLONBASE_API APIIMPORT
#endif

#if defined(PYLON_BASE_3_0_NO_DEPRECATE)
#   define PYLON_BASE_3_0_DEPRECATED(message)
#else
#   define PYLON_BASE_3_0_DEPRECATED(message) PYLON_DEPRECATED(message)
#endif

namespace Pylon
{
/**
  \brief Initializes the pylon runtime system.

  You must call PylonInitialize before calling any other pylon functions.
  When finished you must call PylonTerminate to free up all resources used by pylon.

  You can use the helperclass PylonAutoInitTerm to let the compiler call
  PylonInitialze and PylonTerminate.

  Just create a local object on the stack in your main function and
  the constructor and destructor will call the functions.
  See PylonAutoInitTerm for a sample.

  PylonInitialize/PylonTerminate is reference counted. For every call of PylonInitialize, a call to PylonTerminate is required.
  The last call to PylonTerminate will free up all resources.

  \if windows
  For MFC applications we recommend to call PylonInitialize and PylonTerminate in the
  application's InitInstance() and ExitInstance() methods.
  This prevents the MFC runtime from reporting a huge number of pretended memory leaks.
  This does not apply to DLLs using MFC (see below)!

  \note
  Due to the limitations of functions allowed during DLLMain, it is not allowed to call PylonIntialize from DLLMain.
  For further information see the official documentation of DLLMain in the Windows documentation.
  \endif

  */
    PYLONBASE_API void CDECL PylonInitialize( void );

    /**
        \brief Frees up resources allocated by the pylon runtime system.

        Call this function before terminating the application. Don't use any pylon methods or pylon objects after
        having called PylonTerminate().

        PylonInitialize/PylonTerminate is reference counted. For every call of PylonInitialize, a call to PylonTerminate is required.
        The last call to PylonTerminate will free up all resources.

        \if windows
        \note
        Due to the limitations of functions allowed during DLLMain, it is not allowed to call PylonTerminate from DLLMain.
        For further information see the official documentation of DLLMain in the Windows documentation.
        \endif
        */
    PYLONBASE_API void CDECL PylonTerminate( bool ShutDownLogging = true );

    /**
        \brief Returns the version number of pylon

        It is possible to pass a NULL pointer for a version number category if the value is not of interest.
        */
    extern "C" PYLONBASE_API void CDECL GetPylonVersion( unsigned int* major, unsigned int* minor, unsigned int* subminor, unsigned int* build );

    /**
        \brief Returns the version number of pylon as string.
        */
    extern "C" PYLONBASE_API const char* CDECL GetPylonVersionString();


    /**
        \brief Set the value of a property.

        \param propertyId Identifies the property.
        \param pData A pointer to the buffer containing the data.
        \param size Size of the buffer in bytes.

        Call this function to set the value of a property.

        You must have called PylonInitialize() before you can call this function.
    */
    PYLONBASE_API void CDECL SetProperty( int propertyId, const void* pData, size_t size );


    /**
    \brief Get the value of a property.

    \param propertyId Identifies the property.
    \param pData A pointer to the buffer containing the data.
    \param pSize Size of the buffer in bytes when calling. Holds the resulting size on return.

    Call this function to get the value of a property.

    You must have called PylonInitialize() before you can call this function.
    */
    PYLONBASE_API void CDECL GetProperty( int propertyId, void* pData, size_t* pSize );


    /**
        \brief Helper class to automagically call PylonInitialize and PylonTerminate in constructor and destructor

        \code

        #include <pylon/TlFactory.h>

        // ...

        using namespace Pylon;

        int main(int argc, char* argv[])
        {

            PylonAutoInitTerm autoInitTerm;

            // Get the transport layer factory
            CTlFactory& TlFactory = CTlFactory::GetInstance();

            // Get all attached cameras and exit application if no camera is found
            DeviceInfoList_t devices;
            if ( 0 == TlFactory.EnumerateDevices( devices ) )
            {
                cerr << "No camera present!" << endl;
                return 1;
            }
            else
            {
                // do something with devices ...
                //...
            }


            return 0;

        }  // When leaving the main function, the destructor of the PylonAutoInitTerm object will be called
           // and it will in turn call PylonTerminate.
        \endcode
    */
    class PylonAutoInitTerm
    {
    public:
        PYLONBASE_API PylonAutoInitTerm( void )
        {
            PylonInitialize();
        }

        PYLONBASE_API ~PylonAutoInitTerm( void )
        {
            PylonTerminate();
        }
    private:
        // unimplemented new operator to prevent creation on the heap which is a bad idea.
        // This object must be created in the local stack frame (see sample above)
        void* operator new(size_t);
        void* operator new[]( size_t );
    };

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* PYLONBASE_H__ */
