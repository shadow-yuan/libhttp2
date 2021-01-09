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

#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "src/utils/slice.h"
#include "src/hpack/metadata.h"

#define HPACK_STATIC_MDSTR_COUNT 108
#define HPACK_STATIC_MDELEM_COUNT 85

typedef enum {
    METADATA_STORAGE_EXTERNAL = 0,
    METADATA_STORAGE_STATIC = 1,
    METADATA_STORAGE_ALLOCATED = 2,
} metadata_storage_type;

typedef struct {
    uintptr_t payload;
} metadata_payload;

#ifdef __cplusplus
#define MAKE_METADATA_PAYLOAD(data, storage) \
    (metadata_payload{((uintptr_t)(data)) | ((uintptr_t)storage)})
#else
#define MAKE_METADATA_PAYLOAD(data, storage) \
    ((metadata_payload){((uintptr_t)(data)) | ((uintptr_t)storage)})
#endif

namespace hpack {
extern const static_slice* g_static_metadata_slice_table;
extern static_metadata* g_static_metadata_table;
extern metadata_payload* g_static_metadata_payload;
}  // namespace hpack

void init_static_metadata_ctx(void);
void destroy_static_metadata_ctx(void);

// get every slice
inline const static_slice* get_static_slice_table() {
    assert(hpack::g_static_metadata_slice_table != nullptr);
    return hpack::g_static_metadata_slice_table;
}
// get key-value pair
inline hpack::static_metadata* get_static_metadata_table() {
    assert(hpack::g_static_metadata_table != nullptr);
    return hpack::g_static_metadata_table;
}

// get key-value pair payload
inline metadata_payload* get_static_metadata_payload() {
    assert(hpack::g_static_metadata_payload != nullptr);
    return hpack::g_static_metadata_payload;
}

// --------- slice ---------
/* ":path" */
#define HPACK_MDSTR_PATH (get_static_slice_table()[0])
/* ":method" */
#define HPACK_MDSTR_METHOD (get_static_slice_table()[1])
/* ":status" */
#define HPACK_MDSTR_STATUS (get_static_slice_table()[2])
/* ":authority" */
#define HPACK_MDSTR_AUTHORITY (get_static_slice_table()[3])
/* ":scheme" */
#define HPACK_MDSTR_SCHEME (get_static_slice_table()[4])
/* "te" */
#define HPACK_MDSTR_TE (get_static_slice_table()[5])
/* "grpc-message" */
#define HPACK_MDSTR_GRPC_MESSAGE (get_static_slice_table()[6])
/* "grpc-status" */
#define HPACK_MDSTR_GRPC_STATUS (get_static_slice_table()[7])
/* "grpc-payload-bin" */
#define HPACK_MDSTR_GRPC_PAYLOAD_BIN (get_static_slice_table()[8])
/* "grpc-encoding" */
#define HPACK_MDSTR_GRPC_ENCODING (get_static_slice_table()[9])
/* "grpc-accept-encoding" */
#define HPACK_MDSTR_GRPC_ACCEPT_ENCODING (get_static_slice_table()[10])
/* "grpc-server-stats-bin" */
#define HPACK_MDSTR_GRPC_SERVER_STATS_BIN (get_static_slice_table()[11])
/* "grpc-tags-bin" */
#define HPACK_MDSTR_GRPC_TAGS_BIN (get_static_slice_table()[12])
/* "grpc-trace-bin" */
#define HPACK_MDSTR_GRPC_TRACE_BIN (get_static_slice_table()[13])
/* "content-type" */
#define HPACK_MDSTR_CONTENT_TYPE (get_static_slice_table()[14])
/* "content-encoding" */
#define HPACK_MDSTR_CONTENT_ENCODING (get_static_slice_table()[15])
/* "accept-encoding" */
#define HPACK_MDSTR_ACCEPT_ENCODING (get_static_slice_table()[16])
/* "grpc-internal-encoding-request" */
#define HPACK_MDSTR_GRPC_INTERNAL_ENCODING_REQUEST \
  (get_static_slice_table()[17])
