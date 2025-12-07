#include "BluetoothManager.h"
#include <cstring>
static const char* TAG = "BTManager";

// Constructor
BluetoothManager::BluetoothManager(const char* deviceName)
    : m_deviceName(deviceName) {}

// Register callback
void BluetoothManager::onData(void (*callback)(const char* data)) {
    m_userCallback = callback;
}

bool BluetoothManager::init() {
    esp_err_t ret;

    // Enable Bluetooth
    ret = esp_bt_controller_mem_release(ESP_BT_MODE_BLE);
    if (ret) ESP_LOGW(TAG, "BLE memory release failed");

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    ESP_ERROR_CHECK(ret);

    ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    ESP_ERROR_CHECK(ret);

    // Init Bluedroid
    ret = esp_bluedroid_init();
    ESP_ERROR_CHECK(ret);
    ret = esp_bluedroid_enable();
    ESP_ERROR_CHECK(ret);

    // Register SPP callback
    esp_spp_register_callback(BluetoothManager::sppCallback);
    esp_spp_init(ESP_SPP_MODE_CB);

    ESP_LOGI(TAG, "Bluetooth SPP initialized");
    return true;
}

void BluetoothManager::sppCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t* param) 
{
    switch (event) 
    {
        case ESP_SPP_START_EVT:
            ESP_LOGI(TAG, "SPP server started");
            break;

        case ESP_SPP_SRV_OPEN_EVT:
            ESP_LOGI(TAG, "Client connected");
            m_sppHandle = param->srv_open.handle;
            break;

        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(TAG, "Client disconnected");
            m_sppHandle = 0;
            break;

        case ESP_SPP_DATA_IND_EVT:
            ESP_LOGI(TAG, "Received data: %.*s", param->data_ind.len, param->data_ind.data);

            if (m_userCallback)
                m_userCallback((const char*)param->data_ind.data);
            break;

        default:
            break;
    }
}

void BluetoothManager::sendMessage(const char* msg) 
{
    if (m_sppHandle != 0) {
        esp_spp_write(m_sppHandle, strlen(msg), (uint8_t*)msg);
    } else {
        ESP_LOGW(TAG, "No Bluetooth client connected");
    }
}
