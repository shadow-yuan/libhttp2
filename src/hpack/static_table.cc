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

/*
 * WARNING: Auto-generated code.
 *
 * To make changes to this file, change
 * tools/codegen/core/gen_static_metadata.py, and then re-run it.
 *
 * See metadata.h for an explanation of the interface here, and metadata.cc for
 * an explanation of what's going on.
 */

#include "src/hpack/static_table.h"

// from gRPC static_metadata table
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

namespace hpack {
struct StaticMetadataCtx {
static_slice_refcount refcounts[HPACK_STATIC_MDSTR_COUNT] = {

    static_slice_refcount(0),   static_slice_refcount(1),
    static_slice_refcount(2),   static_slice_refcount(3),
    static_slice_refcount(4),   static_slice_refcount(5),
    static_slice_refcount(6),   static_slice_refcount(7),
    static_slice_refcount(8),   static_slice_refcount(9),
    static_slice_refcount(10),  static_slice_refcount(11),
    static_slice_refcount(12),  static_slice_refcount(13),
    static_slice_refcount(14),  static_slice_refcount(15),
    static_slice_refcount(16),  static_slice_refcount(17),
    static_slice_refcount(18),  static_slice_refcount(19),
    static_slice_refcount(20),  static_slice_refcount(21),
    static_slice_refcount(22),  static_slice_refcount(23),
    static_slice_refcount(24),  static_slice_refcount(25),
    static_slice_refcount(26),  static_slice_refcount(27),
    static_slice_refcount(28),  static_slice_refcount(29),
    static_slice_refcount(30),  static_slice_refcount(31),
    static_slice_refcount(32),  static_slice_refcount(33),
    static_slice_refcount(34),  static_slice_refcount(35),
    static_slice_refcount(36),  static_slice_refcount(37),
    static_slice_refcount(38),  static_slice_refcount(39),
    static_slice_refcount(40),  static_slice_refcount(41),
    static_slice_refcount(42),  static_slice_refcount(43),
    static_slice_refcount(44),  static_slice_refcount(45),
    static_slice_refcount(46),  static_slice_refcount(47),
    static_slice_refcount(48),  static_slice_refcount(49),
    static_slice_refcount(50),  static_slice_refcount(51),
    static_slice_refcount(52),  static_slice_refcount(53),
    static_slice_refcount(54),  static_slice_refcount(55),
    static_slice_refcount(56),  static_slice_refcount(57),
    static_slice_refcount(58),  static_slice_refcount(59),
    static_slice_refcount(60),  static_slice_refcount(61),
    static_slice_refcount(62),  static_slice_refcount(63),
    static_slice_refcount(64),  static_slice_refcount(65),
    static_slice_refcount(66),  static_slice_refcount(67),
    static_slice_refcount(68),  static_slice_refcount(69),
    static_slice_refcount(70),  static_slice_refcount(71),
    static_slice_refcount(72),  static_slice_refcount(73),
    static_slice_refcount(74),  static_slice_refcount(75),
    static_slice_refcount(76),  static_slice_refcount(77),
    static_slice_refcount(78),  static_slice_refcount(79),
    static_slice_refcount(80),  static_slice_refcount(81),
    static_slice_refcount(82),  static_slice_refcount(83),
    static_slice_refcount(84),  static_slice_refcount(85),
    static_slice_refcount(86),  static_slice_refcount(87),
    static_slice_refcount(88),  static_slice_refcount(89),
    static_slice_refcount(90),  static_slice_refcount(91),
    static_slice_refcount(92),  static_slice_refcount(93),
    static_slice_refcount(94),  static_slice_refcount(95),
    static_slice_refcount(96),  static_slice_refcount(97),
    static_slice_refcount(98),  static_slice_refcount(99),
    static_slice_refcount(100), static_slice_refcount(101),
    static_slice_refcount(102), static_slice_refcount(103),
    static_slice_refcount(104), static_slice_refcount(105),
    static_slice_refcount(106), static_slice_refcount(107),
};

const static_slice slices[HPACK_STATIC_MDSTR_COUNT] = {

    static_slice(&refcounts[0].base, 5, g_bytes + 0),
    static_slice(&refcounts[1].base, 7, g_bytes + 5),
    static_slice(&refcounts[2].base, 7, g_bytes + 12),
    static_slice(&refcounts[3].base, 10, g_bytes + 19),
    static_slice(&refcounts[4].base, 7, g_bytes + 29),
    static_slice(&refcounts[5].base, 2, g_bytes + 36),
    static_slice(&refcounts[6].base, 12, g_bytes + 38),
    static_slice(&refcounts[7].base, 11, g_bytes + 50),
    static_slice(&refcounts[8].base, 16, g_bytes + 61),
    static_slice(&refcounts[9].base, 13, g_bytes + 77),
    static_slice(&refcounts[10].base, 20, g_bytes + 90),
    static_slice(&refcounts[11].base, 21, g_bytes + 110),
    static_slice(&refcounts[12].base, 13, g_bytes + 131),
    static_slice(&refcounts[13].base, 14, g_bytes + 144),
    static_slice(&refcounts[14].base, 12, g_bytes + 158),
    static_slice(&refcounts[15].base, 16, g_bytes + 170),
    static_slice(&refcounts[16].base, 15, g_bytes + 186),
    static_slice(&refcounts[17].base, 30, g_bytes + 201),
    static_slice(&refcounts[18].base, 37, g_bytes + 231),
    static_slice(&refcounts[19].base, 10, g_bytes + 268),
    static_slice(&refcounts[20].base, 4, g_bytes + 278),
    static_slice(&refcounts[21].base, 26, g_bytes + 282),
    static_slice(&refcounts[22].base, 22, g_bytes + 308),
    static_slice(&refcounts[23].base, 27, g_bytes + 330),
    static_slice(&refcounts[24].base, 12, g_bytes + 357),
    static_slice(&refcounts[25].base, 1, g_bytes + 369),
    static_slice(&refcounts[26].base, 1, g_bytes + 370),
    static_slice(&refcounts[27].base, 1, g_bytes + 371),
    static_slice(&refcounts[28].base, 1, g_bytes + 372),
    static_slice(&refcounts[29].base, 0, g_bytes + 373),
    static_slice(&refcounts[30].base, 19, g_bytes + 373),
    static_slice(&refcounts[31].base, 12, g_bytes + 392),
    static_slice(&refcounts[32].base, 30, g_bytes + 404),
    static_slice(&refcounts[33].base, 31, g_bytes + 434),
    static_slice(&refcounts[34].base, 36, g_bytes + 465),
    static_slice(&refcounts[35].base, 65, g_bytes + 501),
    static_slice(&refcounts[36].base, 28, g_bytes + 566),
    static_slice(&refcounts[37].base, 80, g_bytes + 594),
    static_slice(&refcounts[38].base, 7, g_bytes + 674),
    static_slice(&refcounts[39].base, 4, g_bytes + 681),
    static_slice(&refcounts[40].base, 11, g_bytes + 685),
    static_slice(&refcounts[41].base, 3, g_bytes + 696),
    static_slice(&refcounts[42].base, 4, g_bytes + 699),
    static_slice(&refcounts[43].base, 1, g_bytes + 703),
    static_slice(&refcounts[44].base, 11, g_bytes + 704),
    static_slice(&refcounts[45].base, 4, g_bytes + 715),
    static_slice(&refcounts[46].base, 5, g_bytes + 719),
    static_slice(&refcounts[47].base, 3, g_bytes + 724),
    static_slice(&refcounts[48].base, 3, g_bytes + 727),
    static_slice(&refcounts[49].base, 3, g_bytes + 730),
    static_slice(&refcounts[50].base, 3, g_bytes + 733),
    static_slice(&refcounts[51].base, 3, g_bytes + 736),
    static_slice(&refcounts[52].base, 3, g_bytes + 739),
    static_slice(&refcounts[53].base, 3, g_bytes + 742),
    static_slice(&refcounts[54].base, 14, g_bytes + 745),
    static_slice(&refcounts[55].base, 13, g_bytes + 759),
    static_slice(&refcounts[56].base, 15, g_bytes + 772),
    static_slice(&refcounts[57].base, 13, g_bytes + 787),
    static_slice(&refcounts[58].base, 6, g_bytes + 800),
    static_slice(&refcounts[59].base, 27, g_bytes + 806),
    static_slice(&refcounts[60].base, 3, g_bytes + 833),
    static_slice(&refcounts[61].base, 5, g_bytes + 836),
    static_slice(&refcounts[62].base, 13, g_bytes + 841),
    static_slice(&refcounts[63].base, 13, g_bytes + 854),
    static_slice(&refcounts[64].base, 19, g_bytes + 867),
    static_slice(&refcounts[65].base, 16, g_bytes + 886),
    static_slice(&refcounts[66].base, 14, g_bytes + 902),
    static_slice(&refcounts[67].base, 16, g_bytes + 916),
    static_slice(&refcounts[68].base, 13, g_bytes + 932),
    static_slice(&refcounts[69].base, 6, g_bytes + 945),
    static_slice(&refcounts[70].base, 4, g_bytes + 951),
    static_slice(&refcounts[71].base, 4, g_bytes + 955),
    static_slice(&refcounts[72].base, 6, g_bytes + 959),
    static_slice(&refcounts[73].base, 7, g_bytes + 965),
    static_slice(&refcounts[74].base, 4, g_bytes + 972),
    static_slice(&refcounts[75].base, 8, g_bytes + 976),
    static_slice(&refcounts[76].base, 17, g_bytes + 984),
    static_slice(&refcounts[77].base, 13, g_bytes + 1001),
    static_slice(&refcounts[78].base, 8, g_bytes + 1014),
    static_slice(&refcounts[79].base, 19, g_bytes + 1022),
    static_slice(&refcounts[80].base, 13, g_bytes + 1041),
    static_slice(&refcounts[81].base, 4, g_bytes + 1054),
    static_slice(&refcounts[82].base, 8, g_bytes + 1058),
    static_slice(&refcounts[83].base, 12, g_bytes + 1066),
    static_slice(&refcounts[84].base, 18, g_bytes + 1078),
    static_slice(&refcounts[85].base, 19, g_bytes + 1096),
    static_slice(&refcounts[86].base, 5, g_bytes + 1115),
    static_slice(&refcounts[87].base, 7, g_bytes + 1120),
    static_slice(&refcounts[88].base, 7, g_bytes + 1127),
    static_slice(&refcounts[89].base, 11, g_bytes + 1134),
    static_slice(&refcounts[90].base, 6, g_bytes + 1145),
    static_slice(&refcounts[91].base, 10, g_bytes + 1151),
    static_slice(&refcounts[92].base, 25, g_bytes + 1161),
    static_slice(&refcounts[93].base, 17, g_bytes + 1186),
    static_slice(&refcounts[94].base, 4, g_bytes + 1203),
    static_slice(&refcounts[95].base, 3, g_bytes + 1207),
    static_slice(&refcounts[96].base, 16, g_bytes + 1210),
    static_slice(&refcounts[97].base, 1, g_bytes + 1226),
    static_slice(&refcounts[98].base, 8, g_bytes + 1227),
    static_slice(&refcounts[99].base, 8, g_bytes + 1235),
    static_slice(&refcounts[100].base, 16, g_bytes + 1243),
    static_slice(&refcounts[101].base, 4, g_bytes + 1259),
    static_slice(&refcounts[102].base, 3, g_bytes + 1263),
    static_slice(&refcounts[103].base, 11, g_bytes + 1266),
    static_slice(&refcounts[104].base, 16, g_bytes + 1277),
    static_slice(&refcounts[105].base, 13, g_bytes + 1293),
    static_slice(&refcounts[106].base, 12, g_bytes + 1306),
    static_slice(&refcounts[107].base, 21, g_bytes + 1318),
};

static_metadata static_metadata_table[HPACK_STATIC_MDELEM_COUNT] = {
    static_metadata(
        static_slice(&refcounts[3].base, 10, g_bytes + 19),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        0),
    static_metadata(
        static_slice(&refcounts[1].base, 7, g_bytes + 5),
        static_slice(&refcounts[41].base, 3, g_bytes + 696),
        1),
    static_metadata(
        static_slice(&refcounts[1].base, 7, g_bytes + 5),
        static_slice(&refcounts[42].base, 4, g_bytes + 699),
        2),
    static_metadata(
        static_slice(&refcounts[0].base, 5, g_bytes + 0),
        static_slice(&refcounts[43].base, 1, g_bytes + 703),
        3),
    static_metadata(
        static_slice(&refcounts[0].base, 5, g_bytes + 0),
        static_slice(&refcounts[44].base, 11,g_bytes + 704),
        4),
    static_metadata(
        static_slice(&refcounts[4].base, 7, g_bytes + 29),
        static_slice(&refcounts[45].base, 4, g_bytes + 715),
        5),
    static_metadata(
        static_slice(&refcounts[4].base, 7, g_bytes + 29),
        static_slice(&refcounts[46].base, 5, g_bytes + 719),
        6),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[47].base, 3, g_bytes + 724),
        7),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[48].base, 3, g_bytes + 727),
        8),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[49].base, 3, g_bytes + 730),
        9),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[50].base, 3, g_bytes + 733),
        10),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[51].base, 3, g_bytes + 736),
        11),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[52].base, 3, g_bytes + 739),
        12),
    static_metadata(
        static_slice(&refcounts[2].base, 7, g_bytes + 12),
        static_slice(&refcounts[53].base, 3, g_bytes + 742),
        13),
    static_metadata(
        static_slice(&refcounts[54].base, 14,g_bytes + 745),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        14),
    static_metadata(
        static_slice(&refcounts[16].base, 15,g_bytes + 186),
        static_slice(&refcounts[55].base, 13,g_bytes + 759),
        15),
    static_metadata(
        static_slice(&refcounts[56].base, 15, g_bytes + 772),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        16),
    static_metadata(
        static_slice(&refcounts[57].base, 13, g_bytes + 787),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        17),
    static_metadata(
        static_slice(&refcounts[58].base, 6, g_bytes + 800),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        18),
    static_metadata(
        static_slice(&refcounts[59].base, 27, g_bytes + 806),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        19),
    static_metadata(
        static_slice(&refcounts[60].base, 3, g_bytes + 833),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        20),
    static_metadata(
        static_slice(&refcounts[61].base, 5, g_bytes + 836),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        21),
    static_metadata(
        static_slice(&refcounts[62].base, 13, g_bytes + 841),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        22),
    static_metadata(
        static_slice(&refcounts[63].base, 13, g_bytes + 854),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        23),
    static_metadata(
        static_slice(&refcounts[64].base, 19, g_bytes + 867),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        24),
    static_metadata(
        static_slice(&refcounts[15].base, 16,g_bytes + 170),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        25),
    static_metadata(
        static_slice(&refcounts[65].base, 16, g_bytes + 886),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        26),
    static_metadata(
        static_slice(&refcounts[66].base, 14, g_bytes + 902),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        27),
    static_metadata(
        static_slice(&refcounts[67].base, 16, g_bytes + 916),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        28),
    static_metadata(
        static_slice(&refcounts[68].base, 13,g_bytes + 932),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        29),
    static_metadata(
        static_slice(&refcounts[14].base, 12, g_bytes + 158),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        30),
    static_metadata(
        static_slice(&refcounts[69].base, 6, g_bytes + 945),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        31),
    static_metadata(
        static_slice(&refcounts[70].base, 4, g_bytes + 951),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        32),
    static_metadata(
        static_slice(&refcounts[71].base, 4, g_bytes + 955),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        33),
    static_metadata(
        static_slice(&refcounts[72].base, 6, g_bytes + 959),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        34),
    static_metadata(
        static_slice(&refcounts[73].base, 7, g_bytes + 965),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        35),
    static_metadata(
        static_slice(&refcounts[74].base, 4, g_bytes + 972),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        36),
    static_metadata(
        static_slice(&refcounts[20].base, 4, g_bytes + 278),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        37),
    static_metadata(
        static_slice(&refcounts[75].base, 8, g_bytes + 976),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        38),
    static_metadata(
        static_slice(&refcounts[76].base, 17, g_bytes + 984),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        39),
    static_metadata(
        static_slice(&refcounts[77].base, 13, g_bytes + 1001),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        40),
    static_metadata(
        static_slice(&refcounts[78].base, 8,g_bytes + 1014),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        41),
    static_metadata(
        static_slice(&refcounts[79].base, 19, g_bytes + 1022),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        42),
    static_metadata(
        static_slice(&refcounts[80].base, 13, g_bytes + 1041),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        43),
    static_metadata(
        static_slice(&refcounts[81].base, 4, g_bytes + 1054),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        44),
    static_metadata(
        static_slice(&refcounts[82].base, 8, g_bytes + 1058),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        45),
    static_metadata(
        static_slice(&refcounts[83].base, 12, g_bytes + 1066),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        46),
    static_metadata(
        static_slice(&refcounts[84].base, 18,g_bytes + 1078),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        47),
    static_metadata(
        static_slice(&refcounts[85].base, 19, g_bytes + 1096),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        48),
    static_metadata(
        static_slice(&refcounts[86].base, 5, g_bytes + 1115),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        49),
    static_metadata(
        static_slice(&refcounts[87].base, 7, g_bytes + 1120),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        50),
    static_metadata(
        static_slice(&refcounts[88].base, 7,g_bytes + 1127),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        51),
    static_metadata(
        static_slice(&refcounts[89].base, 11, g_bytes + 1134),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        52),
    static_metadata(
        static_slice(&refcounts[90].base, 6, g_bytes + 1145),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        53),
    static_metadata(
        static_slice(&refcounts[91].base, 10, g_bytes + 1151),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        54),
    static_metadata(
        static_slice(&refcounts[92].base, 25,g_bytes + 1161),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        55),
    static_metadata(
        static_slice(&refcounts[93].base, 17,g_bytes + 1186),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        56),
    static_metadata(
        static_slice(&refcounts[19].base, 10, g_bytes + 268),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        57),
    static_metadata(
        static_slice(&refcounts[94].base, 4,g_bytes + 1203),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        58),
    static_metadata(
        static_slice(&refcounts[95].base, 3,g_bytes + 1207),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        59),
    static_metadata(
        static_slice(&refcounts[96].base, 16,g_bytes + 1210),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        60),
    static_metadata(
        static_slice(&refcounts[7].base, 11, g_bytes + 50),
        static_slice(&refcounts[97].base, 1,g_bytes + 1226),
        61),
    static_metadata(
        static_slice(&refcounts[7].base, 11, g_bytes + 50),
        static_slice(&refcounts[25].base, 1, g_bytes + 369),
        62),
    static_metadata(
        static_slice(&refcounts[7].base, 11, g_bytes + 50),
        static_slice(&refcounts[26].base, 1, g_bytes + 370),
        63),
    static_metadata(
        static_slice(&refcounts[9].base, 13, g_bytes + 77),
        static_slice(&refcounts[98].base, 8,g_bytes + 1227),
        64),
    static_metadata(
        static_slice(&refcounts[9].base, 13, g_bytes + 77),
        static_slice(&refcounts[39].base, 4, g_bytes + 681),
        65),
    static_metadata(
        static_slice(&refcounts[9].base, 13, g_bytes + 77),
        static_slice(&refcounts[38].base, 7, g_bytes + 674),
        66),
    static_metadata(
        static_slice(&refcounts[5].base, 2, g_bytes + 36),
        static_slice(&refcounts[99].base, 8,g_bytes + 1235),
        67),
    static_metadata(
        static_slice(&refcounts[14].base, 12,g_bytes + 158),
        static_slice(&refcounts[100].base, 16,g_bytes + 1243),
        68),
    static_metadata(
        static_slice(&refcounts[4].base, 7, g_bytes + 29),
        static_slice(&refcounts[101].base, 4,g_bytes + 1259),
        69),
    static_metadata(
        static_slice(&refcounts[1].base, 7, g_bytes + 5),
        static_slice(&refcounts[102].base, 3,g_bytes + 1263),
        70),
    static_metadata(
        static_slice(&refcounts[16].base, 15,g_bytes + 186),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        71),
    static_metadata(
        static_slice(&refcounts[15].base, 16,g_bytes + 170),
        static_slice(&refcounts[98].base, 8,g_bytes + 1227),
        72),
    static_metadata(
        static_slice(&refcounts[15].base, 16,g_bytes + 170),
        static_slice(&refcounts[39].base, 4, g_bytes + 681),
        73),
    static_metadata(
        static_slice(&refcounts[103].base, 11,g_bytes + 1266),
        static_slice(&refcounts[29].base, 0, g_bytes + 373),
        74),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[98].base, 8,g_bytes + 1227),
        75),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[38].base, 7, g_bytes + 674),
        76),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[104].base, 16,g_bytes + 1277),
        77),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[39].base, 4, g_bytes + 681),
        78),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[105].base, 13,g_bytes + 1293),
        79),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[106].base, 12,g_bytes + 1306),
        80),
    static_metadata(
        static_slice(&refcounts[10].base, 20, g_bytes + 90),
        static_slice(&refcounts[107].base, 21, g_bytes + 1318),
        81),
    static_metadata(
        static_slice(&refcounts[16].base, 15,g_bytes + 186),
        static_slice(&refcounts[98].base, 8,g_bytes + 1227),
        82),
    static_metadata(
        static_slice(&refcounts[16].base, 15,g_bytes + 186),
        static_slice(&refcounts[39].base, 4, g_bytes + 681),
        83),
    static_metadata(
        static_slice(&refcounts[16].base, 15, g_bytes + 186),
        static_slice(&refcounts[105].base, 13,g_bytes + 1293),
        84),
};