/* "grpc-internal-stream-encoding-request" */
#define HPACK_MDSTR_GRPC_INTERNAL_STREAM_ENCODING_REQUEST \
  (get_static_slice_table()[18])
/* "user-agent" */
#define HPACK_MDSTR_USER_AGENT (get_static_slice_table()[19])
/* "host" */
#define HPACK_MDSTR_HOST (get_static_slice_table()[20])
/* "grpc-previous-rpc-attempts" */
#define HPACK_MDSTR_GRPC_PREVIOUS_RPC_ATTEMPTS (get_static_slice_table()[21])
/* "grpc-retry-pushback-ms" */
#define HPACK_MDSTR_GRPC_RETRY_PUSHBACK_MS (get_static_slice_table()[22])
/* "x-endpoint-load-metrics-bin" */
#define HPACK_MDSTR_X_ENDPOINT_LOAD_METRICS_BIN (get_static_slice_table()[23])
/* "grpc-timeout" */
#define HPACK_MDSTR_GRPC_TIMEOUT (get_static_slice_table()[24])
/* "1" */
#define HPACK_MDSTR_1 (get_static_slice_table()[25])
/* "2" */
#define HPACK_MDSTR_2 (get_static_slice_table()[26])
/* "3" */
#define HPACK_MDSTR_3 (get_static_slice_table()[27])
/* "4" */
#define HPACK_MDSTR_4 (get_static_slice_table()[28])
/* "" */
#define HPACK_MDSTR_EMPTY (get_static_slice_table()[29])
/* "grpc.wait_for_ready" */
#define HPACK_MDSTR_GRPC_DOT_WAIT_FOR_READY (get_static_slice_table()[30])
/* "grpc.timeout" */
#define HPACK_MDSTR_GRPC_DOT_TIMEOUT (get_static_slice_table()[31])
/* "grpc.max_request_message_bytes" */
#define HPACK_MDSTR_GRPC_DOT_MAX_REQUEST_MESSAGE_BYTES \
  (get_static_slice_table()[32])
/* "grpc.max_response_message_bytes" */
#define HPACK_MDSTR_GRPC_DOT_MAX_RESPONSE_MESSAGE_BYTES \
  (get_static_slice_table()[33])
/* "/grpc.lb.v1.LoadBalancer/BalanceLoad" */
#define HPACK_MDSTR_SLASH_GRPC_DOT_LB_DOT_V1_DOT_LOADBALANCER_SLASH_BALANCELOAD \
  (get_static_slice_table()[34])
/* "/envoy.service.load_stats.v2.LoadReportingService/StreamLoadStats" */
#define HPACK_MDSTR_SLASH_ENVOY_DOT_SERVICE_DOT_LOAD_STATS_DOT_V2_DOT_LOADREPORTINGSERVICE_SLASH_STREAMLOADSTATS \
  (get_static_slice_table()[35])
/* "/grpc.health.v1.Health/Watch" */
#define HPACK_MDSTR_SLASH_GRPC_DOT_HEALTH_DOT_V1_DOT_HEALTH_SLASH_WATCH \
  (get_static_slice_table()[36])
/* "/envoy.service.discovery.v2.AggregatedDiscoveryService/StreamAggregatedResources"
 */
#define HPACK_MDSTR_SLASH_ENVOY_DOT_SERVICE_DOT_DISCOVERY_DOT_V2_DOT_AGGREGATEDDISCOVERYSERVICE_SLASH_STREAMAGGREGATEDRESOURCES \
  (get_static_slice_table()[37])
