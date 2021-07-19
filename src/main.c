#include <esp_log.h>
#include <libesp.h>
#include <libiot.h>

#include "secret.h"

#define DEVICE_NAME "dev"

static const char* TAG = "app";

static void mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED: {
            // Note: libiot automatically subscribes to the `IOT_MQTT_DEVICE_TOPIC()` namespace,
            // but anything outside of that must be explicitly subscribed here.
            assert(esp_mqtt_client_subscribe(client, IOT_MQTT_COMMAND_TOPIC("example"), 1) >= 0);
            break;
        }
        case MQTT_EVENT_DATA: {
            // Handle inbound MQTT messages here

            break;
        }
        default: {
            break;
        }
    }
}

void app_run() {
    ESP_LOGI(TAG, "running!");

    // App code goes here
}

void app_main() {
    struct node_config config = {
        .name = DEVICE_NAME,
        .ssid = SECRET_WIFI_SSID,
        .pass = SECRET_WIFI_PASS,
        .ps_type = WIFI_PS_NONE,

        .uri = "mqtts://storagebox.local",
        .cert = SECRET_MQTT_CERT,
        .key = SECRET_MQTT_KEY,
        .mqtt_pass = SECRET_MQTT_PASS,
        .mqtt_cb = &mqtt_event_handler_cb,

        .app_run = &app_run,
    };

    libiot_startup(&config);
}