metadata_payload static_metadata_payload[HPACK_STATIC_MDELEM_COUNT] = {
    // clang-format off
    /* HPACK_MDELEM_AUTHORITY_EMPTY:
        ":authority": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[0].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_GET:
        ":method": "GET" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[1].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_POST:
        ":method": "POST" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[2].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PATH_SLASH:
        ":path": "/" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[3].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PATH_SLASH_INDEX_DOT_HTML:
        ":path": "/index.html" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[4].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_HTTP:
        ":scheme": "http" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[5].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_HTTPS:
        ":scheme": "https" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[6].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_200:
        ":status": "200" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[7].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_204:
        ":status": "204" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[8].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_206:
        ":status": "206" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[9].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_304:
        ":status": "304" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[10].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_400:
        ":status": "400" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[11].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_404:
        ":status": "404" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[12].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STATUS_500:
        ":status": "500" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[13].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_CHARSET_EMPTY:
        "accept-charset": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[14].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_GZIP_COMMA_DEFLATE:
        "accept-encoding": "gzip, deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[15].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_LANGUAGE_EMPTY:
        "accept-language": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[16].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_RANGES_EMPTY:
        "accept-ranges": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[17].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_EMPTY:
        "accept": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[18].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCESS_CONTROL_ALLOW_ORIGIN_EMPTY:
        "access-control-allow-origin": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[19].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_AGE_EMPTY:
        "age": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[20].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ALLOW_EMPTY:
        "allow": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[21].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_AUTHORIZATION_EMPTY:
        "authorization": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[22].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CACHE_CONTROL_EMPTY:
        "cache-control": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[23].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_DISPOSITION_EMPTY:
        "content-disposition": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[24].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_EMPTY:
        "content-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[25].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LANGUAGE_EMPTY:
        "content-language": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[26].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LENGTH_EMPTY:
        "content-length": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[27].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_LOCATION_EMPTY:
        "content-location": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[28].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_RANGE_EMPTY:
        "content-range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[29].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_TYPE_EMPTY:
        "content-type": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[30].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_COOKIE_EMPTY:
        "cookie": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[31].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_DATE_EMPTY:
        "date": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[32].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ETAG_EMPTY:
        "etag": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[33].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_EXPECT_EMPTY:
        "expect": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[34].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_EXPIRES_EMPTY:
        "expires": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[35].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_FROM_EMPTY:
        "from": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[36].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_HOST_EMPTY:
        "host": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[37].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_MATCH_EMPTY:
        "if-match": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[38].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_MODIFIED_SINCE_EMPTY:
        "if-modified-since": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[39].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_NONE_MATCH_EMPTY:
        "if-none-match": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[40].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_RANGE_EMPTY:
        "if-range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[41].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_IF_UNMODIFIED_SINCE_EMPTY:
        "if-unmodified-since": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[42].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LAST_MODIFIED_EMPTY:
        "last-modified": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[43].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LINK_EMPTY:
        "link": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[44].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LOCATION_EMPTY:
        "location": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[45].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_MAX_FORWARDS_EMPTY:
        "max-forwards": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[46].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PROXY_AUTHENTICATE_EMPTY:
        "proxy-authenticate": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[47].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_PROXY_AUTHORIZATION_EMPTY:
        "proxy-authorization": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[48].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_RANGE_EMPTY:
        "range": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[49].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_REFERER_EMPTY:
        "referer": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[50].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_REFRESH_EMPTY:
        "refresh": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[51].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_RETRY_AFTER_EMPTY:
        "retry-after": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[52].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SERVER_EMPTY:
        "server": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[53].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SET_COOKIE_EMPTY:
        "set-cookie": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[54].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_STRICT_TRANSPORT_SECURITY_EMPTY:
        "strict-transport-security": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[55].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_TRANSFER_ENCODING_EMPTY:
        "transfer-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[56].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_USER_AGENT_EMPTY:
        "user-agent": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[57].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_VARY_EMPTY:
        "vary": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[58].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_VIA_EMPTY:
        "via": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[59].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_WWW_AUTHENTICATE_EMPTY:
        "www-authenticate": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[60].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_0:
        "grpc-status": "0" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[61].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_1:
        "grpc-status": "1" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[62].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_STATUS_2:
        "grpc-status": "2" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[63].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_IDENTITY:
        "grpc-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[64].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_GZIP:
        "grpc-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[65].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ENCODING_DEFLATE:
        "grpc-encoding": "deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[66].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_TE_TRAILERS:
        "te": "trailers" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[67].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_TYPE_APPLICATION_SLASH_GRPC:
        "content-type": "application/grpc" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[68].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_SCHEME_GRPC:
        ":scheme": "grpc" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[69].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_METHOD_PUT:
        ":method": "PUT" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[70].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_EMPTY:
        "accept-encoding": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[71].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_IDENTITY:
        "content-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[72].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_CONTENT_ENCODING_GZIP:
        "content-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[73].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_LB_COST_BIN_EMPTY:
        "lb-cost-bin": "" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[74].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY:
        "grpc-accept-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[75].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE:
        "grpc-accept-encoding": "deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[76].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE:
        "grpc-accept-encoding": "identity,deflate" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[77].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_GZIP:
        "grpc-accept-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[78].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP:
        "grpc-accept-encoding": "identity,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[79].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE_COMMA_GZIP:
        "grpc-accept-encoding": "deflate,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[80].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE_COMMA_GZIP:
        "grpc-accept-encoding": "identity,deflate,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[81].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY:
        "accept-encoding": "identity" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[82].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_GZIP:
        "accept-encoding": "gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[83].data(),
        METADATA_STORAGE_STATIC),
    /* HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP:
        "accept-encoding": "identity,gzip" */
    MAKE_METADATA_PAYLOAD(
        &static_metadata_table[84].data(),
        METADATA_STORAGE_STATIC)
        // clang-format on
};
}; // struct StaticMetadataCtx