/* "deflate" */
#define HPACK_MDSTR_DEFLATE (get_static_slice_table()[38])
/* "gzip" */
#define HPACK_MDSTR_GZIP (get_static_slice_table()[39])
/* "stream/gzip" */
#define HPACK_MDSTR_STREAM_SLASH_GZIP (get_static_slice_table()[40])
/* "GET" */
#define HPACK_MDSTR_GET (get_static_slice_table()[41])
/* "POST" */
#define HPACK_MDSTR_POST (get_static_slice_table()[42])
/* "/" */
#define HPACK_MDSTR_SLASH (get_static_slice_table()[43])
/* "/index.html" */
#define HPACK_MDSTR_SLASH_INDEX_DOT_HTML (get_static_slice_table()[44])
/* "http" */
#define HPACK_MDSTR_HTTP (get_static_slice_table()[45])
/* "https" */
#define HPACK_MDSTR_HTTPS (get_static_slice_table()[46])
/* "200" */
#define HPACK_MDSTR_200 (get_static_slice_table()[47])
/* "204" */
#define HPACK_MDSTR_204 (get_static_slice_table()[48])
/* "206" */
#define HPACK_MDSTR_206 (get_static_slice_table()[49])
/* "304" */
#define HPACK_MDSTR_304 (get_static_slice_table()[50])
/* "400" */
#define HPACK_MDSTR_400 (get_static_slice_table()[51])
/* "404" */
#define HPACK_MDSTR_404 (get_static_slice_table()[52])
/* "500" */
#define HPACK_MDSTR_500 (get_static_slice_table()[53])
/* "accept-charset" */
#define HPACK_MDSTR_ACCEPT_CHARSET (get_static_slice_table()[54])
/* "gzip, deflate" */
#define HPACK_MDSTR_GZIP_COMMA_DEFLATE (get_static_slice_table()[55])
/* "accept-language" */
#define HPACK_MDSTR_ACCEPT_LANGUAGE (get_static_slice_table()[56])
/* "accept-ranges" */
#define HPACK_MDSTR_ACCEPT_RANGES (get_static_slice_table()[57])
/* "accept" */
#define HPACK_MDSTR_ACCEPT (get_static_slice_table()[58])
/* "access-control-allow-origin" */
#define HPACK_MDSTR_ACCESS_CONTROL_ALLOW_ORIGIN (get_static_slice_table()[59])
/* "age" */
#define HPACK_MDSTR_AGE (get_static_slice_table()[60])
/* "allow" */
#define HPACK_MDSTR_ALLOW (get_static_slice_table()[61])
/* "authorization" */
#define HPACK_MDSTR_AUTHORIZATION (get_static_slice_table()[62])
/* "cache-control" */
#define HPACK_MDSTR_CACHE_CONTROL (get_static_slice_table()[63])
/* "content-disposition" */
#define HPACK_MDSTR_CONTENT_DISPOSITION (get_static_slice_table()[64])
/* "content-language" */
#define HPACK_MDSTR_CONTENT_LANGUAGE (get_static_slice_table()[65])
/* "content-length" */
#define HPACK_MDSTR_CONTENT_LENGTH (get_static_slice_table()[66])
/* "content-location" */
#define HPACK_MDSTR_CONTENT_LOCATION (get_static_slice_table()[67])
/* "content-range" */
#define HPACK_MDSTR_CONTENT_RANGE (get_static_slice_table()[68])
/* "cookie" */
#define HPACK_MDSTR_COOKIE (get_static_slice_table()[69])
/* "date" */
#define HPACK_MDSTR_DATE (get_static_slice_table()[70])
/* "etag" */
#define HPACK_MDSTR_ETAG (get_static_slice_table()[71])
/* "expect" */
#define HPACK_MDSTR_EXPECT (get_static_slice_table()[72])
/* "expires" */
#define HPACK_MDSTR_EXPIRES (get_static_slice_table()[73])
/* "from" */
#define HPACK_MDSTR_FROM (get_static_slice_table()[74])
/* "if-match" */
#define HPACK_MDSTR_IF_MATCH (get_static_slice_table()[75])
/* "if-modified-since" */
#define HPACK_MDSTR_IF_MODIFIED_SINCE (get_static_slice_table()[76])
/* "if-none-match" */
#define HPACK_MDSTR_IF_NONE_MATCH (get_static_slice_table()[77])
/* "if-range" */
#define HPACK_MDSTR_IF_RANGE (get_static_slice_table()[78])
/* "if-unmodified-since" */
#define HPACK_MDSTR_IF_UNMODIFIED_SINCE (get_static_slice_table()[79])
/* "last-modified" */
#define HPACK_MDSTR_LAST_MODIFIED (get_static_slice_table()[80])
/* "link" */
#define HPACK_MDSTR_LINK (get_static_slice_table()[81])
/* "location" */
#define HPACK_MDSTR_LOCATION (get_static_slice_table()[82])
/* "max-forwards" */
#define HPACK_MDSTR_MAX_FORWARDS (get_static_slice_table()[83])
/* "proxy-authenticate" */
#define HPACK_MDSTR_PROXY_AUTHENTICATE (get_static_slice_table()[84])
/* "proxy-authorization" */
#define HPACK_MDSTR_PROXY_AUTHORIZATION (get_static_slice_table()[85])
/* "range" */
#define HPACK_MDSTR_RANGE (get_static_slice_table()[86])
/* "referer" */
#define HPACK_MDSTR_REFERER (get_static_slice_table()[87])
/* "refresh" */
#define HPACK_MDSTR_REFRESH (get_static_slice_table()[88])
/* "retry-after" */
#define HPACK_MDSTR_RETRY_AFTER (get_static_slice_table()[89])
/* "server" */
#define HPACK_MDSTR_SERVER (get_static_slice_table()[90])
/* "set-cookie" */
#define HPACK_MDSTR_SET_COOKIE (get_static_slice_table()[91])
/* "strict-transport-security" */
#define HPACK_MDSTR_STRICT_TRANSPORT_SECURITY (get_static_slice_table()[92])
/* "transfer-encoding" */
#define HPACK_MDSTR_TRANSFER_ENCODING (get_static_slice_table()[93])
/* "vary" */
#define HPACK_MDSTR_VARY (get_static_slice_table()[94])
/* "via" */
#define HPACK_MDSTR_VIA (get_static_slice_table()[95])
/* "www-authenticate" */
#define HPACK_MDSTR_WWW_AUTHENTICATE (get_static_slice_table()[96])
/* "0" */
#define HPACK_MDSTR_0 (get_static_slice_table()[97])
/* "identity" */
#define HPACK_MDSTR_IDENTITY (get_static_slice_table()[98])
/* "trailers" */
#define HPACK_MDSTR_TRAILERS (get_static_slice_table()[99])
/* "application/grpc" */
#define HPACK_MDSTR_APPLICATION_SLASH_GRPC (get_static_slice_table()[100])
/* "grpc" */
#define HPACK_MDSTR_GRPC (get_static_slice_table()[101])
/* "PUT" */
#define HPACK_MDSTR_PUT (get_static_slice_table()[102])
/* "lb-cost-bin" */
#define HPACK_MDSTR_LB_COST_BIN (get_static_slice_table()[103])
/* "identity,deflate" */
#define HPACK_MDSTR_IDENTITY_COMMA_DEFLATE (get_static_slice_table()[104])
/* "identity,gzip" */
#define HPACK_MDSTR_IDENTITY_COMMA_GZIP (get_static_slice_table()[105])
/* "deflate,gzip" */
#define HPACK_MDSTR_DEFLATE_COMMA_GZIP (get_static_slice_table()[106])
/* "identity,deflate,gzip" */
#define HPACK_MDSTR_IDENTITY_COMMA_DEFLATE_COMMA_GZIP \
  (get_static_slice_table()[107])

