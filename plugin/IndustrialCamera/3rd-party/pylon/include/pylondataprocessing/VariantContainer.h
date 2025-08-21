//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  TvdM
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Container for pushing data to inputs and receiving data from outputs.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/Variant.h>

#ifdef _MSC_VER
#pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */
namespace Pylon
{
    namespace DataProcessing
    {
        /*!
         \brief
            \c CVariantContainer is a map-like container providing an interface like a C++ standard library.

         Values can be processed like this:
         \code
             CVariantContainer container;
             for (const auto& element : container)
             {
                 String_t name = element.first;
                 CVariant value = element.second;
             }
         \endcode

         \threading
            The \c CVariantContainer class isn't thread-safe.
        */
        class PYLONDATAPROCESSING_API CVariantContainer
        {
        public:
            /*!
             \brief
                Creates an empty variant container object.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer();

            /*!
             \brief
                Copies a variant container object.

             \param[in] rhs The variant container to copy.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer(const CVariantContainer& rhs);

            /*!
             \brief
                Move constructs a variant container object.

             \param[in] rhs The variant container to move the data from.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer(CVariantContainer&& rhs);

            /*!
             \brief
                Assigns a variant container object.

             \param[in] rhs The variant container to assign.

             \return
                This variant container.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer& operator=(const CVariantContainer& rhs);

            /*!
             \brief
                Move assigns a variant container object.

             \param[in] rhs The variant container to move the data from.

             \return
                This variant container.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer& operator=(CVariantContainer&& rhs);

            /*!
             \brief
                Destroys a variant container object.

             \error
                Doesn't throw C++ exceptions.
            */
            ~CVariantContainer();

            /*!
             \brief
                Gets the element with the \c key passed.

             \note
                If the \c key passed is not contained in the \c CVariantContainer, an empty element with the \c key passed is created.

             \param[in] key The key as string value, typically the name of an input or an output.

             \return
                The value as \c CVariant reference.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariant& operator[](const String_t& key);

            /*!
             \brief
                Key value pair used by the iterator.
            */
            struct keyvalue_pair
            {
                /*!
                 \brief
                  The key.
                */
                String_t first;

                /*!
                 \brief
                    The value.
                */
                CVariant second;
            };

            /// Iterator interface.
            struct PYLONDATAPROCESSING_API iterator
            {
                using element = keyvalue_pair;
                /*!
                 \brief
                    Gets the element.

                 \return
                    Element reference (key value pair).
                */
                const element& operator*() const;

                /*!
                 \brief
                    Gets the element.

                 \return
                    Element pointer (key value pair).
                */
                const element* operator->() const;

                /*!
                 \brief
                    Prefix increment.

                 \return
                    Iterator reference.
                */
                iterator& operator++();

                /*!
                 \brief
                    Postfix increment, less efficient because implicitly cloning the iterator.

                 \return
                    Next iterator.
                */
                iterator operator++(int);

                /*!
                 \brief
                    Compare if equal.

                 \return
                    True if equal.
                */
                bool operator==(const iterator& rhs) const;

                /*!
                 \brief
                    Compare if not equal.

                 \return
                    True if not equal.
                */
                bool operator!=(const iterator& rhs) const;

                /*!
                 \brief
                    Creates an empty variant container iterator object.
                */
                iterator();

                /*!
                 \brief
                    Copies a variant container iterator object.

                 \param[in] rhs The variant container iterator to copy.
                */
                iterator(const iterator& rhs);

                /*!
                 \brief
                    Move constructs a variant container iterator object.

                 \param[in] rhs The variant container iterator to move the data from.
                */
                iterator(iterator&& rhs);

                /*!
                 \brief
                    Assigns a variant container iterator object.

                 \param[in] rhs The variant container iterator to assign.

                 \return
                    This variant container iterator.
                */
                iterator& operator=(const iterator& rhs);

                /*!
                 \brief
                    Move assigns a variant container iterator object.

                 \param[in] rhs The variant container iterator to move the data from.

                 \return
                    This variant container iterator.
                */
                iterator& operator=(iterator&& rhs);

                /*!
                 \brief
                    Destroys a variant container iterator object.
                */
                ~iterator();

            private:
                // Internal use only. Subject to change without notice.
                friend class CVariantContainer;
                struct iteratorimpl;
                iterator(iteratorimpl* p);
                iteratorimpl* m_pImpl;
            };

            /*!
             \brief
                Gets the \c iterator to the first element.

             \return
                \c iterator to the first element.

             \error
                Doesn't throw C++ exceptions.
            */
            iterator begin() const;

            /*!
             \brief
                Gets the \c iterator to the element after the last element.

             \return
                \c iterator to the element after the last element.

             \error
                Doesn't throw C++ exceptions.
            */
            const iterator& end() const;

            /*!
             \brief
                Finds an element.

             \param[in] key The key as string value, typically the name of an input or an output.

             \return
                \c iterator to an element or \c end() if not found.

             \error
                Doesn't throw C++ exceptions.
            */
            iterator find(const String_t& key) const;

            /*!
             \brief
                Number of elements with key.

             \param[in] key The key as string value, typically the name of an input or an output.

             \return
                The number of elements with key, which is either 1 or 0.

             \error
                Doesn't throw C++ exceptions.
            */
            size_t count(const String_t& key) const;

            /*!
             \brief
                Clears all elements.

             \post
                <ul>
                    <li>The \c CVariantContainer has no elements.<\li>
                </ul>

             \error
                Doesn't throw C++ exceptions.
            */
            void clear();

            /*!
             \brief
                Checks \c CVariantContainer has no elements.

             \return
                \c true if empty, \c false otherwise.

             \error
                Doesn't throw C++ exceptions.
            */
            bool empty() const;

            /*!
             \brief
                Returns the number of elements.

             \return
                The number of elements.

             \error
                Doesn't throw C++ exceptions.
            */
            size_t size() const;

            /*!
             \brief
                Erases an element.

             \return
                \c iterator to next element or \c end() if there is no successor.

             \error
                Doesn't throw C++ exceptions.
            */
            CVariantContainer::iterator erase(const CVariantContainer::iterator& it);

            /*!
             \brief
                Erases an element by key.

             \param[in] key The key as string value, typically the name of an input or an output.

             \return
                The number of deletions, which is either 0 or 1.

             \error
                Doesn't throw C++ exceptions.
            */
            size_t erase(const String_t& key);

        private:
            // Internal use only. Subject to change without notice.
            struct CVariantContainerImpl;
            CVariantContainerImpl* m_pImpl = nullptr;
        };
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
