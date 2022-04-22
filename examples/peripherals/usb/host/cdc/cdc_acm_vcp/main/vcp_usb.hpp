/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include "usb/cdc_acm_host.h"

namespace esp_usb {
/**
 * @brief VcpUsb interface class
 *
 * This is a pure virtual class implementing interface design pattern.
 */
class VcpUsb {
  public:
    virtual ~VcpUsb() = default; // Virtual desctructor. To destroy underlying device.
    // Following functions must be implemented by derived classes
    template <class T>
    static T* open(uint16_t pid, const cdc_acm_host_device_config_t *dev_config, uint8_t interface_idx = 0)
    {
       return T::open(pid, dev_config, interface_idx);
    }
    template <class T>
    static T* open(const cdc_acm_host_device_config_t *dev_config, uint8_t interface_idx = 0)
    {
       return T::open(dev_config, interface_idx);
    }
    virtual esp_err_t tx_blocking(uint8_t *data, size_t len, uint32_t timeout_ms = 100) = 0;
    virtual esp_err_t close() = 0;

    // Following functions are optional
    virtual esp_err_t line_coding_get(cdc_acm_line_coding_t *line_coding) { return ESP_ERR_NOT_SUPPORTED;}
    virtual esp_err_t line_coding_set(cdc_acm_line_coding_t *line_coding) { return ESP_ERR_NOT_SUPPORTED;}
    virtual esp_err_t set_control_line_state(bool dtr, bool rts) { return ESP_ERR_NOT_SUPPORTED;}
    virtual esp_err_t send_break(uint16_t duration_ms) { return ESP_ERR_NOT_SUPPORTED;}
};


} // namespace esp_usb