// --------- key : value ---------

/* ":authority": "" */
#define HPACK_MDELEM_AUTHORITY_EMPTY (get_static_metadata_payload()[0])
/* ":method": "GET" */
#define HPACK_MDELEM_METHOD_GET (get_static_metadata_payload()[1])
/* ":method": "POST" */
#define HPACK_MDELEM_METHOD_POST (get_static_metadata_payload()[2])
/* ":path": "/" */
#define HPACK_MDELEM_PATH_SLASH (get_static_metadata_payload()[3])
/* ":path": "/index.html" */
#define HPACK_MDELEM_PATH_SLASH_INDEX_DOT_HTML \
  (get_static_metadata_payload()[4])
/* ":scheme": "http" */
#define HPACK_MDELEM_SCHEME_HTTP (get_static_metadata_payload()[5])
/* ":scheme": "https" */
#define HPACK_MDELEM_SCHEME_HTTPS (get_static_metadata_payload()[6])
/* ":status": "200" */
#define HPACK_MDELEM_STATUS_200 (get_static_metadata_payload()[7])
/* ":status": "204" */
#define HPACK_MDELEM_STATUS_204 (get_static_metadata_payload()[8])
/* ":status": "206" */
#define HPACK_MDELEM_STATUS_206 (get_static_metadata_payload()[9])
/* ":status": "304" */
#define HPACK_MDELEM_STATUS_304 (get_static_metadata_payload()[10])
/* ":status": "400" */
#define HPACK_MDELEM_STATUS_400 (get_static_metadata_payload()[11])
/* ":status": "404" */
#define HPACK_MDELEM_STATUS_404 (get_static_metadata_payload()[12])
/* ":status": "500" */
#define HPACK_MDELEM_STATUS_500 (get_static_metadata_payload()[13])
/* "accept-charset": "" */
#define HPACK_MDELEM_ACCEPT_CHARSET_EMPTY (get_static_metadata_payload()[14])
/* "accept-encoding": "gzip, deflate" */
#define HPACK_MDELEM_ACCEPT_ENCODING_GZIP_COMMA_DEFLATE \
  (get_static_metadata_payload()[15])