static StaticMetadataCtx* g_static_metadata_slice_ctx = nullptr;
const static_slice* g_static_metadata_slice_table = nullptr;
static_slice_refcount* g_static_metadata_slice_refcounts = nullptr;
static_metadata* g_static_metadata_table = nullptr;
metadata_payload* g_static_metadata_payload = nullptr;
}  // namespace hapck

void init_static_metadata_ctx(void) {
    hpack::g_static_metadata_slice_ctx = new hpack::StaticMetadataCtx();
    hpack::g_static_metadata_slice_table =
        hpack::g_static_metadata_slice_ctx->slices;
    hpack::g_static_metadata_slice_refcounts =
        hpack::g_static_metadata_slice_ctx->refcounts;
    hpack::g_static_metadata_table =
        hpack::g_static_metadata_slice_ctx->static_metadata_table;
    hpack::g_static_metadata_payload =
        hpack::g_static_metadata_slice_ctx->static_metadata_payload;
}

void destroy_static_metadata_ctx(void) {
    delete hpack::g_static_metadata_slice_ctx;
    hpack::g_static_metadata_slice_ctx = nullptr;
    hpack::g_static_metadata_slice_table = nullptr;
    hpack::g_static_metadata_slice_refcounts = nullptr;
    hpack::g_static_metadata_table = nullptr;
    hpack::g_static_metadata_payload = nullptr;
}
