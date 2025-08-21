//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG, BR, TvdM
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains the recipe class that can be used to load and run data processing designs.
*/

#pragma once

#include <pylon/PylonIncludes.h>
#include <pylon/InstantCamera.h> // for ETimeoutHandling
#include <pylon/WaitObject.h> // for Infinite

#include <pylondataprocessing/IEventObserver.h>
#include <pylondataprocessing/VariantContainer.h>
#include <pylondataprocessing/IParameterCollection.h>
#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/AcquisitionMode.h>
#include <pylondataprocessing/Update.h>
#include <pylondataprocessing/VariantDataType.h>
#include <pylondataprocessing/VariantContainerType.h>

namespace Pylon
{
    namespace DataProcessing
    {
        class CVariant;
        class IOutputObserver;
        class IUpdateObserver;
        class CVariantContainer;
    }
}

#ifdef _MSC_VER
#pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    namespace DataProcessing
    {
        /*!
         \class CRecipe

         \brief
            Provides convenient access to a data processing design described by a recipe file.
        */
        class PYLONDATAPROCESSING_API CRecipe
        {
        public:
            /*!
             \brief
                Creates a \c CRecipe object with no recipe loaded.

             \error
                Doesn't throw C++ exceptions.
            */
            CRecipe();

            /*!
             \brief
                Destroys a \c CRecipe object.

             Calls \c Unload() for cleaning up if any recipe is currently loaded.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual ~CRecipe();

            /*!
             \brief
                Loads a recipe from disk and creates the objects of the design described by the recipe. Relative paths, i.e., relative to the directory the recipe file is located in, are used for loading external recipe components, e.g., images.

             \param[in] filename The name and path of the recipe.

             \pre
                <ul>
                    <li>The given file name must be a valid file path of an existing file containing valid recipe data.</li>
                </ul>

             \post
                <ul>
                    <li>A recipe is loaded. You can use \c IsLoaded() to check whether a recipe is loaded. Implicitly calls \c Unload() and unregisters all observers already connected.</li>
                </ul>

             \error
                Throws an exception if the recipe can't be loaded. No recipe is loaded if an error occurred.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Load(const String_t& filename);

            /*!
             \brief
                Loads a recipe from binary buffer and creates the objects of the design described by the recipe. Relative paths, i.e., relative to the current directory, are used for loading external recipe components, e.g., images.

             \param[in] pBuffer    Buffer pointer to binary recipe.
             \param[in] bufferSize Buffer size for binary recipe buffer in bytes.

             \pre
                <ul>
                    <li>The buffer specified by pBuffer and bufferSize must contain valid recipe data.</li>
                </ul>

             \post
                <ul>
                    <li>A recipe is loaded. You can use \c IsLoaded() to check whether a recipe is loaded. Implicitly calls \c Unload() and unregisters all observers already connected.</li>
                </ul>

             \error
                Throws an exception if the recipe can't be loaded. No recipe is loaded if an error occurred.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void LoadFromBinary(const void* pBuffer, size_t bufferSize);

            /*!
             \brief
                Loads a recipe from binary buffer and creates the objects of the design described by the recipe.

             \param[in] pBuffer    Buffer pointer to binary recipe.
             \param[in] bufferSize Buffer size for binary recipe buffer in bytes.
             \param[in] directory External recipe components, e.g., images, will be loaded relative to this directory.

             \pre
                <ul>
                    <li>The buffer specified by pBuffer and bufferSize must contain valid recipe data.</li>
                </ul>

             \post
                <ul>
                    <li>A recipe is loaded. You can use \c IsLoaded() to check whether a recipe is loaded. Implicitly calls \c Unload() and unregisters all observers already connected.</li>
                </ul>

             \error
                Throws an exception if the recipe can't be loaded. No recipe is loaded if an error occurred.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void LoadFromBinary(const void* pBuffer, size_t bufferSize, const String_t& directory);

            /*!
             \brief
                Checks whether a recipe is loaded.

             \return
                \c true if a recipe is loaded.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool IsLoaded() const;

            /*!
             \brief
                Optional method to pre-allocate resources.

             All resources that could be allocated successfully stay allocated until a call to \c DeallocateResources().

             \pre
                <ul>
                    <li>A recipe is loaded.</li>
                    <li>The recipe must not be started.</li>
                </ul>

             \post
                <ul>
                    <li>All resources are allocated.</li>
                </ul>

             \error
                Throws an exception if:
                <ul>
                    <li>The preconditions aren't met.</li>
                    <li>The resources couldn't be allocated.</li>
                </ul>

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void PreAllocateResources();

            /*!
             \brief
                Prepares the data processing and allocates resources required by the design. All Camera and Image Loading vTools keep their individual acquisition modes and the recipe is started
                like that (this corresponds to \c Start(AcquisitionMode_Unchanged)).

             \pre
                <ul>
                    <li>A recipe is loaded.</li>
                </ul>

             \error
                The recipe is not started if an error occurred. Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Start();

            /*!
             \brief
                Prepares the data processing and allocates resources required by the design. In addition, the acquisition mode for all Camera and Image Loading vTools can be specified
                (see \c EAcquisitionMode for more details).

            \param[in] acquisitionMode The acquisition mode used to start the recipe (see \c EAcquisitionMode for more details).

            \pre
                <ul>
                <li>A recipe has been loaded.</li>
                </ul>

             \error
                    The recipe is not started if an error occurred. Throws an exception if the preconditions aren't met.

             \threading
                        This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Start(EAcquisitionMode acquisitionMode);

            /*!
             \brief
                Returns information about the recipe being started.

             \return
                \c true if the recipe has been started.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool IsStarted() const;

            /*!
             \brief
                Finishes the data processing and deallocates all resources allocated at start.

             Updates may accumulate at some places in the design, e.g., when updates are triggered more frequently than can be processed and the queue mode of the connections is not set properly.
             \c timeoutMs describes the time these accumulated updates are tolerated before they will be cleared. Updates that are already being processed by a vTool will not be aborted when the
             timeout expires.

             \param[in] timeoutMs Time to wait for updates not yet started to be processed.

             \error
                Doesn't throw C++ exceptions.

             \post
                <ul>
                    <li>The recipe is stopped.</li>
                    <li>Resources allocated when calling \c Start() are deallocated.</li>
                    <li>Resources allocated when calling \c PreAllocateResources() are still allocated.</li>
                </ul>

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Stop(unsigned int timeoutMs = INFINITE);

            /*!
             \brief
                Deallocates all resources used by the recipe.

             Calls \c Stop() if the design described by the recipe has been started.

             \post
                <ul>
                    <li>No resources are allocated.</li>
                </ul>

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void DeallocateResources();

            /*!
             \brief
                Unloads the recipe currently loaded.

             Calls \c DeallocateResources() if the design described by the recipe has allocated resources. Unregisters all observers that have been connected.

             \pre
                <ul>
                    <li>Data received via \c IOutputObserver::OutputDataPush must be freed.</li>
                </ul>

             \post
                <ul>
                    <li>No recipe is loaded.</li>
                </ul>

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Unload();

            /*!
            \brief
                Returns a parameter collection to access the parameters of the recipe.

            \note
                The \c IParameterCollection returns objects based on \c CParameter that can be used while a recipe is loaded. Before unloading a recipe, the parameter objects must be cleared by
                calling \c CParameter::Release(). For parameters that become available only when resources are allocated, e.g., a camera, \c CParameter::Release() must be called before
                deallocating a resource.

            \return
                A reference to the \c IParameterCollection.

            \pre
                <ul>
                    <li>A recipe is loaded.</li>
                </ul>

            \error
                Throws an exception if the preconditions aren't met.

            \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual IParameterCollection& GetParameters();

            /*!
             \brief
                Sets a context.

             This is useful when handling multiple recipes.

             You can access the context using \c GetRecipeContext(), e.g., in \c IOutputObserver::OutputDataPush(), when receiving data from multiple recipes.

             \param[in] context The user-defined context.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using an internal lock for the recipe context.
            */
            virtual void SetRecipeContext(intptr_t context);

            /*!
             \brief
                Returns the context.

             This is useful when handling multiple recipes.

             You can access the context using \c GetRecipeContext(), e.g., in \c IOutputObserver::OutputDataPush(), when receiving data from multiple recipes.

             \return
                The context.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using an internal lock for the recipe context.
            */
            virtual intptr_t GetRecipeContext() const;

            /*!
             \brief
                Checks whether an input pin is available.

             \param[in] inputFullName The identifier of the input pin.

             \return
                \c true if the input pin is available.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool HasInput(const String_t& inputFullName) const;

            /*!
             \brief
                Checks whether an output pin is available.

             \param[in] outputFullName The identifier of the output pin.

             \return
                \c true if the output pin is available.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool HasOutput(const String_t& outputFullName) const;

            /*!
             \brief
                Returns the variant data type of the input pin.

             \param[in] inputFullName The identifier of the input pin.

             \return
                The variant data type of the input pin.

             \pre
                <ul>
                    <li>An input pin with the name \c inputFullName must exist.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual EVariantDataType GetInputType(const String_t& inputFullName) const;

            /*!
             \brief
                Returns the variant container type of the input pin.

             \param[in] inputFullName The identifier of the input pin.

             \return
                The variant container type of the input pin.

             \pre
                <ul>
                    <li>An input pin with the name \c inputFullName must exist.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual EVariantContainerType GetInputContainerType(const String_t& inputFullName) const;

            /*!
             \brief
                Returns the variant data type of the output pin.

             \param[in] outputFullName The identifier of the output pin.

             \return
                The variant data type of the output pin.

             \pre
                <ul>
                    <li>An output pin with the name \c outputFullName must exist.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual EVariantDataType GetOutputType(const String_t& outputFullName) const;

            /*!
             \brief
                Returns the variant container type of the output pin.

             \param[in] outputFullName The identifier of the output pin.

             \return
                The variant container type of the output pin.

             \pre
                <ul>
                    <li>An output pin with the name \c outputFullName must exist.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual EVariantContainerType GetOutputContainerType(const String_t& outputFullName) const;

            /*!
             \brief
                Checks whether triggering an update is possible.

             An update can't be triggered if the recipe is not started or at least one connection connected to the input terminal has its queue mode set to blocking and there is no space available.

             \return
                \c true if an update can be triggered, \c false otherwise.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool CanTriggerUpdate() const;

            /*!
             \brief
                Starts an update asynchronously for a single input pin.

             \param[in] inputFullName    The name of the input pin.
             \param[in] value            The value to feed the input pin with.
             \param[in] pObserver        Optionally, the observer to notify when the update has been processed completely.
                                         This doesn't include subsequent updates triggered by this update. This depends on the vTools used in the recipe.
             \param[in] userProvidedId   This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \return
                The update object that has been produced by this call.

             \pre
                <ul>
                    <li>The recipe is started.</li>
                    <li>The input pin exists.</li>
                    <li>The type of the \c value is compatible with the input data type.</li>
                    <li>\c CanTriggerUpdate() must return \c true.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual CUpdate TriggerUpdateAsync(const String_t& inputFullName, CVariant value, IUpdateObserver* pObserver = nullptr, intptr_t userProvidedId = 0);

            /*!
             \brief
                Starts an update in a blocking call for a single input pin.

             \param[in]  inputFullName      The name of the input pin.
             \param[in]  value              The value to feed the input pin with.
             \param[in]  timeoutMs          The timeout for the update to finish completely.
             \param[in]  timeoutHandling    If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.
             \param[in]  pObserver          An optional observer to notify when the update has been processed completely.
                                            This doesn't include subsequent updates triggered by this update. This depends on the vTools used in the recipe.
             \param[in]  userProvidedId     This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \return
                The update object that has been produced by this call.

             \pre
                <ul>
                    <li>The recipe is started.</li>
                    <li>The input pin exists.</li>
                    <li>The type of the \c value is compatible with the input data type.</li>
                    <li>\c CanTriggerUpdate() must return \c true.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.
                Throws an exception if the update couldn't be processed in the time specified by \c timeoutMs and \c timeoutHandling == TimeoutHandling_ThrowException.

             \threading
                This method is synchronized using the lock provided by \c GetLock() while not waiting for the update to finish completely.
            */
            virtual CUpdate TriggerUpdate(const String_t& inputFullName, CVariant value, unsigned int timeoutMs, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException,
                                          IUpdateObserver* pObserver = nullptr, intptr_t userProvidedId = 0);

            /*!
            \brief
                Starts an update asynchronously for a number of input pins.

             \param[in] inputCollection Provides the input names and the values.
             \param[in] pObserver       An optional observer to notify when the update has been processed completely.
                                        This doesn't include subsequent updates triggered by this update. This depends on the vTools used in the recipe.
             \param[in] userProvidedId  This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \return
                The update object that has been produced by this call.

             \pre
                <ul>
                    <li>The recipe is started.</li>
                    <li>The \c inputCollection argument is not empty.</li>
                    <li>The input pins exist.</li>
                    <li>The types of the values in \c inputCollection are compatible with the input data types.</li>
                    <li>\c CanTriggerUpdate() must return \c true.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual CUpdate TriggerUpdateAsync(CVariantContainer inputCollection, IUpdateObserver* pObserver = nullptr, intptr_t userProvidedId = 0);

            /*!
             \brief
                Starts an update in a blocking call for a number of input pins.

             \param[in] inputCollection     Provides the input names and the values.
             \param[in] timeoutMs           The timeout for the update to finish completely.
             \param[in] timeoutHandling     If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.
             \param[in] pObserver           An optional observer to notify when the update has been processed completely.
                                            This doesn't include subsequent updates triggered by this update. This depends on the vTools used in the recipe.
             \param[in] userProvidedId      This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \return
                The update object that has been produced by this call.

             \pre
                <ul>
                    <li>The recipe is started.</li>
                    <li>The \c inputCollection argument is not empty.</li>
                    <li>The input pins exist.</li>
                    <li>The types of the values in \c inputCollection are compatible with the input data types.</li>
                    <li>\c CanTriggerUpdate() must return \c true.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.
                Throws an exception if the update couldn't be processed in the time specified by \c timeoutMs and \c timeoutHandling == TimeoutHandling_ThrowException.

             \threading
                This method is synchronized using the lock provided by \c GetLock() while not waiting for the update to finish completely.
            */
            virtual CUpdate TriggerUpdate(CVariantContainer inputCollection, unsigned int timeoutMs, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException,
                                          IUpdateObserver* pObserver = nullptr, intptr_t userProvidedId = 0);

            /*!
             \brief
                Starts an update in a blocking call for a number of input pins.
                After the update has been processed, a variant container containing the recipe output is returned.
                This method is only intended for cases where the input triggers exactly one result.

             \param[in] inputCollection     Provides the input names and the values.
             \param[in] timeoutMs           The timeout for the update to finish completely.
             \param[in] timeoutHandling     If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.

             \return
                The variant container that has been output by the recipe.

             \pre
                <ul>
                    <li>The recipe is started.</li>
                    <li>The \c inputCollection argument is not empty.</li>
                    <li>The input pins exist.</li>
                    <li>The types of the values in \c inputCollection are compatible with the input data types.</li>
                    <li>\c CanTriggerUpdate() must return \c true.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.
                Throws an exception if the update couldn't be processed in the time specified by \c timeoutMs and \c timeoutHandling == TimeoutHandling_ThrowException.

             \threading
                This method is synchronized using the lock provided by \c GetLock() while not waiting for the update to finish completely.
            */
            virtual CVariantContainer TriggerUpdateWithReturn(CVariantContainer inputCollection, unsigned int timeoutMs, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException);

            /*!
             \brief
                Returns the count and the list of names of all output pins.

             \param[out] result The list of output pin names of the recipe.

             \return
                Number of output pin names of the recipe.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetOutputNames(StringList_t& result) const;

            /*!
             \brief
                Adds an output observer to the list of registered output observers.

                If mode equals \c RegistrationMode_ReplaceAll, the list of registered observes is cleared.

             \note
                <ul>
                    <li>The observer must not be deleted before the \c CRecipe is destroyed while it is registered.</li>
                    <li>If the \c IOutputObserver and the \c CRecipe are created on the stack in the same scope, the observer must be created prior to the \c CRecipe it is registered to because the
                        objects are destroyed in reverse order.</li>
                </ul>

             \param[in] outputFullName  The name of the output pin.
             \param[in] pObserver       The receiver of events.
             \param[in] mode            Indicates how to register the new observer.
             \param[in] userProvidedId  This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \pre
                <ul>
                    <li>A recipe is loaded.</li>
                    <li>The output pin exists.</li>
                    <li>\c pObserver is not nullptr.</li>
                </ul>

             \post
                <ul>
                    <li>The observer is registered and called when output data is available.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met. If an exception is thrown, the observer is not registered and its \c OnDeregistered method will not be called.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RegisterOutputObserver(const String_t& outputFullName, IOutputObserver* pObserver, ERegistrationMode mode, intptr_t userProvidedId = 0);

            /*!
             \brief
                Adds an output observer to the list of registered output observers.

                If \c mode equals \c RegistrationMode_ReplaceAll, the list of registered observes is cleared.

             \note
                <ul>
                    <li>The observer must not be deleted before the \c CRecipe is destroyed while it is registered.</li>
                    <li>If the \c IOutputObserver and the \c CRecipe are created on the stack in the same scope, the observer must be created prior to the \c CRecipe it is registered to because the
                        objects are destroyed in reverse order.</li>
                </ul>

             \param[in] outputFullNames  A list of names of the observed output pins.
             \param[in] pObserver        The receiver of events.
             \param[in] mode             Indicates how to register the new observer.
             \param[in] userProvidedId   This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \pre
                <ul>
                    <li>A recipe is loaded.</li>
                    <li>The output pins exist.</li>
                    <li>\c pObserver is not nullptr.</li>
                </ul>

             \post
                <ul>
                    <li>The observer is registered and called when output data is available.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met. If an exception is thrown, the observer is not registered and its \c OnDeregistered method will not be called.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RegisterOutputObserver(const StringList_t& outputFullNames, IOutputObserver* pObserver, ERegistrationMode mode, intptr_t userProvidedId = 0);

            /*!
             \brief
                Adds an output observer to the list of registered output observers.

                If \c mode equals \c RegistrationMode_ReplaceAll, the list of registered observes is cleared.

             \note
                <ul>
                    <li>The observer must not be deleted before the \c CRecipe is destroyed while it is registered.</li>
                    <li>If the \c IOutputObserver and the \c CRecipe are created on the stack in the same scope, the observer must be created prior to the \c CRecipe it is registered to because the
                        objects are destroyed in reverse order.</li>
                </ul>

             \param[in] pObserver           The receiver of events.
             \param[in] mode                Indicates how to register the new observer.
             \param[in] userProvidedId      This optional ID is passed to distinguish between different events. This ID is provided to \c IUpdateObserver::UpdateDone.

             \pre
                <ul>
                    <li>A recipe is loaded.</li>
                    <li>\c pObserver is not nullptr.</li>
                </ul>

             \post
                <ul>
                    <li>The observer is registered and called when any output data is available.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met. If an exception is thrown, the observer is not registered and its \c OnDeregistered method will not be called.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RegisterAllOutputsObserver(IOutputObserver* pObserver, ERegistrationMode mode, intptr_t userProvidedId = 0);

            /*!
             \brief
                Removes an output observer from the list of registered output observers and calls the observer's \c OnDeregistered method.

                If the output pin or the observer with \c userProvidedId is not found, nothing is done.

             \note
                The last registered observer with \c userProvidedId is unregistered first if the same observer with \c userProvidedId has been registered multiple times.

             \param[in] outputFullName  The name of the output pin.
             \param[in] pObserver       The receiver of events.
             \param[in] userProvidedId  This optional ID is passed to distinguish between different events. If an observer has been registered multiple times, the observer with the matching
                                        user id is deregistered.

             \return
                \c true if the output pin and the observer were found and the observer has been unregistered.

             \post
                <ul>
                    <li>If the output pin and the observer were found, the observer is unregistered.</li>
                    <li>If an observer has been registered multiple times, the observer with the matching user ID is deregistered.</li>
                </ul>

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool UnregisterOutputObserver(const String_t& outputFullName, IOutputObserver* pObserver, intptr_t userProvidedId = 0);

            /*!
             \brief
                Removes an output observer from the list of registered output observers for all output pins and calls the observer's \c OnDeregistered method.

                If the observer with \c userProvidedId is not found, nothing is done.

             \note
                The last registered observer with \c userProvidedId is unregistered first if the same observer with \c userProvidedId has been registered multiple times.

             \param[in] pObserver       The receiver of events.
             \param[in] userProvidedId  This optional ID is passed to distinguish between different events.
                                        If an observer has been registered multiple times, the observer with the matching user ID is deregistered.

             \return
                \c true if the output pin and the observer were found and the observer has been unregistered.

             \post
                <ul>
                    <li>If the output pin and the observer were found, the observer is unregistered.</li>
                    <li>If an observer has been registered multiple times, the observer with the matching user ID is deregistered.</li>
                </ul>

             \error
                 Doesn't throw C++ exceptions.

             \threading
                 This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool UnregisterOutputObserver(IOutputObserver* pObserver, intptr_t userProvidedId = 0);

            /*!
             \brief
                Registers an event observer to the recipe. Only one single observer per recipe is supported. Registering a new one
                automatically unregisters the old one. Registered observers must be unregistered before destruction.

             \param[in] pObserver The receiver of events.

             \pre
                <ul>
                    <li>\c pObserver is not nullptr.</li>
                </ul>

             \post
                <ul>
                    <li>The observer is registered and called when events occur, e.g., an error is detected by a vTool.</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met. If an exception is thrown, the observer is not registered and its \c OnDeregistered method will not be called.

             \threading
                This method is synchronized using an internal lock for event observer handling.
            */
            virtual void RegisterEventObserver(IEventObserver* pObserver);

            /*!
             \brief
                Removes any registered event observer from the recipe and calls the observer's \c OnDeregistered method.

                If an observer is not found, nothing is done.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is synchronized using an internal lock for event observer handling.
            */
            virtual void UnregisterEventObserver();

            /*!
             \brief
                Provides access to the lock used for synchronizing the access to the recipe.

                This lock can be used when extending the Recipe class.

             Example:
             \code
                class CMyRecipe : public CRecipe
                {
                    // Method extending the Instant Camera class.
                    void Foo()
                    {
                        // Scoped Lock.
                        AutoLock lock( CRecipe::GetLock());

                        //...
                    }
                };
             \endcode

             \error
                Doesn't throw C++ exceptions.
            */
            CLock& GetLock();

        private:
            // The object can't be copied.
            CRecipe(const CRecipe&) = delete;

            // The object can't be copied.
            void operator=(const CRecipe&) = delete;

        protected:
            class CRecipeImpl;
            CRecipeImpl* m_pImpl = nullptr;
        };
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