/* "accept-language": "" */
#define HPACK_MDELEM_ACCEPT_LANGUAGE_EMPTY (get_static_metadata_payload()[16])
/* "accept-ranges": "" */
#define HPACK_MDELEM_ACCEPT_RANGES_EMPTY (get_static_metadata_payload()[17])
/* "accept": "" */
#define HPACK_MDELEM_ACCEPT_EMPTY (get_static_metadata_payload()[18])
/* "access-control-allow-origin": "" */
#define HPACK_MDELEM_ACCESS_CONTROL_ALLOW_ORIGIN_EMPTY \
  (get_static_metadata_payload()[19])
/* "age": "" */
#define HPACK_MDELEM_AGE_EMPTY (get_static_metadata_payload()[20])
/* "allow": "" */
#define HPACK_MDELEM_ALLOW_EMPTY (get_static_metadata_payload()[21])
/* "authorization": "" */
#define HPACK_MDELEM_AUTHORIZATION_EMPTY (get_static_metadata_payload()[22])
/* "cache-control": "" */
#define HPACK_MDELEM_CACHE_CONTROL_EMPTY (get_static_metadata_payload()[23])
/* "content-disposition": "" */
#define HPACK_MDELEM_CONTENT_DISPOSITION_EMPTY \
  (get_static_metadata_payload()[24])
