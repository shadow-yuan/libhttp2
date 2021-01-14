/*
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "src/hpack/static_table.h"

static constexpr uint8_t g_bytes[1339] = {
	0x3A, 0x70, 0x61, 0x74, 0x68, 0x3A, 0x6D, 0x65, 0x74, 0x68, 0x6F, 0x64, 0x3A, 0x73, 0x74, 0x61,
	0x74, 0x75, 0x73, 0x3A, 0x61, 0x75, 0x74, 0x68, 0x6F, 0x72, 0x69, 0x74, 0x79, 0x3A, 0x73, 0x63,
	0x68, 0x65, 0x6D, 0x65, 0x74, 0x65, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x6D, 0x65, 0x73, 0x73, 0x61,
	0x67, 0x65, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x67, 0x72, 0x70,
	0x63, 0x2D, 0x70, 0x61, 0x79, 0x6C, 0x6F, 0x61, 0x64, 0x2D, 0x62, 0x69, 0x6E, 0x67, 0x72, 0x70,
	0x63, 0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x61,
	0x63, 0x63, 0x65, 0x70, 0x74, 0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x67, 0x72,
	0x70, 0x63, 0x2D, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2D, 0x73, 0x74, 0x61, 0x74, 0x73, 0x2D,
	0x62, 0x69, 0x6E, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x74, 0x61, 0x67, 0x73, 0x2D, 0x62, 0x69, 0x6E,
	0x67, 0x72, 0x70, 0x63, 0x2D, 0x74, 0x72, 0x61, 0x63, 0x65, 0x2D, 0x62, 0x69, 0x6E, 0x63, 0x6F,
	0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x74, 0x79, 0x70, 0x65, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E,
	0x74, 0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74,
	0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x69, 0x6E,
	0x74, 0x65, 0x72, 0x6E, 0x61, 0x6C, 0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x2D,
	0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x69, 0x6E, 0x74, 0x65,
	0x72, 0x6E, 0x61, 0x6C, 0x2D, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D, 0x2D, 0x65, 0x6E, 0x63, 0x6F,
	0x64, 0x69, 0x6E, 0x67, 0x2D, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x75, 0x73, 0x65, 0x72,
	0x2D, 0x61, 0x67, 0x65, 0x6E, 0x74, 0x68, 0x6F, 0x73, 0x74, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x70,
	0x72, 0x65, 0x76, 0x69, 0x6F, 0x75, 0x73, 0x2D, 0x72, 0x70, 0x63, 0x2D, 0x61, 0x74, 0x74, 0x65,
	0x6D, 0x70, 0x74, 0x73, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x72, 0x65, 0x74, 0x72, 0x79, 0x2D, 0x70,
	0x75, 0x73, 0x68, 0x62, 0x61, 0x63, 0x6B, 0x2D, 0x6D, 0x73, 0x78, 0x2D, 0x65, 0x6E, 0x64, 0x70,
	0x6F, 0x69, 0x6E, 0x74, 0x2D, 0x6C, 0x6F, 0x61, 0x64, 0x2D, 0x6D, 0x65, 0x74, 0x72, 0x69, 0x63,
	0x73, 0x2D, 0x62, 0x69, 0x6E, 0x67, 0x72, 0x70, 0x63, 0x2D, 0x74, 0x69, 0x6D, 0x65, 0x6F, 0x75,
	0x74, 0x31, 0x32, 0x33, 0x34, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x77, 0x61, 0x69, 0x74, 0x5F, 0x66,
	0x6F, 0x72, 0x5F, 0x72, 0x65, 0x61, 0x64, 0x79, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x74, 0x69, 0x6D,
	0x65, 0x6F, 0x75, 0x74, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x6D, 0x61, 0x78, 0x5F, 0x72, 0x65, 0x71,
	0x75, 0x65, 0x73, 0x74, 0x5F, 0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x5F, 0x62, 0x79, 0x74,
	0x65, 0x73, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x6D, 0x61, 0x78, 0x5F, 0x72, 0x65, 0x73, 0x70, 0x6F,
	0x6E, 0x73, 0x65, 0x5F, 0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x5F, 0x62, 0x79, 0x74, 0x65,
	0x73, 0x2F, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x6C, 0x62, 0x2E, 0x76, 0x31, 0x2E, 0x4C, 0x6F, 0x61,
	0x64, 0x42, 0x61, 0x6C, 0x61, 0x6E, 0x63, 0x65, 0x72, 0x2F, 0x42, 0x61, 0x6C, 0x61, 0x6E, 0x63,
	0x65, 0x4C, 0x6F, 0x61, 0x64, 0x2F, 0x65, 0x6E, 0x76, 0x6F, 0x79, 0x2E, 0x73, 0x65, 0x72, 0x76,
	0x69, 0x63, 0x65, 0x2E, 0x6C, 0x6F, 0x61, 0x64, 0x5F, 0x73, 0x74, 0x61, 0x74, 0x73, 0x2E, 0x76,
	0x32, 0x2E, 0x4C, 0x6F, 0x61, 0x64, 0x52, 0x65, 0x70, 0x6F, 0x72, 0x74, 0x69, 0x6E, 0x67, 0x53,
	0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x2F, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6D, 0x4C, 0x6F, 0x61,
	0x64, 0x53, 0x74, 0x61, 0x74, 0x73, 0x2F, 0x67, 0x72, 0x70, 0x63, 0x2E, 0x68, 0x65, 0x61, 0x6C,
	0x74, 0x68, 0x2E, 0x76, 0x31, 0x2E, 0x48, 0x65, 0x61, 0x6C, 0x74, 0x68, 0x2F, 0x57, 0x61, 0x74,
	0x63, 0x68, 0x2F, 0x65, 0x6E, 0x76, 0x6F, 0x79, 0x2E, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
	0x2E, 0x64, 0x69, 0x73, 0x63, 0x6F, 0x76, 0x65, 0x72, 0x79, 0x2E, 0x76, 0x32, 0x2E, 0x41, 0x67,
	0x67, 0x72, 0x65, 0x67, 0x61, 0x74, 0x65, 0x64, 0x44, 0x69, 0x73, 0x63, 0x6F, 0x76, 0x65, 0x72,
	0x79, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x2F, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6D, 0x41,
	0x67, 0x67, 0x72, 0x65, 0x67, 0x61, 0x74, 0x65, 0x64, 0x52, 0x65, 0x73, 0x6F, 0x75, 0x72, 0x63,
	0x65, 0x73, 0x64, 0x65, 0x66, 0x6C, 0x61, 0x74, 0x65, 0x67, 0x7A, 0x69, 0x70, 0x73, 0x74, 0x72,
	0x65, 0x61, 0x6D, 0x2F, 0x67, 0x7A, 0x69, 0x70, 0x47, 0x45, 0x54, 0x50, 0x4F, 0x53, 0x54, 0x2F,
	0x2F, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x2E, 0x68, 0x74, 0x6D, 0x6C, 0x68, 0x74, 0x74, 0x70, 0x68,
	0x74, 0x74, 0x70, 0x73, 0x32, 0x30, 0x30, 0x32, 0x30, 0x34, 0x32, 0x30, 0x36, 0x33, 0x30, 0x34,
	0x34, 0x30, 0x30, 0x34, 0x30, 0x34, 0x35, 0x30, 0x30, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2D,
	0x63, 0x68, 0x61, 0x72, 0x73, 0x65, 0x74, 0x67, 0x7A, 0x69, 0x70, 0x2C, 0x20, 0x64, 0x65, 0x66,
	0x6C, 0x61, 0x74, 0x65, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2D, 0x6C, 0x61, 0x6E, 0x67, 0x75,
	0x61, 0x67, 0x65, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2D, 0x72, 0x61, 0x6E, 0x67, 0x65, 0x73,
	0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x61, 0x63, 0x63, 0x65, 0x73, 0x73, 0x2D, 0x63, 0x6F, 0x6E,
	0x74, 0x72, 0x6F, 0x6C, 0x2D, 0x61, 0x6C, 0x6C, 0x6F, 0x77, 0x2D, 0x6F, 0x72, 0x69, 0x67, 0x69,
	0x6E, 0x61, 0x67, 0x65, 0x61, 0x6C, 0x6C, 0x6F, 0x77, 0x61, 0x75, 0x74, 0x68, 0x6F, 0x72, 0x69,
	0x7A, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x63, 0x61, 0x63, 0x68, 0x65, 0x2D, 0x63, 0x6F, 0x6E, 0x74,
	0x72, 0x6F, 0x6C, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x64, 0x69, 0x73, 0x70, 0x6F,
	0x73, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x6C, 0x61,
	0x6E, 0x67, 0x75, 0x61, 0x67, 0x65, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x6C, 0x65,
	0x6E, 0x67, 0x74, 0x68, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x6C, 0x6F, 0x63, 0x61,
	0x74, 0x69, 0x6F, 0x6E, 0x63, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x72, 0x61, 0x6E, 0x67,
	0x65, 0x63, 0x6F, 0x6F, 0x6B, 0x69, 0x65, 0x64, 0x61, 0x74, 0x65, 0x65, 0x74, 0x61, 0x67, 0x65,
	0x78, 0x70, 0x65, 0x63, 0x74, 0x65, 0x78, 0x70, 0x69, 0x72, 0x65, 0x73, 0x66, 0x72, 0x6F, 0x6D,
	0x69, 0x66, 0x2D, 0x6D, 0x61, 0x74, 0x63, 0x68, 0x69, 0x66, 0x2D, 0x6D, 0x6F, 0x64, 0x69, 0x66,
	0x69, 0x65, 0x64, 0x2D, 0x73, 0x69, 0x6E, 0x63, 0x65, 0x69, 0x66, 0x2D, 0x6E, 0x6F, 0x6E, 0x65,
	0x2D, 0x6D, 0x61, 0x74, 0x63, 0x68, 0x69, 0x66, 0x2D, 0x72, 0x61, 0x6E, 0x67, 0x65, 0x69, 0x66,
	0x2D, 0x75, 0x6E, 0x6D, 0x6F, 0x64, 0x69, 0x66, 0x69, 0x65, 0x64, 0x2D, 0x73, 0x69, 0x6E, 0x63,
	0x65, 0x6C, 0x61, 0x73, 0x74, 0x2D, 0x6D, 0x6F, 0x64, 0x69, 0x66, 0x69, 0x65, 0x64, 0x6C, 0x69,
	0x6E, 0x6B, 0x6C, 0x6F, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x6D, 0x61, 0x78, 0x2D, 0x66, 0x6F,
	0x72, 0x77, 0x61, 0x72, 0x64, 0x73, 0x70, 0x72, 0x6F, 0x78, 0x79, 0x2D, 0x61, 0x75, 0x74, 0x68,
	0x65, 0x6E, 0x74, 0x69, 0x63, 0x61, 0x74, 0x65, 0x70, 0x72, 0x6F, 0x78, 0x79, 0x2D, 0x61, 0x75,
	0x74, 0x68, 0x6F, 0x72, 0x69, 0x7A, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x72, 0x61, 0x6E, 0x67, 0x65,
	0x72, 0x65, 0x66, 0x65, 0x72, 0x65, 0x72, 0x72, 0x65, 0x66, 0x72, 0x65, 0x73, 0x68, 0x72, 0x65,
	0x74, 0x72, 0x79, 0x2D, 0x61, 0x66, 0x74, 0x65, 0x72, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x73,
	0x65, 0x74, 0x2D, 0x63, 0x6F, 0x6F, 0x6B, 0x69, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x2D,
	0x74, 0x72, 0x61, 0x6E, 0x73, 0x70, 0x6F, 0x72, 0x74, 0x2D, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69,
	0x74, 0x79, 0x74, 0x72, 0x61, 0x6E, 0x73, 0x66, 0x65, 0x72, 0x2D, 0x65, 0x6E, 0x63, 0x6F, 0x64,
	0x69, 0x6E, 0x67, 0x76, 0x61, 0x72, 0x79, 0x76, 0x69, 0x61, 0x77, 0x77, 0x77, 0x2D, 0x61, 0x75,
	0x74, 0x68, 0x65, 0x6E, 0x74, 0x69, 0x63, 0x61, 0x74, 0x65, 0x30, 0x69, 0x64, 0x65, 0x6E, 0x74,
	0x69, 0x74, 0x79, 0x74, 0x72, 0x61, 0x69, 0x6C, 0x65, 0x72, 0x73, 0x61, 0x70, 0x70, 0x6C, 0x69,
	0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x2F, 0x67, 0x72, 0x70, 0x63, 0x67, 0x72, 0x70, 0x63, 0x50,
	0x55, 0x54, 0x6C, 0x62, 0x2D, 0x63, 0x6F, 0x73, 0x74, 0x2D, 0x62, 0x69, 0x6E, 0x69, 0x64, 0x65,
	0x6E, 0x74, 0x69, 0x74, 0x79, 0x2C, 0x64, 0x65, 0x66, 0x6C, 0x61, 0x74, 0x65, 0x69, 0x64, 0x65,
	0x6E, 0x74, 0x69, 0x74, 0x79, 0x2C, 0x67, 0x7A, 0x69, 0x70, 0x64, 0x65, 0x66, 0x6C, 0x61, 0x74,
	0x65, 0x2C, 0x67, 0x7A, 0x69, 0x70, 0x69, 0x64, 0x65, 0x6E, 0x74, 0x69, 0x74, 0x79, 0x2C, 0x64,
	0x65, 0x66, 0x6C, 0x61, 0x74, 0x65, 0x2C, 0x67, 0x7A, 0x69, 0x70
};

inline slice make_static_slice(int len , const uint8_t* buf) {
    return slice(buf, len, slice::STATIC);
}

namespace hpack {
struct static_metadata_context {

const slice slices[HPACK_STATIC_MDSTR_COUNT] = {

    make_static_slice( 5, g_bytes + 0),
    make_static_slice( 7, g_bytes + 5),
    make_static_slice( 7, g_bytes + 12),
    make_static_slice( 10, g_bytes + 19),
    make_static_slice( 7, g_bytes + 29),
    make_static_slice( 2, g_bytes + 36),
    make_static_slice( 12, g_bytes + 38),
    make_static_slice( 11, g_bytes + 50),
    make_static_slice( 16, g_bytes + 61),
    make_static_slice( 13, g_bytes + 77),
    make_static_slice( 20, g_bytes + 90),
    make_static_slice( 21, g_bytes + 110),
    make_static_slice( 13, g_bytes + 131),
    make_static_slice( 14, g_bytes + 144),
    make_static_slice( 12, g_bytes + 158),
    make_static_slice( 16, g_bytes + 170),
    make_static_slice( 15, g_bytes + 186),
    make_static_slice( 30, g_bytes + 201),
    make_static_slice( 37, g_bytes + 231),
    make_static_slice( 10, g_bytes + 268),
    make_static_slice( 4, g_bytes + 278),
    make_static_slice( 26, g_bytes + 282),
    make_static_slice( 22, g_bytes + 308),
    make_static_slice( 27, g_bytes + 330),
    make_static_slice( 12, g_bytes + 357),
    make_static_slice( 1, g_bytes + 369),
    make_static_slice( 1, g_bytes + 370),
    make_static_slice( 1, g_bytes + 371),
    make_static_slice( 1, g_bytes + 372),
    make_static_slice( 0, g_bytes + 373),
    make_static_slice( 19, g_bytes + 373),
    make_static_slice( 12, g_bytes + 392),
    make_static_slice( 30, g_bytes + 404),
    make_static_slice( 31, g_bytes + 434),
    make_static_slice( 36, g_bytes + 465),
    make_static_slice( 65, g_bytes + 501),
    make_static_slice( 28, g_bytes + 566),
    make_static_slice( 80, g_bytes + 594),
    make_static_slice( 7, g_bytes + 674),
    make_static_slice( 4, g_bytes + 681),
    make_static_slice( 11, g_bytes + 685),
    make_static_slice( 3, g_bytes + 696),
    make_static_slice( 4, g_bytes + 699),
    make_static_slice( 1, g_bytes + 703),
    make_static_slice( 11, g_bytes + 704),
    make_static_slice( 4, g_bytes + 715),
    make_static_slice( 5, g_bytes + 719),
    make_static_slice( 3, g_bytes + 724),
    make_static_slice( 3, g_bytes + 727),
    make_static_slice( 3, g_bytes + 730),
    make_static_slice( 3, g_bytes + 733),
    make_static_slice( 3, g_bytes + 736),
    make_static_slice( 3, g_bytes + 739),
    make_static_slice( 3, g_bytes + 742),
    make_static_slice( 14, g_bytes + 745),
    make_static_slice( 13, g_bytes + 759),
    make_static_slice( 15, g_bytes + 772),
    make_static_slice( 13, g_bytes + 787),
    make_static_slice( 6, g_bytes + 800),
    make_static_slice( 27, g_bytes + 806),
    make_static_slice( 3, g_bytes + 833),
    make_static_slice( 5, g_bytes + 836),
    make_static_slice( 13, g_bytes + 841),
    make_static_slice( 13, g_bytes + 854),
    make_static_slice( 19, g_bytes + 867),
    make_static_slice( 16, g_bytes + 886),
    make_static_slice( 14, g_bytes + 902),
    make_static_slice( 16, g_bytes + 916),
    make_static_slice( 13, g_bytes + 932),
    make_static_slice( 6, g_bytes + 945),
    make_static_slice( 4, g_bytes + 951),
    make_static_slice( 4, g_bytes + 955),
    make_static_slice( 6, g_bytes + 959),
    make_static_slice( 7, g_bytes + 965),
    make_static_slice( 4, g_bytes + 972),
    make_static_slice( 8, g_bytes + 976),
    make_static_slice( 17, g_bytes + 984),
    make_static_slice( 13, g_bytes + 1001),
    make_static_slice( 8, g_bytes + 1014),
    make_static_slice( 19, g_bytes + 1022),
    make_static_slice( 13, g_bytes + 1041),
    make_static_slice( 4, g_bytes + 1054),
    make_static_slice( 8, g_bytes + 1058),
    make_static_slice( 12, g_bytes + 1066),
    make_static_slice( 18, g_bytes + 1078),
    make_static_slice( 19, g_bytes + 1096),
    make_static_slice( 5, g_bytes + 1115),
    make_static_slice( 7, g_bytes + 1120),
    make_static_slice( 7, g_bytes + 1127),
    make_static_slice( 11, g_bytes + 1134),
    make_static_slice( 6, g_bytes + 1145),
    make_static_slice( 10, g_bytes + 1151),
    make_static_slice( 25, g_bytes + 1161),
    make_static_slice( 17, g_bytes + 1186),
    make_static_slice( 4, g_bytes + 1203),
    make_static_slice( 3, g_bytes + 1207),
    make_static_slice( 16, g_bytes + 1210),
    make_static_slice( 1, g_bytes + 1226),
    make_static_slice( 8, g_bytes + 1227),
    make_static_slice( 8, g_bytes + 1235),
    make_static_slice( 16, g_bytes + 1243),
    make_static_slice( 4, g_bytes + 1259),
    make_static_slice( 3, g_bytes + 1263),
    make_static_slice( 11, g_bytes + 1266),
    make_static_slice( 16, g_bytes + 1277),
    make_static_slice( 13, g_bytes + 1293),
    make_static_slice( 12, g_bytes + 1306),
    make_static_slice( 21, g_bytes + 1318),
};

static_metadata static_metadata_element_table[HPACK_STATIC_MDELEM_COUNT] = {
    static_metadata(
        make_static_slice( 10, g_bytes + 19),
        make_static_slice( 0, g_bytes + 373),
        0),
    static_metadata(
        make_static_slice( 7, g_bytes + 5),
        make_static_slice( 3, g_bytes + 696),
        1),
    static_metadata(
        make_static_slice( 7, g_bytes + 5),
        make_static_slice( 4, g_bytes + 699),
        2),
    static_metadata(
        make_static_slice( 5, g_bytes + 0),
        make_static_slice( 1, g_bytes + 703),
        3),
    static_metadata(
        make_static_slice( 5, g_bytes + 0),
        make_static_slice( 11,g_bytes + 704),
        4),
    static_metadata(
        make_static_slice( 7, g_bytes + 29),
        make_static_slice( 4, g_bytes + 715),
        5),
    static_metadata(
        make_static_slice( 7, g_bytes + 29),
        make_static_slice( 5, g_bytes + 719),
        6),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 724),
        7),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 727),
        8),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 730),
        9),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 733),
        10),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 736),
        11),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 739),
        12),
    static_metadata(
        make_static_slice( 7, g_bytes + 12),
        make_static_slice( 3, g_bytes + 742),
        13),
    static_metadata(
        make_static_slice( 14,g_bytes + 745),
        make_static_slice( 0, g_bytes + 373),
        14),
    static_metadata(
        make_static_slice( 15,g_bytes + 186),
        make_static_slice( 13,g_bytes + 759),
        15),
    static_metadata(
        make_static_slice( 15, g_bytes + 772),
        make_static_slice( 0, g_bytes + 373),
        16),
    static_metadata(
        make_static_slice( 13, g_bytes + 787),
        make_static_slice( 0, g_bytes + 373),
        17),
    static_metadata(
        make_static_slice( 6, g_bytes + 800),
        make_static_slice( 0, g_bytes + 373),
        18),
    static_metadata(
        make_static_slice( 27, g_bytes + 806),
        make_static_slice( 0, g_bytes + 373),
        19),
    static_metadata(
        make_static_slice( 3, g_bytes + 833),
        make_static_slice( 0, g_bytes + 373),
        20),
    static_metadata(
        make_static_slice( 5, g_bytes + 836),
        make_static_slice( 0, g_bytes + 373),
        21),
    static_metadata(
        make_static_slice( 13, g_bytes + 841),
        make_static_slice( 0, g_bytes + 373),
        22),
    static_metadata(
        make_static_slice( 13, g_bytes + 854),
        make_static_slice( 0, g_bytes + 373),
        23),
    static_metadata(
        make_static_slice( 19, g_bytes + 867),
        make_static_slice( 0, g_bytes + 373),
        24),
    static_metadata(
        make_static_slice( 16,g_bytes + 170),
        make_static_slice( 0, g_bytes + 373),
        25),
    static_metadata(
        make_static_slice( 16, g_bytes + 886),
        make_static_slice( 0, g_bytes + 373),
        26),
    static_metadata(
        make_static_slice( 14, g_bytes + 902),
        make_static_slice( 0, g_bytes + 373),
        27),
    static_metadata(
        make_static_slice( 16, g_bytes + 916),
        make_static_slice( 0, g_bytes + 373),
        28),
    static_metadata(
        make_static_slice( 13,g_bytes + 932),
        make_static_slice( 0, g_bytes + 373),
        29),
    static_metadata(
        make_static_slice( 12, g_bytes + 158),
        make_static_slice( 0, g_bytes + 373),
        30),
    static_metadata(
        make_static_slice( 6, g_bytes + 945),
        make_static_slice( 0, g_bytes + 373),
        31),
    static_metadata(
        make_static_slice( 4, g_bytes + 951),
        make_static_slice( 0, g_bytes + 373),
        32),
    static_metadata(
        make_static_slice( 4, g_bytes + 955),
        make_static_slice( 0, g_bytes + 373),
        33),
    static_metadata(
        make_static_slice( 6, g_bytes + 959),
        make_static_slice( 0, g_bytes + 373),
        34),
    static_metadata(
        make_static_slice( 7, g_bytes + 965),
        make_static_slice( 0, g_bytes + 373),
        35),
    static_metadata(
        make_static_slice( 4, g_bytes + 972),
        make_static_slice( 0, g_bytes + 373),
        36),
    static_metadata(
        make_static_slice( 4, g_bytes + 278),
        make_static_slice( 0, g_bytes + 373),
        37),
    static_metadata(
        make_static_slice( 8, g_bytes + 976),
        make_static_slice( 0, g_bytes + 373),
        38),
    static_metadata(
        make_static_slice( 17, g_bytes + 984),
        make_static_slice( 0, g_bytes + 373),
        39),
    static_metadata(
        make_static_slice( 13, g_bytes + 1001),
        make_static_slice( 0, g_bytes + 373),
        40),
    static_metadata(
        make_static_slice( 8,g_bytes + 1014),
        make_static_slice( 0, g_bytes + 373),
        41),
    static_metadata(
        make_static_slice( 19, g_bytes + 1022),
        make_static_slice( 0, g_bytes + 373),
        42),
    static_metadata(
        make_static_slice( 13, g_bytes + 1041),
        make_static_slice( 0, g_bytes + 373),
        43),
    static_metadata(
        make_static_slice( 4, g_bytes + 1054),
        make_static_slice( 0, g_bytes + 373),
        44),
    static_metadata(
        make_static_slice( 8, g_bytes + 1058),
        make_static_slice( 0, g_bytes + 373),
        45),
    static_metadata(
        make_static_slice( 12, g_bytes + 1066),
        make_static_slice( 0, g_bytes + 373),
        46),
    static_metadata(
        make_static_slice( 18,g_bytes + 1078),
        make_static_slice( 0, g_bytes + 373),
        47),
    static_metadata(
        make_static_slice( 19, g_bytes + 1096),
        make_static_slice( 0, g_bytes + 373),
        48),
    static_metadata(
        make_static_slice( 5, g_bytes + 1115),
        make_static_slice( 0, g_bytes + 373),
        49),
    static_metadata(
        make_static_slice( 7, g_bytes + 1120),
        make_static_slice( 0, g_bytes + 373),
        50),
    static_metadata(
        make_static_slice( 7,g_bytes + 1127),
        make_static_slice( 0, g_bytes + 373),
        51),
    static_metadata(
        make_static_slice( 11, g_bytes + 1134),
        make_static_slice( 0, g_bytes + 373),
        52),
    static_metadata(
        make_static_slice( 6, g_bytes + 1145),
        make_static_slice( 0, g_bytes + 373),
        53),
    static_metadata(
        make_static_slice( 10, g_bytes + 1151),
        make_static_slice( 0, g_bytes + 373),
        54),
    static_metadata(
        make_static_slice( 25,g_bytes + 1161),
        make_static_slice( 0, g_bytes + 373),
        55),
    static_metadata(
        make_static_slice( 17,g_bytes + 1186),
        make_static_slice( 0, g_bytes + 373),
        56),
    static_metadata(
        make_static_slice( 10, g_bytes + 268),
        make_static_slice( 0, g_bytes + 373),
        57),
    static_metadata(
        make_static_slice( 4,g_bytes + 1203),
        make_static_slice( 0, g_bytes + 373),
        58),
    static_metadata(
        make_static_slice( 3,g_bytes + 1207),
        make_static_slice( 0, g_bytes + 373),
        59),
    static_metadata(
        make_static_slice( 16,g_bytes + 1210),
        make_static_slice( 0, g_bytes + 373),
        60),
    static_metadata(
        make_static_slice( 11, g_bytes + 50),
        make_static_slice( 1,g_bytes + 1226),
        61),
    static_metadata(
        make_static_slice( 11, g_bytes + 50),
        make_static_slice( 1, g_bytes + 369),
        62),
    static_metadata(
        make_static_slice( 11, g_bytes + 50),
        make_static_slice( 1, g_bytes + 370),
        63),
    static_metadata(
        make_static_slice( 13, g_bytes + 77),
        make_static_slice( 8,g_bytes + 1227),
        64),
    static_metadata(
        make_static_slice( 13, g_bytes + 77),
        make_static_slice( 4, g_bytes + 681),
        65),
    static_metadata(
        make_static_slice( 13, g_bytes + 77),
        make_static_slice( 7, g_bytes + 674),
        66),
    static_metadata(
        make_static_slice( 2, g_bytes + 36),
        make_static_slice( 8,g_bytes + 1235),
        67),
    static_metadata(
        make_static_slice( 12,g_bytes + 158),
        make_static_slice( 16,g_bytes + 1243),
        68),
    static_metadata(
        make_static_slice( 7, g_bytes + 29),
        make_static_slice( 4,g_bytes + 1259),
        69),
    static_metadata(
        make_static_slice( 7, g_bytes + 5),
        make_static_slice( 3,g_bytes + 1263),
        70),
    static_metadata(
        make_static_slice( 15,g_bytes + 186),
        make_static_slice( 0, g_bytes + 373),
        71),
    static_metadata(
        make_static_slice( 16,g_bytes + 170),
        make_static_slice( 8,g_bytes + 1227),
        72),
    static_metadata(
        make_static_slice( 16,g_bytes + 170),
        make_static_slice( 4, g_bytes + 681),
        73),
    static_metadata(
        make_static_slice( 11,g_bytes + 1266),
        make_static_slice( 0, g_bytes + 373),
        74),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 8,g_bytes + 1227),
        75),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 7, g_bytes + 674),
        76),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 16,g_bytes + 1277),
        77),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 4, g_bytes + 681),
        78),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 13,g_bytes + 1293),
        79),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 12,g_bytes + 1306),
        80),
    static_metadata(
        make_static_slice( 20, g_bytes + 90),
        make_static_slice( 21, g_bytes + 1318),
        81),
    static_metadata(
        make_static_slice( 15,g_bytes + 186),
        make_static_slice( 8,g_bytes + 1227),
        82),
    static_metadata(
        make_static_slice( 15,g_bytes + 186),
        make_static_slice( 4, g_bytes + 681),
        83),
    static_metadata(
        make_static_slice( 15, g_bytes + 186),
        make_static_slice( 13,g_bytes + 1293),
        84),
};

metadata_payload static_metadata_element_payload_table[HPACK_STATIC_MDELEM_COUNT] = {
    // clang-format off
    /* HPACK_MDELEM_AUTHORITY_EMPTY:
        ":authority": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[0].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_GET:
        ":method": "GET" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[1].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_POST:
        ":method": "POST" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[2].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PATH_SLASH:
        ":path": "/" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[3].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PATH_SLASH_INDEX_DOT_HTML:
        ":path": "/index.html" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[4].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_HTTP:
        ":scheme": "http" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[5].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_HTTPS:
        ":scheme": "https" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[6].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_200:
        ":status": "200" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[7].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_204:
        ":status": "204" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[8].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_206:
        ":status": "206" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[9].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_304:
        ":status": "304" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[10].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_400:
        ":status": "400" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[11].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_404:
        ":status": "404" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[12].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_500:
        ":status": "500" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[13].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_CHARSET_EMPTY:
        "accept-charset": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[14].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_GZIP_COMMA_DEFLATE:
        "accept-encoding": "gzip, deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[15].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_LANGUAGE_EMPTY:
        "accept-language": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[16].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_RANGES_EMPTY:
        "accept-ranges": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[17].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_EMPTY:
        "accept": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[18].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCESS_CONTROL_ALLOW_ORIGIN_EMPTY:
        "access-control-allow-origin": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[19].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_AGE_EMPTY:
        "age": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[20].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ALLOW_EMPTY:
        "allow": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[21].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_AUTHORIZATION_EMPTY:
        "authorization": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[22].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CACHE_CONTROL_EMPTY:
        "cache-control": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[23].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_DISPOSITION_EMPTY:
        "content-disposition": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[24].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_EMPTY:
        "content-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[25].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LANGUAGE_EMPTY:
        "content-language": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[26].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LENGTH_EMPTY:
        "content-length": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[27].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LOCATION_EMPTY:
        "content-location": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[28].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_RANGE_EMPTY:
        "content-range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[29].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_TYPE_EMPTY:
        "content-type": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[30].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_COOKIE_EMPTY:
        "cookie": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[31].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_DATE_EMPTY:
        "date": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[32].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ETAG_EMPTY:
        "etag": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[33].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_EXPECT_EMPTY:
        "expect": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[34].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_EXPIRES_EMPTY:
        "expires": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[35].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_FROM_EMPTY:
        "from": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[36].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_HOST_EMPTY:
        "host": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[37].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_MATCH_EMPTY:
        "if-match": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[38].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_MODIFIED_SINCE_EMPTY:
        "if-modified-since": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[39].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_NONE_MATCH_EMPTY:
        "if-none-match": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[40].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_RANGE_EMPTY:
        "if-range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[41].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_UNMODIFIED_SINCE_EMPTY:
        "if-unmodified-since": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[42].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LAST_MODIFIED_EMPTY:
        "last-modified": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[43].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LINK_EMPTY:
        "link": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[44].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LOCATION_EMPTY:
        "location": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[45].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_MAX_FORWARDS_EMPTY:
        "max-forwards": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[46].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PROXY_AUTHENTICATE_EMPTY:
        "proxy-authenticate": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[47].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PROXY_AUTHORIZATION_EMPTY:
        "proxy-authorization": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[48].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_RANGE_EMPTY:
        "range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[49].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_REFERER_EMPTY:
        "referer": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[50].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_REFRESH_EMPTY:
        "refresh": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[51].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_RETRY_AFTER_EMPTY:
        "retry-after": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[52].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SERVER_EMPTY:
        "server": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[53].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SET_COOKIE_EMPTY:
        "set-cookie": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[54].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STRICT_TRANSPORT_SECURITY_EMPTY:
        "strict-transport-security": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[55].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_TRANSFER_ENCODING_EMPTY:
        "transfer-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[56].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_USER_AGENT_EMPTY:
        "user-agent": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[57].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_VARY_EMPTY:
        "vary": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[58].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_VIA_EMPTY:
        "via": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[59].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_WWW_AUTHENTICATE_EMPTY:
        "www-authenticate": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[60].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_0:
        "grpc-status": "0" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[61].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_1:
        "grpc-status": "1" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[62].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_2:
        "grpc-status": "2" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[63].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_IDENTITY:
        "grpc-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[64].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_GZIP:
        "grpc-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[65].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_DEFLATE:
        "grpc-encoding": "deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[66].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_TE_TRAILERS:
        "te": "trailers" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[67].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_TYPE_APPLICATION_SLASH_GRPC:
        "content-type": "application/grpc" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[68].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_GRPC:
        ":scheme": "grpc" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[69].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_PUT:
        ":method": "PUT" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[70].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_EMPTY:
        "accept-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[71].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_IDENTITY:
        "content-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[72].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_GZIP:
        "content-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[73].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LB_COST_BIN_EMPTY:
        "lb-cost-bin": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[74].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY:
        "grpc-accept-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[75].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE:
        "grpc-accept-encoding": "deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[76].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE:
        "grpc-accept-encoding": "identity,deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[77].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_GZIP:
        "grpc-accept-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[78].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP:
        "grpc-accept-encoding": "identity,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[79].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE_COMMA_GZIP:
        "grpc-accept-encoding": "deflate,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[80].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE_COMMA_GZIP:
        "grpc-accept-encoding": "identity,deflate,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[81].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY:
        "accept-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[82].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_GZIP:
        "accept-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[83].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP:
        "accept-encoding": "identity,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_element_table[84].data(),
        METADATA_STORAGE_STATIC)
        // clang-format on
};
}; // struct static_metadata_context

static static_metadata_context* g_static_metadata_slice_ctx = nullptr;
const slice* g_static_metadata_slice_table = nullptr;
static_metadata* g_static_metadata_element_table = nullptr;
metadata_payload* g_static_metadata_element_payload_table = nullptr;
}  // namespace hapck

void init_static_metadata_ctx(void) {
    hpack::g_static_metadata_slice_ctx = new hpack::static_metadata_context();
    hpack::g_static_metadata_slice_table =
        hpack::g_static_metadata_slice_ctx->slices;
    hpack::g_static_metadata_element_table =
        hpack::g_static_metadata_slice_ctx->static_metadata_element_table;
    hpack::g_static_metadata_element_payload_table =
        hpack::g_static_metadata_slice_ctx->static_metadata_element_payload_table;
}

void destroy_static_metadata_ctx(void) {
    delete hpack::g_static_metadata_slice_ctx;
    hpack::g_static_metadata_slice_ctx = nullptr;
    hpack::g_static_metadata_slice_table = nullptr;
    hpack::g_static_metadata_element_table = nullptr;
    hpack::g_static_metadata_element_payload_table = nullptr;
}
