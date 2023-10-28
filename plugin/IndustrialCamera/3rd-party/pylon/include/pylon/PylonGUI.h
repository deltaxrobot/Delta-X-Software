//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  NN
//-----------------------------------------------------------------------------
/*!
\file
\brief Implements a simple window to show a pylon Image.

To use the pylon GUI classes and functions you should not include this file directly.
Instead, you should include \c pylon/PylonGUIIncludes.h.
*/

#ifndef PYLON_GUI_H_INCLUDED__
#define PYLON_GUI_H_INCLUDED__

#include <pylon/stdinclude.h>

#pragma pack(push, PYLON_PACKING)

#include <pylon/PylonLinkage.h>

#ifdef PYLONGUI_EXPORTS
#   define PYLONGUI_API APIEXPORT
#else
#   define PYLONGUI_API APIIMPORT

#   ifndef PYLON_NO_AUTO_IMPLIB
#       pragma comment(lib, PYLON_LIB_NAME( "PylonGUI" ))
#   endif
#endif


#if defined(__cplusplus)

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    // forwards
    interface IImage;

    ///////////////////////////////////////////////////////////////////////
    // convenience function to show an image in one row

    /*!
    \brief  Convenience function to display an image on screen with one function call.

    \param[in]  winIndex    The window used for displaying the image. Valid window indexes range from 0 to 31.
    \param[in]  image       The image to display in the window, specified in winIndex.
                            You can also pass a CGrabResultPtr.

    This convenience function displays the image or grab result passed in the \a image parameter in a window on the screen.
    Using this function is the easiest way to display an image on the screen.

    You can pass any IImage based object or a GrabResultPtr. If the window hasn't been created before, it will be created with default positions and the image will be shown.
    When the function returns, you can free/delete the image.
    If you need more control over the window creation (e.g. to specify the position or size of the window), you can use the CPylonImageWindow class.

    When you pass an empty/invalid (e.g. image.IsValid() returns false) image, the window will be cleared.

    \code
    // This smart pointer will receive the grab result data.
    CGrabResultPtr ptrGrabResult;
    // Open the first device.
    CInstantCamera Camera( CTlFactory::GetInstance().CreateFirstDevice());
    // Grab one image.
    Camera.GrabOne( 1000, ptrGrabResult);
    // Display the image on the screen. If the grab result is invalid, the image window will be empty.
    Pylon::DisplayImage(1, ptrGrabResult);
    \endcode

    \post
    <ul>
    <li>The window specified by \a winIndex will be created and shown on the screen.
    <li>If the passed image is valid, it is shown in the window specified by \a winIndex.
    <li>If the passed image is invalid, the window specified by \a winIndex will be cleared.
    </ul>

    \remark
    To use this function, you must explicitly include \c pylon/PylonGUIIncludes.h in your code.
    Unlike other pylon headers, the GUI headers will not be included automatically when you include \c pylon/PylonIncludes.h.

    \error
        Can throw an exception if the passed winIndex is invalid or the window could not be created.

    \threading
        This function is thread-safe.
    */
    PYLONGUI_API void DisplayImage( size_t winIndex, const Pylon::IImage& image );



    /*!
    \class  CPylonImageWindow
    \brief  Class to manage a pylon image window.

    Use this class to manage a pylon image window.

    To diplay an image, you need to create and show it first. You can the call SetImage() to let the window display any %Pylon image. The following snippet shows how to do this:

    \code
    CPylonImageWindow win;
    // Create the window with winIndex = 1 using default position and size.
    // The window will not be visible until Show() has been called.
    win.Create(1);
    // Set the contents of the window.
    win.SetImage(myImage);
    // Make the window visible on the screen.
    win.Show();
    \endcode

    If the user closes the window, it will only be hidden and not truly closed. You can call Show() to make it visible again.
    The window will be closed (destroyed) when you call Close().
    The destructor automatically closes (i.e destroys) the window. To prevent this, you can call Detach() before the object is destroyed.
    All windows will be closed when PylonTerminate() is called.

    \remark The easiest way to display an image on screen is to use the DisplayImage() global function.

    \remark
    To use this class, you must explicitly include \c pylon/PylonGUIIncludes.h in your code.
    Unlike other pylon headers, the GUI headers will not be included automatically when you include \c pylon/PylonIncludes.h.

    */
    class PYLONGUI_API CPylonImageWindow
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Creates an empty CPylonImageWindow object. To actuall create the window, you must call Create()

        \error
            Does not throw C++ exceptions.
        */
        CPylonImageWindow( void );

        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Destroys a CPylonImageWindow object. If the window hasn't been closed, it will be closed.

        \error
            Does not throw C++ exceptions.

        \threading
            This function is thread-safe.
        */
        ~CPylonImageWindow( void );


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Returns the window handle (HWND) for the image window.

        Returns the native window handle of the image window.
        The handle will become invalid after Close() has been called.

        \return Returns the native window handle (HWND) for the image window.

        \error
            Throws an exception if the window hasn't been created yet or the window has been already closed.

        \threading
            This function is thread-safe.
        */
        HWND GetWindowHandle() const;


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Returns the window index handled by this object.

        The index will become valid if you call Create() or Attach().
        The index will become invalid when you call Close() or Detach().
        Valid window indexes range from 0 to 31.

        \return Returns the window index stored in this object.

        \error
            Does not throw C++ exceptions.

        \threading
            This function is thread-safe.

        \sa IsValid()
        */
        size_t GetWindowIndex( void ) const
        {
            return m_winIndex;
        }


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Returns true if the object holds a valid window index.

        Returns true if the object holds a valid window index

        \return Returns \a true if the objects holds a valid window index. Otherwise, \a false is returned.

        \error
            Does not throw C++ exceptions.

        \threading
            This function is thread-safe.
        */
        bool IsValid( void ) const;


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Attaches the window index passed in \a winIndex to this object.

        \param[in]  winIndex    The new window index to attach to this object. Valid window indexes range from 0 to 31.

        \error
            Throws an exception if the object already holds a valid window index. If you want to reuse an existing object, you should call Detach() or Close() to clear the object.

        \threading
            This function is thread-safe.
        */
        void Attach( size_t winIndex );


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Detaches the window index from this object and returns the window index previously stored in the object.

        Detaches the window index from this object and returns the window index previously stored in the object.
        After this function returns the state of the object will be invalid.

        You can call this function to prevent the window being closed when the CPylonImageWindow is destroyed.
        If you don't close a CPylonImageWindow, it will be closed automatically when PylonTerminate() is called.

        \return Returns the current window index. If no window index is stored, invalidWinIndex will be returned.

        \error
            Does not throw C++ exceptions.

        \threading
            This function is thread-safe.
        */
        size_t Detach( void );


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Creates a window for index passed in \a winIndex.

        Creates a window for the index passed in \a winIndex. If there is already an existing window with \a winIndex, an exception will be thrown.

        When you pass the \a CPylonImageWindow::useDefault for the \a x parameter, the window will be shown at the same position and with the same size as the previous one before it was closed.
        Otherwise, the position and size parameters are passed directly to the CreateWindow() function of the Windows API.

        When the function returns successfully, the window has been created but is not visible. You must call Show() to make the window visible.

        \param[in]  winIndex    The window used for displaying the image. Valid window indexes range from 0 to 31.
        \param[in]  x           The x-coordinate of the upper-left corner of the window in screen coordinates.
                                You can pass the CPylonImageWindow::useDefault value to create the window at the same position as the previous one before it was closed. The other position parameters will be ignored.
                                If the window is shown the very first time the system select a default position and size for the window.
        \param[in]  y           The y-coordinate of the upper-left corner of the window in screen-coordinates.
        \param[in]  nWidth      The width of the window in screen coordinates.
        \param[in]  nHeight     The height of the window in screen coordinates.

        \error
            <ul>
            <li>Will throw an exception if an invalid \a winIndex is passed.
            <li>Will throw an exception if the a window with the specified window index already exists.
            </ul>

        \threading
            This function is thread-safe.
        */
        void Create( size_t winIndex, int x = useDefault, int y = useDefault, int nWidth = useDefault, int nHeight = useDefault );


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Shows or hides the image window.

        This function calls ShowWindow from the Windows API.
        You can pass the same values for the \a nShow parameter as described in the official documentation for ShowWindow()
        The default value \a nShowDefault (which equals SW_SHOW) will show the window in its current state and position.

        When the user closes the window it will be hidden, but not destroyed. You can call Show() to make it visible again.

        \remark After you create a window using Create() it will be invisible. You must call Show() to make the window visible.

        \error
            Throws an exception if the window hasn't been created yet and the object doesn't hold a valid window index.

        \threading
            This function is thread-safe.
        */
        void Show( int nShow = showDefault ) const;


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Hides the image window.

        This is a convenience function to hide the window. It will call Show(SW_HIDE)

        \error
            Throws an exception if the window hasn't been created yet and the object doesn't hold a valid window index.

        \threading
            This function is thread-safe.

        \sa Show()
        */
        void Hide( void ) const;


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Closes and destroys the window.

        Closes and destroys the window.
        When the function returns successfully, the object will be invalid and the stored window index will be set to invalid.

        If you don't close a CPylonImageWindow, it will be closed automatically when PylonTerminate() is called.

        \remark If you just want to hide the window from the user you should call Hide() instead.

        \error
            Does not throw C++ exceptions.

        \threading
            This function is thread-safe.
        */
        bool Close( void );


        ///////////////////////////////////////////////////////////////////////
        /*!
        \brief Sets the contents of the image window.

        Use this function to set the image shown in the window.
        You can pass any IImage based object (like CPylonImage or CPylonBitmapImage).
        You can also pass a GrabResultPtr object as it will convert its contents automatically to an IImage.

        If you pass an empty or invalid image the contents of the image window will be cleared.

        \param[in] image    The image to display in the window.

        \error
            Throws an exception if the window hasn't been created yet and the object doesn't hold a valid window index.

        \threading
            This function is thread-safe.
        */
        void SetImage( const Pylon::IImage& image ); //accepts also CGrabResultPtr

    public:
        /// Default value for window position/size when calling Create()
        static const int useDefault = static_cast<int>(0x80000000); // CW_USEDEFAULT
        /// Default value for window position/size when calling Show()
        static const int showDefault = 5; // SW_SHOW

    protected:
        /// Invalid window index.
        static const size_t invalidWinIndex = static_cast<size_t>(-1);

        /// The window index managed by this object. Valid window indexes range from 0 to 31. If no window is currently managed, invalidWinIndex will be stored.
        size_t m_winIndex;

    protected:
        // no copy
        CPylonImageWindow( const CPylonImageWindow& );
        CPylonImageWindow& operator=( const CPylonImageWindow& );
    };

/**
 * @}
 */
}

#endif /* __cplusplus */

#pragma pack(pop)

#endif /* PYLON_GUI_H_INCLUDED__ */
