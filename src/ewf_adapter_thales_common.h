/************************************************************************//**
 * @file
 * @version Preview
 * @copyright Copyright (c) Microsoft Corporation. All rights reserved.
 * SPDX-License-Identifier: MIT
 * @brief The Embedded Wireless Framework generic Thales adapter functionality
 ****************************************************************************/

#ifndef __ewf_adapter_thales_common__h__included__
#define __ewf_adapter_thales_common__h__included__

#include "ewf_adapter.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************//**
 * @defgroup group_configuration_adapter_thales_common Thales common configuration
 * @ingroup group_configuration
 * @brief Thales common adapter configuration
 * @{
 ****************************************************************************/

#ifndef EWF_ADAPTER_THALES_COMMON_DEFAULT_TIMEOUT
#define EWF_ADAPTER_THALES_COMMON_DEFAULT_TIMEOUT (EWF_PLATFORM_TICKS_PER_SECOND * 10)
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_FFS_ENABLED
#define EWF_ADAPTER_THALES_COMMON_FFS_ENABLED (1)
#endif

#if !defined(EWF_ADAPTER_THALES_COMMON_TLS_ENABLED) && !defined(EWF_ADAPTER_THALES_COMMON_TLS_BASIC_ENABLED)
#if 1
#define EWF_ADAPTER_THALES_COMMON_TLS_BASIC_ENABLED (1)
#define EWF_ADAPTER_THALES_COMMON_TLS_ENABLED (0)
#else
#define EWF_ADAPTER_THALES_COMMON_TLS_BASIC_ENABLED (0)
#define EWF_ADAPTER_THALES_COMMON_TLS_ENABLED (1)
#endif
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_TCP_ENABLED
#define EWF_ADAPTER_THALES_COMMON_TCP_ENABLED (1)
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_UDP_ENABLED
#define EWF_ADAPTER_THALES_COMMON_UDP_ENABLED (1)
#endif

#if !defined(EWF_ADAPTER_THALES_COMMON_MQTT_ENABLED) && !defined(EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED)
#if 1
#define EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED (1)
#define EWF_ADAPTER_THALES_COMMON_MQTT_ENABLED (0)
#else
#define EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED (0)
#define EWF_ADAPTER_THALES_COMMON_MQTT_ENABLED (1)
#endif
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_INTERNET_SOCKET_POOL_SIZE
/** @brief The total number of supported internet sockets in the adapter */
#define EWF_ADAPTER_THALES_COMMON_INTERNET_SOCKET_POOL_SIZE (10)
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_INTERNET_SOCKET_INVALID
/** @brief The internet socket invalid value */
#define EWF_ADAPTER_THALES_COMMON_INTERNET_SOCKET_INVALID (-1)
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_MQTT_SOCKET_POOL_SIZE
/** @brief The total number of supported MQTT sockets in the adapter */
#define EWF_ADAPTER_THALES_COMMON_MQTT_SOCKET_POOL_SIZE (10)
#endif

#ifndef EWF_ADAPTER_THALES_COMMON_MQTT_SOCKET_INVALID
/** @brief The MQTT socket invalid value */
#define EWF_ADAPTER_THALES_COMMON_MQTT_SOCKET_INVALID (-1)
#endif

/************************************************************************//**
 * @} *** group_configuration_adapter_thales_common
 ****************************************************************************/

/************************************************************************//**
 * @defgroup group_adapter_thales_common Thales common driver implementation
 * @ingroup group_adapter
 * @brief Thales common adapter implementation
 * @{
 ****************************************************************************/

/************************************************************************//**
 * @defgroup group_adapter_thales_common_tokenizer Thales common driver tokenizer
 * @brief Thales common adapter tokenizer
 * @{
 ****************************************************************************/

extern ewf_interface_tokenizer_pattern* ewf_adapter_thales_common_message_tokenizer_pattern_ptr;
extern ewf_interface_tokenizer_pattern* ewf_adapter_thales_common_command_response_end_tokenizer_pattern_ptr;
static ewf_interface_tokenizer_pattern* ewf_adapter_thales_common_command_response_tokenizer_pattern_ptr;
extern ewf_interface_tokenizer_pattern* ewf_adapter_thales_common_urc_tokenizer_pattern_ptr;

/************************************************************************//**
 * @} *** group_adapter_thales_common_tokenizer
 ****************************************************************************/

/************************************************************************//**
 * @defgroup group_adapter_thales_common_data Thales common driver internal data
 * @brief Thales common adapter data structure
 * @{
 ****************************************************************************/

/** @brief The socket service type  */
typedef enum _ewf_adapter_common_internet_socket_service_type
{
    ewf_adapter_thales_common_internet_socket_service_type_not_initialized,
    ewf_adapter_thales_common_internet_socket_service_type_tcp,
    ewf_adapter_thales_common_internet_socket_service_type_udp,
    ewf_adapter_thales_common_internet_socket_service_type_tcp_listener,
    ewf_adapter_thales_common_internet_socket_service_type_udp_listener,
    ewf_adapter_thales_common_internet_socket_service_type_ftp,
    ewf_adapter_thales_common_internet_socket_service_type_http,
    ewf_adapter_thales_common_internet_socket_service_type_mqtt,

} ewf_adapter_thales_common_internet_socket_service_type;

/** @brief Internal structure for internet socket status  */
typedef struct _ewf_adapter_thales_common_internet_socket
{
    void* socket_ptr;
    uint32_t id;
    uint16_t local_port;
    ewf_adapter_thales_common_internet_socket_service_type type;
    volatile bool used : 1;
    volatile bool open : 1;
    volatile bool open_error : 1;
    volatile bool conn : 1;
    volatile bool conn_error : 1;
    volatile int16_t cnfWriteLength;
    volatile int16_t cnfReadLength;

} ewf_adapter_thales_common_internet_socket;

/** @brief The Thales common adapter data structure */
typedef struct _ewf_adapter_thales_common
{
    uint32_t default_timeout;

#if EWF_ADAPTER_THALES_COMMON_TCP_ENABLED || EWF_ADAPTER_THALES_COMMON_UDP_ENABLED || EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED || EWF_ADAPTER_THALES_COMMON_MQTT_ENABLED
    /**< The internal pool of internet sockets */
    ewf_adapter_thales_common_internet_socket internet_socket_pool[EWF_ADAPTER_THALES_COMMON_INTERNET_SOCKET_POOL_SIZE];
#endif

} ewf_adapter_thales_common;

/************************************************************************//**
 * @} *** group_adapter_thales_common_data
 ****************************************************************************/

/************************************************************************//**
 * @defgroup group_adapter_thales_common_functions Thales generic adapter functions
 * @brief Thales generic adapter functions
 * @{
 ****************************************************************************/

/**
 * @defgroup group_adapter_thales_common_context Context activation, deactivation and configuration
 * @brief Thales common adapter driver context API
 * @{
 */

/**
  * @brief Activate a context
  * @return #ewf_result success and error conditions
  */
ewf_result ewf_adapter_thales_common_context_activate(ewf_adapter* adapter_ptr, uint32_t ctx);

/**
 * @brief Deactivate a context
 * @return #ewf_result success and error conditions
 */
ewf_result ewf_adapter_thales_common_context_deactivate(ewf_adapter* adapter_ptr, uint32_t ctx);

/**
 * @brief Configure a context
 * @return #ewf_result success and error conditions
 */
ewf_result ewf_adapter_thales_common_context_configure(ewf_adapter* adapter_ptr, uint32_t ctx, uint32_t type, const char* apn, const char* username, const char* password, uint32_t authentication);

/**
 * @brief Configure a context DNS
 * @return #ewf_result success and error conditions
 */
ewf_result ewf_adapter_thales_common_context_configure_dns(ewf_adapter* adapter_ptr, uint32_t ctx, const char* primary_dns, const char* secondary_dns);

/** @} *** group_adapter_thales_common_context */

/**
 * @defgroup group_adapter_thales_common_ufs User File System (FFS) API
 * @brief Functions to use the modem's User File System (FFS)
 * @{
 */

ewf_result ewf_adapter_thales_common_ufs_start(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_ufs_stop(ewf_adapter* adapter_ptr);

ewf_result ewf_adapter_thales_common_ufs_urc_callback(ewf_interface* interface_ptr, uint8_t* buffer_ptr, uint32_t buffer_length);

 /**
  * @brief List the files in the user file system
  * @return #ewf_result status code
  */
ewf_result ewf_adapter_thales_common_ufs_list(ewf_adapter* adapter_ptr);

/**
 * @brief Delete a file from the user file system
 * @param filename_str the file name of the file to be deleted.
 * @return #ewf_result status code
 */
ewf_result ewf_adapter_thales_common_ufs_delete(ewf_adapter* adapter_ptr, const char* filename_str);

/**
 * @brief Upload a file to the user file system.
 * @param filename_str the file name where the data will be uploaded.
 * @param buffer_ptr a pointer to a buffer with data to upload to the file system.
 * @param buffer_length the size of the data pointed by the buffer.
 * @return #ewf_result status code
 */
ewf_result ewf_adapter_thales_common_ufs_upload(ewf_adapter* adapter_ptr, const char* filename_str, const uint8_t* buffer_ptr, uint32_t buffer_length);

/** @} *** group_adapter_thales_common_ufs */

/**
 * @defgroup group_adapter_thales_common_control Adapter control
 * @brief Thales common adapter control API
 * @{
 */

extern ewf_adapter_api_control ewf_adapter_thales_common_api_control;

ewf_result ewf_adapter_thales_common_start(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_stop(ewf_adapter* adapter_ptr);

/** @} *** group_adapter_thales_common_control */

/**
 * @defgroup group_adapter_thales_common_info Adapter information
 * @brief Thales common adapter driver info API
 * @{
 */

extern ewf_adapter_api_info ewf_adapter_thales_common_api_info;

ewf_result ewf_adapter_thales_common_info(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_get_ipv4_address(ewf_adapter* adapter_ptr, uint32_t* address_ptr);
ewf_result ewf_adapter_thales_common_get_ipv4_netmask(ewf_adapter* adapter_ptr, uint32_t* netmask_ptr);
ewf_result ewf_adapter_thales_common_get_ipv4_gateway(ewf_adapter* adapter_ptr, uint32_t* gateway_ptr);
ewf_result ewf_adapter_thales_common_get_ipv4_dns(ewf_adapter* adapter_ptr, uint32_t* dns);

/** @} *** group_adapter_thales_common_info */

/**
 * @defgroup group_adapter_thales_common_urc URC handling
 * @brief Thales common adapter driver URC handling
 * @{
 */

ewf_result ewf_adapter_thales_common_urc_callback(ewf_interface* interface_ptr, uint8_t* buffer_ptr, uint32_t buffer_length);

/** @} *** group_adapter_thales_common_urc */

/**
 * @defgroup group_adapter_thales_common_internet Common internet functions (TCP+UDP)
 * @brief Functions common to TCP and UDP in the Thales common internet implementation
 * @{
 */

#if EWF_ADAPTER_THALES_COMMON_TCP_ENABLED || EWF_ADAPTER_THALES_COMMON_UDP_ENABLED

ewf_result ewf_adapter_thales_common_internet_start(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_internet_stop(ewf_adapter* adapter_ptr);

ewf_result ewf_adapter_thales_common_internet_urc_callback(ewf_interface* interface_ptr, uint8_t* buffer_ptr, uint32_t buffer_length);

#endif /* EWF_ADAPTER_THALES_COMMON_TCP_ENABLED || EWF_ADAPTER_THALES_COMMON_UDP_ENABLED */

/** @} *** group_adapter_thales_common_internet */

/**
 * @defgroup group_adapter_thales_common_tcp TCP API implementation
 * @brief Thales common adapter TCP API
 * @{
 */

#if EWF_ADAPTER_THALES_COMMON_TCP_ENABLED

extern ewf_adapter_api_tcp ewf_adapter_thales_common_api_tcp;

ewf_result ewf_adapter_thales_common_tcp_open(ewf_adapter* adapter_ptr, ewf_socket_tcp* socket_ptr);
ewf_result ewf_adapter_thales_common_tcp_close(ewf_socket_tcp* socket_ptr);
ewf_result ewf_adapter_thales_common_tcp_control(ewf_socket_tcp* socket_ptr, const char* control_str, const uint8_t* buffer_ptr, uint32_t* buffer_length_ptr);
ewf_result ewf_adapter_thales_common_tcp_set_tls_configuration(ewf_socket_tcp* socket_ptr, uint32_t tls_configuration_id);
ewf_result ewf_adapter_thales_common_tcp_bind(ewf_socket_tcp* socket_ptr, uint32_t local_port);
ewf_result ewf_adapter_thales_common_tcp_listen(ewf_socket_tcp* socket_ptr);
ewf_result ewf_adapter_thales_common_tcp_accept(ewf_socket_tcp* socket_ptr, ewf_socket_tcp* socket_new_ptr);
ewf_result ewf_adapter_thales_common_tcp_connect(ewf_socket_tcp* socket_ptr, const char* const server, uint32_t port);
ewf_result ewf_adapter_thales_common_tcp_shutdown(ewf_socket_tcp* socket_ptr);
ewf_result ewf_adapter_thales_common_tcp_send(ewf_socket_tcp* socket_ptr, const uint8_t* buffer_ptr, uint32_t buffer_length);
ewf_result ewf_adapter_thales_common_tcp_receive(ewf_socket_tcp* socket_ptr, uint8_t* buffer_ptr, uint32_t* buffer_length, bool wait);

#endif /* EWF_ADAPTER_THALES_COMMON_TCP_ENABLED */

/** @} *** group_adapter_thales_common_tcp */

/**
 * @defgroup group_adapter_thales_common_udp UDP API implementation
 * @brief Thales common adapter UDP API
 * @{
 */

#if EWF_ADAPTER_THALES_COMMON_UDP_ENABLED

extern ewf_adapter_api_udp ewf_adapter_thales_common_api_udp;

ewf_result ewf_adapter_thales_common_udp_open(ewf_adapter* adapter_ptr, ewf_socket_udp* socket_ptr);
ewf_result ewf_adapter_thales_common_udp_close(ewf_socket_udp* socket_ptr);
ewf_result ewf_adapter_thales_common_udp_control(ewf_socket_udp* socket_ptr, const char* control_str, const uint8_t* buffer_ptr, uint32_t* buffer_length_ptr);
ewf_result ewf_adapter_thales_common_udp_set_dtls_configuration(ewf_socket_udp* socket_ptr, uint32_t dtls_configuration_id);
ewf_result ewf_adapter_thales_common_udp_bind(ewf_socket_udp* socket_ptr, uint32_t port);
ewf_result ewf_adapter_thales_common_udp_shutdown(ewf_socket_udp* socket_ptr);
ewf_result ewf_adapter_thales_common_udp_send_to(ewf_socket_udp* socket_ptr, const char* remote_address_str, uint32_t remote_port, const uint8_t* buffer_ptr, uint32_t buffer_length);
ewf_result ewf_adapter_thales_common_udp_receive_from(ewf_socket_udp* socket_ptr, char* remote_address, uint32_t* remote_address_length_ptr, uint32_t* remote_port_ptr, uint8_t* buffer_ptr, uint32_t* buffer_length_ptr, bool wait);

#endif /* EWF_ADAPTER_THALES_COMMON_UDP_ENABLED */

/** @} *** group_adapter_thales_common_udp */

/**
 * @defgroup group_adapter_thales_common_tls_basic The Thales common adapter TLS basic API
 * @brief The Thales common adapter TLS basic API
 * @{
 */

#if EWF_ADAPTER_THALES_COMMON_TLS_BASIC_ENABLED

extern ewf_adapter_api_tls_basic ewf_adapter_thales_common_api_tls_basic;

ewf_result ewf_adapter_thales_common_tls_basic_start(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_tls_basic_stop(ewf_adapter* adapter_ptr);

ewf_result ewf_adapter_thales_common_tls_basic_urc_callback(ewf_interface* interface_ptr, uint8_t* buffer_ptr, uint32_t buffer_length);

ewf_result ewf_adapter_thales_common_tls_basic_init(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_tls_basic_clean(ewf_adapter* adapter_ptr);

#endif /* EWF_ADAPTER_THALES_COMMON_TLS_BASIC_ENABLED */

/** @} *** group_adapter_thales_common_tls_basic */

/**
 * @defgroup group_adapter_thales_common_mqtt_basic MQTT basic API implementation
 * @brief Thales common adapter MQTT basic API
 * @{
 */

#if EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED

extern ewf_adapter_api_mqtt_basic ewf_adapter_thales_common_api_mqtt_basic;

ewf_result ewf_adapter_thales_common_mqtt_basic_start(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_mqtt_basic_stop(ewf_adapter* adapter_ptr);

ewf_result ewf_adapter_thales_common_mqtt_basic_urc_callback(ewf_interface* interface_ptr, uint8_t* buffer_ptr, uint32_t buffer_length);

ewf_result ewf_adapter_thales_common_mqtt_basic_default_state_callback(ewf_adapter* adapter_ptr, const char* state_cstr, const char* param_cstr);
ewf_result ewf_adapter_thales_common_mqtt_basic_default_message_callback(ewf_adapter* adapter_ptr, const char* topic_cstr, const char* payload_cstr);

ewf_result ewf_adapter_thales_common_mqtt_basic_connect(ewf_adapter* adapter_ptr, char const* server_str, uint32_t port, char const* clientid, char const* username, char const* password);
ewf_result ewf_adapter_thales_common_mqtt_basic_disconnect(ewf_adapter* adapter_ptr);
ewf_result ewf_adapter_thales_common_mqtt_basic_subscribe(ewf_adapter* adapter_ptr, char const* topic);
ewf_result ewf_adapter_thales_common_mqtt_basic_unsubscribe(ewf_adapter* adapter_ptr, char const* topic);
ewf_result ewf_adapter_thales_common_mqtt_basic_publish(ewf_adapter* adapter_ptr, const char* topic, const char* msg_cstr);

#endif /* EWF_ADAPTER_THALES_COMMON_MQTT_BASIC_ENABLED */

/** @} *** group_adapter_thales_common_mqtt_basic */

/************************************************************************//**
 * @} *** group_adapter_thales_common_functions
 ****************************************************************************/

/************************************************************************//**
 * @} *** group_adapter_thales_common
 ****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __ewf_adapter_thales_common__h__included__ */