/* "content-encoding": "" */
#define HPACK_MDELEM_CONTENT_ENCODING_EMPTY (get_static_metadata_payload()[25])
/* "content-language": "" */
#define HPACK_MDELEM_CONTENT_LANGUAGE_EMPTY (get_static_metadata_payload()[26])
/* "content-length": "" */
#define HPACK_MDELEM_CONTENT_LENGTH_EMPTY (get_static_metadata_payload()[27])
/* "content-location": "" */
#define HPACK_MDELEM_CONTENT_LOCATION_EMPTY (get_static_metadata_payload()[28])
/* "content-range": "" */
#define HPACK_MDELEM_CONTENT_RANGE_EMPTY (get_static_metadata_payload()[29])
/* "content-type": "" */
#define HPACK_MDELEM_CONTENT_TYPE_EMPTY (get_static_metadata_payload()[30])
/* "cookie": "" */
#define HPACK_MDELEM_COOKIE_EMPTY (get_static_metadata_payload()[31])
/* "date": "" */
#define HPACK_MDELEM_DATE_EMPTY (get_static_metadata_payload()[32])
/* "etag": "" */
#define HPACK_MDELEM_ETAG_EMPTY (get_static_metadata_payload()[33])
/* "expect": "" */
#define HPACK_MDELEM_EXPECT_EMPTY (get_static_metadata_payload()[34])
/* "expires": "" */
#define HPACK_MDELEM_EXPIRES_EMPTY (get_static_metadata_payload()[35])
/* "from": "" */
#define HPACK_MDELEM_FROM_EMPTY (get_static_metadata_payload()[36])
/* "host": "" */
#define HPACK_MDELEM_HOST_EMPTY (get_static_metadata_payload()[37])
/* "if-match": "" */
#define HPACK_MDELEM_IF_MATCH_EMPTY (get_static_metadata_payload()[38])
/* "if-modified-since": "" */
#define HPACK_MDELEM_IF_MODIFIED_SINCE_EMPTY \
  (get_static_metadata_payload()[39])
/* "if-none-match": "" */
#define HPACK_MDELEM_IF_NONE_MATCH_EMPTY (get_static_metadata_payload()[40])
/* "if-range": "" */
#define HPACK_MDELEM_IF_RANGE_EMPTY (get_static_metadata_payload()[41])
/* "if-unmodified-since": "" */
#define HPACK_MDELEM_IF_UNMODIFIED_SINCE_EMPTY \
  (get_static_metadata_payload()[42])
/* "last-modified": "" */
#define HPACK_MDELEM_LAST_MODIFIED_EMPTY (get_static_metadata_payload()[43])
/* "link": "" */
#define HPACK_MDELEM_LINK_EMPTY (get_static_metadata_payload()[44])
/* "location": "" */
#define HPACK_MDELEM_LOCATION_EMPTY (get_static_metadata_payload()[45])
/* "max-forwards": "" */
#define HPACK_MDELEM_MAX_FORWARDS_EMPTY (get_static_metadata_payload()[46])
/* "proxy-authenticate": "" */
#define HPACK_MDELEM_PROXY_AUTHENTICATE_EMPTY \
  (get_static_metadata_payload()[47])
/* "proxy-authorization": "" */
#define HPACK_MDELEM_PROXY_AUTHORIZATION_EMPTY \
  (get_static_metadata_payload()[48])
/* "range": "" */
#define HPACK_MDELEM_RANGE_EMPTY (get_static_metadata_payload()[49])
/* "referer": "" */
#define HPACK_MDELEM_REFERER_EMPTY (get_static_metadata_payload()[50])
/* "refresh": "" */
#define HPACK_MDELEM_REFRESH_EMPTY (get_static_metadata_payload()[51])
/* "retry-after": "" */
#define HPACK_MDELEM_RETRY_AFTER_EMPTY (get_static_metadata_payload()[52])
/* "server": "" */
#define HPACK_MDELEM_SERVER_EMPTY (get_static_metadata_payload()[53])
/* "set-cookie": "" */
#define HPACK_MDELEM_SET_COOKIE_EMPTY (get_static_metadata_payload()[54])
/* "strict-transport-security": "" */
#define HPACK_MDELEM_STRICT_TRANSPORT_SECURITY_EMPTY \
  (get_static_metadata_payload()[55])
/* "transfer-encoding": "" */
#define HPACK_MDELEM_TRANSFER_ENCODING_EMPTY \
  (get_static_metadata_payload()[56])
