//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author: RN
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains the builder's recipe class that can be used to create recipes programmatically.
*/

#pragma once

#include <pylondataprocessing/QueueMode.h>
#include <pylondataprocessing/Recipe.h>
#include <pylondataprocessing/RecipeFileFormat.h>

#ifdef _MSC_VER
#pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    namespace DataProcessing
    {
        /*!
         \class CBuildersRecipe

         \brief
            This class can be used to build recipes programmatically and run them.
        */
        class PYLONDATAPROCESSING_API CBuildersRecipe : public CRecipe
        {
        public:
            /*!
             \brief
                Creates a \c CBuildersRecipe object.

             \error
                Doesn't throw C++ exceptions.
            */
            CBuildersRecipe();

            /*!
             \brief
                Destroys a \c CBuildersRecipe object.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual ~CBuildersRecipe();

            /*!
             \brief
                Retrieves a list of type IDs of all available vTool types and returns the number of available types.

             \param[out] vToolTypeIDs A string list to store the available vTools' type IDs in.

             \post
                - \c vToolTypeIDs contains the type IDs of the available vTool types in alphabetical order.

             \error
                Doesn't throw C++ exceptions, except when memory allocation fails.

             \return
                The number of available type IDs.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetAvailableVToolTypeIDs(Pylon::StringList_t& vToolTypeIDs) const;

            /*!
             \brief
                Retrieves the display name of the vTool type identified by the given type ID.

             \param[in] vToolTypeID The type ID of the vTool type whose display name is retrieved.

             \pre
                - \c vToolTypeID refers to an available vTool type (use \c GetAvailableVToolTypeIDs() to get a list of all available vTool type IDs).

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The display name of the vTool type identified by \c vToolTypeID.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual String_t GetVToolDisplayNameForTypeID(const Pylon::String_t& vToolTypeID) const;

            /*!
             \brief
                Creates a vTool of a specific type and adds it to the recipe with the given identifier.

             \param[in] identifier Identifier for the vTool instance that can be used to identify the vTool instance in the recipe.
             \param[in] vToolTypeID Type ID specifying the vTool type of the vTool to be added.

             \pre
                - \c identifier is a valid C++ identifier and must not start with an underscore.
                - No vTool with the same \c identifier already exists in the recipe.
                - \c vToolTypeID refers to an available vTool type (use \c GetAvailableVToolTypeIDs() to get a list of all available vTool type IDs).
                - Your license allows instantiating the requested vTool type from the Data Processing SDK.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - A new vTool of the type identified by \c vToolTypeID has been added to the recipe with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void AddVTool(const Pylon::String_t& identifier, const Pylon::String_t& vToolTypeID);

            /*!
             \brief
                Creates a vTool of a specific type and adds it to the recipe with an automatically generated identifier.

             \param[in] vToolTypeID Type ID specifying the vTool type of the vTool to be added.

             \pre
                - \c vToolTypeID refers to an available vTool type (use \c GetAvailableVToolTypeIDs() to get a list of all available vTool type IDs).
                - Your license allows instantiating the requested vTool type from the Data Processing SDK.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - A new vTool of the type identified by \c vToolTypeID has been added to the recipe with a unique identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                Returns the identifier of the newly created vTool instance.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t AddVTool(const Pylon::String_t& vToolTypeID);

            /*!
             \brief
                Retrieves a list of the identifiers of all vTools that exist in the recipe and returns the total number of vTools.

             \param[out] identifiers A string list to store the vTool identifiers in.

             \post
                - \c identifiers contains the identifiers of all vTools in the recipe in alphabetical order.

             \error
                Doesn't throw C++ exceptions, except when memory allocation fails.

             \return
                The number of vTools contained in the recipe.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetVToolIdentifiers(Pylon::StringList_t& identifiers) const;

            /*!
             \brief
                Returns the type ID of the vTool instance with the given identifier.

             \param[in] identifier Identifier of the vTool whose type ID is retrieved.

             \pre
                - The recipe contains a vTool with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The type ID of the vTool instance with the identifier \c identifier.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t GetVToolTypeID(const String_t& identifier) const;

            /*!
             \brief
                Checks whether the recipe contains a vTool with a specific identifier.

             \param[in] identifier Identifier of the vTool.

             \error
                Doesn't throw C++ exceptions.

             \return
                Returns true if the recipe contains a vTool with the identifier \c identifier, otherwise false.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool HasVTool(const String_t& identifier) const;

            /*!
             \brief
                Assigns a new identifier to an existing vTool instance.

             \param[in] oldIdentifier The identifier of the vTool to be renamed.
             \param[in] newIdentifier The new identifier of the vTool.

             \pre
                - The recipe contains a vTool with the identifier \c oldIdentifier.
                - \c newIdentifier is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain a vTool with the identifier \c newIdentifier.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The vTool with the identifier \c oldIdentifier has been renamed to \c newIdentifier.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RenameVTool(const Pylon::String_t& oldIdentifier, const Pylon::String_t& newIdentifier);

            /*!
             \brief
                Removes an existing vTool instance. Any connections attached to any of the vTool's pins will be removed as well.

             \param[in] identifier The identifier of the vTool to be removed.

             \pre
                - The recipe contains a vTool with the identifier \c identifier.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The vTool with the identifier \c identifier has been removed from the recipe.
                - Any connections attached to any of the vTool's pins have been removed from the recipe.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RemoveVTool(const Pylon::String_t& identifier);

            /*!
             \brief
                Adds an input of a specific type to the recipe with a given identifier.

             \param[in] inputFullName The identifier of the new input.
             \param[in] inputDataType Data type of the new input.
             \param[in] inputContainerType Container type of the new input.

             \pre
                - \c inputFullName is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain an input with the identifier \c inputFullName.
                - \c inputDataType refers to an actual data type and is not equal to \c VariantDataType_Composite, \c VariantDataType_None, or \c VariantDataType_Unsupported.
                - \c inputContainerType refers to an actual container type and is not equal to \c VariantContainerType_Unsupported.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - An input with the type identified by \c inputDataType and \c inputContainerType has been added to the recipe with the identifier \c inputFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void AddInput(const Pylon::String_t& inputFullName, EVariantDataType inputDataType, EVariantContainerType inputContainerType = VariantContainerType_None);

            /*!
             \brief
                Adds an input of a specific type to the recipe with an automatically generated identifier.

             \param[in] inputDataType Data type of the new input.
             \param[in] inputContainerType Container type of the new input.

             \pre
                - \c inputDataType refers to an actual data type and is not equal to \c VariantDataType_Composite, \c VariantDataType_None, or \c VariantDataType_Unsupported.
                - \c inputContainerType refers to an actual container type and is not equal to \c VariantContainerType_Unsupported.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - An input with the type identified by \c inputDataType and \c inputContainerType has been added to the recipe.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                Returns the automatically generated identifier of the newly created input.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t AddInput(EVariantDataType inputDataType, EVariantContainerType inputContainerType = VariantContainerType_None);

            /*!
             \brief
                Assigns a new identifier to an existing input.

             \param[in] oldInputFullName The identifier of the input to be renamed.
             \param[in] newInputFullName The new identifier of the input.

             \pre
                - The recipe contains an input with the identifier \c oldInputFullName.
                - \c newInputFullName is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain an input with the identifier \c newInputFullName.
                - The input with the given identifier isn't connected.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The input with the identifier \c oldInputFullName has been renamed to \c newInputFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RenameInput(const Pylon::String_t& oldInputFullName, const Pylon::String_t& newInputFullName);

            /*!
             \brief
                Retrieves a list of the identifiers of all inputs that exist in the recipe and returns the total number of inputs.

             \param[out] inputFullNames A string list to store the input identifiers in.

             \post
                - \c inputFullNames contains the identifiers of all inputs of the recipe in the order that they have been added.

             \error
                Doesn't throw C++ exceptions, except when memory allocation fails.

             \return
                The number of inputs that the recipe currently has.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetInputNames(Pylon::StringList_t& inputFullNames) const;

            /*!
             \brief
                Removes an input from the recipe. If any connections are attached to this input, they will be removed as well.

             \param[in] inputFullName The identifiers of the input to be removed.

             \pre
                - The recipe has an input with the identifier \c inputFullName.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The input with the identifier \c inputFullName has been removed from the recipe.
                - Any connections attached to the removed input have been removed.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RemoveInput(const Pylon::String_t& inputFullName);

            /*!
             \brief
                Adds an output of a specific type to the recipe with a given identifier.

             \param[in] outputFullName The identifier of the new output.
             \param[in] outputDataType Data type of the new output.
             \param[in] outputContainerType Container type of the new output.

             \pre
                - \c outputFullName is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain an output with the identifier \c outputFullName.
                - \c outputDataType refers to an actual data type and is not equal to \c VariantDataType_Composite, \c VariantDataType_None, or \c VariantDataType_Unsupported.
                - \c outputContainerType refers to an actual container type and is not equal to \c VariantContainerType_Unsupported.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - An output with the type identified by \c outputDataType and \c outputContainerType has been added to the recipe with the identifier \c outputFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void AddOutput(const Pylon::String_t& outputFullName, EVariantDataType outputDataType, EVariantContainerType outputContainerType = VariantContainerType_None);

            /*!
             \brief
                Adds an output of a specific type to the recipe with an automatically generated identifier.

             \param[in] outputDataType Data type of the new output.
             \param[in] outputContainerType Container type of the new output.

             \pre
                - \c outputDataType refers to an actual data type and is not equal to \c VariantDataType_Composite, \c VariantDataType_None, or \c VariantDataType_Unsupported.
                - \c outputContainerType refers to an actual container type and is not equal to \c VariantContainerType_Unsupported.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - An output with the type identified by \c outputDataType and \c outputContainerType has been added to the recipe.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                Returns the automatically generated identifier of the newly created output.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t AddOutput(EVariantDataType outputDataType, EVariantContainerType outputContainerType = VariantContainerType_None);

            /*!
             \brief
                Assigns a new identifier to an existing output.

             \param[in] oldOutputFullName The identifier of the output to be renamed.
             \param[in] newOutputFullName The new identifier of the output.

             \pre
                - The recipe contains an output with the identifier \c oldOutputFullName.
                - \c newOutputFullName is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain an output with the identifier \c newOutputFullName.
                - The output with the given identifier isn't connected.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The output with the identifier \c oldOutputFullName has been renamed to \c newOutputFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RenameOutput(const Pylon::String_t& oldOutputFullName, const Pylon::String_t& newOutputFullName);

            /*!
             \brief
                Removes an output from the recipe. If a connection is attached to this output, it will be removed as well.

             \param[in] outputFullName The identifier of the output to be removed.

             \pre
                - The recipe contains an output with the identifier \c outputFullName.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The output with the identifier \c outputFullName has been removed from the recipe.
                - If a connection was attached to this output, it has been removed from the recipe.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RemoveOutput(const Pylon::String_t& outputFullName);

            /*!
             \brief
                Creates a connection between vTool pins and/or recipe inputs or outputs with a given identifier.

             \param[in] identifier Identifier to uniquely identify the connection in the recipe.
             \param[in] sourceFullName  Full name of the source of the connection in the form "[vToolIdentifier].[vToolOutputIdentifier]"
                                        (e.g., "Camera.Image" or "myVTool.Point").
                                        To create a connection from a recipe input, use \<RecipeInput\> as the vToolIdentifier (e.g., "\<RecipeInput\>.Image").
             \param[in] destinationFullName Full name of the destination of the connection "[vToolIdentifier].[vToolInputIdentifier]"
                                            (e.g., "ImageFormatConverter.Image" or "myVTool.Point").
                                            To create a connection to a recipe output, use \<RecipeOutput\> as the vToolIdentifier (e.g., "\<RecipeOutput\>.Image").
             \param[in] queueMode The queue mode for the connection queue (see \c EQueueMode for all available queue modes). The default value is QueueMode_Blocking.
             \param[in] maxQueueSize The initial maximum size of the connection queue. The default value is 1. If \c queueMode is \c QueueMode_Unlimited, this has no effect.

             \pre
                - \c identifier is a valid C++ identifier and must not start with an underscore.
                - The recipe must not contain a connection with the same \c identifier.
                - \c sourceFullName must specify the full name of an existing vTool output pin or an existing recipe input.
                - \c destinationFullName must specify the full name of an existing vTool input pin or an existing recipe output.
                - \c sourceFullName and \c destinationFullName must have compatible data types.
                - \c maxQueueSize must be greater than 0 and lower than the maximum value of size_t.
                - The destination must not be connected.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - A new connection with the identifier \c identifier has been created in the recipe connecting \c sourceFullName to \c destinationFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void AddConnection(const Pylon::String_t& identifier, const Pylon::String_t& sourceFullName, const Pylon::String_t& destinationFullName, EQueueMode queueMode = EQueueMode::QueueMode_Blocking, size_t maxQueueSize = 1);

            /*!
             \brief
                Creates a connection between vTool pins and/or recipe inputs or outputs with an automatically generated identifier.

             \param[in] sourceFullName Full name of the source of the connection in the form "[vToolIdentifier].[vToolOutputIdentifier]"
                                       (e.g., "Camera.Image" or "myVTool.Point").
                                       To create a connection from a recipe input, use \<RecipeInput\> as the vToolIdentifier (e.g., "\<RecipeInput\>.Image").
             \param[in] destinationFullName Full name of the destination of the connection "[vToolIdentifier].[vToolInputIdentifier]"
                                            (e.g., "ImageFormatConverter.Image" or "myVTool.Point").
                                            To create a connection to a recipe output, use \<RecipeOutput\> as the vToolIdentifier (e.g., "\<RecipeOutput\>.Image").
             \param[in] queueMode The queue mode for the connection queue (see \c EQueueMode for all available queue modes). The default value is QueueMode_Blocking.
             \param[in] maxQueueSize The initial maximum size of the connection queue. The default value is 1. If \c queueMode is \c QueueMode_Unlimited, this has no effect.

             \pre
                - \c sourceFullName must specify the full name of an existing vTool output pin or an existing recipe input.
                - \c destinationFullName must specify the full name of an existing vTool input pin or an existing recipe output.
                - \c sourceFullName and \c destinationFullName must have compatible data types.
                - \c maxQueueSize must be greater than 0 and lower than the maximum value of size_t.
                - The destination must not be connected.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - A new connection has been created in the recipe connecting \c sourceFullName to \c destinationFullName.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                Returns the identifier of the newly created connection.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t AddConnection(const Pylon::String_t& sourceFullName, const Pylon::String_t& destinationFullName, EQueueMode queueMode = EQueueMode::QueueMode_Blocking, size_t maxQueueSize = 1);

            /*!
             \brief
                Gets the current maximum queue size for a connection identified by its identifier.

             \param[in] identifier Identifier of the connection whose maximum queue size is retrieved.

             \pre
                - The recipe contains a connection with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The maximum queue size of the connection with the identifier \c identifier.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetConnectionMaxQueueSize(const Pylon::String_t& identifier) const;

            /*!
             \brief
                Gets the full name of a connection's source.

             \param[in] identifier Identifier of the connection.

             \pre
                - The recipe contains a connection with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The full name of the connection's source.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t GetConnectionSource(const Pylon::String_t& identifier) const;

            /*!
             \brief
                Gets the full name of a connection's destination.

             \param[in] identifier Identifier of the connection.

             \pre
                - The recipe contains a connection with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The full name of the connection's destination.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual Pylon::String_t GetConnectionDestination(const Pylon::String_t& identifier) const;

            /*!
             \brief
                Gets the current queue mode for a connection identified by its identifier.

             \param[in] identifier Identifier of the connection whose queue mode is retrieved.

             \pre
                - The recipe contains a connection with the identifier \c identifier.

             \error
                Throws an exception if the preconditions aren't met.

             \return
                The queue mode of the connection with the identifier \c identifier.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual EQueueMode GetConnectionQueueMode(const Pylon::String_t& identifier) const;

            /*!
             \brief
                Checks whether the recipe contains a connection with a specific identifier.

             \param[in] identifier Identifier of the connection.

             \error
                Doesn't throw C++ exceptions.

             \return
                Returns true if the recipe contains a connection with the identifier \c identifier, otherwise false.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual bool HasConnection(const String_t& identifier) const;

            /*!
             \brief
                Retrieves a list of the identifiers of all connections that exist in the recipe and returns the total number of connections.

             \param[out] identifiers A string list to store the connection identifiers in.

             \post
                - \c identifiers contains the identifiers of all connections in the recipe in alphabetical order.

             \error
                Doesn't throw C++ exceptions, except when memory allocation fails.

             \return
                The number of connections contained in the recipe.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual size_t GetConnectionIdentifiers(Pylon::StringList_t& identifiers) const;

            /*!
             \brief
                Assigns a new identifier to an existing connection.

             \param[in] oldIdentifier The identifier of the connection to be renamed.
             \param[in] newIdentifier The new identifier of the connection.

             \pre
                - The recipe contains a connection with the identifier \c oldIdentifier.
                - \c newIdentifier is a valid C++ identifier and must not start with an underscore.
                - The recipe doesn't contain a connection with the identifier \c newIdentifier.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The connection with the identifier \c oldIdentifier has been renamed to \c newIdentifier.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RenameConnection(const Pylon::String_t& oldIdentifier, const Pylon::String_t& newIdentifier);

            /*!
             \brief
                Modifies the settings of an existing connection.

             \param[in] identifier The identifier of the connection to be modified.
             \param[in] queueMode The new queue mode of the connection.
             \param[in] maxQueueSize The new maximum queue size of the connection.

             \pre
                - The recipe contains a connection with the identifier \c identifier.
                - \c maxQueueSize must be greater than 0 and lower than the maximum value of size_t.

             \post
                - The connection's queue mode has been set to \c queueMode.
                - The connection's maximum queue size has been set to \c maxQueueSize.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void SetConnectionSettings(const Pylon::String_t& identifier, EQueueMode queueMode, size_t maxQueueSize);

            /*!
             \brief
                Modifies the queue mode of an existing connection.

             \param[in] identifier The identifier of the connection to be modified.
             \param[in] queueMode The new queue mode of the connection.

             \pre
                - The recipe contains a connection with the identifier \c identifier.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The connection's queue mode has been set to \c queueMode.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void SetConnectionQueueMode(const Pylon::String_t& identifier, EQueueMode queueMode);

            /*!
             \brief
                Modifies the maximum queue size of an existing connection.

             \param[in] identifier The identifier of the connection to be modified.
             \param[in] maxQueueSize The new maximum queue size of the connection.

             \pre
                - The recipe contains a connection with the identifier \c identifier.
                - \c maxQueueSize must be greater than 0 and lower than the maximum value of size_t.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The connection's maximum queue size has been set to \c maxQueueSize.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void SetConnectionMaxQueueSize(const Pylon::String_t& identifier, size_t maxQueueSize);

            /*!
             \brief
                Removes an existing connection.

             \param[in] identifier The identifier of the connection to be removed.

             \pre
                - The recipe contains a connection with the identifier \c identifier.
                - The recipe hasn't been started (i.e., IsStarted() must return false).

             \post
                - The connection with the identifier \c identifier has been removed from the recipe.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void RemoveConnection(const Pylon::String_t& identifier);


            /*!
             \brief
                Writes the recipe to a recipe file.

             \param[in] fileName Path to the file to store the recipe in.
                                 This can be an absolute or a relative path.
                                 If it is relative, the file will be saved relative to your current working directory.

             \pre
                - \c fileName is a writable file path and a valid file path for your platform.

             \post
                - The recipe has been written to the specified file path and can be loaded using the \c CRecipe API.

             \error
                Throws an exception if the preconditions aren't met.

             \threading
                This method is synchronized using the lock provided by \c GetLock().
            */
            virtual void Save(const Pylon::String_t& fileName) const;

            /*!
             \brief
               Resets the recipe by removing all vTools, inputs, outputs, connections, and observers.
               Stop() is called implicitly with an infinite timeout if the recipe has been started.

             \post
                - The recipe is empty, i.e., all vTools, inputs, outputs, connections, and observers have been removed.
                - \c IsStarted() returns false.
                - \c IsLoaded() returns true.
                - The recipe can be modified.

             \error
                Throws an exception if the preconditions aren't met.
            */
            virtual void ResetToEmpty();

        private:
            // The object can't be copied.
            CBuildersRecipe(const CBuildersRecipe&) = delete;

            // The object can't be copied.
            void operator=(const CBuildersRecipe&) = delete;
        };
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
