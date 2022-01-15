/*
 * Logical volume descriptor functions
 *
 * Copyright (C) 2011-2022, Omar Choudary <choudary.omar@gmail.com>
 *                          Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfvde_libcdata.h"
#include "libfvde_libcerror.h"
#include "libfvde_libuna.h"
#include "libfvde_logical_volume_descriptor.h"

/* Creates logical volume descriptor
 * Make sure the value logical_volume_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_initialize(
     libfvde_logical_volume_descriptor_t **logical_volume_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_initialize";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( *logical_volume_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid logical volume descriptor value already set.",
		 function );

		return( -1 );
	}
	*logical_volume_descriptor = memory_allocate_structure(
	                              libfvde_logical_volume_descriptor_t );

	if( *logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to logical volume descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *logical_volume_descriptor,
	     0,
	     sizeof( libfvde_logical_volume_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear logical volume descriptor.",
		 function );

		memory_free(
		 *logical_volume_descriptor );

		*logical_volume_descriptor = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *logical_volume_descriptor != NULL )
	{
		memory_free(
		 *logical_volume_descriptor );

		*logical_volume_descriptor = NULL;
	}
	return( -1 );
}

/* Frees logical volume descriptor
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_free(
     libfvde_logical_volume_descriptor_t **logical_volume_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_free";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( *logical_volume_descriptor != NULL )
	{
		if( ( *logical_volume_descriptor )->name != NULL )
		{
			memory_free(
			 ( *logical_volume_descriptor )->name );
		}
		memory_free(
		 *logical_volume_descriptor );

		*logical_volume_descriptor = NULL;
	}
	return( 1 );
}

/* Compares two logical volume descriptors based on their identifier
 * Returns LIBCDATA_COMPARE_LESS, LIBCDATA_COMPARE_EQUAL, LIBCDATA_COMPARE_GREATER if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_compare(
     libfvde_logical_volume_descriptor_t *first_logical_volume_descriptor,
     libfvde_logical_volume_descriptor_t *second_logical_volume_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_compare";
	int compare_result    = 0;

	if( first_logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( second_logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second logical volume descriptor.",
		 function );

		return( -1 );
	}
	compare_result = memory_compare(
	                  first_logical_volume_descriptor->identifier,
	                  second_logical_volume_descriptor->identifier,
	                  16 );

	if( compare_result < 0 )
	{
		return( LIBCDATA_COMPARE_LESS );
	}
	else if( compare_result > 0 )
	{
		return( LIBCDATA_COMPARE_GREATER );
	}
	return( LIBCDATA_COMPARE_EQUAL );
}

/* Retrieves the identifier
 * The identifier is a UUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_identifier(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_identifier";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( uuid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UUID data.",
		 function );

		return( -1 );
	}
	if( ( uuid_data_size < 16 )
	 || ( uuid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     uuid_data,
	     logical_volume_descriptor->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the family identifier
 * The identifier is a UUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_family_identifier(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_family_identifier";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( uuid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UUID data.",
		 function );

		return( -1 );
	}
	if( ( uuid_data_size < 16 )
	 || ( uuid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     uuid_data,
	     logical_volume_descriptor->family_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy family identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded volume group name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_utf8_name_size(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_utf8_name_size";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_size_from_utf8_stream(
	     logical_volume_descriptor->name,
	     logical_volume_descriptor->name_size,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded volume group name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_utf8_name(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_utf8_name";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_copy_from_utf8_stream(
	     utf8_string,
	     utf8_string_size,
	     logical_volume_descriptor->name,
	     logical_volume_descriptor->name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded volume group name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_utf16_name_size(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_utf16_name_size";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_size_from_utf8_stream(
	     logical_volume_descriptor->name,
	     logical_volume_descriptor->name_size,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded volume group name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_utf16_name(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_utf16_name";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_copy_from_utf8_stream(
	     utf16_string,
	     utf16_string_size,
	     logical_volume_descriptor->name,
	     logical_volume_descriptor->name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfvde_logical_volume_descriptor_get_size(
     libfvde_logical_volume_descriptor_t *logical_volume_descriptor,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libfvde_logical_volume_descriptor_get_size";

	if( logical_volume_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume descriptor.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = logical_volume_descriptor->size;

	return( 1 );
}