/* "user-agent": "" */
#define HPACK_MDELEM_USER_AGENT_EMPTY (get_static_metadata_payload()[57])
/* "vary": "" */
#define HPACK_MDELEM_VARY_EMPTY (get_static_metadata_payload()[58])
/* "via": "" */
#define HPACK_MDELEM_VIA_EMPTY (get_static_metadata_payload()[59])
/* "www-authenticate": "" */
#define HPACK_MDELEM_WWW_AUTHENTICATE_EMPTY (get_static_metadata_payload()[60])
/* "grpc-status": "0" */
#define HPACK_MDELEM_GRPC_STATUS_0 (get_static_metadata_payload()[61])
/* "grpc-status": "1" */
#define HPACK_MDELEM_GRPC_STATUS_1 (get_static_metadata_payload()[62])
/* "grpc-status": "2" */
#define HPACK_MDELEM_GRPC_STATUS_2 (get_static_metadata_payload()[63])
/* "grpc-encoding": "identity" */
#define HPACK_MDELEM_GRPC_ENCODING_IDENTITY (get_static_metadata_payload()[64])
/* "grpc-encoding": "gzip" */
#define HPACK_MDELEM_GRPC_ENCODING_GZIP (get_static_metadata_payload()[65])
/* "grpc-encoding": "deflate" */
#define HPACK_MDELEM_GRPC_ENCODING_DEFLATE (get_static_metadata_payload()[66])
/* "te": "trailers" */
#define HPACK_MDELEM_TE_TRAILERS (get_static_metadata_payload()[67])
/* "content-type": "application/grpc" */
#define HPACK_MDELEM_CONTENT_TYPE_APPLICATION_SLASH_GRPC \
  (get_static_metadata_payload()[68])
/* ":scheme": "grpc" */
#define HPACK_MDELEM_SCHEME_GRPC (get_static_metadata_payload()[69])
/* ":method": "PUT" */
#define HPACK_MDELEM_METHOD_PUT (get_static_metadata_payload()[70])
/* "accept-encoding": "" */
#define HPACK_MDELEM_ACCEPT_ENCODING_EMPTY (get_static_metadata_payload()[71])
/* "content-encoding": "identity" */
#define HPACK_MDELEM_CONTENT_ENCODING_IDENTITY \
  (get_static_metadata_payload()[72])
/* "content-encoding": "gzip" */
#define HPACK_MDELEM_CONTENT_ENCODING_GZIP (get_static_metadata_payload()[73])
/* "lb-cost-bin": "" */
#define HPACK_MDELEM_LB_COST_BIN_EMPTY (get_static_metadata_payload()[74])
/* "grpc-accept-encoding": "identity" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY \
  (get_static_metadata_payload()[75])
/* "grpc-accept-encoding": "deflate" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE \
  (get_static_metadata_payload()[76])
/* "grpc-accept-encoding": "identity,deflate" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE \
  (get_static_metadata_payload()[77])
/* "grpc-accept-encoding": "gzip" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_GZIP \
  (get_static_metadata_payload()[78])
/* "grpc-accept-encoding": "identity,gzip" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP \
  (get_static_metadata_payload()[79])
/* "grpc-accept-encoding": "deflate,gzip" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_DEFLATE_COMMA_GZIP \
  (get_static_metadata_payload()[80])
/* "grpc-accept-encoding": "identity,deflate,gzip" */
#define HPACK_MDELEM_GRPC_ACCEPT_ENCODING_IDENTITY_COMMA_DEFLATE_COMMA_GZIP \
  (get_static_metadata_payload()[81])
/* "accept-encoding": "identity" */
#define HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY \
  (get_static_metadata_payload()[82])
/* "accept-encoding": "gzip" */
#define HPACK_MDELEM_ACCEPT_ENCODING_GZIP (get_static_metadata_payload()[83])
/* "accept-encoding": "identity,gzip" */
#define HPACK_MDELEM_ACCEPT_ENCODING_IDENTITY_COMMA_GZIP \
  (get_static_metadata_payload()[84])
