/*
 * Copyright (C) 2016 Canonical, Ltd.
 * Author: Martin Pitt <martin.pitt@ubuntu.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file util.h
 *  \brief A set of high-level helper functions that can be used when working
 *  with datastructures of the library.
 *
 *  For example, it can be used to initialize iterators or clear error structures.
 */

#pragma once

#include <glib.h>
#include <stdint.h>
#include "types.h"

/**
 * @brief Parses YAML hierarchy from @rootdir, drops the configuration for @id
 * from the state and re-generates the YAML files.
 * 
 * @param id The NetplanID for a specific configuration block of network interface(s)
 * @param rootdir The location where the YAML hierarchy is read from and written to.
 * @return gboolean, Indicating success.
 */
NETPLAN_PUBLIC gboolean
netplan_delete_connection(const char* id, const char* rootdir);

NETPLAN_PUBLIC gboolean
netplan_generate(const char* rootdir);

NETPLAN_PUBLIC ssize_t
netplan_get_id_from_nm_filepath(const char* filename, const char* ssid, char* out_buffer, size_t out_buf_size);

NETPLAN_PUBLIC ssize_t
netplan_netdef_get_output_filename(const NetplanNetDefinition* netdef, const char* ssid, char* out_buffer, size_t out_buf_size);

NETPLAN_PUBLIC void
netplan_error_clear(NetplanError** error);

NETPLAN_PUBLIC ssize_t
netplan_error_message(NetplanError* error, char* buf, size_t buf_size);

/* u64 return value contains both GLib domain and error code. The two values are
 * concatenated, so that the relevant data can easily be masked:
 * (u32)domain | (u32)code */
NETPLAN_PUBLIC uint64_t
netplan_error_code(NetplanError* error);

NETPLAN_PUBLIC void
netplan_state_iterator_init(const NetplanState* np_state, NetplanStateIterator* iter);

NETPLAN_PUBLIC NetplanNetDefinition*
netplan_state_iterator_next(NetplanStateIterator* iter);

NETPLAN_PUBLIC gboolean
netplan_state_iterator_has_next(const NetplanStateIterator* iter);

NETPLAN_PUBLIC gboolean
netplan_util_create_yaml_patch(const char* conf_obj_path, const char* obj_payload, int out_fd, NetplanError** error);

NETPLAN_PUBLIC gboolean
netplan_util_dump_yaml_subtree(const char* prefix, int input_fd, int output_fd, NetplanError** error);

/********** Old API below this ***********/

/**
 * \deprecated Use `netplan_netdef_get_filepath()` instead.
 */
NETPLAN_DEPRECATED NETPLAN_PUBLIC gchar*
netplan_get_filename_by_id(const char* netdef_id, const char* rootdir);

/**
 * \deprecated Use `netplan_get_id_from_nm_filepath()` instead.
 */
NETPLAN_DEPRECATED NETPLAN_PUBLIC gchar*
netplan_get_id_from_nm_filename(const char* filename, const char* ssid);
