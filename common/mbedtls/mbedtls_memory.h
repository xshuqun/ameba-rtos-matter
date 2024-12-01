/********************************************************************************
 * @file    mbedtls_memory.h
 * @author
 * @version
 * @brief  mbedtls memory allocation
 ********************************************************************************
 * @attention
 *
 * This module is a confidential and proprietary property of RealTek and
 * possession or use of this module requires written permission of RealTek.
 *
 * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
********************************************************************************/

#ifndef __MBEDTLS_MEMORY_H__
#define __MBEDTLS_MEMORY_H__

/*
 * @brief  This module defines a custom memory allocation function for mbed TLS.
 */
void* app_mbedtls_calloc_func(size_t nelements, size_t elementSize);

#endif /* __MBEDTLS_MEMORY_H__ */
