/*
 *
 * (C) COPYRIGHT 2010-2019 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 */

#if !defined(_KBASE_MIPE_PROTO_H)
#define _KBASE_MIPE_PROTO_H

#define _BITFIELD_MASK_FIELD(pos, len) \
	(((1u << len) - 1) << pos)

#define _BITFIELD_SET_FIELD(pos, len, value) \
	(_BITFIELD_MASK_FIELD(pos, len) & (((u32) value) << pos))

#define BITFIELD_SET(field_name, value) \
	_BITFIELD_SET_FIELD(field_name ## _POS, field_name ## _LEN, value)

/* The version of swtrace protocol used in timeline stream. */
#define SWTRACE_VERSION    3

/* Packet header - first word.
 * These values must be defined according to MIPE documentation.
 */
#define PACKET_STREAMID_POS  0
#define PACKET_STREAMID_LEN  8
#define PACKET_RSVD1_POS     (PACKET_STREAMID_POS + PACKET_STREAMID_LEN)
#define PACKET_RSVD1_LEN     8
#define PACKET_TYPE_POS      (PACKET_RSVD1_POS + PACKET_RSVD1_LEN)
#define PACKET_TYPE_LEN      3
#define PACKET_CLASS_POS     (PACKET_TYPE_POS + PACKET_TYPE_LEN)
#define PACKET_CLASS_LEN     7
#define PACKET_FAMILY_POS    (PACKET_CLASS_POS + PACKET_CLASS_LEN)
#define PACKET_FAMILY_LEN    6

/* Packet header - second word
 * These values must be defined according to MIPE documentation.
 */
#define PACKET_LENGTH_POS    0
#define PACKET_LENGTH_LEN    24
#define PACKET_SEQBIT_POS    (PACKET_LENGTH_POS + PACKET_LENGTH_LEN)
#define PACKET_SEQBIT_LEN    1
#define PACKET_RSVD2_POS     (PACKET_SEQBIT_POS + PACKET_SEQBIT_LEN)
#define PACKET_RSVD2_LEN     7

/* First word of a MIPE packet */
#define MIPE_PACKET_HEADER_W0(pkt_family, pkt_class, pkt_type, stream_id) \
	(0                                          \
	| BITFIELD_SET(PACKET_FAMILY,   pkt_family) \
	| BITFIELD_SET(PACKET_CLASS,    pkt_class)  \
	| BITFIELD_SET(PACKET_TYPE,     pkt_type)   \
	| BITFIELD_SET(PACKET_STREAMID, stream_id))

/* Second word of a MIPE packet */
#define MIPE_PACKET_HEADER_W1(packet_length, seqbit) \
	(0                                           \
	| BITFIELD_SET(PACKET_LENGTH, packet_length) \
	| BITFIELD_SET(PACKET_SEQBIT, seqbit))

/* The number of bytes reserved for packet header.
 * These value must be defined according to MIPE documentation.
 */
#define PACKET_HEADER_SIZE 8 /* bytes */

/* The number of bytes reserved for packet sequence number.
 * These value must be defined according to MIPE documentation.
 */
#define PACKET_NUMBER_SIZE 4 /* bytes */

/* Timeline packet family ids.
 * Values are significant! Check MIPE documentation.
 */
enum tl_packet_family {
	TL_PACKET_FAMILY_CTRL = 0, /* control packets */
	TL_PACKET_FAMILY_TL = 1,   /* timeline packets */
	TL_PACKET_FAMILY_COUNT
};

/* Packet classes used in timeline streams.
 * Values are significant! Check MIPE documentation.
 */
enum tl_packet_class {
	TL_PACKET_CLASS_OBJ = 0, /* timeline objects packet */
	TL_PACKET_CLASS_AUX = 1, /* auxiliary events packet */
};

/* Packet types used in timeline streams.
 * Values are significant! Check MIPE documentation.
 */
enum tl_packet_type {
	TL_PACKET_TYPE_HEADER = 0,  /* stream's header/directory */
	TL_PACKET_TYPE_BODY = 1,    /* stream's body */
	TL_PACKET_TYPE_SUMMARY = 2, /* stream's summary */
};

#endif /* _KBASE_MIPE_PROTO_H */

